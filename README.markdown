# MIDIInput

- is a plugin for VOCALOID3 Editor.

## License

- The BSD License.

## Usage

- (not documented yet)

## Building the project

### Requirements
- liblua 5.1
- Qt 4.7
- Visual C++ 2008 (Express Ed.)
- libvsq
- javac
- Windows OS

### Build steps

building vsq.lib using Visual C++ command prompt.

    git clone git://github.com/cadencii/cadencii.git
    cd cadencii\vsq
    mkdir build
    mkdir build\win32
    qmake vsq.pro -o build\win32
    cd build\win32
    nmake /f Makefile.Release

building MidiInput.dll using Visual C++ command prompt.

    git clone git://github.com/kbinani/MIDIInput.git
    cd MIDIInput\MidiInput
    mkdir build
    qmake MidiInput.pro -o build
    cd build
    nmake /f Makefile.Release

building luavsq.lua

    git clone git://github.com/kbinani/luavsq.git
    cd luavsq\tool
    nmake

collecting release files

    MidiInput.dll (in MIDIInput\MidiInput\build\release\)
    MidiInput.lua (in MIDIInput\)
    luavsq.lua (in luavsq\trunk\tool\)
    QtCore4.dll (in your QtSDK installation directory)
    QtGui4.dll (same as above)

done.

## Copyright notice

### Qt version 4.7.4 (LGPL)

> This program uses Qt version 4.7.4.
>
> Qt is a C++ toolkit for cross-platform application development.
>
> Qt provides single-source portability across MS Windows, Mac OS X, Linux, and all major commercial Unix variants. Qt is also available for embedded devices as Qt for Embedded Linux and Qt for Windows CE.
>
> Qt is available under three different licensing options designed to accommodate the needs of our various users.
>
> Qt licensed under our commercial license agreement is appropriate for development of proprietary/commercial software where you do not want to share any source code with third parties or otherwise cannot comply with the terms of the GNU LGPL version 2.1 or GNU GPL version 3.0.
>
> Qt licensed under the GNU LGPL version 2.1 is appropriate for the development of Qt applications (proprietary or open source) provided you can comply with the terms and conditions of the GNU LGPL version 2.1.
>
> Qt licensed under the GNU General Public License version 3.0 is appropriate for the development of Qt applications where you wish to use such applications in combination with software subject to the terms of the GNU GPL version 3.0 or where you are otherwise willing to comply with the terms of the GNU GPL version 3.0.
>
> Please see qt.nokia.com/products/licensing for an overview of Qt licensing.
>
> Copyright (C) 2011 Nokia Corporation and/or its subsidiary(-ies).
>
> Qt is a Nokia product. See qt.nokia.com for more information.

### lua version 5.1

> Copyright © 1994–2012 Lua.org, PUC-Rio.
> Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:
>
> The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.
>
> THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
