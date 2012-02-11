#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>
#include "DialogListener.h"

namespace Ui {
    class Dialog;
}

class Dialog : public QDialog
{
    Q_OBJECT

public:
    DialogListener *listener;

public:
    explicit Dialog( DialogListener *listener, QWidget *parent = 0 );
    ~Dialog();
    
private slots:
    void on_pushButtonStart_clicked();

    void on_pushButtonStop_clicked();

private:
    Ui::Dialog *ui;
};

#endif // DIALOG_H
