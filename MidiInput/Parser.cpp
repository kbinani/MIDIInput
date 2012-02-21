#include <iostream>
#include <sstream>
#include <TimesigList.h>
#include "Parser.h"
#include "StringUtil.h"
#include "VSLuaNoteEx.h"

using namespace std;
using namespace VSQ_NS;

map<tick_t, PianorollItem *> *Parser::getEvent( const string eventText )
{
    map<tick_t, PianorollItem *> *items = new map<tick_t, PianorollItem *>;

    vector<string> lines = StringUtil::explode( "\x0A", eventText );
    for( int i = 0; i < lines.size(); i++ ){
        string line = lines[i];
        if( line.size() == 0 ){
            continue;
        }
        VSLuaNoteEx note( line );

        PianorollItem *item = new PianorollItem();
        item->noteNumber = note.noteNum;
        item->phrase = note.lyric;
        item->symbols = note.phonemes;
        item->length = note.durTick;

        tick_t tick = note.posTick;
        if( items->find( tick ) != items->end() ){
            delete items->find( tick )->second;
        }
        items->insert( make_pair( tick, item ) );
    }

    return items;
}

TimesigList *Parser::getTimesig( const string timesigText )
{
    TimesigList *timesigList = new TimesigList();
    vector<string> lines = StringUtil::explode( "\x0A", timesigText );
    for( int i = 0; i < lines.size(); i++ ){
        string line = lines[i];
        if( line.size() == 0 ){
            continue;
        }
        vector<string> parameters = StringUtil::explode( ",", line );
        if( parameters.size() < 3 ){
            continue;
        }
        tick_t tick = (tick_t)atol( parameters[0].c_str() );
        int numerator = atoi( parameters[1].c_str() );
        int denominator = atoi( parameters[2].c_str() );

        Timesig timesig = timesigList->getTimesigAt( tick );
        timesigList->push( Timesig( numerator, denominator, timesig.barCount ) );
        timesigList->updateTimesigInfo();
    }

    return timesigList;
}

const string Parser::toString( map<tick_t, PianorollItem *> *items )
{
    ostringstream oss;
    map<tick_t, PianorollItem *>::iterator i;
    for( i = items->begin(); i != items->end(); i++ ){
        tick_t tick = i->first;
        PianorollItem *item = i->second;

        VSLuaNoteEx note;
        note.posTick = tick;
        note.durTick = item->length;
        note.noteNum = item->noteNumber;
        note.lyric = item->phrase;
        note.phonemes = item->symbols;

        oss << note.toString() << "\x0A";
    }
    return oss.str();
}
