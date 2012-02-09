#include <QtGui>
#include "MidiInputUi.h"
#include "Dialog.h"

MidiInputUi::MidiInputUi()
{
}

void MidiInputUi::doSomething()
{
    int argc = 0;
    QApplication app( argc, NULL );
    Dialog d( (QWidget *)0 );
    d.show();
    app.exec();
    return;
}
