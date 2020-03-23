#include "styleapp.h"

QString StyleApp::getMainDarkBackground()
{
    return "background:rgba(62, 62, 62, 0.5);"
           "color: #fff; "
           "border: 2px solid #000;"
           "padding: 10px;";
}

QString StyleApp::getDarkBtnStyle()
{
    return "QPushButton {"
           "background:#3d3d3d;"
           "color: #fff;"
           "}"
           "QPushButton:hover { "
           "background:#5B5B5B;"
           "color: #fff;"
           "}";
};

QString StyleApp::getTitleEdit()
{
    return "QGroupBox {"
           "font-size: 18px;"
           "color: #fff;"
           "margin: 5px;"
           "}";
}


QString StyleApp::getDarkBtnMaximize()
{
    return "QPushButton {"
           "background:#3d3d3d;"
           "background-image: url(:/image/window-maximize-gray.png);"
           "background-repeat: no-repeat; margin: 0px;"
           "}"
           "QPushButton:hover { "
           "background:#5B5B5B;"
           "background-image: url(:/image/window-maximize-gray.png);"
           "background-repeat: no-repeat; margin: 0px;"
           "color: #fff;"
           "}";
}

QString StyleApp::getDarlBtnRestore()
{
    return "QPushButton {"
           "background:#3d3d3d;"
           "background-image: url(:/image/window-restore-gray.png);"
           "background-repeat: no-repeat; margin: 0px;"
           "}"
           "QPushButton:hover { "
           "background:#5B5B5B;"
           "background-image: url(:/image/window-restore-gray.png);"
           "background-repeat: no-repeat; margin: 0px;"
           "color: #fff;"
           "}";
}

QString StyleApp::getDarkBtnMinimize()
{
    return "QPushButton {"
           "background:#3d3d3d;"
           "background-image: url(:/image/window-minimize-gray.png);"
           "}"
           "QPushButton:hover { "
           "background:#5B5B5B;"
           "background-image: url(:/image/window-minimize-gray.png);"
           "color: #fff;"
           "}";
}

QString StyleApp::getDarkBtnClose()
{
    return "QPushButton {"
           "background:#3d3d3d;"
           "background-image: url(:/image/close-gray.png);"
           "}"
           "QPushButton:hover { "
           "background:#5B5B5B;"
           "background-image: url(:/image/close-gray.png);"
           "color: #fff;"
           "}";
}

QString StyleApp::getDarkContextMenu()
{
    return "QMenu {"
           "background:#2f2f2f;"
           "color: #fff;"
           "border: 2px solid #000;"
           "padding: 10px;"
           "font-size: 20px;"
           "text-align: center;"
           "}"
           "QMenu::item:selected {"
           "padding: 10px;"
           "background: #373737;"
           "}";
}

QString StyleApp::getDarkMessageBoardList()
{
    return "QListView {"
           "background:#3d3d3d;"
           ""
           "}";
}

QString StyleApp::getDarkLineEdit()
{
    return "background:#3d3d3d;"
           "color: #fff";
}

QString StyleApp::getDarkMessageBoardItem()
{
    return  "QListView::item {"
            "background:#3d3d3d;"
            "color: #fff;"
            "border: 2px solid #5B5B5B;"
            "border-radius: 10px;"
            "}"
            "QListView::item::hover  {"
            "background:#5B5B5B;"
            "color: #fff;"
            "border: 2px solid #3d3d3d;"
            "border-radius: 10px;"
            "}"
            "QListView::item:selected {"
            "border: 1px solid #6a6ea9;"
            "border-radius: 10px;"
            "}";
}

QString StyleApp::getInvisibleStyle()
{
    return "background: transparent; "
           "border-color: transparent;";
}

QString StyleApp::getLogoPolytech()
{
//    return "<img src=\":/image/icon.ico\"/>";
    return ":/image/screeen_top.ico";
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


