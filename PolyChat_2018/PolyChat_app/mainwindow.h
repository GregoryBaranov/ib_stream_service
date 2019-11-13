#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "client.h"
#include <QPushButton>
#include <QLineEdit>
#include <QTextEdit>
#include <QListWidget>
#include <QLabel>
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

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0); // явный конструктор
    ~MainWindow();

private:
    Ui::MainWindow *ui;

    Client* client;

    // Кнопка каоторая отвечает за свёртывание и развертывание
    // программы в маленький и большой режимы
    void btn_max();

    void mainApplicationDesigner(); // Дефолтный фид приложения
    void settingDesigner(); // Вид и проверки для hostEdit, spinPort, connect;

private slots:
    void onReceiveMessage(QString message); // Слот для получения сообщения
    void onConnectBtnClick(); // Слот для кнопки соединения с сервером
    void onDisconnectBtnClick(); // Слот для кнопки отключения от сервера (можно удалить)
    void onSendMessageBtnClick(); // Слот для кнопки отправки сообщения
    void on_Settings_clicked(); // Слот для отображения/скрытия меню настроек
    void on_btn_close_clicked(); // Слот для отключения от сервера
    void on_DarkDesign_clicked(); // Слот для переключения на темную тему
    void on_WhiteDesign_clicked(); // Слот для переключения на светлую тему
};

#endif // MAINWINDOW_H
