#include "styleapp.h"

QString StyleApp::getMainDarkBackground()
{
    return "background:rgba(62, 62, 62, 0.5);"
           "color: #fff; border: 2px solid #000;"
           "padding: 10px;";
}

QString StyleApp::getDarkBtnStyle()
{
    return "background:#3d3d3d;"
            "color: #fff;";
};

QString StyleApp::getDarkBtnMaximize()
{
    return "background:#3d3d3d;"
           "background-image: url(:/image/window-maximize-gray.png);"
           "background-repeat: no-repeat; margin: 0px;";
}

QString StyleApp::getDarlBtnRestore()
{
    return "background:#3d3d3d;"
           "background-image: url(:/image/window-restore-gray.png); "
           "background-repeat: no-repeat; margin: 0px;";
}

QString StyleApp::getDarkBtnMinimize()
{
    return "background:#3d3d3d; "
           "background-image: url(:/image/window-minimize-gray.png);";
}

QString StyleApp::getDarkBtnClose()
{
    return "background:#3d3d3d; "
           "background-image: url(:/image/close-gray.png);";
}

QString StyleApp::getInvisibleStyle()
{
    return "background: transparent; "
           "border-color: transparent;";
}

QString StyleApp::getLogoPolytech()
{
    return "<img src=\":/image/top_logo.png\"/>";
}

QString StyleApp::getBtnShowChatIcon()
{
    return ":/image/messagedef.png";
}

QString StyleApp::getBtnShowSettingIcon()
{
    return ":/image/settings-cogwheel-button.png";
}

QString StyleApp::getLogoBan()
{
    return ":/image/ban.png";
}

QString StyleApp::getLogoMute()
{
    return ":/image/mute.png";
}

QString StyleApp::getLogoStudent()
{
    return ":/image/student.png";
}

QString StyleApp::getLogoDefMessage()
{
    return ":/image/messagedef.png";
}

QString StyleApp::getLogoNewMessage()
{
    return ":/image/messageNew.png";
}

QString StyleApp::getDarkBtnDisable()
{
    return "background:#a0a0a0;";
}


