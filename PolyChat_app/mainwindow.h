#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPushButton>
#include <QLineEdit>
#include <QTextEdit>
#include <QListWidget>
#include "client.h"
#include <QLabel>
#include <QStandardItemModel>
#include <QMouseEvent>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    void disable();

private:
    Ui::MainWindow *ui;

    QLineEdit* hostEdt;
    QLabel* boxMsg;
    QString design;
    Client* client;
    void btn_max();
    // Переменная, от которой будем отталкиваться при работе с перемещением и изменением размера окна

private slots:
    void onConnectBtnClick();
    void onDisconnectBtnClick();
    void onSendMessageBtnClick();
    void onReceiveMessage(QString message);
    void onReceiveServiceMessage(QString message);

    void on_Settings_clicked();
    void on_HideSettings_clicked();
    void on_btn_close_clicked();
    void on_DarkDesign_clicked();
    void on_WhiteDesign_clicked();

protected:

};

#endif // MAINWINDOW_H
