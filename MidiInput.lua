---
-- MidiInput.lua
-- Copyright © 2012 kbinani
--
-- This file is part of `MIDIInput UG Job Plugin'.
--
-- `MIDIInput UG Job Plugin' is free software; you can redistribute it and/or
-- modify it under the terms of the BSD License.
--
-- `MIDIInput UG Job Plugin' is distributed in the hope that it will be useful,
-- but WITHOUT ANY WARRANTY; without even the implied warranty of
-- MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
--
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
        return 1;
    end

    local start = package.loadlib( dllPath, "start" );
    if( nil == start )then
        VSMessageBox( "MidiInput.dll の読み込みに失敗しました", 0 );
        return 1;
    end

    local eventText = getEventText();
    local timesigText = getTimesigText();
    local musicalPartOffset = getMusicalPartOffset();
    local result = start( eventText, timesigText, musicalPartOffset );

    local notes = getNotes( result );
    replaceAllNotes( notes );

    return 0;
end

---
-- Musical Part と曲頭のオフセットを取得する
-- @return number 曲頭から計った、Musical Part の開始時刻(tick 単位)
function getMusicalPartOffset()
    local result, part;
    result, part = VSGetMusicalPart();
    if( result ~= 0 )then
        return part.posTick;
    else
        return 0;
    end
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

---
-- 拍子変更情報をテキストに変換する
-- @return string 変換後のテキスト
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
