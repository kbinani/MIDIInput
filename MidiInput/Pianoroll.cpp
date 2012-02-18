#include <sstream>
#include <QScrollBar>
#include "Pianoroll.h"
#include "PianorollContent.h"
#include "ui_Pianoroll.h"

using namespace std;
using namespace cadencii::vsq;

Pianoroll::Pianoroll( QWidget *parent ) :
    QWidget( parent ),
    ui( new Ui::Pianoroll )
{
    ui->setupUi( this );
    ui->scrollArea->setBackgroundRole( QPalette::Dark );
    ui->scrollArea->setPianoroll( this );
    ui->content->setPianoroll( this );
    ui->keyboard->setPianoroll( this );
    ui->keyboard->notifyVerticalScroll( 0 );
    autoScroll = true;
}

void Pianoroll::notifyVerticalScroll()
{
    QRect rect = ui->content->getVisibleArea();
    ui->keyboard->notifyVerticalScroll( rect.y() );
}

void Pianoroll::setTrackHeight( int trackHeight )
{
    ui->content->setTrackHeight( trackHeight );
    ui->keyboard->setTrackHeight( trackHeight );
}

void Pianoroll::setSongPosition( tick_t songPosition )
{
    tick_t lastSongPosition = ui->content->getSongPosition();
    ui->content->setSongPosition( songPosition );
    if( autoScroll ){
        int x = ui->content->getXFromTick( songPosition );
        QRect visibleArea = ui->content->getVisibleArea();
        QScrollBar *scrollBar = ui->scrollArea->horizontalScrollBar();
        int dx = 0;
        if( lastSongPosition < songPosition ){
            // 右へ移動した場合
            if( visibleArea.right() < x ){
                dx = ui->scrollArea->width() - (x - visibleArea.right());
            }
        }else{
            // 左へ移動した場合
            if( x < visibleArea.left() ){
                dx = -ui->scrollArea->width() + (visibleArea.left() - x);
            }
        }
        if( dx ){
            int value = scrollBar->value() + dx;
            if( value < scrollBar->minimum() ){
                scrollBar->setValue( scrollBar->minimum() );
            }else if( scrollBar->maximum() < value ){
                scrollBar->setValue( scrollBar->maximum() );
            }else{
                scrollBar->setValue( scrollBar->value() + dx );
            }
        }
    }
}

tick_t Pianoroll::getSongPosition()
{
    return ui->content->getSongPosition();
}

void Pianoroll::setTimesigList( TimesigList *timesigList )
{
    ui->content->setTimesigList( timesigList );
}

void Pianoroll::setItems( vector<PianorollItem *> *items )
{
    ui->content->setItems( items );
}

void Pianoroll::repaint()
{
    ui->content->repaint();
    ui->keyboard->repaint();
    QWidget::repaint();
}

void Pianoroll::setMutex( QMutex *mutex )
{
    ui->content->setMutex( mutex );
}

void Pianoroll::setAutoScroll( bool autoScroll )
{
    this->autoScroll = autoScroll;
}
