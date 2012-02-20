#include <TimesigList.h>
#include "Parser.h"
#include "StringUtil.h"

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
        vector<string> parameters = StringUtil::explode( ",", line );
        if( parameters.size() < 5 ){
            continue;
        }

        tick_t tick = (tick_t)atol( parameters[0].c_str() );
        int noteNumber = atoi( parameters[1].c_str() );
        string phrase = parameters[2];
        string symbol = parameters[3];
        tick_t length = (tick_t)atol( parameters[4].c_str() );

        PianorollItem *item = new PianorollItem();
        item->noteNumber = noteNumber;
        item->phrase = phrase;
        item->symbols = symbol;
        item->length = length;

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