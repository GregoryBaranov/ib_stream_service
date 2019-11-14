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
#include <QPropertyAnimation>
#include <QThread>
#include <random>
#include <ctime>

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

    // для отслеживания состояния окна чата
    enum BellStatus{
        showChat,
        hideChat
    };

public:
    explicit MainWindow(QWidget *parent = nullptr); // явный конструктор
    ~MainWindow(); // деструктор

    template<class T1, class T2>
    bool checkUserInList(const list<T1> &lst, T2 username); // проверка есть юзер или нет
    void hide_all(QListWidget *listWidjet); // скрывает все не нужные элименты

public slots:
    void setPreviousPosition(QPoint previousPosition); // устанавливаем новую предыдущую позицию

signals:
    void previousPositionChanged(QPoint previousPosition); // новая предыдущая позиция

private:
    Ui::MainWindow *ui;

    Client* client;

    void btn_max();  // свёртывание и развертывание программы в маленький и большой режимы
    void mainApplicationDesigner(); // Дефолтный фид приложения
    void settingDesigner(); // Вид и проверки для hostEdit, spinPort, connect;

    // Переменная, от которой будем отталкиваться при работе с перемещением и изменением размера окна
    MouseType m_leftMouseButtonPressed; // enum значения курсора
    QPoint m_previousPosition; // предыдущая позиция

    // проверка состояния курсора и получение его внешнего вида
    MouseType checkResizableField(QMouseEvent *event);
    QPoint previousPosition() const; // получение предыдущей позиции

    QListWidgetItem *user_in_list; // выбранное значение из списка

    list<QString> mute_user_list; // список немых
    list<QString> bun_user_list; // cписок забаненных
    QStringList userList; // все пользователи

    BellStatus statusBell; // enum для проверки статуса окна
protected:
    // функции отслеживания мыши
    void mousePressEvent(QMouseEvent *event); // Позиция клика
    void mouseReleaseEvent(QMouseEvent *event); // Когда кнопка мыши отжата вызываем ->
    void mouseMoveEvent(QMouseEvent *event); // Изменение размера (тут отслеживают клик и конечное состояние окна)

private slots:
    void onReceiveMessage(QString message); // Слот для получения сообщения
    void onNumberSession(QString session);
    void onFailedConnect();
    void onConnectBtnClick(); // Слот для кнопки соединения с сервером
    void onDisconnectBtnClick(); // Слот для кнопки отключения от сервера (можно удалить)
    void onSendMessageBtnClick(); // Слот для кнопки отправки сообщения
    void on_Settings_clicked(); // Слот для отображения/скрытия меню настроек
    void on_btn_close_clicked(); // Слот для отключения от сервера
    void on_DarkDesign_clicked(); // Слот для переключения на темную тему
    void on_WhiteDesign_clicked(); // Слот для переключения на светлую тему
    void on_BtnUserControl_clicked(); // Слот отображения списка пользоватеей
    void on_To_Ban_Button_clicked(); // Слот для бана пользователей
    void on_Mute_Button_clicked(); // Слот для мьюта пользователей
    void on_ShowBlacklist_clicked();// Слот для отображения черного списка (забаненых)
    void slot_UnbrokenUser(QListWidgetItem*); // Слот разбана
    void slot_UnMuteUser(QListWidgetItem*); // Слот размьюта
    void on_lineSearchUserList_textChanged(const QString &arg1); // при вызове определенного сигнала делаем поиск
    void on_lineSearchBanUserList_textChanged(const QString &arg1); // при вызове определенного сигнала делаем поиск
    void on_ChatBtn_clicked(); // Скрытие чата
    void on_messageBoard_textChanged();// при вызове определенного сигнала что-то делаем.....
    void on_StartSession_clicked();
    void on_StopSession_clicked();
};

#endif // MAINWINDOW_H