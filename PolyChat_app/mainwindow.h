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
#include <QMessageBox>
#include <QInputDialog>
#include "client.h"
#include <QFileDialog>
#include <QDir>
#include <QGraphicsDropShadowEffect>
#include <QToolButton>

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

    Client* client;

    void btn_max();
    void mainApplicationDesigner();
    void settingDesigner();

private slots:
    void onReceiveMessage(QString message);
    void onReceiveServiceMessage(QString message);

    void onConnectBtnClick();
    void onDisconnectBtnClick();
    void onSendMessageBtnClick();
    void on_Settings_clicked();
    void on_btn_close_clicked();
    void on_DarkDesign_clicked();
    void on_WhiteDesign_clicked();
};

#endif // MAINWINDOW_H
