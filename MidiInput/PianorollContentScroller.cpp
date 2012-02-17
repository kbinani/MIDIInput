#include "PianorollContentScroller.h"
#include "Pianoroll.h"
#include <sstream>

PianorollContentScroller::PianorollContentScroller( QWidget *parent ) :
    QScrollArea( parent )
{
}

void PianorollContentScroller::setPianoroll( Pianoroll *pianoroll )
{
    this->pianoroll = pianoroll;
}

void PianorollContentScroller::scrollContentsBy( int dx, int dy )
{
    QScrollArea::scrollContentsBy( dx, dy );
    if( dy ){
        this->pianoroll->notifyVerticalScroll();
    }
}
