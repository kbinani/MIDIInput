#include "Util.h"
#include "../MidiInput/Parser.h"
#include <sstream>

using namespace std;
using namespace VSQ_NS;

class ParserTest : public CppUnit::TestCase
{
public:
    void testGetEvent()
    {
        ostringstream oss;
        oss << "{posTick=480,noteNum=60,lyric='あ',phonemes='a',durTick=480}" << "\x0A";
        oss << "\x0A";
        oss << "{posTick=960,noteNum=62,lyric='わ',phonemes='w a',durTick=480}" <<  "\x0A";
        Parser parser;
        map<tick_t, PianorollItem *> *actual = parser.getEvent( oss.str() );

        CPPUNIT_ASSERT_EQUAL( 2, (int)actual->size() );

        map<tick_t, PianorollItem *>::iterator i = actual->begin();

        CPPUNIT_ASSERT_EQUAL( (tick_t)480, i->first );
        CPPUNIT_ASSERT_EQUAL( 60, i->second->noteNumber );
        CPPUNIT_ASSERT_EQUAL( string( "あ" ), i->second->phrase );
        CPPUNIT_ASSERT_EQUAL( string( "a" ), i->second->symbols );
        CPPUNIT_ASSERT_EQUAL( 480, i->second->length );

        i++;

        CPPUNIT_ASSERT_EQUAL( (tick_t)960, i->first );
        CPPUNIT_ASSERT_EQUAL( 62, i->second->noteNumber );
        CPPUNIT_ASSERT_EQUAL( string( "わ" ), i->second->phrase );
        CPPUNIT_ASSERT_EQUAL( string( "w a" ), i->second->symbols );
        CPPUNIT_ASSERT_EQUAL( 480, i->second->length );

        i = actual->begin();
        for( ; i != actual->end(); i++ ){
            delete i->second;
        }
        delete actual;
    }

    void testGetTimesig()
    {
        ostringstream oss;
        oss << "\x0A";
        oss << "0,3,4" << "\x0A";
        Parser parser;
        TimesigList *list = parser.getTimesig( oss.str() );
        CPPUNIT_ASSERT_EQUAL( 1, list->size() );

        CPPUNIT_ASSERT_EQUAL( 3, list->get( 0 ).numerator );
        CPPUNIT_ASSERT_EQUAL( 4, list->get( 0 ).denominator );
        CPPUNIT_ASSERT_EQUAL( 0, list->get( 0 ).barCount );

        delete list;
    }

    void testGetTimesigEmpty()
    {
        Parser parser;
        TimesigList *list = parser.getTimesig( "" );
        CPPUNIT_ASSERT_EQUAL( 0, list->size() );
        delete list;
    }

    void testToString()
    {
        map<tick_t, PianorollItem *> items;
        PianorollItem *itemA = new PianorollItem();
        itemA->noteNumber = 60;
        itemA->phrase = "あ";
        itemA->symbols = "a";
        itemA->length = 480;
        items.insert( make_pair( 480, itemA ) );

        PianorollItem *itemB = new PianorollItem();
        itemB->noteNumber = 62;
        itemB->phrase = "わ";
        itemB->symbols = "w a";
        itemB->length = 480;
        items.insert( make_pair( 960, itemB ) );

        Parser parser;
        string actual = parser.toString( &items );
        string expected = "{"
                "posTick=480,"
                "durTick=480,"
                "noteNum=60,"
                "velocity=64,"
                "lyric='あ',"
                "phonemes='a',"
                "bendDepth=8,"
                "bendLength=0,"
                "risePort=0,"
                "fallPort=0,"
                "decay=50,"
                "accent=50,"
                "opening=127,"
                "vibratoLength=66,"
                "vibratoType=1"
                "}\x0A{"
                "posTick=960,"
                "durTick=480,"
                "noteNum=62,"
                "velocity=64,"
                "lyric='わ',"
                "phonemes='w a',"
                "bendDepth=8,"
                "bendLength=0,"
                "risePort=0,"
                "fallPort=0,"
                "decay=50,"
                "accent=50,"
                "opening=127,"
                "vibratoLength=66,"
                "vibratoType=1"
                "}\x0A";

        CPPUNIT_ASSERT_EQUAL( expected, actual );

        delete itemA;
        delete itemB;
    }

    CPPUNIT_TEST_SUITE( ParserTest );
    CPPUNIT_TEST( testGetEvent );
    CPPUNIT_TEST( testGetTimesig );
    CPPUNIT_TEST( testGetTimesigEmpty );
    CPPUNIT_TEST( testToString );
    CPPUNIT_TEST_SUITE_END();
};

REGISTER_TEST_SUITE( ParserTest );
