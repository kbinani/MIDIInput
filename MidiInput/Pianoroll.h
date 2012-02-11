#ifndef PIANOROLL_H
#define PIANOROLL_H

#include <vector>
#include <QWidget>
#include "PianorollItem.h"

namespace Ui {
    class Pianoroll;
}

class Pianoroll : public QWidget
{
    Q_OBJECT

private:
    std::vector<PianorollItem *> *items;
    Ui::Pianoroll *ui;

public:
    explicit Pianoroll(QWidget *parent = 0);
    ~Pianoroll();
    void setItems( std::vector<PianorollItem *> *aItems );
    void paintEvent( QPaintEvent *e );

private:
    QRect getVisibleArea();
};

#endif // PIANOROLL_H
