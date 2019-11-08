#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "client.h"
#include <QPushButton>
#include <QLineEdit>
#include <QTextEdit>
#include <QListWidget>
#include <QLabel>
#include <list>
#include <QStandardItemModel>
#include <QMouseEvent>
#include <QMessageBox>
#include <QInputDialog>
#include <QFileDialog>
#include <QDir>
#include <QGraphicsDropShadowEffect>
#include <QToolButton>
#include <QRegExp>
#include <QRegExpValidator>

using namespace std;

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
    // Свойство с точкой предыдущей позиции мыши
    // Относительно данной точки идёт пересчёт позиции окна
    // Или размеров окна. При этом свойство устанавливается при нажатии мыши
    // по окну и в ряде иных случаев
    Q_PROPERTY(QPoint previousPosition READ previousPosition WRITE setPreviousPosition NOTIFY previousPositionChanged)

    // тип клика мыши, при перемещении курсора по этому типу будем определять
    // что именно нужно сделать, перенести окно, или изменить его размер с одной из сторон
    enum MouseType {
        None = 0,
        Top,
        Bottom,
        Left,
        Right,
        Move
    };
public:
    explicit MainWindow(QWidget *parent = nullptr); // явный конструктор
    ~MainWindow();

    QPoint previousPosition() const;

    template<class T1, class T2>
    bool checkUserInList(const list<T1> &lst, T2 username)
    {
        for (auto i = lst.cbegin(); i != lst.cend(); i++)
        {
            if (username == *i)
            {
                return true;
            }
            else
            {
                continue;
            }
        }
        return false;
    }

    void hide_all(QListWidget *listWidjet);

public slots:
    void setPreviousPosition(QPoint previousPosition);

signals:
    void previousPositionChanged(QPoint previousPosition);

private:
    Ui::MainWindow *ui;

    Client* client;

    // Кнопка каоторая отвечает за свёртывание и развертывание
    // программы в маленький и большой режимы
    void btn_max();

    void mainApplicationDesigner(); // Дефолтный фид приложения
    void settingDesigner(); // Вид и проверки для hostEdit, spinPort, connect;

    // Переменная, от которой будем отталкиваться при работе с перемещением и изменением размера окна
    MouseType m_leftMouseButtonPressed;
    QPoint m_previousPosition;
    QMouseEvent *mouseEv;
    MouseType checkResizableField(QMouseEvent *event);
    QListWidgetItem *user_in_list;

    list<QString> mute_user_list;
    list<QString> bun_user_list;
    QStringList userList;

protected:
    void mousePressEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);

private slots:
    void onReceiveMessage(QString message); // Слот для получения сообщения
    void onConnectBtnClick(); // Слот для кнопки соединения с сервером
    void onDisconnectBtnClick(); // Слот для кнопки отключения от сервера (можно удалить)
    void onSendMessageBtnClick(); // Слот для кнопки отправки сообщения
    void on_Settings_clicked(); // Слот для отображения/скрытия меню настроек
    void on_btn_close_clicked(); // Слот для отключения от сервера
    void on_DarkDesign_clicked(); // Слот для переключения на темную тему
    void on_WhiteDesign_clicked(); // Слот для переключения на светлую тему
    void on_BtnUserControl_clicked();
    void on_To_Ban_Button_clicked();
    void on_Mute_Button_clicked();
    void on_ShowBlacklist_clicked();
    void slot_UnbrokenUser(QListWidgetItem*);
    void slot_UnMuteUser(QListWidgetItem*);

    void on_lineSearchUserList_textChanged(const QString &arg1);
    void on_lineSearchBanUserList_textChanged(const QString &arg1);
};

#endif // MAINWINDOW_H
