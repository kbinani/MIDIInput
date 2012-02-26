#include "Util.h"
#include "../MidiInput/Settings.h"

using namespace std;

class SettingsTest : public CppUnit::TestCase, public Settings
{
public:
    void testGetToolButtonShortcut()
    {
        toolButtonShortcut.clear();

        map<Qt::Key, string> *shortcut = SettingsTest::getToolButtonShortcut();
        CPPUNIT_ASSERT_EQUAL( 10, (int)shortcut->size() );

        map<Qt::Key, string>::iterator i = shortcut->begin();
        CPPUNIT_ASSERT_EQUAL( string( "toolButtonRest001" ), i->second );
        CPPUNIT_ASSERT_EQUAL( Qt::Key_A, i->first );
        i++;
        CPPUNIT_ASSERT_EQUAL( string( "toolButtonRest004" ), i->second );
        CPPUNIT_ASSERT_EQUAL( Qt::Key_D, i->first );
        i++;
        CPPUNIT_ASSERT_EQUAL( string( "toolButtonNote004" ), i->second );
        CPPUNIT_ASSERT_EQUAL( Qt::Key_E, i->first );
        i++;
        CPPUNIT_ASSERT_EQUAL( string( "toolButtonRest008" ), i->second );
        CPPUNIT_ASSERT_EQUAL( Qt::Key_F, i->first );
        i++;
        CPPUNIT_ASSERT_EQUAL( string( "toolButtonRest016" ), i->second );
        CPPUNIT_ASSERT_EQUAL( Qt::Key_G, i->first );
        i++;
        CPPUNIT_ASSERT_EQUAL( string( "toolButtonNote001" ), i->second );
        CPPUNIT_ASSERT_EQUAL( Qt::Key_Q, i->first );
        i++;
        CPPUNIT_ASSERT_EQUAL( string( "toolButtonNote008" ), i->second );
        CPPUNIT_ASSERT_EQUAL( Qt::Key_R, i->first );
        i++;
        CPPUNIT_ASSERT_EQUAL( string( "toolButtonRest002" ), i->second );
        CPPUNIT_ASSERT_EQUAL( Qt::Key_S, i->first );
        i++;
        CPPUNIT_ASSERT_EQUAL( string( "toolButtonNote016" ), i->second );
        CPPUNIT_ASSERT_EQUAL( Qt::Key_T, i->first );
        i++;
        CPPUNIT_ASSERT_EQUAL( string( "toolButtonNote002" ), i->second );
        CPPUNIT_ASSERT_EQUAL( Qt::Key_W, i->first );
        i++;
        CPPUNIT_ASSERT( i == shortcut->end() );
    }

    CPPUNIT_TEST_SUITE( SettingsTest );
    CPPUNIT_TEST( testGetToolButtonShortcut );
    CPPUNIT_TEST_SUITE_END();
};

REGISTER_TEST_SUITE( SettingsTest );
