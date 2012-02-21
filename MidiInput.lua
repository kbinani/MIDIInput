function manifest()
    return {
        name          = "MIDIInput",
        comment       = "MIDIInput",
        author        = "kbinani_103",
        pluginID      = "{2A879F9A-7BC7-4379-ADB0-082A28BBE78B}",
        pluginVersion = "0.0.0.0",
        apiVersion    = "3.0.0.1"
    };
end

function main( processParam, envParam )
    local scriptDirectory = envParam.scriptDir;
    local dllPath = scriptDirectory .. "MidiInput.dll";
    local luavsqPath = scriptDirectory .. "luavsq.lua";

    if( false == pcall( dofile, luavsqPath ) )then
        VSMessageBox( "luavsq ライブラリの読み込みに失敗しました", 0 );
        return 0;
    end

    luavsq.Log.setLevel( 1 );
    luavsq.Log.println( "dllPath=" .. dllPath );
    luavsq.Log.println( "luavsqPath=" .. luavsqPath );

    local start = package.loadlib( dllPath, "start" );

    local eventText = getEventText();
    local timesigText = getTimesigText();
    luavsq.Log.println( "eventText=" .. eventText );
    luavsq.Log.println( "timesigText=" .. timesigText );
    local result = start( eventText, timesigText );

    luavsq.Log.println( "result=" .. result );

    return 0;
end

function getEventText()
    local text = "";

    VSSeekToBeginNote();
    local result, noteEx;
    result, noteEx = VSGetNextNoteEx();
    while( result ~= 0 )do
        local clock = noteEx.posTick;
        text = text .. luavsq.Util.export( noteEx ) .. string.char( 0x0A );
        result, noteEx = VSGetNextNoteEx();
    end

    return text;
end

function getTimesigText()
    local result = "";
    local timesigInfo = {};
    local succeeded = 1;
    VSSeekToBeginTimeSig();
    succeeded, timesigInfo = VSGetNextTimeSig();
    while( succeeded ~= 0 )do
        result = result .. timesigInfo.posTick .. "," .. timesigInfo.numerator .. "," .. timesigInfo.denominator .. string.char( 0x0A );
        succeeded, timesigInfo = VSGetNextTimeSig();
    end
    return result;
end

---
-- 指定した tick 時刻にあるノート情報を取得する
-- @param number position tick 単位の時刻
-- @return VSLuaNote
function selectAt( position )
    VSSeekToBeginNote();
    while( true )do
        local note = VSGetNextNote();
        if( note == 0 )then
            break;
        end
        if( note.posTick == position )then
            return note;
        end
    end
    return nil;
end
