#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPushButton>
#include <QLineEdit>
#include <QTextEdit>
#include <QListWidget>
#include "client.h"


namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT


public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    QPushButton* connectBtn;
    QPushButton* sendMessageBtn;
    QPushButton* loginBtn;
    QListWidget* userList;
    QLineEdit* hostEdt;
    QLineEdit* messageEdt;
    QTextEdit* messageBoard;

    Client* client;

    // Переменная, от которой будем отталкиваться при работе с перемещением и изменением размера окна


private slots:
    void onConnectBtnClick();
    void onSendMessageBtnClick();
    void onReceiveMessage(QString message);
    void onReceiveServiceMessage(QString message);
    void on_pushButton_clicked();
protected:

};

#endif // MAINWINDOW_H
