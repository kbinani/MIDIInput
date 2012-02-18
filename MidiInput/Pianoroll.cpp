#include "Pianoroll.h"
#include "ui_Pianoroll.h"
#include <sstream>
#include <QScrollBar>

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
    ui->content->setSongPosition( songPosition );
}

tick_t Pianoroll::getSongPosition()
{
    return ui->content->getSongPosition();
}

void Pianoroll::setTimesigList( TimesigList *timesigList )
{
    ui->content->setTimesigList( timesigList );
}

void Pianoroll::repaint()
{
    ui->content->repaint();
    ui->keyboard->repaint();
    QWidget::repaint();
}
