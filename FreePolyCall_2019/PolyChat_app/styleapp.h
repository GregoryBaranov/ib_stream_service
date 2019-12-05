#ifndef STYLEAPP_H
#define STYLEAPP_H

#include <QString>

class StyleApp
{
public:
    static QString getMainDarkBackground();
    static QString getDarkBtnStyle();
    static QString getDarkBtnMaximize();
    static QString getDarkBtnMinimize();
    static QString getDarkBtnClose();
    static QString getDarkBtnDisable();

    //******************************************

    static QString getBtnShowChatIcon();
    static QString getBtnShowSettingIcon();
    static QString getInvisibleStyle();
    static QString getLogoPolytech();
    static QString getLogoDefMessage();
    static QString getLogoNewMessage();

    //******************************************
    static QString getLogoBan();
    static QString getLogoMute();
    static QString getLogoStudent();
};

#endif // STYLEAPP_H
