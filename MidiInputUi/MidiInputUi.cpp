#include <QtGui>
#include "MidiInputUi.h"
#include "Dialog.h"
#include "DialogRunner.h"

void MidiInputUi::showDialog()
{
    DialogRunner *dialogRunner = new DialogRunner();
    dialogRunner->start();
}
