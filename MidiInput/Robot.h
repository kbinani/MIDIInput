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

private:
    Robot(){
    }
};

#endif
