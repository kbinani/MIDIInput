#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>
#include <TimesigList.h>
#include "DialogListener.h"

namespace Ui {
    class Dialog;
}

class Dialog : public QDialog
{
    Q_OBJECT

public:
    DialogListener *listener;

private:
    /**
     * @brief テンポ変更
     */
    VSQ_NS::TimesigList *timesigList;

    /**
     * 左右キーを押した際に、ソングポジションが移動する量
     */
    VSQ_NS::tick_t stepUnit;

public:
    explicit Dialog( DialogListener *listener, QWidget *parent = 0 );
    ~Dialog();
    void keyPressEvent( QKeyEvent *e );
    
private slots:
    void on_pushButtonStart_clicked();

    void on_pushButtonStop_clicked();

    void on_toolButtonNote001_toggled(bool checked);

    void on_toolButtonNote002_toggled(bool checked);

    void on_toolButtonNote004_toggled(bool checked);

    void on_toolButtonNote008_toggled(bool checked);

    void on_toolButtonNote016_toggled(bool checked);

    void on_toolButtonRest001_toggled(bool checked);

    void on_toolButtonRest002_toggled(bool checked);

    void on_toolButtonRest004_toggled(bool checked);

    void on_toolButtonRest008_toggled(bool checked);

    void on_toolButtonRest016_toggled(bool checked);

private:
    Ui::Dialog *ui;
};

#endif // DIALOG_H
