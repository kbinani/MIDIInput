#include <sstream>
#include <math.h>
#include "Pianoroll.h"
#include "QScrollArea"
#include "QPainter"
#include "ui_Pianoroll.h"

using namespace std;
using namespace cadencii::vsq;

Pianoroll::Pianoroll(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Pianoroll)
{
    ui->setupUi(this);
    this->items = NULL;
    this->keyWidth = 68;
    this->trackHeight = DEFAULT_TRACK_HEIGHT;
    this->pixelPerTick = 0.2;

    this->defaultTimesigList.push( Timesig( 4, 4, 0 ) );
    this->measureLineIterator = new MeasureLineIterator( &defaultTimesigList );
    this->setMouseTracking( true );

    // キーボードのキーの音名を作成
    this->keyNames = new QString[NOTE_MAX - NOTE_MIN + 1];
    char *names[] = { "C", "C#", "D", "Eb", "E", "F", "F#", "G", "G#", "A", "Bb", "B" };
    for( int noteNumber = NOTE_MIN; noteNumber <= NOTE_MAX; noteNumber++ ){
        int modura = getNoteModuration( noteNumber );
        int order = getNoteOctave( noteNumber );
        char *name = names[modura];
        ostringstream oss;
        oss << name << order;
        this->keyNames[noteNumber - NOTE_MIN] = QString( oss.str().c_str() );
    }
}

Pianoroll::~Pianoroll()
{
    delete ui;
    delete [] keyNames;
    delete measureLineIterator;
}

int Pianoroll::getMinimumHeight()
{
    return this->trackHeight * (NOTE_MAX - NOTE_MIN + 1);
}

void Pianoroll::paintEvent( QPaintEvent * ){
    int minimumHeight = this->getMinimumHeight();
    if( this->minimumHeight() != minimumHeight ){
        this->setMinimumHeight( minimumHeight );
    }
    QPainter p( this );

    QRect visibleArea = this->getVisibleArea();

    paintBackground( &p, visibleArea );
    paintMeasureLines( &p, visibleArea );
    paintItems( &p, visibleArea );
    paintKeyboard( &p, visibleArea );
}

void Pianoroll::paintBackground( QPainter *g, QRect visibleArea ){
    // 背景
    int height = getYFromNoteNumber( NOTE_MIN - 1 ) - visibleArea.y();
    g->fillRect( visibleArea.x(), visibleArea.y(),
                 visibleArea.width(), height,
                 QColor( 240, 240, 240 ) );

    // 黒鍵
    for( int noteNumber = NOTE_MIN; noteNumber <= NOTE_MAX; noteNumber++ ){
        int y = getYFromNoteNumber( noteNumber );
        int modura = getNoteModuration( noteNumber );

        if( visibleArea.y() + visibleArea.height() < y ){
            continue;
        }

        // 黒鍵
        if( modura == 1 || modura == 3 || modura == 6 || modura == 8 || modura == 10 ){
            g->fillRect( visibleArea.x() + keyWidth, y,
                         visibleArea.width() - keyWidth, trackHeight + 1,
                         QColor( 212, 212, 212 ) );
        }

        // 白鍵が隣り合う部分に境界線を書く
        if( modura == 11 || modura == 4 ){
            g->setPen( QColor( 210, 203, 173 ) );
            g->drawLine( visibleArea.x() + keyWidth, y,
                         visibleArea.x() + visibleArea.width(), y );
        }

        if( y < visibleArea.y() ){
            break;
        }
    }
}

void Pianoroll::paintItems( QPainter *g, QRect visibleArea ){
    if( items == NULL ){
        return;
    }
    int count = this->items->size();
    int height = trackHeight - 1;

    QColor fillColor = QColor( 181, 220, 86 );
    g->setPen( QColor( 125, 123, 124 ) );

    int visibleMinX = visibleArea.x() + keyWidth;
    int visibleMaxX = visibleArea.x() + visibleArea.width();
    int visibleMinY = visibleArea.y();
    int visibleMaxY = visibleArea.y() + visibleArea.height();

    for( int i = 0; i < count; i++ ){
        PianorollItem *item = items->at( i );
        int x = getXFromTick( item->tick );
        int width = getXFromTick( item->tick + item->length ) - x;

        if( visibleMinX <= x + width && x <= visibleMaxX ){
            int y = getYFromNoteNumber( item->noteNumber ) + 1;
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

void Pianoroll::mouseMoveEvent( QMouseEvent *e )
{
    this->repaint();
    QWidget::mouseMoveEvent( e );
}

void Pianoroll::paintKeyboard( QPainter *g, QRect visibleArea ){
    // カーソル位置でのノート番号を取得する
    QPoint cursor = QCursor::pos();
    QPoint pianoroll = getPositionOnScreen( this );
    int noteAtCursor = getNoteNumberFromY( cursor.y() - pianoroll.y() );

    int height = getYFromNoteNumber( NOTE_MIN - 1 ) - visibleArea.y();
    g->fillRect( visibleArea.x(), visibleArea.y(),
                 keyWidth, height,
                 QColor( 240, 240, 240 ) );
    QColor keyNameColor = QColor( 72, 77, 98 );
    QColor blackKeyColor = QColor( 125, 123, 124 );
    for( int noteNumber = NOTE_MIN; noteNumber <= NOTE_MAX; noteNumber++ ){
        int y = getYFromNoteNumber( noteNumber );
        int modura = getNoteModuration( noteNumber );

        // C4 などの表示を描画
        if( modura == 0 || noteAtCursor == noteNumber ){
            g->setPen( keyNameColor );
            g->drawText( visibleArea.x(), y,
                         keyWidth - 2, trackHeight,
                         Qt::AlignRight | Qt::AlignVCenter, keyNames[noteNumber - NOTE_MIN] );
        }

        // 鍵盤ごとの横線
        g->setPen( QColor( 212, 212, 212 ) );
        g->drawLine( visibleArea.x(), y, visibleArea.x() + keyWidth, y );

        // 黒鍵を描く
        if( modura == 1 || modura == 3 || modura == 6 || modura == 8 || modura == 10 ){
            g->fillRect( visibleArea.x(), y, 34, trackHeight + 1, blackKeyColor );
        }
    }

    // 鍵盤とピアノロール本体との境界線
    g->setPen( QColor( 212, 212, 212 ) );
    g->drawLine( visibleArea.x() + keyWidth,
                 visibleArea.y(),
                 visibleArea.x() + keyWidth,
                 visibleArea.y() + height );
}

void Pianoroll::setItems( std::vector<PianorollItem *> *items, TimesigList *timesigList ){
    this->items = items;
    this->timesigList = timesigList;
    if( this->measureLineIterator ){
        delete this->measureLineIterator;
    }
    this->measureLineIterator = new MeasureLineIterator( this->timesigList );
}

void Pianoroll::setTrackHeight( int trackHeight )
{
    this->trackHeight = trackHeight;
    this->setMinimumHeight( this->getMinimumHeight() );
}

void Pianoroll::paintMeasureLines( QPainter *g, QRect visibleArea )
{
    int top = visibleArea.y();
    int bottom = getYFromNoteNumber( NOTE_MIN - 1 );
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

QRect Pianoroll::getVisibleArea()
{
    QScrollArea *scroll = (QScrollArea *)this->parent();
    if( scroll ){
        QRect rect = scroll->childrenRect();
        int x = -rect.x();
        int y = -rect.y();
        int width = scroll->width();
        int height = scroll->height();
        return QRect( x, y, width, height );
    }else{
        return QRect( 0, 0, this->width(), this->height() );
    }
}

int Pianoroll::getXFromTick( tick_t tick ){
    return (int)(tick * pixelPerTick) + keyWidth;
}

int Pianoroll::getYFromNoteNumber( int noteNumber ){
    return (NOTE_MAX - noteNumber) * trackHeight;
}

int Pianoroll::getNoteNumberFromY( int y )
{
    return NOTE_MAX - (int)::floor( (double)(y / trackHeight) );
}

double Pianoroll::getTickFromX( int x )
{
    return (x - keyWidth) / pixelPerTick;
}

int Pianoroll::getNoteModuration( int noteNumber )
{
    return ((noteNumber % 12) + 12) % 12;
}

int Pianoroll::getNoteOctave( int noteNumber )
{
    int modura = getNoteModuration( noteNumber );
    return (noteNumber - modura) / 12 - 2;
}

void Pianoroll::getPosition( QWidget *widget, QPoint &p )
{
    if( widget->parent() != 0 ){
        QWidget *parent = (QWidget *)widget->parent();
        QRect rect = parent->geometry();
        p.setX( p.x() + rect.x() );
        p.setY( p.y() + rect.y() );
        getPosition( parent, p );
    }
}

QPoint Pianoroll::getPositionOnScreen( QWidget *widget )
{
    QRect rect = widget->geometry();
    QPoint p( rect.x(), rect.y() );
    getPosition( widget, p );
    return p;
}
