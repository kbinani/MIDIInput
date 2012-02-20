#ifndef DIALOG_H
#define DIALOG_H

#include <map>
#include <QDialog>
#include <QMutex>
#include <TimesigList.h>
#include "MidiInputReceiver.h"
#include "PianorollItem.h"

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
     * @brief 描画対象のリスト
     */
    std::map<VSQ_NS::tick_t, PianorollItem *> *items;

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

    /**
     * @brief 休符を入力している状態であれば true
     */
    bool isRest;

    /**
     * @brief items フィールドに更新をかけるときに使用するミューテックス
     */
    QMutex *mutex;

    /**
     * @brief ソングポジションの移動に伴って自動スクロールするかどうか
     */
    bool autoScroll;

    /**
     * @brief メタテキスト
     */
    std::string metaText;

public:
    /**
     * @brief コンストラクタ
     * @param eventText ノート情報を記録したメタテキスト
     * @param ダイアログの親
     */
    explicit Dialog( const std::string eventText, const std::string timesigText, QWidget *parent = 0 );

    ~Dialog();

    void keyPressEvent( QKeyEvent *e );
    
    void send( unsigned char b1, unsigned char b2, unsigned char b3 );

    /**
     * @brief 編集結果のメタテキストを取得する
     * @return メタテキスト
     */
    const std::string getMetaText();

signals:
    /**
     * @brief スレッドセーフに画面の再描画を行うためのシグナル
     */
    void doRepaint();

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

    /**
     * @brief 画面の再描画を行う
     */
    void onRepaintRequired();

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
