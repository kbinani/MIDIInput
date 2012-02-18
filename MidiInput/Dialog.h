#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>
#include <TimesigList.h>
#include "MidiInputReceiver.h"

namespace Ui {
    class Dialog;
}

class Dialog : public QDialog, public MidiInputReceiver
{
    Q_OBJECT

private:
    Ui::Dialog *ui;

    /**
     * @brief テンポ変更
     */
    VSQ_NS::TimesigList *timesigList;

    /**
     * 左右キーを押した際に、ソングポジションが移動する量
     */
    VSQ_NS::tick_t stepUnit;

    /**
     * @brief MIDI 入力が開始されたかどうか
     */
    bool inputStarted;

    /**
     * @brief MIDI 入力しているチャンネル番号
     */
    int channel;

public:
    explicit Dialog( QWidget *parent = 0 );

    ~Dialog();

    void keyPressEvent( QKeyEvent *e );
    
    void send( unsigned char b1, unsigned char b2, unsigned char b3 );

private slots:
    void on_pushButtonInputToggle_clicked();

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
    /**
     * MIDI 入力開始が要求されたとき呼ばれる
     * @param channel MIDI 入力ポート番号
     */
    void inputStartRequired( int channel );

    /**
     * MIDI 入力終了が要求されたとき呼ばれる
     */
    void inputStopRequired();
};

#endif // DIALOG_H
