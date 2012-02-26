#ifndef __Settings_h__
#define __Settings_h__

#include <map>
#include <Qt>

class Settings
{
protected:
    /**
     * @brief ツールボタンのショートカット
     */
    static std::map<Qt::Key, std::string> toolButtonShortcut;

public:
    /**
     * @brief ツールボタンのショートカットを取得する
     * @return ショートカットキーをキーとする、ツールボタンの名前の連想配列
     */
    static std::map<Qt::Key, std::string> *getToolButtonShortcut();

protected:
    Settings()
    {
    }
};

#endif
