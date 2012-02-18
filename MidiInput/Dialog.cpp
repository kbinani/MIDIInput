#include <sstream>
#include <QKeyEvent>
#include "MidiInput.h"
#include "Dialog.h"
#include "Pianoroll.h"
#include "ui_Dialog.h"

using namespace std;
using namespace VSQ_NS;

Dialog::Dialog( QWidget *parent ) :
    QDialog( parent ),
    ui( new Ui::Dialog )
{
    ui->setupUi( this );

    stepUnit = 480;
    isRest = false;
    ui->toolButtonNote004->toggle();
    inputStarted = false;

    ui->pushButtonInputToggle->setEnabled( false );
    ui->comboBox->clear();
    ui->comboBox->setEnabled( false );

    this->setWindowFlags( Qt::Window );

    int count = MidiInput::getDeviceCount();
    for( int i = 0; i < count; i++ ){
        string name = MidiInput::getDeviceName( i );
        ui->comboBox->addItem( QString::fromStdString( name ) );
    }
    if( ui->comboBox->count() > 0 ){
        ui->comboBox->setEnabled( true );
        ui->pushButtonInputToggle->setEnabled( true );
    }

    timesigList = new TimesigList();
    timesigList->push( Timesig( 4, 4, 0 ) );
    ui->pianoroll->setTimesigList( timesigList );
    ui->pianoroll->setItems( &items );
    ui->pianoroll->setSongPosition( 0 );
    mutex = new QMutex();
    ui->pianoroll->setMutex( mutex );

    connect( this, SIGNAL(doRepaint()), SLOT(onRepaintRequired()) );
}

Dialog::~Dialog()
{
    delete ui;
    delete timesigList;
    for( int i = 0; i < items.size(); i++ ){
        PianorollItem *item = items[i];
        if( item ){
            delete item;
        }
    }
    items.clear();
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
            ui->pianoroll->setSongPosition( newSongPosition );
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
    MidiInput::stop( this->channel );
    MidiInput::setReceiver( NULL );
}

void Dialog::send( unsigned char b1, unsigned char b2, unsigned char b3 )
{
    int command = (b1 & 0xF0);
    if( command == 0x90 && b3 != 0 ){
        tick_t length = stepUnit;
        tick_t position = ui->pianoroll->getSongPosition();

        if( !isRest ){
            PianorollItem *add = new PianorollItem();
            add->length = length;
            add->noteNumber = b2;
            add->phrase = "\xE3\x81\x82";
            add->symbols = "a";
            add->tick = position;
            mutex->lock();
            items.push_back( add );
            mutex->unlock();
        }

        ui->pianoroll->setSongPosition( position + length );
        emit doRepaint();
    }
}

void Dialog::onRepaintRequired()
{
    ui->pianoroll->repaint();
}
