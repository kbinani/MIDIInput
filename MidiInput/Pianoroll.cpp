#include "sstream"
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
    this->trackHeight = 14;
    this->pixelPerTick = 0.2;

    this->defaultTimesigList.push( Timesig( 4, 4, 0 ) );
    this->measureLineIterator = new MeasureLineIterator( &defaultTimesigList );

    // キーボードのキーの音名を作成
    char *names[] = { "C", "C#", "D", "Eb", "E", "F", "F#", "G", "G#", "A", "Bb", "B" };
    for( int noteNumber = 0; noteNumber < 128; noteNumber++ ){
        int modura = noteNumber % 12;
        int order = (noteNumber - modura) / 12 - 2;
        char *name = names[modura];
        ostringstream oss;
        oss << name << order;
        this->keyNames[noteNumber] = QString( oss.str().c_str() );
    }
}

Pianoroll::~Pianoroll()
{
    delete ui;
}

void Pianoroll::paintEvent( QPaintEvent * ){
    QPainter p( this );

    QRect visibleArea = this->getVisibleArea();

    QRect geometry = this->geometry();
    paintBackground( &p, visibleArea );

    paintMeasureLines( &p, visibleArea );

    paintItems( &p, visibleArea );

    paintKeyboard( &p, geometry, visibleArea );
}

void Pianoroll::paintBackground( QPainter *g, QRect visibleArea ){
    // 背景
    int width = this->width();
    int height = this->height();
    g->fillRect( 0, 0, width, height, QColor( 240, 240, 240 ) );

    // 黒鍵
    int y = 128 * trackHeight;
    int modura = -1;
    for( int noteNumber = 0; noteNumber < 128; noteNumber++ ){
        y -= trackHeight;
        modura++;
        if( modura == 12 ){
            modura = 0;
        }

        if( visibleArea.y() + visibleArea.height() < y ){
            continue;
        }

        // 黒鍵
        if( modura == 1 || modura == 3 || modura == 6 || modura == 8 || modura == 10 ){
            g->fillRect( visibleArea.x() + keyWidth,
                         y,
                         visibleArea.width() - keyWidth,
                         trackHeight + 1,
                         QColor( 212, 212, 212 ) );
        }

        // 白鍵が隣り合う部分に境界線を書く
        if( modura == 11 || modura == 4 ){
            g->setPen( QColor( 210, 203, 173 ) );
            g->drawLine( visibleArea.x() + keyWidth,
                         y,
                         visibleArea.x() + visibleArea.width(),
                         y );
        }

        if( y < 0 ){
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

void Pianoroll::paintKeyboard( QPainter *g, QRect geometry, QRect visibleArea ){
    g->fillRect( visibleArea.x(),
                 visibleArea.y(),
                 keyWidth,
                 visibleArea.height(),
                 QColor( 240, 240, 240 ) );
    int y = 128 * trackHeight;
    int modura = -1;
    int order = -2;
    QColor keyNameColor = QColor( 72, 77, 98 );
    QColor blackKeyColor = QColor( 125, 123, 124 );
    for( int noteNumber = 0; noteNumber < 128; noteNumber++ ){
        y -= trackHeight;
        modura++;
        if( modura == 12 ){
            modura = 0;
            order++;
        }

        // C4 などの表示を描画
        if( modura == 0 ){
            g->setPen( keyNameColor );
            g->drawText( visibleArea.x() + 42, y + trackHeight - 1, keyNames[noteNumber] );
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
                 visibleArea.y() + visibleArea.height() );
}

void Pianoroll::setItems( std::vector<PianorollItem *> *items, TimesigList *timesigList ){
    this->items = items;
    this->timesigList = timesigList;
    if( this->measureLineIterator ){
        delete this->measureLineIterator;
    }
    this->measureLineIterator = new MeasureLineIterator( this->timesigList );
}

void Pianoroll::paintMeasureLines( QPainter *g, QRect visibleArea )
{
    int top = visibleArea.y();
    int bottom = top + visibleArea.height();
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
    QRect rect = scroll->childrenRect();
    int x = -rect.x();
    int y = -rect.y();
    int width = scroll->width();
    int height = scroll->height();
    return QRect( x, y, width, height );
}

int Pianoroll::getXFromTick( long int tick ){
    return (int)(tick * pixelPerTick) + keyWidth;
}

int Pianoroll::getYFromNoteNumber( int noteNumber ){
    return (127 - noteNumber) * trackHeight;
}

double Pianoroll::getTickFromX( int x )
{
    return (x - keyWidth) / pixelPerTick;
}
