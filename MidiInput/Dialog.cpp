#include <QKeyEvent>
#include "MidiInput.h"
#include "Dialog.h"
#include "Pianoroll.h"
#include "ui_Dialog.h"

using namespace std;
using namespace VSQ_NS;

Dialog::Dialog( DialogListener *listener, QWidget *parent ) :
    QDialog( parent ),
    ui( new Ui::Dialog )
{
    ui->setupUi( this );

    this->listener = listener;
    stepUnit = 480;
    ui->toolButtonNote004->toggle();

    ui->pushButtonStart->setEnabled( false );
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
        ui->pushButtonStart->setEnabled( true );
    }

    timesigList = new TimesigList();
    timesigList->push( Timesig( 4, 4, 0 ) );
    ui->pianoroll->setTimesigList( timesigList );
    ui->pianoroll->setSongPosition( 0 );
}

Dialog::~Dialog()
{
    delete ui;
    delete timesigList;
}

void Dialog::on_pushButtonStart_clicked()
{
    if( this->listener ){
        int channel = ui->comboBox->currentIndex();
        if( 0 <= channel && channel < MidiInput::getDeviceCount() ){
            this->listener->inputStartRequired( channel );
        }
    }
}

void Dialog::on_pushButtonStop_clicked()
{
    if( this->listener ){
        this->listener->inputStopRequired();
    }
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
    }
}

void Dialog::on_toolButtonNote002_toggled(bool checked)
{
    if( checked ){
        stepUnit = 960;
    }
}

void Dialog::on_toolButtonNote004_toggled(bool checked)
{
    if( checked ){
        stepUnit = 480;
    }
}

void Dialog::on_toolButtonNote008_toggled(bool checked)
{
    if( checked ){
        stepUnit = 240;
    }
}

void Dialog::on_toolButtonNote016_toggled(bool checked)
{
    if( checked ){
        stepUnit = 120;
    }
}

void Dialog::on_toolButtonRest001_toggled(bool checked)
{
    if( checked ){
        stepUnit = 1920;
    }
}

void Dialog::on_toolButtonRest002_toggled(bool checked)
{
    if( checked ){
        stepUnit = 960;
    }
}

void Dialog::on_toolButtonRest004_toggled(bool checked)
{
    if( checked ){
        stepUnit = 480;
    }
}

void Dialog::on_toolButtonRest008_toggled(bool checked)
{
    if( checked ){
        stepUnit = 240;
    }
}

void Dialog::on_toolButtonRest016_toggled(bool checked)
{
    if( checked ){
        stepUnit = 120;
    }
}
