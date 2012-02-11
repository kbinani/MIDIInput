#include <windows.h>
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

    ui->comboBox->clear();
    ui->comboBox->addItem( "" );
    int count = MidiInput::getDeviceCount();
    for( int i = 0; i < count; i++ ){
        string name = MidiInput::getDeviceName( i );
        ui->comboBox->addItem( QString::fromStdString( name ) );
    }
    ui->stackedWidget->setCurrentIndex( 0 );
}

Dialog::~Dialog()
{
    delete ui;
}

void Dialog::on_pushButtonStart_clicked()
{
    ui->stackedWidget->setCurrentIndex( 1 );
}

void Dialog::on_pushButtonStop_clicked()
{
    ui->stackedWidget->setCurrentIndex( 0 );
}
