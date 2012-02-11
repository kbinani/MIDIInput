#include "MidiInput.h"
#include "Dialog.h"
#include "ui_Dialog.h"

using namespace std;

Dialog::Dialog( DialogListener *listener, QWidget *parent ) :
    QDialog( parent ),
    ui( new Ui::Dialog )
{
    ui->setupUi( this );

    this->listener = listener;

    ui->pushButtonStart->setEnabled( false );
    ui->comboBox->clear();
    ui->comboBox->setEnabled( false );

    int count = MidiInput::getDeviceCount();
    for( int i = 0; i < count; i++ ){
        string name = MidiInput::getDeviceName( i );
        ui->comboBox->addItem( QString::fromStdString( name ) );
    }
    if( ui->comboBox->count() > 0 ){
        ui->comboBox->setEnabled( true );
        ui->pushButtonStart->setEnabled( true );
    }
}

Dialog::~Dialog()
{
    delete ui;
}

void Dialog::on_pushButtonStart_clicked()
{
    int channel = ui->comboBox->currentIndex();
    if( 0 <= channel && channel < MidiInput::getDeviceCount() ){
        this->listener->inputStartRequired( channel );
    }
}

void Dialog::on_pushButtonStop_clicked()
{
    this->listener->inputStopRequired();
}
