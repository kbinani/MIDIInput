#include <sstream>
#include "VSLuaNoteEx.h"
#include "StringUtil.h"

using namespace VSQ_NS;
using namespace std;

VSLuaNoteEx::VSLuaNoteEx( const string line )
{
    risePort = 0;
    vibratoType = 1;
    durTick = 480;
    noteNum = 72;
    opening = 127;
    velocity = 64;
    vibratoLength = 66;
    decay = 50;
    posTick = 0;
    phonemes = "a";
    fallPort = 0;
    bendLength = 0;
    bendDepth = 8;
    lyric = "a";
    accent = 50;

    string parse = line;
    chomp( parse );
    if( 0 < parse.length() ){
        if( parse[0] == '{' ){
            parse = parse.substr( 1 );
        }
    }
    if( 0 < parse.length() ){
        if( parse[parse.length() - 1] == '}' ){
            parse = parse.substr( 0, parse.length() - 1 );
        }
    }
    vector<string> parameters = StringUtil::explode( ",", parse, string::npos, "\\" );
    for( int i = 0; i < parameters.size(); i++ ){
        string parameter = parameters[i];
        chomp( parameter );

        vector<string> keyAndValue = StringUtil::explode( "=", parameter, string::npos, "\\" );
        if( keyAndValue.size() != 2 ){
            continue;
        }
        string key = keyAndValue[0];
        string value = keyAndValue[1];
        chomp( key );
        chomp( value );
        if( 0 < value.length() ){
            if( value[0] == '\'' ){
                value = value.substr( 1 );
            }
        }
        if( 0 < value.length() ){
            if( value[value.length() - 1] == '\'' ){
                value = value.substr( 0, value.length() - 1 );
            }
        }

        if( key == "posTick" ){
            posTick = (tick_t)atol( value.c_str() );
        }else if( key == "durTick" ){
            durTick = (tick_t)atol( value.c_str() );
        }else if( key == "noteNum" ){
            noteNum = atoi( value.c_str() );
        }else if( key == "velocity" ){
            velocity = atoi( value.c_str() );
        }else if( key == "lyric" ){
            lyric = value;
        }else if( key == "phonemes" ){
            phonemes = value;
        }else if( key == "bendDepth" ){
            bendDepth = atoi( value.c_str() );
        }else if( key == "bendLength" ){
            bendLength = atoi( value.c_str() );
        }else if( key == "risePort" ){
            risePort = (atoi( value.c_str() ) ? true : false);
        }else if( key == "fallPort" ){
            fallPort = (atoi( value.c_str() ) ? true : false);
        }else if( key == "decay" ){
            decay = atoi( value.c_str() );
        }else if( key == "accent" ){
            accent = atoi( value.c_str() );
        }else if( key == "opening" ){
            opening = atoi( value.c_str() );
        }else if( key == "vibratoLength" ){
            vibratoLength = atoi( value.c_str() );
        }else if( key == "vibratoType" ){
            vibratoType = atoi( value.c_str() );
        }
    }
}

const string VSLuaNoteEx::toString()
{
    ostringstream oss;
    oss << "{posTick=" << posTick << ",";
    oss << "durTick=" << durTick << ",";
    oss << "noteNum=" << noteNum << ",";
    oss << "velocity=" << velocity << ",";
    oss << "lyric='" << lyric << "',";
    oss << "phonemes='" << phonemes << "',";
    oss << "bendDepth=" << bendDepth << ",";
    oss << "bendLength=" << bendLength << ",";
    oss << "risePort=" << (risePort ? "1" : "0") << ",";
    oss << "fallPort=" << (fallPort ? "1" : "0") << ",";
    oss << "decay=" << decay << ",";
    oss << "accent=" << accent << ",";
    oss << "opening=" << opening << ",";
    oss << "vibratoLength=" << vibratoLength << ",";
    oss << "vibratoType=" << vibratoType << "}";
    return oss.str();
}

void VSLuaNoteEx::chomp( string &text )
{
    while( 0 < text.length() ){
        if( text[0] == ' ' ){
            text = text.substr( 1 );
        }else if( text[text.length() - 1] == ' ' ){
            text = text.substr( 0, text.length() - 1 );
        }else{
            break;
        }
    }
}
