#include "sstream"
#include "Pianoroll.h"
#include "QScrollArea"
#include "QPainter"
#include "ui_Pianoroll.h"

using namespace std;

Pianoroll::Pianoroll(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Pianoroll)
{
    ui->setupUi(this);
    this->items = NULL;
    this->keyWidth = 68;
    this->trackHeight = 14;

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

    int width = this->width();
    int height = this->height();
    QRect rect = this->getVisibleArea();

    paintKeyboard( &p, geometry(), rect );

    int margin = 10;
    p.fillRect( rect.x() + margin, rect.y() + margin, rect.width() - 2 * margin, rect.height() - 2 * margin, QColor( 200, 200, 200 ) );
    char text[5120];
    sprintf( text, "{x=%d, y=%d, width=%d, height=%d}", rect.x(), rect.y(), rect.width(), rect.height() );
    p.drawText( 200, 200, text );
}

void Pianoroll::paintKeyboard( QPainter *g, QRect geometry, QRect visibleArea ){
    if( visibleArea.x() < keyWidth ){
        g->fillRect( 0, 0, keyWidth, geometry.height(), QColor( 240, 240, 240 ) );
        int y = 128 * trackHeight;
        int dy = -trackHeight;
        int modura = -1;
        int order = -2;
        QColor keyNameColor = QColor( 72, 77, 98 );
        QColor blackKeyColor = QColor( 125, 123, 124 );
        for( int noteNumber = 0; noteNumber < 128; noteNumber++ ){
            y += dy;
            modura++;
            if( modura == 12 ){
                modura = 0;
                order++;
            }

            // C4 などの表示を描画
            if( modura == 0 ){
                g->setPen( keyNameColor );
                g->drawText( 42, y + trackHeight, keyNames[noteNumber] );
            }

            // 黒鍵を描く
            if( modura == 1 || modura == 3 || modura == 6 || modura == 8 || modura == 10 ){
                g->fillRect( 0, y, 34, trackHeight, blackKeyColor );
            }
        }
    }
}

void Pianoroll::setItems( std::vector<PianorollItem *> *items ){
    this->items = items;
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
