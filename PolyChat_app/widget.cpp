#include "widget.h"
#include "ui_widget.h"
#include "QMessageBox"
#include "fstream"
#include "string"
#include "iostream"
#include "vector"
#include "downloader.h"
#include "QThread"
#include "QTimer"

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);

    downloader = new Downloader();

    connect(ui->lineEdit, SIGNAL(returnPressed()), this, SLOT(on_pushButton_clicked()));
    connect(ui->lineEdit, SIGNAL(returnPressed()), downloader,SLOT(getData()));

   connect(ui->pushButton, &QPushButton::clicked, downloader, &Downloader::getData);
     connect(this, SIGNAL(sendText(QString)),downloader,SLOT(resirvedText(QString)));

     connect(downloader, SIGNAL(onReady(QString)), this, SLOT(readFile(QString)));

    QTimer *timer = new QTimer(this);
       connect(timer, SIGNAL(timeout()), downloader, SLOT(chatData()));
        timer->start(1000);

}

Widget::~Widget()
{
    delete ui;
}

void Widget::readFile(QString buf)
{
    QString slov = "Пользователь написал: ";
    QString res = slov + buf;

   ui->plainTextEdit->appendPlainText(res);

}

void Widget::on_pushButton_clicked()
{

    QString message = ui->lineEdit->text();
    emit sendText(message);
    ui->lineEdit->setText("");


}
