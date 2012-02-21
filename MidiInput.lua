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
    local result = start( eventText, timesigText );

    local notes = getNotes( result );
    replaceAllNotes( notes );

    return 0;
end

---
-- ダイアログの戻りのテキストを、音符のリストに変換する
-- @param string 変換元のテキスト
-- @return table<VSLuaNoteEx> 変換後の音符リスト
function getNotes( text )
    local result = {};
    local lines = luavsq.Util.split( text, string.char( 0x0A ) );
    local i;
    for i = 1, #lines, 1 do
        local code = "return " .. lines[i];
        local note = loadstring( code )();
        table.insert( result, note );
    end
    return result;
end

---
-- 選択中の Musical Part 内の音符をすべて削除し、引数で渡された音符を挿入する
-- @param table<VSLuaNoteEx> 挿入する音符のリスト
function replaceAllNotes( notes )
    -- 全削除
    VSSeekToBeginNote();
    local result, note;
    result, note = VSGetNextNote();
    while( result ~= 0 )do
        VSRemoveNote( note );
        result, note = VSGetNextNote();
    end

    -- 挿入
    local i;
    for i = 1, #notes, 1 do
        VSInsertNoteEx( notes[i] );
    end
end

---
-- 選択中の Musical Part 内の音符情報をテキストに変換する
-- @return string 変換後のテキスト
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
