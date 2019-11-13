#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QGraphicsDropShadowEffect>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    mainApplicationDesigner(); // Дефолтный фид приложения
    settingDesigner(); // Вид и проверки для hostEdit, spinPort, connect;
    btn_max(); // Кнопка каоторая отвечает за свёртывание и развертывание программы в маленький и большой режимы

    client = new Client(this);

    // connect для получения сообщений
    connect(client, SIGNAL(receiveMessage(QString)),
            this, SLOT(onReceiveMessage(QString)));

    // connect для получения номера сессии
    connect(client, SIGNAL(newNumberSession(QString)),
            this, SLOT(onNumberSession(QString)));

    // connect для кнопки подключиться
    connect(ui->connect, &QToolButton::clicked,
            this, &MainWindow::onConnectBtnClick);

    // connect для кнопки отключится
    connect(ui->Disconnect, &QToolButton::clicked,
            this, &MainWindow::onDisconnectBtnClick);

    connect(client, SIGNAL(disconnected()),
            client, SLOT(deleteLater()));

    // connect для кнопки отправить сообщение
    connect(ui->send, SIGNAL(clicked()),
            this, SLOT(onSendMessageBtnClick()));

    // connect для кнопки скрытия окна
    connect(ui->btn_minimize, &QToolButton::clicked,
            this, &MainWindow::showMinimized);

    // connect для кнопки закрытия приложения
    connect(ui->btn_close, &QToolButton::clicked,
            this, &MainWindow::close);

    // connect при сигнале failedConnect
    connect(client, SIGNAL(failedConnect()),
            this, SLOT(onFailedConnect()));

    // connect двойного клика в виджете по значению
    connect(ui->user_blacklist, SIGNAL(itemDoubleClicked(QListWidgetItem*)),
            this, SLOT(slot_UnbrokenUser(QListWidgetItem*)));

    // connect двойного клика в виджете по значению
    connect(ui->listViewUser, SIGNAL(itemDoubleClicked(QListWidgetItem*)),
            this, SLOT(slot_UnMuteUser(QListWidgetItem*)));
}

MainWindow::~MainWindow()
{
    delete ui;
    delete user_in_list;
}

void MainWindow::settingDesigner() // Вид и проверки для hostEdit, spinPort, connect;
{
    ui->GroupUserListWidget->hide();
    ui->verticalSp->show();
    ui->To_Ban_Button->hide();
    ui->Mute_Button->hide();
    ui->GroupBanWidget->hide();

    /* Создаем строку для регулярного выражения */
    QString ipRange = "(?:[0-1]?[0-9]?[0-9]|2[0-4][0-9]|25[0-5])";

    /* Создаем регулярное выражение с применением строки, как
     * повторяющегося элемента
     */
    QRegExp ipRegex ("^" + ipRange
                     + "\\." + ipRange
                     + "\\." + ipRange
                     + "\\." + ipRange + "$");

    // Создаем Валидатор регулярного выражения с применением
    // созданного регулярного выражения
    QRegExpValidator *ipValidator = new QRegExpValidator(ipRegex, this);

    /* Устанавливаем Валидатор на QLineEdit */
    ui->hostEdit->setValidator(ipValidator);
    ui->hostEdit->setPlaceholderText("127.0.0.1");
    ui->hostEdit->setText("31.10.65.179");

    ui->spinPort->setMaximum(999999999);
    ui->spinPort->setValue(5000);
}

void MainWindow::mainApplicationDesigner() // Дефолтный фид приложения
{
    // Убираем дефолтную строку заголовка и делаем ненужное пространство прозрачным
    this->setWindowFlag(Qt::FramelessWindowHint);
    this->setAttribute(Qt::WA_TranslucentBackground);
    this->setStyleSheet("font: 12pt Microsoft YaHei UI;");
    this->setMouseTracking(true); // отслеживание курсора мыши без нажатых кнопокы

    // Разрешаем остлеживание курсора по всему приложению (блокам)
    ui->centralWidget->setMouseTracking(true);
    ui->titleBar->setMouseTracking(true);
    ui->pnlSettings->setMouseTracking(true);
    ui->pnlStream->setMouseTracking(true);
    ui->pnlChat->setMouseTracking(true);

    QGraphicsDropShadowEffect *shadowEffect = new QGraphicsDropShadowEffect(this);
    shadowEffect->setBlurRadius(9); // Устанавливаем радиус размытия
    shadowEffect->setOffset(0);     // Устанавливаем смещение тени

    ui->centralWidget->setGraphicsEffect(shadowEffect);   // Устанавливаем эффект тени на окно
    ui->centralWidget->layout()->setMargin(0);            // Устанавливаем размер полей
    ui->centralWidget->layout()->setSpacing(0);

    // позволяет нажать кнопку send с помощью Enter
    ui->send->setShortcut(Qt::Key_Return);

    ui->label->setDisabled(true);

    ui->StartSession->setDisabled(false);
    ui->StopSession->setDisabled(true);

    on_DarkDesign_clicked();

    statusBell = showChat;

    //----------------------------------------- фэйковое добавление пользователей -------------------------------------------
    char names[][255] = {"Timur", "Alex", "Vasya", "Marina", "Demid", "Arseniy", "Serega"};

    for (int index=0; index<sizeof(names)/sizeof(names[0]); index++){
        user_in_list = new QListWidgetItem(QIcon(":/image/student.png"), names[index]);
        userList.append(names[index]);
        ui->listViewUser->addItem(user_in_list);
    }
    //----------------------------------------- фэйковое добавление пользователей -------------------------------------------

    // Только для чтения информации
    ui->messageBoard->setReadOnly(true);
}

QPoint MainWindow::previousPosition() const
{
    return m_previousPosition;
}

void MainWindow::setPreviousPosition(QPoint previousPosition)
{
    if (m_previousPosition == previousPosition)
        return;

    m_previousPosition = previousPosition;
    emit previousPositionChanged(previousPosition);
}

void MainWindow::mousePressEvent(QMouseEvent *event)
{
    // При клике левой кнопкой мыши
    if (event->button() == Qt::LeftButton ) {
        // Определяем, в какой области произошёл клик
        m_leftMouseButtonPressed = checkResizableField(event);
        setPreviousPosition(event->pos()); // и устанавливаем позицию клика
    }
    return QWidget::mousePressEvent(event);
}

void MainWindow::mouseReleaseEvent(QMouseEvent *event)
{
    // При отпускании левой кнопки мыши сбрасываем состояние клика
    if (event->button() == Qt::LeftButton) {
        m_leftMouseButtonPressed = None;
    }
    return QWidget::mouseReleaseEvent(event);
}

void MainWindow::mouseMoveEvent(QMouseEvent *event)
{
    // При перемещении мыши, проверяем статус нажатия левой кнопки мыши
    switch (m_leftMouseButtonPressed) {
    case Move: {
        // При этом проверяем, не максимизировано ли окно
        if (isMaximized()) {
            // При перемещении из максимизированного состояния
            // Необходимо вернуть окно в нормальное состояние и установить стили кнопки
            // А также путём нехитрых вычислений пересчитать позицию окна,
            // чтобы оно оказалось под курсором
            this->layout()->setMargin(9);
            auto part = event->screenPos().x() / width();
            this->showNormal();
            auto offsetX = width() * part;
            setGeometry(event->screenPos().x() - offsetX, 0, width(), height());
            setPreviousPosition(QPoint(offsetX, event->y()));
        } else {
            // Если окно не максимизировано, то просто перемещаем его относительно
            // последней запомненной позиции, пока не отпустим кнопку мыши
            auto dx = event->x() - m_previousPosition.x();
            auto dy = event->y() - m_previousPosition.y();
            setGeometry(x() + dx, y() + dy, width(), height());
        }
        break;
    }
    case Top: {
        // Для изменения размеров также проверяем на максимизацию
        // поскольку мы же не можем изменить размеры у максимизированного окна
        if (!isMaximized()) {
            auto dy = event->y() - m_previousPosition.y();
            setGeometry(x(), y() + dy, width(), height() - dy);
        }
        break;
    }
    case Bottom: {
        if (!isMaximized()) {
            auto dy = event->y() - m_previousPosition.y();
            setGeometry(x(), y(), width(), height() + dy);
            setPreviousPosition(event->pos());
        }
        break;
    }
    case Left: {
        if (!isMaximized()) {
            auto dx = event->x() - m_previousPosition.x();
            setGeometry(x() + dx, y(), width() - dx, height());
        }
        break;
    }
    case Right: {
        if (!isMaximized()) {
            auto dx = event->x() - m_previousPosition.x();
            setGeometry(x(), y(), width() + dx, height());
            setPreviousPosition(event->pos());
        }
        break;
    }
    default:
        // Если курсор перемещается по окну без зажатой кнопки,
        // то просто отслеживаем в какой области он находится
        // и изменяем его курсор
        checkResizableField(event);
        break;
    }
    return QWidget::mouseMoveEvent(event);
}

MainWindow::MouseType MainWindow::checkResizableField(QMouseEvent *event)
{
    QPointF position = event->screenPos();  // Определяем позицию курсора на экране
    qreal x = this->x();                    // координаты окна приложения, ...
    qreal y = this->y();                    // ... то есть координату левого верхнего угла окна
    qreal width = this->width();            // А также ширину ...
    qreal height = this->height();          // ... и высоту окна

    // Определяем области, в которых может находиться курсор мыши
    // По ним будет определён статус клика
    QRectF rectTop(x + 9, y, width - 18, 7);
    QRectF rectBottom(x + 9, y + height - 7, width - 18, 7);
    QRectF rectLeft(x, y + 9, 7, height - 18);
    QRectF rectRight(x + width - 7, y + 9, 7, height - 18);
    QRectF rectInterface(x + 9, y + 9, width - 18, height - 18);

    // И в зависимости от области, в которой находится курсор
    // устанавливаем внешний вид курсора и возвращаем его статус
    if (rectTop.contains(position)) {
        setCursor(Qt::SizeVerCursor);
        return Top;
    } else if (rectBottom.contains(position)) {
        setCursor(Qt::SizeVerCursor);
        return Bottom;
    } else if (rectLeft.contains(position)) {
        setCursor(Qt::SizeHorCursor);
        return Left;
    } else if (rectRight.contains(position)) {
        setCursor(Qt::SizeHorCursor);
        return Right;
    } else if (rectInterface.contains(position)){
        setCursor(QCursor());
        return Move;
    } else {
        return None;
    }
}

// Кнопка каоторая отвечает за свёртывание и развертывание программы в маленький и большой режимы
void MainWindow::btn_max()
{
    connect(ui->btn_maximize, &QToolButton::clicked, [this]()
    {
        // Если окно находится в максимально развернутом состоянии, то кнопка находится в режиме свертывания
        if (this->isMaximized())
        {
            ui->btn_maximize->setStyleSheet("background:#3d3d3d; background-image: url(:/image/window-maximize-gray.png);"
                                            "background-repeat: no-repeat; margin: 0px;");
            this->showNormal();
        }
        else
        {
            ui->btn_maximize->setStyleSheet("background:#3d3d3d; background-image: url(:/image/window-restore-gray.png); "
                                            "background-repeat: no-repeat; margin: 0px;");
            this->showMaximized();
        }
    });
}

void MainWindow::onConnectBtnClick() // Слот для кнопки соединения с сервером
{
    qDebug() << "connect";
    // Логическая блокировка кнопок connect и разблокировка Disconnect
    ui->connect->setDisabled(true);
    ui->Disconnect->setDisabled(false);

    ui->messageBoard->append("Connection attempt...");
    unsigned int port = ui->spinPort->value();
    client->connectSocket(ui->hostEdit->text(), port);
}

void MainWindow::onDisconnectBtnClick() // Слот для кнопки отключения от сервера
{
    // Если произошел disconnect, то проверяем логику кнопок
    // Логическая блокировка кнопки запуска и остановки стрима
    ui->StartSession->setDisabled(false);
    ui->StopSession->setDisabled(true);

    // Логическая блокировка кнопок Disconnect и разблокировка connect
    ui->connect->setDisabled(false);
    ui->Disconnect->setDisabled(true);

    client->sendMessage("Disconnect");
}

void MainWindow::onSendMessageBtnClick() // Слот для кнопки отправки сообщения
{
    if(ui->messageEdt->text() != "") // Проверка на пустое сообщение
    {
        client->sendMessage(ui->messageEdt->text()); // отправка сообщения
        ui->messageEdt->clear(); // очищение отправленного сообщения
    }
}

void MainWindow::onReceiveMessage(QString message) // Слот для получения сообщения
{
    QString fullMessage = QString("[%1] %2")
            .arg(QDateTime::currentDateTime().toString("hh:mm:ss")) // отображает время прихода сообщения
            .arg(message); // само сообщение

    ui->messageBoard->append(fullMessage); // отображение пришедшего сообщения
}

void MainWindow::on_Settings_clicked() // Слот для отображения/скрытия меню настроек
{
    static int ShowOrHide = 0;
    if(++ShowOrHide % 2) // Если открыт то закрываем, иначе отображаем
    {
        QPropertyAnimation *animation = new QPropertyAnimation(ui->pnlSettings, "maximumWidth"); //wdgSMS is your widget
        animation->setDuration(150);
        animation->setStartValue(302);
        animation->setEndValue(0);
        animation->start();


    }
    else
    {
        QPropertyAnimation *animation = new QPropertyAnimation(ui->pnlSettings, "maximumWidth");
        animation->setDuration(150);
        animation->setStartValue(0);
        animation->setEndValue(302);
        animation->start();
    }
}

void MainWindow::on_btn_close_clicked() // Слот для отключения от сервера
{
    client->sendMessage("Disconnect");
}

void MainWindow::on_DarkDesign_clicked() // Слот для переключения на темную тему
{
    // Логическая блокировка кнопок DarkDesign (семены темы) и разблокировки WhiteDesign
    ui->DarkDesign->setDisabled(true);
    ui->WhiteDesign->setDisabled(false);

    // Выставление стиля для темы "Dark"
    // Выставление стиля для дефолтной темы "Dark"
    ui->hostEdit->setStyleSheet("background:#3d3d3d;");
    ui->spinPort->setStyleSheet("background:#3d3d3d;");
    ui->connect->setStyleSheet("background:#3d3d3d;");
    ui->ChatBtn->setStyleSheet("background:#3d3d3d;");
    ui->Settings->setStyleSheet("background:#3d3d3d; color:#fff;");
    ui->btn_close->setStyleSheet("background:#3d3d3d; background-image: url(:/image/close-gray.png);");
    ui->send->setStyleSheet("font: 12pt Microsoft YaHei UI; background:#3d3d3d; color: #fff; border: 2px solid #000;");
    ui->btn_maximize->setStyleSheet("background:#3d3d3d; background-image: url(:/image/window-maximize-gray.png);");
    ui->btn_minimize->setStyleSheet("background:#3d3d3d; background-image: url(:/image/window-minimize-gray.png);");
    ui->Disconnect->setStyleSheet("background:#3d3d3d;");
    ui->DarkDesign->setStyleSheet("background:#3d3d3d;");
    ui->WhiteDesign->setStyleSheet("background:#3d3d3d;");
    ui->messageEdt->setStyleSheet("background:#3d3d3d; color: #fff; border: 2px solid #000;");
    ui->messageBoard->setStyleSheet("background:rgba(62, 62, 62, 0.5); color: #fff; border: 2px solid #000;");
    ui->titleBar->setStyleSheet("background:rgba(62, 62, 62, 0.5); color: #fff; border: 2px solid #000;");
    ui->pnlSettings->setStyleSheet("background:rgba(62, 62, 62, 0.5); color: #fff; border: 2px solid #000;");
    ui->pnlStream->setStyleSheet("background:rgba(62, 62, 62, 0.5); color: #fff; border: 2px solid #000;");
    ui->pnlChat->setStyleSheet("background:rgba(62, 62, 62, 0.5); color: #fff; border: 2px solid #000;");
    ui->messageEdt->setPlaceholderText("Message...");
    ui->StartSession->setStyleSheet("background:#3d3d3d; color:#fff;");
    ui->StopSession->setStyleSheet("background:#3d3d3d; color:#fff;");
    ui->verticalSp->setStyleSheet("background: transparent; border-color: transparent;");
    ui->label->setText("<img src=\":/image/top_logo.png\"  />");
    ui->lable_session_num->setText("*****");

    ui->ChatBtn->setIcon(QIcon(":/image/messagedef.png"));
    ui->ChatBtn->setIconSize(QSize(45,45));

    ui->Settings->setIcon(QIcon(":/image/settings-cogwheel-button.png"));
    ui->Settings->setIconSize(QSize(35,35));
}

void MainWindow::on_WhiteDesign_clicked() // Слот для переключения на светлую тему
{
    // Логическая блокировка кнопок WhiteDesign (семены темы) и разблокировки DarkDesign
    ui->DarkDesign->setDisabled(false);
    ui->WhiteDesign->setDisabled(true);

    // Выставление стиля для темы "White"
    ui->send->setStyleSheet("background:#fff; color:#000;");
    ui->StartSession->setStyleSheet("background:#fff; color:#000;");
    ui->StopSession->setStyleSheet("background:#fff; color:#000;");
    ui->Disconnect->setStyleSheet("background:#fff;");
    ui->DarkDesign->setStyleSheet("background:#fff;");
    ui->WhiteDesign->setStyleSheet("background:#fff;");
    ui->connect->setStyleSheet("background:#fff;");
    ui->messageEdt->setStyleSheet("background:#fff; color:#000;");
    ui->hostEdit->setStyleSheet("background:#fff; border: 2px solid #000;");
    ui->spinPort->setStyleSheet("background:#fff; border: 2px solid #000;");
    ui->messageBoard->setStyleSheet("background:#fff; color:#000; border: 2px solid #000;");
    ui->titleBar->setStyleSheet("background:rgba(255, 255, 255); color: #000; border: 2px solid #000;");
    ui->pnlSettings->setStyleSheet("background:rgba(255, 255, 255); color: #000; border: 2px solid #000;");
    ui->pnlStream->setStyleSheet("background:rgba(255, 255, 255); color: #000; border: 2px solid #000;");
    ui->pnlChat->setStyleSheet("background:rgba(255, 255, 255); color: #000; border: 2px solid #000;");
}

void MainWindow::on_BtnUserControl_clicked()
{
    if(ui->GroupUserListWidget->isVisible()){
        ui->GroupUserListWidget->hide();
        ui->To_Ban_Button->hide();
        ui->Mute_Button->hide();
        ui->verticalSp->show();

    }
    else
    {
        ui->GroupUserListWidget->show();
        ui->To_Ban_Button->show();
        ui->Mute_Button->show();
        ui->verticalSp->hide();
    }

}

void MainWindow::on_To_Ban_Button_clicked()
{
    // to do
    // Реализовать запрос на сервер для бана пользователя с трансляции
    if(ui->listViewUser->currentItem())
    {
        QString status = "БАН ПОЛЬЗОВАТЕЛЯ " + ui->listViewUser->currentItem()->text(); // само сообщение

        client->sendMessage(status); // отправка оповещения на сайт

        QString username = ui->listViewUser->currentItem()->text();
        user_in_list = new QListWidgetItem(QIcon(":/image/ban.png"), username);
        ui->user_blacklist->addItem(user_in_list);

        bun_user_list.push_back(username);

        delete ui->listViewUser->currentItem();
    }
}

void MainWindow::on_Mute_Button_clicked()
{
    if(ui->listViewUser->currentItem())
    {
        QString status = "ПОЛЬЗОВАТЕЛЬ " + ui->listViewUser->currentItem()->text() + " ПОЛУЧИЛ MUTE";

        client->sendMessage(status); // отправка оповещения на сайт

        QString username = ui->listViewUser->currentItem()->text();
        user_in_list = new QListWidgetItem(QIcon(":/image/mute.png"), username);
        ui->listViewUser->addItem(user_in_list);

        mute_user_list.push_back(username);

        delete ui->listViewUser->currentItem();
    }
}

void MainWindow::on_ShowBlacklist_clicked()
{
    if(ui->GroupBanWidget->isVisible())
    {
        ui->GroupBanWidget->hide();
        ui->verticalSp->show();
    }
    else
    {
        ui->GroupBanWidget->show();
        ui->verticalSp->hide();
    }
}

void MainWindow::slot_UnbrokenUser(QListWidgetItem* item)
{
    QString username = ui->user_blacklist->currentItem()->text();
    item = new QListWidgetItem(QIcon(":/image/student.png"), username);
    ui->listViewUser->addItem(item);

    bun_user_list.remove(username);// Удаляем user-a из списка ban_user_list

    delete ui->user_blacklist->currentItem();
}

void MainWindow::slot_UnMuteUser(QListWidgetItem* item)
{
    QString username = ui->listViewUser->currentItem()->text();

    if (checkUserInList(mute_user_list, username) == true) // проверка есть ли user в списке замьюченых
    {
        item = new QListWidgetItem(QIcon(":/image/student.png"), username);
        ui->listViewUser->addItem(item);

        mute_user_list.remove(username); // Удаляем user-a из списка mute_user_list

        delete ui->listViewUser->currentItem();
    }
}

void MainWindow::on_lineSearchUserList_textChanged(const QString &arg1)
{
    hide_all(ui->listViewUser);
    QList<QListWidgetItem*> matches ( ui->listViewUser->findItems(arg1, Qt::MatchFlag::MatchContains) );
    for(QListWidgetItem* item : matches)
        item->setHidden(false);
}

void MainWindow::on_lineSearchBanUserList_textChanged(const QString &arg1)
{
    hide_all(ui->user_blacklist);
    QList<QListWidgetItem*> matches ( ui->user_blacklist->findItems(arg1, Qt::MatchFlag::MatchContains) );
    for(QListWidgetItem* item : matches)
        item->setHidden(false);
}

void MainWindow::hide_all(QListWidget *listWidjet)
{
    for(int row(0); row < listWidjet->count(); row++ )
        listWidjet->item(row)->setHidden(true);
}

template<class T1, class T2>
bool MainWindow::checkUserInList(const list<T1> &lst, T2 username)
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

void MainWindow::on_ChatBtn_clicked()
{
    QPropertyAnimation *animation = new QPropertyAnimation(ui->pnlChat, "maximumWidth");
    static int ShowOrHide = 0;

    if(++ShowOrHide % 2) // Если открыт то закрываем, иначе отображаем
    {
        animation->setDuration(100);
        animation->setStartValue(500);
        animation->setEndValue(0);
        animation->start();

        statusBell = hideChat;
    }
    else
    {
        animation->setDuration(100);
        animation->setStartValue(0);
        animation->setEndValue(500);
        animation->start();

        ui->ChatBtn->setIcon(QIcon(":/image/messagedef.png"));
        ui->ChatBtn->setIconSize(QSize(45,45));
        statusBell = showChat;
    }
}


void MainWindow::on_messageBoard_textChanged()
{
    if(statusBell == hideChat)
    {
        ui->ChatBtn->setIcon(QIcon(":/image/messageNew.png"));
        ui->ChatBtn->setIconSize(QSize(45,45));
    }
}

void MainWindow::on_StartSession_clicked()
{
    ui->StartSession->setDisabled(true);
    ui->StopSession->setDisabled(false);
}

void MainWindow::on_StopSession_clicked()
{
    ui->StartSession->setDisabled(false);
    ui->StopSession->setDisabled(true);

    ui->lable_session_num->setText("");
}

void MainWindow::onNumberSession(QString session)
{
    ui->lable_session_num->setText(session);
}

void MainWindow::onFailedConnect()
{
    // Если произошел Faile Connect, то проверяем логику кнопок
    // Логическая блокировка кнопки запуска и остановки стрима
    ui->StartSession->setDisabled(false);
    ui->StopSession->setDisabled(true);

    // Логическая блокировка кнопок Disconnect и разблокировка connect
    ui->connect->setDisabled(false);
    ui->Disconnect->setDisabled(true);
}
