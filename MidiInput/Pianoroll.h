#ifndef PIANOROLL_H
#define PIANOROLL_H

#include <vector>
#include <QScrollArea>
#include <MeasureLineIterator.h>
#include <TimesigList.h>
#include "PianorollItem.h"
#include "PianorollContent.h"
#include "PianorollKeyboard.h"

namespace Ui{
    class Pianoroll;
}

class Pianoroll : public QWidget
{
    Q_OBJECT

public:
    Ui::Pianoroll *ui;

    explicit Pianoroll( QWidget *parent = 0 );

    /**
     * スクロール領域が縦方向にスクロールしたことを子→親に通知する
     */
    void notifyVerticalScroll();

    void setTrackHeight( int trackHeight );
};


#endif // PIANOROLL_H
