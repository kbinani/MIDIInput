# MIDIInput

- is a plugin for VOCALOID3 Editor.

## License

- The BSD License.

## Usage

- (not documented yet)

## Building the project

### Requirements
- liblua 5.1
- QtSDK 4.7
- Visual C++ 2008 (Express Ed.)
- libvsq
- javac
- Windows OS

### Build steps

1. building vsq.lib using Visual C++ command prompt.

    git clone git:://github.com/cadencii/cadencii.git
    cd cadencii\vsq
    mkdir build
    mkdir build\win32
    qmake vsq.pro -o build\win32
    cd build\win32
    nmake /f Makefile.Release

1. building MidiInput.dll using Visual C++ command prompt.

    git clone git://github.com/kbinani/MIDIInput.git
    cd MIDIInput/MidiInput
    mkdir build
    qmake MidiInput.pro -o build
    cd build
    nmake /f Makefile.Release

1. building luavsq.lua

    svn co http://svn.sourceforge.jp/svnroot/cadencii/luavsq
    cd luavsq\trunk\tool
    nmake

1. collecting release files

    MidiInput.dll (in MIDIInput\MidiInput\build\release\)
    MidiInput.lua (in MIDIInput\)
    luavsq.lua (in luavsq\trunk\tool\)
    QtCore4.dll (in your QtSDK installation directory)
    QtGui4.dll (same as above)
