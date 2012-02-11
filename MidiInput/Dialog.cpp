#include <windows.h>
#include "Dialog.h"
#include "ui_Dialog.h"

using namespace std;

Dialog::Dialog( QWidget *parent ) :
    QDialog( parent ),
    ui( new Ui::Dialog )
{
    ui->setupUi( this );

    int count = midiInGetNumDevs();
    for( int i = 0; i < count; i++ ){
        MIDIINCAPSA caps;
        memset( &caps, 0, sizeof( MIDIINCAPSA ) );
        midiInGetDevCapsA( i, &caps, sizeof( MIDIINCAPSA ) );
        string name = caps.szPname;
        ui->comboBox->addItem( QString::fromStdString( name ) );
    }
}

Dialog::~Dialog()
{
    delete ui;
}
