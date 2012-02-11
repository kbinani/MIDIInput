#ifndef PIANOROLLITEM_H
#define PIANOROLLITEM_H

#include <string>

class PianorollItem
{
public:
    int x;
    int y;
    int width;
    std::string phrase;
    std::string symbols;

public:
    PianorollItem();
};

#endif // PIANOROLLITEM_H
