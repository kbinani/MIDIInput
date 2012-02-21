#include <QApplication>
#include "DialogRunner.h"
#include "Dialog.h"

using namespace std;

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
    eventText = dialog.getEventText();
}

const string DialogRunner::getEventText()
{
    return eventText;
}
