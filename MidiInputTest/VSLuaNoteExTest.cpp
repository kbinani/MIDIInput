#include "Util.h"
#include <string>
#include "../MidiInput/VSLuaNoteEx.h"

using namespace std;
using namespace VSQ_NS;

class VSLuaNoteExTest : public CppUnit::TestCase, public VSLuaNoteEx
{
public:

    void testConstructWithArgument()
    {
        VSLuaNoteEx note( getFixture() );
        CPPUNIT_ASSERT_EQUAL( (tick_t)0, note.posTick );
        CPPUNIT_ASSERT_EQUAL( (tick_t)480, note.durTick );
        CPPUNIT_ASSERT_EQUAL( 60, note.noteNum );
        CPPUNIT_ASSERT_EQUAL( 64, note.velocity );
        CPPUNIT_ASSERT_EQUAL( string( "は" ), note.lyric );
        CPPUNIT_ASSERT_EQUAL( string( "a" ), note.phonemes );
        CPPUNIT_ASSERT_EQUAL( 65, note.bendDepth );
        CPPUNIT_ASSERT_EQUAL( 66, note.bendLength );
        CPPUNIT_ASSERT_EQUAL( true, note.risePort );
        CPPUNIT_ASSERT_EQUAL( false, note.fallPort );
        CPPUNIT_ASSERT_EQUAL( 67, note.decay );
        CPPUNIT_ASSERT_EQUAL( 68, note.accent );
        CPPUNIT_ASSERT_EQUAL( 69, note.opening );
        CPPUNIT_ASSERT_EQUAL( 70, note.vibratoLength );
        CPPUNIT_ASSERT_EQUAL( 1, note.vibratoType );
    }

    void testConstructWithoutArgument()
    {
        VSLuaNoteEx note;
        CPPUNIT_ASSERT_EQUAL( false, note.risePort );
        CPPUNIT_ASSERT_EQUAL( 1, note.vibratoType );
        CPPUNIT_ASSERT_EQUAL( (tick_t)480, note.durTick );
        CPPUNIT_ASSERT_EQUAL( 72, note.noteNum );
        CPPUNIT_ASSERT_EQUAL( 127, note.opening );
        CPPUNIT_ASSERT_EQUAL( 64, note.velocity );
        CPPUNIT_ASSERT_EQUAL( 66, note.vibratoLength );
        CPPUNIT_ASSERT_EQUAL( 50, note.decay );
        CPPUNIT_ASSERT_EQUAL( (tick_t)0, note.posTick );
        CPPUNIT_ASSERT_EQUAL( string( "a" ), note.phonemes );
        CPPUNIT_ASSERT_EQUAL( false, note.fallPort );
        CPPUNIT_ASSERT_EQUAL( 0, note.bendLength );
        CPPUNIT_ASSERT_EQUAL( 8, note.bendDepth );
        CPPUNIT_ASSERT_EQUAL( string( "a" ), note.lyric );
        CPPUNIT_ASSERT_EQUAL( 50, note.accent );
    }

    void testToString()
    {
        VSLuaNoteEx note;
        note.posTick = 0;
        note.durTick = 480;
        note.noteNum = 60;
        note.velocity = 64;
        note.lyric = "は";
        note.phonemes = "a";
        note.bendDepth = 65;
        note.bendLength = 66;
        note.risePort = true;
        note.fallPort = false;
        note.decay = 67;
        note.accent = 68;
        note.opening = 69;
        note.vibratoLength = 70;
        note.vibratoType = 1;
        CPPUNIT_ASSERT_EQUAL( getFixture(), note.toString() );
    }

    const string getFixture()
    {
        string fixture = "{"
            "posTick=0,"
            "durTick=480,"
            "noteNum=60,"
            "velocity=64,"
            "lyric=\"は\","
            "phonemes=\"a\","
            "bendDepth=65,"
            "bendLength=66,"
            "risePort=1,"
            "fallPort=0,"
            "decay=67,"
            "accent=68,"
            "opening=69,"
            "vibratoLength=70,"
            "vibratoType=1}";
        return fixture;
    }

    void testChomp()
    {
        string fixture = "   ab  c  ";
        VSLuaNoteEx::chomp( fixture );
        CPPUNIT_ASSERT_EQUAL( string( "ab  c" ), fixture );
    }

    CPPUNIT_TEST_SUITE( VSLuaNoteExTest );
    CPPUNIT_TEST( testConstructWithArgument );
    CPPUNIT_TEST( testConstructWithoutArgument );
    CPPUNIT_TEST( testToString );
    CPPUNIT_TEST( testChomp );
    CPPUNIT_TEST_SUITE_END();
};

REGISTER_TEST_SUITE( VSLuaNoteExTest );
