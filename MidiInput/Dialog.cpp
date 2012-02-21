/**
 * Dialog.cpp
 * Copyright © 2012 kbinani
 *
 * This file is part of `MIDIInput UG Job Plugin'.
 *
 * `MIDIInput UG Job Plugin' is free software; you can redistribute it and/or
 * modify it under the terms of the BSD License.
 *
 * `MIDIInput UG Job Plugin' is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 */
#include <sstream>
#include <QKeyEvent>
#include <QString>
#include <QStringList>
#include "MidiInput.h"
#include "Dialog.h"
#include "Pianoroll.h"
#include "Parser.h"
#include "Robot.h"
#include "ui_Dialog.h"

using namespace std;
using namespace VSQ_NS;

Dialog::Dialog( const string eventText, const string timesigText, tick_t musicalPartOffset, QWidget *parent ) :
    QDialog( parent ),
    ui( new Ui::Dialog )
{
    ui->setupUi( this );

    stepUnit = 480;
    isRest = false;
    ui->toolButtonNote004->toggle();
    inputStarted = false;
    autoScroll = true;
    this->musicalPartOffset = musicalPartOffset;

    ui->pushButtonInputToggle->setEnabled( false );
    ui->comboBox->clear();
    ui->comboBox->setEnabled( false );

    this->setWindowFlags( Qt::Window );

    int count = MidiInput::getDeviceCount();
    for( int i = 0; i < count; i++ ){
        QString name = MidiInput::getDeviceName( i );
        ui->comboBox->addItem( name );
    }
    if( ui->comboBox->count() > 0 ){
        ui->comboBox->setEnabled( true );
        ui->pushButtonInputToggle->setEnabled( true );
    }

    mutex = new QMutex();
    Parser parser;
    timesigList = parser.getTimesig( timesigText );
    items = parser.getEvent( eventText );
    ui->pianoroll->setTimesigList( timesigList );
    ui->pianoroll->setItems( items );
    ui->pianoroll->setMutex( mutex );
    ui->pianoroll->setMusicalPartOffset( this->musicalPartOffset );

    connect( this, SIGNAL(doRepaint()), SLOT(onRepaintRequired()) );

    Robot::disablePluginCancelButton();

    tick_t songPosition = getSongPosition( timesigList, this->musicalPartOffset );
    ui->pianoroll->setSongPosition( songPosition, false );
}

Dialog::~Dialog()
{
    inputStopRequired();
    delete ui;
    delete timesigList;
    for( map<tick_t, PianorollItem *>::iterator i = items->begin(); i != items->end(); i++ ){
        PianorollItem *item = i->second;
        if( item ){
            delete item;
        }
    }
    items->clear();
    delete items;
    delete mutex;
}

void Dialog::on_pushButtonInputToggle_clicked()
{
    if( inputStarted ){
        ui->pushButtonInputToggle->setText( tr( "Start" ) );
        inputStopRequired();
    }else{
        ui->pushButtonInputToggle->setText( tr( "Stop" ) );
        int channel = ui->comboBox->currentIndex();
        if( 0 <= channel && channel < MidiInput::getDeviceCount() ){
            inputStartRequired( channel );
        }
    }
    inputStarted = !inputStarted;
    ui->comboBox->setEnabled( !inputStarted );
}

void Dialog::keyPressEvent( QKeyEvent *e )
{
    int key = e->key();
    int delta = (key == Qt::Key_Left ? -1 : (key == Qt::Key_Right ? 1 : 0));
    if( delta ){
        tick_t songPosition = ui->pianoroll->getSongPosition();
        tick_t newSongPosition = songPosition + delta * stepUnit;
        if( newSongPosition < 0 ){
            newSongPosition = 0;
        }
        if( newSongPosition != songPosition ){
            ui->pianoroll->setSongPosition( newSongPosition, autoScroll );
            ui->pianoroll->repaint();
        }
    }
}

void Dialog::on_toolButtonNote001_toggled( bool checked )
{
    if( checked ){
        stepUnit = 1920;
        isRest = false;
    }
}

void Dialog::on_toolButtonNote002_toggled(bool checked)
{
    if( checked ){
        stepUnit = 960;
        isRest = false;
    }
}

void Dialog::on_toolButtonNote004_toggled(bool checked)
{
    if( checked ){
        stepUnit = 480;
        isRest = false;
    }
}

void Dialog::on_toolButtonNote008_toggled(bool checked)
{
    if( checked ){
        stepUnit = 240;
        isRest = false;
    }
}

void Dialog::on_toolButtonNote016_toggled(bool checked)
{
    if( checked ){
        stepUnit = 120;
        isRest = false;
    }
}

void Dialog::on_toolButtonRest001_toggled(bool checked)
{
    if( checked ){
        stepUnit = 1920;
        isRest = true;
    }
}

void Dialog::on_toolButtonRest002_toggled(bool checked)
{
    if( checked ){
        stepUnit = 960;
        isRest = true;
    }
}

void Dialog::on_toolButtonRest004_toggled(bool checked)
{
    if( checked ){
        stepUnit = 480;
        isRest = true;
    }
}

void Dialog::on_toolButtonRest008_toggled(bool checked)
{
    if( checked ){
        stepUnit = 240;
        isRest = true;
    }
}

void Dialog::on_toolButtonRest016_toggled(bool checked)
{
    if( checked ){
        stepUnit = 120;
        isRest = true;
    }
}

void Dialog::inputStartRequired( int channel )
{
    this->channel = channel;
    MidiInput::setReceiver( this );
    MidiInput::start( this->channel );
}

void Dialog::inputStopRequired()
{
    MidiInput::stop();
    MidiInput::setReceiver( NULL );
}

void Dialog::send( unsigned char b1, unsigned char b2, unsigned char b3 )
{
    int command = (b1 & 0xF0);
    if( command == 0x90 && b3 != 0 ){
        tick_t length = stepUnit;
        tick_t position = ui->pianoroll->getSongPosition();
        int noteNumber = b2;

        mutex->lock();
        map<tick_t, PianorollItem *>::iterator i = items->find( position );
        if( isRest ){
            if( i != items->end() ){
                PianorollItem *item = i->second;
                items->erase( i );
                delete item;
            }
        }else{
            PianorollItem *add = new PianorollItem();
            add->length = length;
            add->noteNumber = noteNumber;
            add->phrase = "\xE3\x81\x82";
            add->symbols = "a";

            if( i != items->end() ){
                PianorollItem *item = i->second;
                items->erase( i );
                delete item;
            }

            items->insert( make_pair( position, add ) );
        }
        mutex->unlock();

        if( !isRest ){
            ui->pianoroll->ensureNoteVisible( position, length, noteNumber );
        }
        ui->pianoroll->setSongPosition( position + length, isRest );
        emit doRepaint();
    }
}

void Dialog::onRepaintRequired()
{
    ui->pianoroll->repaint();
}

const string Dialog::getEventText()
{
    Parser parser;
    return parser.toString( items );
}

tick_t Dialog::getSongPosition( TimesigList *timesigList, tick_t musicalPartOffset )
{
    QString songPositionString = QString::fromStdString( Robot::getSongPosition() );
    QStringList parameters = songPositionString.split( " : " );
    if( 3 <= parameters.size() ){
        int preMeasure = Robot::getPreMeasure();
        int barCount = parameters[0].toInt() + (preMeasure - 1);
        int beat = parameters[1].toInt();
        int tick = parameters[2].toInt();

        int localTickAtBar = timesigList->getClockFromBarCount( barCount );
        Timesig timesig = timesigList->getTimesigAt( localTickAtBar );
        int tickPerBeat = 480 * 4 / timesig.denominator;
        tick_t songPosition = localTickAtBar - musicalPartOffset;
        songPosition += (beat - 1) * tickPerBeat;
        songPosition += tick;
        return songPosition;
    }else{
        return 0;
    }
}
