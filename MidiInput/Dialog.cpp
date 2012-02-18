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
        Timesig timesig = timesigList->getTimesigAt( songPosition );
        tick_t newSongPosition = songPosition + (delta * 480 * 4 / timesig.denominator);
        if( newSongPosition < 0 ){
            newSongPosition = 0;
        }
        if( newSongPosition != songPosition ){
            ui->pianoroll->setSongPosition( newSongPosition );
            ui->pianoroll->repaint();
        }
    }
}
