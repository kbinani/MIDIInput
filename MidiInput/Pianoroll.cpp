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
