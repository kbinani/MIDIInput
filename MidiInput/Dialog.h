/**
 * Dialog.h
 * Copyright © 2012 kbinani
 *
 * This file is part of `MIDIInput UG Job Plugin'.
 *
 * `MIDIInput UG Job Plugin' is free software; you can redistribute it and/or
 * modify it under the terms of the BSD License.
 *
 * `MIDIInput UG Job Plugin' is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 */
#ifndef DIALOG_H
#define DIALOG_H

#include <map>
#include <QDialog>
#include <QMutex>
#include <QToolButton>
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
    /**
     * @brief ソングポジションの移動に伴って自動スクロールするかどうか
     */
    bool autoScroll;

    /**
     * @brief MIDI 入力しているチャンネル番号
     */
    int channel;

    /**
     * @brief MIDI 入力が開始されたかどうか
     */
    bool inputStarted;

    /**
     * @brief 休符を入力している状態であれば true
     */
    bool isRest;

    /**
     * @brief 描画対象のリスト
     */
    std::map<VSQ_NS::tick_t, PianorollItem *> *items;

    VSQ_NS::tick_t musicalPartOffset;

    /**
     * @brief items フィールドに更新をかけるときに使用するミューテックス
     */
    QMutex *mutex;

    /**
     * 左右キーを押した際に、ソングポジションが移動する量
     */
    VSQ_NS::tick_t stepUnit;

    /**
     * @brief テンポ変更
     */
    VSQ_NS::TimesigList *timesigList;

    /**
     * @brief ツールボタンのショートカットキーと、対応するコンポーネントとの紐付けを格納
     */
    std::map<Qt::Key, QToolButton *> toolButtonShortcut;

    Ui::Dialog *ui;

public:
    /**
     * @brief コンストラクタ
     * @param eventText ノート情報を記録した文字列
     * @param timesigText 拍子変更情報を記録した文字列
     * @param musicalPartOffset Musical Part と曲頭とのオフセット
     * @param parent ダイアログの親
     */
    explicit Dialog( const std::string eventText, const std::string timesigText, VSQ_NS::tick_t musicalPartOffset, QWidget *parent = 0 );

    ~Dialog();

    /**
     * @brief 編集結果のノート情報を記録した文字列を取得する
     * @return 音符情報を記録した文字列
     */
    const std::string getEventText();

    void keyPressEvent( QKeyEvent *e );
    
    void send( unsigned char b1, unsigned char b2, unsigned char b3 );

signals:
    /**
     * @brief スレッドセーフに画面の再描画を行うためのシグナル
     */
    void doRepaint();

private slots:
    /**
     * @brief ソングポジションの位置を初期化する
     */
    void initSongPosition();

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
     * @brief ソングポジションに一番近い音符のノート番号を取得する
     * @param items 音符のリスト
     * @param songPosition ソングポジション
     * @return ノート番号
     */
    int findNearestNoteNumber( std::map<VSQ_NS::tick_t, PianorollItem *> *items, VSQ_NS::tick_t songPosition );

    /**
     * @brief 現在のエディタウィンドウのソングポジションを取得する
     * @param timesigList 拍子情報
     * @param musicalPartOffset オフセット
     * @return ソングポジション
     */
    VSQ_NS::tick_t getSongPosition( VSQ_NS::TimesigList *timesigList, VSQ_NS::tick_t musicalPartOffset );

    /**
     * @brief ツールボタンのショートカットキーと、対応するコンポーネントの紐付けを初期化。
     * toolButtonShortcut フィールドの値を初期化する
     */
    void initToolButtonShortcut();

    /**
     * MIDI 入力開始が要求されたとき呼ばれる
     * @param channel MIDI 入力ポート番号
     */
    void inputStartRequired( int channel );

    /**
     * MIDI 入力終了が要求されたとき呼ばれる
     */
    void inputStopRequired();

    /**
     * @brief ソングポジションを現在のクオンタイズに基づいて移動する
     * @param isForward 曲末方向へ移動する場合は true を、曲頭方向へ移動する場合は false を設定する
     */
    void moveSongPosition( bool isForward );
};

#endif // DIALOG_H
