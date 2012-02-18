#include <sstream>
#include <math.h>
#include "Pianoroll.h"
#include "QScrollArea"
#include "QPainter"
#include <sstream>
#include <math.h>
#include "Pianoroll.h"
#include "QScrollArea"
#include "QPainter"
#include <Timesig.h>

using namespace std;
using namespace VSQ_NS;

PianorollContent::PianorollContent(QWidget *parent) :
    QWidget(parent)
{
    this->items = NULL;
    this->trackHeight = DEFAULT_TRACK_HEIGHT;
    this->pixelPerTick = 0.2;

    this->defaultTimesigList.push( Timesig( 4, 4, 0 ) );
    this->measureLineIterator = new MeasureLineIterator( &defaultTimesigList );
    this->setMouseTracking( true );

    this->setMinimumWidth( 5000 );
}

PianorollContent::~PianorollContent()
{
    delete measureLineIterator;
}

int PianorollContent::getMinimumHeight()
{
    return this->trackHeight * (NOTE_MAX - NOTE_MIN + 1);
}

void PianorollContent::paintEvent( QPaintEvent * ){
    int minimumHeight = this->getMinimumHeight();
    if( this->minimumHeight() != minimumHeight ){
        this->setMinimumHeight( minimumHeight );
    }
    QPainter p( this );

    QRect visibleArea = this->getPaintArea();

    paintBackground( &p, visibleArea );
    paintMeasureLines( &p, visibleArea );
    paintItems( &p, visibleArea );
    paintSongPosition( &p, visibleArea );
}

void PianorollContent::paintBackground( QPainter *g, QRect visibleArea ){
    // 背景
    int height = getYFromNoteNumber( NOTE_MIN - 1, trackHeight ) - visibleArea.y();
    g->fillRect( visibleArea.x(), visibleArea.y(),
                 visibleArea.width(), height,
                 QColor( 240, 240, 240 ) );

    // 黒鍵
    for( int noteNumber = NOTE_MIN; noteNumber <= NOTE_MAX; noteNumber++ ){
        int y = getYFromNoteNumber( noteNumber, trackHeight );
        int modura = getNoteModuration( noteNumber );

        if( visibleArea.y() + visibleArea.height() < y ){
            continue;
        }

        // 黒鍵
        if( modura == 1 || modura == 3 || modura == 6 || modura == 8 || modura == 10 ){
            g->fillRect( visibleArea.x(), y,
                         visibleArea.width(), trackHeight + 1,
                         QColor( 212, 212, 212 ) );
        }

        // 白鍵が隣り合う部分に境界線を書く
        if( modura == 11 || modura == 4 ){
            g->setPen( QColor( 210, 203, 173 ) );
            g->drawLine( visibleArea.x(), y,
                         visibleArea.x() + visibleArea.width(), y );
        }

        if( y < visibleArea.y() ){
            break;
        }
    }
}

void PianorollContent::paintItems( QPainter *g, QRect visibleArea ){
    if( items == NULL ){
        return;
    }
    int count = this->items->size();
    int height = trackHeight - 1;

    QColor fillColor = QColor( 181, 220, 86 );
    g->setPen( QColor( 125, 123, 124 ) );

    int visibleMinX = visibleArea.x();
    int visibleMaxX = visibleArea.x() + visibleArea.width();
    int visibleMinY = visibleArea.y();
    int visibleMaxY = visibleArea.y() + visibleArea.height();

    for( int i = 0; i < count; i++ ){
        PianorollItem *item = items->at( i );
        int x = getXFromTick( item->tick );
        int width = getXFromTick( item->tick + item->length ) - x;

        if( visibleMinX <= x + width && x <= visibleMaxX ){
            int y = getYFromNoteNumber( item->noteNumber, trackHeight ) + 1;
            if( visibleMinY <= y + height && y <= visibleMaxY ){
                g->fillRect( x, y, width, height, fillColor );
                g->drawRect( x, y, width, height );

                g->setPen( QColor( 0, 0, 0 ) );
                g->drawText( x + 1, y + trackHeight - 2,
                             QString::fromUtf8( (item->phrase + " [" + item->symbols + "]").c_str() ) );
            }
        }
    }
}

void PianorollContent::mouseMoveEvent( QMouseEvent *e )
{
    this->pianoroll->repaint();
    QWidget::mouseMoveEvent( e );
}

void PianorollContent::setItems( std::vector<PianorollItem *> *items, TimesigList *timesigList ){
    this->items = items;
    this->timesigList = timesigList;
    if( this->measureLineIterator ){
        delete this->measureLineIterator;
    }
    this->measureLineIterator = new MeasureLineIterator( this->timesigList );
}

void PianorollContent::setTrackHeight( int trackHeight )
{
    this->trackHeight = trackHeight;
    this->setMinimumHeight( this->getMinimumHeight() );
}

void PianorollContent::paintMeasureLines( QPainter *g, QRect visibleArea )
{
    int top = visibleArea.y();
    int bottom = getYFromNoteNumber( NOTE_MIN - 1, trackHeight );
    int left = visibleArea.x();
    int right = left + visibleArea.width();
    tick_t tickAtScreenRight = (tick_t)getTickFromX( right );
    measureLineIterator->reset( tickAtScreenRight );

    QColor barColor( 161, 157, 136 );
    QColor beatColor( 209, 204, 172 );
    while( measureLineIterator->hasNext() ){
        MeasureLine line = measureLineIterator->next();
        int x = getXFromTick( line.tick );
        if( x < left ){
            continue;
        }else if( right < x ){
            break;
        }
        if( line.isBorder ){
            g->setPen( barColor );
        }
        g->drawLine( x, top, x, bottom );
        if( line.isBorder ){
            g->setPen( beatColor );
        }
    }
}

void PianorollContent::paintSongPosition( QPainter *g, QRect visibleArea )
{
    int x = getXFromTick( songPosition );
    g->setPen( QColor( 0, 0, 0 ) );
    g->drawLine( x, visibleArea.top(), x, visibleArea.bottom() );
}

QRect PianorollContent::getVisibleArea()
{
    QRect rect = this->getPaintArea();
    return QRect( rect.x() + 1, rect.y() + 1, rect.width() - 2, rect.height() - 2 );
}

QRect PianorollContent::getPaintArea()
{
    QScrollArea *scroll = (QScrollArea *)this->parent();
    if( scroll ){
        QRect rect = scroll->childrenRect();
        int x = -rect.x() - 1;
        int y = -rect.y() - 1;
        int width = scroll->width() + 2;
        int height = scroll->height() + 2;
        return QRect( x, y, width, height );
    }else{
        return QRect( -1, -1, this->width() + 2, this->height() + 2 );
    }
}

int PianorollContent::getXFromTick( tick_t tick ){
    return (int)(tick * pixelPerTick) + 5;
}

int PianorollContent::getYFromNoteNumber( int noteNumber, int trackHeight ){
    return (NOTE_MAX - noteNumber) * trackHeight;
}

int PianorollContent::getNoteNumberFromY( int y, int trackHeight )
{
    return NOTE_MAX - (int)::floor( (double)(y / trackHeight) );
}

double PianorollContent::getTickFromX( int x )
{
    return (x - 5) / pixelPerTick;
}

int PianorollContent::getNoteModuration( int noteNumber )
{
    return ((noteNumber % 12) + 12) % 12;
}

int PianorollContent::getNoteOctave( int noteNumber )
{
    int modura = getNoteModuration( noteNumber );
    return (noteNumber - modura) / 12 - 2;
}

void PianorollContent::setPianoroll( Pianoroll *pianoroll )
{
    this->pianoroll = pianoroll;
}

void PianorollContent::setSongPosition( tick_t songPosition )
{
    this->songPosition = songPosition;
}

tick_t PianorollContent::getSongPosition()
{
    return songPosition;
}
