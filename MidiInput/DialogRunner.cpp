#include <QApplication>
#include "DialogRunner.h"
#include "Dialog.h"

DialogRunner::DialogRunner( const std::string eventText, const std::string timesigText )
{
    this->eventText = eventText;
    this->timesigText = timesigText;
}

void DialogRunner::run()
{
    int argc = 0;
    QApplication app( argc, NULL );
    Dialog dialog( eventText, timesigText, NULL );
    dialog.exec();
}
