#ifndef __Robot_h__
#define __Robot_h__

class Robot{
public:
    /**
     * 早送りボタンを押す
     */
    static void forward();

    /**
     * 巻き戻しボタンを押す
     */
    static void backward();

    /**
     * @brief Job Plugin 実行中に表示される"Running JobPlugin ..."ウィンドウ内の、"Cancel"ボタンを無効化する
     */
    static void disablePluginCancelButton();

private:
    Robot(){
    }
};

#endif
