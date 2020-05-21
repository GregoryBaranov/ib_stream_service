#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "popup.h"
#include "client.h"
#include <QPushButton>
#include <QListWidget>
#include <list>
#include <QStandardItemModel>
#include <QMouseEvent>
#include <QMessageBox>
#include <QGraphicsDropShadowEffect>
#include <QToolButton>
#include <QRegExp>
#include <QRegExpValidator>
#include <QPropertyAnimation>
#include <ctime>
#include "messageviewdelegate.h"
#include "listmessagemodel.h"
#include <QKeyEvent>
#include <QMenuBar>
#include <QAbstractScrollArea>
#include <QScrollBar>
#include <QApplication>
#include "emojis.h"

class MessageViewDelegate;

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
    enum MouseType
    {
        None = 0,
        Top,
        Bottom,
        Left,
        Right,
        Move
    };

    // для отслеживания состояния окна чата
    enum BellStatus
    {
        showChat,
        hideChat
    };

    enum showMesseg
    {
        showMessage,
        hideMessage
    };

    enum CheckConnect
    {
        SUCCESS_CONNECT,
        FAILURE_CONNECT,
        NOT_RECOGNIZED
    };

public:
    explicit MainWindow(QWidget *parent = nullptr); // явный конструктор
    ~MainWindow(); // деструктор

    void hide_all(QListWidget *listWidjet); // скрывает все не нужные элименты
    void popUpView(QString msg = "", QString totification = "");

    QImage defautIcon() const;
    void setDefaultIcon(const QImage & img);
    int getMsgBoardWidth();
    void FailedConnect();

    QString getHost();
    unsigned int getPort();
    void setEmoji();

    CheckConnect checkConnect;
public slots:
    void setPreviousPosition(QPoint previousPosition); // устанавливаем новую предыдущую позицию

signals:
    void previousPositionChanged(QPoint previousPosition); // новая предыдущая позиция
    void NewSession(QString str); // новая предыдущая позиция

private:
    Ui::MainWindow *ui;

    Client* client;

    PopUp *popUp;

    QPropertyAnimation *animationStackedWidget;
    QPropertyAnimation *animationPnlChat;

    int numberListMsg;

    void btn_max();  // свёртывание и развертывание программы в маленький и большой режимы
    void mainApplicationDesigner(); // Дефолтный фид приложения
    void settingDesigner(); // Вид и проверки для hostEdit, spinPort, connect;
    int closeApp();

    void on_DarkDesign_clicked(); // Слот для переключения на темную тему
    void disableBtnStyle(QPushButton *, QPushButton *);

    // Переменная, от которой будем отталкиваться при работе с перемещением и изменением размера окна
    MouseType m_leftMouseButtonPressed; // enum значения курсора
    QPoint m_previousPosition; // предыдущая позиция

    // проверка состояния курсора и получение его внешнего вида
    MouseType checkResizableField(QMouseEvent *event);
    QPoint previousPosition() const; // получение предыдущей позиции

    QListWidgetItem *user_in_list; // выбранное значение из списка

    list<QString> mute_user_list; // список немых
    list<QString> bun_user_list; // cписок забаненных
    list<QString> userList; // все пользователи
//    list<QString> messageList;

    QString num_session;

    BellStatus statusBell; // enum для проверки статуса окна
    showMesseg flagMsg;

    QStringList listCounterMsg;
    QStringList listCounterName;
    QStringList listDateMessage;

    int msgBoardWidth;

    void cursorTracking(); // отслежживание курсора
    void shadowEffect(); // эффект для растягивания окна приложения
    void disconnectFromServer();

    // для смайликов
    QPushButton *btnEmoji;
    QWidget * wdgEmoji;
    QHBoxLayout *vlayEmoji;

    template<class T1, class T2>
    bool checkUserInList(const list<T1> &lst, T2 username); // проверка есть юзер или нет

    template<class T1, class T2>
    QString muteOrUnMute(const list<T1> &lst, T2 msg, T2 lastName);

protected:
    // функции отслеживания мыши
    void mousePressEvent(QMouseEvent *event); // Позиция клика
    void mouseReleaseEvent(QMouseEvent *event); // Когда кнопка мыши отжата вызываем ->
    void mouseMoveEvent(QMouseEvent *event); // Изменение размера (тут отслеживают клик и конечное состояние окна)

    void keyPressEvent(QKeyEvent *event);
    void keyReleaseEvent(QKeyEvent *event);

private slots:
    void onReceiveMessage(QString message); // Слот для получения сообщения
    void onNumberSession(QString session);
    void onConnectBtnClick(); // Слот для кнопки соединения с сервером
    void onDisconnectBtnClick(); // Слот для кнопки отключения от сервера (можно удалить)
    void onSendMessageBtnClick(); // Слот для кнопки отправки сообщения
    void on_Settings_clicked(); // Слот для отображения/скрытия меню настроек
    void on_btn_close_clicked(); // Слот для отключения от сервера
    void on_BtnUserControl_clicked(); // Слот отображения списка пользоватеей
    void on_To_Ban_Button_clicked(); // Слот для бана пользователей
    void on_Mute_Button_clicked(); // Слот для мьюта пользователей
    void slot_UnMuteUser(QListWidgetItem*); // Слот размьюта
    void on_lineSearchUserList_textChanged(const QString &arg1); // при вызове определенного сигнала делаем поиск
    void on_ChatBtn_clicked(); // Скрытие чата
    void slot_clickOnEmoji();

    void slot_muteUser();
    void slot_unMuteUser();
    void slot_muteAllUser();
    void slot_unMuteAllUser();
    void slot_banAllUser();
    void slot_unBanAllUser();


    void on_MessageBoardList_doubleClicked(const QModelIndex &index);
    void on_MessageBoardList_clicked(const QModelIndex &index);
    void on_MessageBoardList_customContextMenuRequested(const QPoint &pos);

    void on_closeUserListPanel_clicked();
    void on_btnSmile_clicked();
    void on_btnClipImage_clicked();
};

#endif // MAINWINDOW_H
