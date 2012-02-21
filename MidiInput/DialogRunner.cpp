/**
 * DialogRunner.cpp
 * Copyright © 2012 kbinani
 *
 * This file is part of `MIDIInput UG Job Plugin'.
 *
 * `MIDIInput UG Job Plugin' is free software; you can redistribute it and/or
 * modify it under the terms of the BSD License.
 *
 * `MIDIInput UG Job Plugin' is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 */
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
