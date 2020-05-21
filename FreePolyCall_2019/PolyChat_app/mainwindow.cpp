#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "styleapp.h"
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
    popUp = new PopUp();

    animationStackedWidget = new QPropertyAnimation(ui->sattingStackedWidget, "maximumWidth");
    animationPnlChat = new QPropertyAnimation(ui->pnlChat, "maximumWidth");

    // connect для получения сообщений
    connect(client, SIGNAL(receiveMessage(QString)),
            this, SLOT(onReceiveMessage(QString)));

    // connect для получения номера сессии
    connect(client, SIGNAL(newNumberSession(QString)),
            this, SLOT(onNumberSession(QString)));

    // connect для кнопки подключиться
    connect(ui->Connect, &QToolButton::clicked,
            this, &MainWindow::onConnectBtnClick);

    // connect для кнопки отключится
    connect(ui->Disconnect, &QToolButton::clicked,
            this, &MainWindow::onDisconnectBtnClick);

    // connect для кнопки отправить сообщение
    connect(ui->send, SIGNAL(clicked()),
            this, SLOT(onSendMessageBtnClick()));

    // connect для кнопки скрытия окна
    connect(ui->btn_minimize, &QToolButton::clicked,
            this, &MainWindow::showMinimized);

    // connect для кнопки закрытия приложения
    connect(ui->btn_close, &QToolButton::clicked,
            this, &MainWindow::close);

    // connect двойного клика в виджете по значению
    connect(ui->listViewUser, SIGNAL(itemDoubleClicked(QListWidgetItem*)),
            this, SLOT(slot_UnMuteUser(QListWidgetItem*)));
}

MainWindow::~MainWindow()
{
    delete ui;
    delete popUp;
    delete animationStackedWidget;
    delete animationPnlChat;
}

void MainWindow::settingDesigner() // Вид и проверки для hostEdit, spinPort, connect;
{
    ui->lable_session_num->setReadOnly(true);
    ui->TitleEdit->setPlaceholderText("Название");

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
//    ui->hostEdit->setText("31.10.65.179");
    ui->hostEdit->setText("127.0.0.1");
//    ui->TitleEdit->setText("Title stream");

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
    ui->messageEdit->setStyleSheet("font: 12pt Segoe UI Emoji;");
    ui->MessageBoardList->setStyleSheet("font: 12pt Segoe UI Emoji;");

    cursorTracking(); // отслеживание курсора
    shadowEffect(); // эффект тени для растягивания окна приложения

    // позволяет нажать кнопку send с помощью Enter
    ui->label->setDisabled(true);
    ui->Connect->setDisabled(false);
    ui->Disconnect->setDisabled(true);

    ui->sattingStackedWidget->setCurrentIndex(0);

    ui->MessageBoardList->setContextMenuPolicy(Qt::CustomContextMenu);
    ui->MessageBoardList->setStyleSheet(StyleApp::getDarkMessageBoardItem());
    ui->MessageBoardList->verticalScrollBar()->setStyleSheet(StyleApp::getInvisibleStyle());

    // дефолтная тема приложения
    on_DarkDesign_clicked();
    setEmoji();

    // дефолтный статус о состоянии окна чата
    statusBell = showChat;

    ui->stackedWidgetForMessage->setVisible(false);
}

void MainWindow::setEmoji(){
    Emojis e;
    auto arr = e.getEmoji();
    int id = -1;
    for (auto var : arr) {
        id++;
        btnEmoji = new QPushButton(this);
        if(id == 0 || id % 5 == 0){
            wdgEmoji = new QWidget(this);
            vlayEmoji = new QHBoxLayout(wdgEmoji);
        }

        btnEmoji->setText(var);
        btnEmoji->setFlat(true);
        btnEmoji->setStyleSheet("text-align: center; font-size: 20px;");
        btnEmoji->setFixedSize(52, 50);
        vlayEmoji->addWidget(btnEmoji);
        ui->verticalLayout->addWidget(wdgEmoji);
        connect(btnEmoji, SIGNAL(clicked()), this, SLOT(slot_clickOnEmoji()));
    }
}

void MainWindow::slot_clickOnEmoji(){
    QPushButton *button = (QPushButton*) sender();
    QString text = ui->messageEdit->toPlainText();
    ui->messageEdit->setText(text + button->text());
}

void MainWindow::cursorTracking()
{
    // Разрешаем остлеживание курсора по всему приложению (блокам)
    ui->centralWidget->setMouseTracking(true);
    ui->titleBar->setMouseTracking(true);
    ui->sattingStackedWidget->setMouseTracking(true);
    ui->pnlStream->setMouseTracking(true);
    ui->pnlChat->setMouseTracking(true);
}

void MainWindow::shadowEffect()
{
    QGraphicsDropShadowEffect *shadowEffect = new QGraphicsDropShadowEffect(this);
    shadowEffect->setBlurRadius(9); // Устанавливаем радиус размытия
    shadowEffect->setOffset(0);     // Устанавливаем смещение тени

    ui->centralWidget->setGraphicsEffect(shadowEffect);   // Устанавливаем эффект тени на окно
    ui->centralWidget->layout()->setMargin(0);            // Устанавливаем размер полей
    ui->centralWidget->layout()->setSpacing(0);
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
    if (event->button() == Qt::LeftButton )
    {
        // Определяем, в какой области произошёл клик
        m_leftMouseButtonPressed = checkResizableField(event);
        setPreviousPosition(event->pos()); // и устанавливаем позицию клика
    }
    return QWidget::mousePressEvent(event);
}

void MainWindow::mouseReleaseEvent(QMouseEvent *event)
{
    // При отпускании левой кнопки мыши сбрасываем состояние клика
    if (event->button() == Qt::LeftButton)
    {
        m_leftMouseButtonPressed = None;
    }
    return QWidget::mouseReleaseEvent(event);
}

void MainWindow::mouseMoveEvent(QMouseEvent *event)
{
    // При перемещении мыши, проверяем статус нажатия левой кнопки мыши
    switch (m_leftMouseButtonPressed)
    {
    case Move:
    {
        // При этом проверяем, не максимизировано ли окно
        if (isMaximized())
        {
            // При перемещении из максимизированного состояния
            // Необходимо вернуть окно в нормальное состояние и установить стили кнопки
            // А также пересчитать позицию окна,
            // чтобы оно оказалось под курсором
            this->layout()->setMargin(9);
            auto part = event->screenPos().x() / width();
            this->showNormal();
            auto offsetX = width() * part;

            setGeometry(event->screenPos().x() - offsetX, 0, width(), height());
            setPreviousPosition(QPoint(offsetX, event->y()));
        }
        else
        {
            // Если окно не максимизировано, то просто перемещаем его относительно
            // последней запомненной позиции, пока не отпустим кнопку мыши
            auto dx = event->x() - m_previousPosition.x();
            auto dy = event->y() - m_previousPosition.y();
            setGeometry(x() + dx, y() + dy, width(), height());
        }
        break;
    }
    case Top:
    {
        // Для изменения размеров также проверяем на максимизацию
        // поскольку мы же не можем изменить размеры у максимизированного окна
        if (!isMaximized())
        {
            auto dy = event->y() - m_previousPosition.y();
            setGeometry(x(), y() + dy, width(), height() - dy);
        }
        break;
    }
    case Bottom:
    {
        if (!isMaximized())
        {
            auto dy = event->y() - m_previousPosition.y();
            setGeometry(x(), y(), width(), height() + dy);
            setPreviousPosition(event->pos());
        }
        break;
    }
    case Left:
    {
        if (!isMaximized())
        {
            auto dx = event->x() - m_previousPosition.x();
            setGeometry(x() + dx, y(), width() - dx, height());
        }
        break;
    }
    case Right:
    {
        if (!isMaximized())
        {
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
            ui->btn_maximize->setStyleSheet(StyleApp::getDarkBtnMaximize());
            this->showNormal();
        }
        else
        {
            ui->btn_maximize->setStyleSheet(StyleApp::getDarlBtnRestore());
            this->showMaximized();
        }
    });
}

void MainWindow::onConnectBtnClick() // Слот для кнопки соединения с сервером
{
    checkConnect = FAILURE_CONNECT;

    if (ui->hostEdit->text() == "")
    {
        popUp->setPopupText("Введите хост!");
        popUp->show();
    }
    else
    {
        client->connectSocket(getHost(), getPort());
    }
}

void MainWindow::onDisconnectBtnClick() // Слот для кнопки отключения от сервера
{
    // Логическая блокировка кнопок Disconnect и разблокировка connect
    ui->Connect->setDisabled(false);
    ui->Disconnect->setDisabled(true);

    disableBtnStyle(ui->Connect, ui->Disconnect);

    client->sendMessage("Disconnect");
    client->clientDisconnect();

    checkConnect = FAILURE_CONNECT;

    ui->listViewUser->clear();
    userList.clear();
    qDebug() << userList;

    FailedConnect();
    popUp->setPopupText("Disconnected");
    popUp->show();
}

void MainWindow::onSendMessageBtnClick() // Слот для кнопки отправки сообщения
{
    QString test = ui->messageEdit->toPlainText();

    QRegExp re( "^\\s+$" );


    QString msg(ui->messageEdit->toPlainText());
    msg.replace(QRegularExpression("\\n{0,}\\s+$")," ");
    msg.replace(QRegularExpression("\\n{0,}\\s+")," ");
    QRegExp urlRe( "^(((\\s*\\;?)?(https?:\\/\\/)?([\\da-z\\.-]+)\\.([a-z\\.]{2,6})([\\/\\w \\.-]*\\/?\\;?\\/s?)?){1,})" );

    if(re.exactMatch(ui->messageEdit->toPlainText()) || ui->messageEdit->toPlainText() == ""){
        ui->messageEdit->clear();
        return;
    }

    if(urlRe.exactMatch(ui->lineEditUrlImg->text())){
        client->sendMessage(msg + getUrlImage(ui->lineEditUrlImg->text()));
    } else {
        client->sendMessage(msg);
    }

    ui->lineEditUrlImg->clear();
    ui->messageEdit->clear();
}

QString MainWindow::getUrlImage(QString str){
    QStringList urls = str.split( ";" );
    str = "";
    for(auto value : urls){
        str += "<br> <a href="+value+" target=\"_blank\"><img src="+value+" width=\"200\" height=\"200\"></a>";
    }
    return str;
}

void MainWindow::keyPressEvent(QKeyEvent *event)
{
    if(event->modifiers() == Qt::ControlModifier)
    {
        if(event->key() == Qt::Key_Enter || event->key() == Qt::Key_Return)
        {
            if(event->isAutoRepeat()) return;
            onSendMessageBtnClick();
        }
    }
}

void MainWindow::keyReleaseEvent(QKeyEvent *event)
{
    if(event->modifiers() == Qt::ControlModifier)
    {
        if(event->key() == Qt::Key_Enter || event->key() == Qt::Key_Return)
        {
            if(event->isAutoRepeat()) return;
        }
    }
}

void MainWindow::onReceiveMessage(QString message) // Слот для получения сообщения
{
    flagMsg = showMessage;

    QRegExp re( "[%]{3}([\\S ]+)[$]{3}" );

    int lastPos = 0;
    while( ( lastPos = re.indexIn( message, lastPos ) ) != -1)
    {
        lastPos += re.matchedLength();
        userList.push_front(re.cap( 1 ));
        ui->listViewUser->addItem(new QListWidgetItem(QIcon(StyleApp::getLogoStudent()), re.cap( 1 )));
        flagMsg = hideMessage;
    }

    if (message == "Pong")
    {
        checkConnect = SUCCESS_CONNECT;
        // Логическая блокировка кнопок connect и разблокировка Disconnect
        ui->Connect->setDisabled(true);
        ui->Disconnect->setDisabled(false);

        disableBtnStyle(ui->Disconnect, ui->Connect);

        popUp->setPopupText("Успешное соединение!");

        ui->lable_session_num->setText(num_session);

        popUp->show();

        QRegExp qe( "^\\s*$" );

        if ( qe.exactMatch(ui->TitleEdit->text()))
        {
            ui->TitleEdit->setText("");
        }

        client->sendMessage("%%%NAME&& " + ui->TitleEdit->text() + "$$$");


        flagMsg = hideMessage;
    }

    if (message == "Streamer: Disconnect")
    {
        flagMsg = hideMessage;
    }

    if(flagMsg == showMessage)
    {
        // Создаем модель и присваеваем delegate для QListView

        ListMessageModel * modelMsg = new ListMessageModel(this);
        ui->MessageBoardList->setModel(modelMsg);
        ui->MessageBoardList->setWordWrap(true);
        ui->MessageBoardList->setItemDelegate(new MessageViewDelegate(this));

        QTime currTime = QTime::currentTime();

        QRegExp re( "([A-zА-я0-9]+)([:]{1})(([\\S+)([\n ]{0,}))" );

        message.replace(QRegularExpression("<br>"), "");
        message.replace(QRegularExpression("<a.*?>.*?<\\/a.*?>"), "[Изображение]");

        // Парсинг сообщения для получения имени и основного текста
        lastPos = 0;
        while( ( lastPos = re.indexIn( message, lastPos ) ) != -1)
        {
            lastPos += re.matchedLength();
            listCounterName.push_back(re.cap(1));
            popUpView(re.cap(1), " написал сообщение!");
            listCounterMsg.push_back(re.cap(3) + " \n");
            listDateMessage.push_back(currTime.toString("hh:mm:ss"));
        }

        // добавление сообщения в QlistView
        for (int index = 0; index < listCounterMsg.length(); index++)
        {
            modelMsg->list.push_front("1"); // Щетчик
            modelMsg->listName << listCounterName[index]; // Добаляем name
            modelMsg->listDescription<< listCounterMsg[index]; // Добаляем message
            modelMsg->listDate << listDateMessage[index]; // Добаляем message
        }

        ui->MessageBoardList->scrollToBottom(); // при новом сообщениии прокрутка вниз

        if(statusBell == hideChat) // Если статус чата hideChat то
        {
            // делаем оповещение о наличии нового сообщения
            ui->ChatBtn->setIcon(QIcon(StyleApp::getLogoNewMessage()));
            ui->ChatBtn->setIconSize(QSize(45,45));
        }
    }
}

int MainWindow::getMsgBoardWidth()
{
    msgBoardWidth = ui->MessageBoardList->width();
    return  msgBoardWidth;
}

void MainWindow::popUpView(QString msg, QString totification)
{
    if(statusBell == hideChat)
    {
        if (msg.split(":")[0] != "")
        {
            popUp->setPopupText(msg.split(":")[0] + " " + totification);
            popUp->show();
        }
    }
}

void MainWindow::on_Settings_clicked() // Слот для отображения/скрытия меню настроек
{
    static int ShowOrHide = 0;
    if(++ShowOrHide % 2) // Если открыт то закрываем, иначе отображаем
    {
        animationStackedWidget->setDuration(100);
        animationStackedWidget->setStartValue(302);
        animationStackedWidget->setEndValue(0);
        animationStackedWidget->start();
    }
    else
    {
        animationStackedWidget->setDuration(100);
        animationStackedWidget->setStartValue(0);
        animationStackedWidget->setEndValue(302);
        animationStackedWidget->start();
    }
}

void MainWindow::on_btn_close_clicked() // Слот выхода из приложения сервера
{
    disconnectFromServer();
    closeApp(); // Закрытие приложения
}

void MainWindow::disconnectFromServer()
{
    client->sendMessage("Disconnect"); // Сигнал о выходе стримира из приложения
}

int MainWindow::closeApp() // Закрытие приложения
{
    exit(0);
}

void MainWindow::on_DarkDesign_clicked() // Метод для переключения на темную тему
{ 
    // Выставление стиля для темы "Dark"
    // Выставление стиля для дефолтной темы "Dark"
    ui->centralWidget->setStyleSheet(StyleApp::getMainDarkBackground());
    ui->sattingStackedWidget->setStyleSheet(StyleApp::getMainDarkBackground());
    ui->scrollAreaEmoji->setStyleSheet(StyleApp::getDarkAreaEmoji());
    ui->hostEdit->setStyleSheet(StyleApp::getDarkBtnStyle());
    ui->spinPort->setStyleSheet(StyleApp::getDarkBtnStyle());
    ui->Connect->setStyleSheet(StyleApp::getDarkBtnStyle());
    ui->ChatBtn->setStyleSheet(StyleApp::getDarkBtnStyle());
    ui->closeUserListPanel->setStyleSheet(StyleApp::getDarkBtnStyle());
    ui->Mute_Button->setStyleSheet(StyleApp::getDarkBtnStyle());
    ui->To_Ban_Button->setStyleSheet(StyleApp::getDarkBtnStyle());
    ui->BtnUserControl->setStyleSheet(StyleApp::getDarkBtnStyle());
    ui->Settings->setStyleSheet(StyleApp::getDarkBtnStyle());
    ui->Disconnect->setStyleSheet(StyleApp::getDarkBtnDisable());
    ui->StartSession->setStyleSheet(StyleApp::getDarkBtnStyle());
    ui->StopSession->setStyleSheet(StyleApp::getDarkBtnStyle());
    ui->send->setStyleSheet(StyleApp::getDarkBtnSend());
    ui->MessageBoardList->setStyleSheet(StyleApp::getDarkMessageBoardList());
    ui->sattingStackedWidget->setStyleSheet("padding: 10px;");
    ui->messageEdit->setStyleSheet(StyleApp::getMainDarkBackground());
    ui->TitleEdit->setStyleSheet(StyleApp::getDarkLineEdit());
    ui->hostEdit->setStyleSheet(StyleApp::getDarkLineEdit());
    ui->lable_session_num->setStyleSheet(StyleApp::getDarkLineEdit());
    ui->lineSearchUserList->setStyleSheet(StyleApp::getDarkLineEdit());
    ui->listViewUser->setStyleSheet(StyleApp::getDarkLineEdit());
    ui->btn_maximize->setStyleSheet(StyleApp::getDarkBtnMaximize());
    ui->btn_minimize->setStyleSheet(StyleApp::getDarkBtnMinimize());
    ui->btn_close->setStyleSheet(StyleApp::getDarkBtnClose());
    ui->groupBoxHost->setStyleSheet(StyleApp::getTitleEdit());
    ui->groupBoxPort->setStyleSheet(StyleApp::getTitleEdit());
    ui->groupBoxNumSession->setStyleSheet(StyleApp::getTitleEdit());
    ui->groupBoxTitleSession->setStyleSheet(StyleApp::getTitleEdit());
    ui->btnSmile->setStyleSheet(StyleApp::getDarkBtnSmile());
    ui->btnClipImage->setStyleSheet(StyleApp::getDarkBtnClipImg());
    ui->lineEditUrlImg->setStyleSheet(StyleApp::getDarkLineEdit());

    ui->ChatBtn->setIcon(QIcon(StyleApp::getBtnShowChatIcon()));
    ui->ChatBtn->setIconSize(QSize(45,45));
    ui->label->setPixmap(StyleApp::getLogoPolytech());

    ui->Settings->setIcon(QIcon(StyleApp::getBtnShowSettingIcon()));
    ui->Settings->setIconSize(QSize(35,35));

    ui->messageEdit->setPlaceholderText("Сообщение...");
    ui->lable_session_num->setPlaceholderText("Номер сессии");
}

void MainWindow::on_To_Ban_Button_clicked() // Панелька со списком юзеров со статусом бан
{
}

void MainWindow::on_Mute_Button_clicked() // Сигнал о мьюте пользователя
{
    if(ui->listViewUser->currentItem())
    {
        if (checkUserInList(mute_user_list, ui->listViewUser->currentItem()->text()) == false) // проверка есть ли user в списке замьюченых
        {
            QString status = "MUTE " + ui->listViewUser->currentItem()->text();
            QString mute = "%%%MUTE&&" + ui->listViewUser->currentItem()->text() + "$$$";
            client->sendMessage(status); // отправка оповещения на сервер
            client->sendMessage(mute); // отправка оповещения на сервер

            QString username = ui->listViewUser->currentItem()->text();

            ui->listViewUser->addItem(new QListWidgetItem(QIcon(StyleApp::getLogoMute()), username));
            mute_user_list.push_back(username);

            delete ui->listViewUser->currentItem();
        }
    }
}

void MainWindow::slot_UnMuteUser(QListWidgetItem* item) // Метод для размьюта пользователя
{
    QString username = ui->listViewUser->currentItem()->text();

    if (checkUserInList(mute_user_list, username) == true) // проверка есть ли user в списке замьюченых
    {
        QString un_mute = "%%%UNMUTE&&" + ui->listViewUser->currentItem()->text() + "$$$";
        QString status = "UNMUTE " + ui->listViewUser->currentItem()->text();
        client->sendMessage(status); // отправка оповещения на сервер
        client->sendMessage(un_mute); // отправка оповещения на сервер

        ui->listViewUser->addItem(new QListWidgetItem(QIcon(StyleApp::getLogoStudent()), username));

        mute_user_list.remove(username); // Удаляем user-a из списка mute_user_list

        delete ui->listViewUser->currentItem();
    }
    if (checkUserInList(bun_user_list, username) == true)
    {
        QString un_mute = "%%%UNBROKEN&&" + ui->listViewUser->currentItem()->text() + "$$$";
        QString status = "UNBROKEN: " + ui->listViewUser->currentItem()->text();
        client->sendMessage(status); // отправка оповещения на сервер
        client->sendMessage(un_mute); // отправка оповещения на сервер

        ui->listViewUser->addItem(new QListWidgetItem(QIcon(StyleApp::getLogoStudent()), username));

        bun_user_list.remove(username); // Удаляем user-a из списка ban_user_list

        delete ui->listViewUser->currentItem();
    }
}

void MainWindow::on_lineSearchUserList_textChanged(const QString &arg1) // поиск в списке пользователей
{
    hide_all(ui->listViewUser);
    QList<QListWidgetItem*> matches ( ui->listViewUser->findItems(arg1, Qt::MatchFlag::MatchContains) );
    for(QListWidgetItem* item : matches)
        item->setHidden(false);
}

// метод для скрытия неподходящих пользователей при поимке
void MainWindow::hide_all(QListWidget *listWidjet)
{
    for(int row(0); row < listWidjet->count(); row++ )
        listWidjet->item(row)->setHidden(true);
}

// метод для проверки на наличие в списке
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

// Анимация открытия и закрытия чата
void MainWindow::on_ChatBtn_clicked()
{
    static int ShowOrHide = 0;

    if(++ShowOrHide % 2) // Если открыт то закрываем, иначе отображаем
    {
        animationPnlChat->setDuration(100);
        animationPnlChat->setStartValue(500);
        animationPnlChat->setEndValue(0);
        animationPnlChat->start();

        statusBell = hideChat; // Статус для оповещения
    }
    else
    {
        animationPnlChat->setDuration(100);
        animationPnlChat->setStartValue(0);
        animationPnlChat->setEndValue(500);
        animationPnlChat->start();

        ui->ChatBtn->setIcon(QIcon(StyleApp::getLogoDefMessage()));
        ui->ChatBtn->setIconSize(QSize(45,45));

        statusBell = showChat; // Статус для оповещения
    }
}

// отоброжение номера трансляции
void MainWindow::onNumberSession(QString num_session)
{
    this->num_session = num_session;
}

void MainWindow::disableBtnStyle(QPushButton *btn, QPushButton *disableBtn)
{
    btn->setStyleSheet(StyleApp::getDarkBtnStyle());
    disableBtn->setStyleSheet(StyleApp::getDarkBtnDisable());
}

void MainWindow::on_MessageBoardList_doubleClicked(const QModelIndex &index)
{
    QString str = index.data().toString();
    qDebug() << str;
}

void MainWindow::on_MessageBoardList_clicked(const QModelIndex &index)
{
//    QString str = index.data().toString();
//    qDebug() << str;
}

void MainWindow::slot_muteUser()
{

//    int row = ui->MessageBoardList->selectionModel()->currentIndex().row();

    if (!listCounterName.isEmpty() && !userList.empty())
    {
        QModelIndex index = ui->MessageBoardList->currentIndex();
        QString username = index.data(Qt::DisplayRole).toString();

        if (username != "Streamer")
        {
            QList<QListWidgetItem *> items = ui->listViewUser->findItems(username, Qt::MatchExactly);
            int row = ui->listViewUser->row(items.first());

            if (checkUserInList(mute_user_list, username) == false)
            {
                QString status = "MUTE " + username;
                QString mute = "%%%MUTE&&" + username + "$$$";
                client->sendMessage(status); // отправка оповещения на сервер
                client->sendMessage(mute); // отправка оповещения на сервер
                mute_user_list.push_back(username);

                delete ui->listViewUser->takeItem(row);

                ui->listViewUser->addItem(new QListWidgetItem(QIcon(StyleApp::getLogoMute()), username));
            }
        }
    }
}

void MainWindow::slot_unMuteUser()
{
    if (!listCounterName.isEmpty() && !userList.empty())
    {
        QModelIndex index = ui->MessageBoardList->currentIndex();
        QString username = index.data(Qt::DisplayRole).toString();
        if (username != "Streamer")
        {
            QList<QListWidgetItem *> items = ui->listViewUser->findItems(username, Qt::MatchExactly);
            int row = ui->listViewUser->row(items.first());

            if (checkUserInList(mute_user_list, username) == true)
            {
                QString status = "UNMUTE " + username;
                QString un_mute = "%%%UNMUTE&&" + username + "$$$";
                client->sendMessage(status); // отправка оповещения на сервер
                client->sendMessage(un_mute); // отправка оповещения на сервер

                mute_user_list.remove(username); // Удаляем user-a из списка mute_user_list

                delete ui->listViewUser->takeItem(row);

                ui->listViewUser->addItem(new QListWidgetItem(QIcon(StyleApp::getLogoStudent()), username));
            }
        }
    }
}

template<class T1, class T2>
QString MainWindow::muteOrUnMute(const list<T1> &lst, T2 msg, T2 lastName)
{
    for (auto i = lst.cbegin(); i != lst.cend(); i++)
    {
        if(lastName != *i)
        {
            msg += *i + "&&";
            qDebug() << *i;
        }
        else
        {
            msg += *i + "$$$";
        }
    }
    return msg;
}

void MainWindow::slot_muteAllUser()
{
    if (!listCounterName.isEmpty() && !userList.empty())
    {
        QString muteAll = "%%%MUTE&&";
        QString lastUser = userList.back();
        muteAll = muteOrUnMute(userList, muteAll, lastUser);
        client->sendMessage(muteAll);
    }
}

void MainWindow::slot_unMuteAllUser()
{
    if (!listCounterName.isEmpty() && !userList.empty())
    {
        QString UnMuteAll = "%%%UNMUTE&&";
        QString lastUser = userList.back();
        UnMuteAll = muteOrUnMute(userList, UnMuteAll, lastUser);
        client->sendMessage(UnMuteAll);
    }
}

void MainWindow::slot_unBanAllUser(){
    popUp->setPopupText("Не реализовано!");
    popUp->show();
}

void MainWindow::slot_banAllUser(){
    popUp->setPopupText("Не реализовано!");
    popUp->show();
}

void MainWindow::on_MessageBoardList_customContextMenuRequested(const QPoint &pos)
{
    /* Создаем объект контекстного меню */
    QMenu * menu = new QMenu();

    /* Создаём действия для контекстного меню */
    menu->setStyleSheet(StyleApp::getDarkContextMenu());

    QAction * Mute = new QAction(trUtf8("Mute"), this);
    QAction * Ban = new QAction(trUtf8("Ban"), this);

    QAction * Unmute = new QAction(trUtf8("Unmute"), this);
    QAction * Unbun = new QAction(trUtf8("Unban"), this);

    QAction * MuteAll = new QAction(trUtf8("Mute All"), this);
    QAction * UnMuteAll = new QAction(trUtf8("Unmute All"), this);

    /* Подключаем СЛОТы обработчики для действий контекстного меню */
    connect(Mute, SIGNAL(triggered()), this, SLOT(slot_muteUser()));     // Обработчик вызова диалога редактирования
    connect(MuteAll, SIGNAL(triggered()), this, SLOT(slot_muteAllUser()));     // Обработчик вызова диалога редактирования
    connect(UnMuteAll, SIGNAL(triggered()), this, SLOT(slot_unMuteAllUser()));
    connect(Unmute, SIGNAL(triggered()), this, SLOT(slot_unMuteUser()));     // Обработчик вызова диалога редактирования
    connect(Unbun, SIGNAL(triggered()), this, SLOT(slot_unBanAllUser()));
    connect(Ban, SIGNAL(triggered()), this, SLOT(slot_banAllUser()));

    /* Устанавливаем действия в меню */
    menu->addAction(Mute);
    menu->addAction(Ban);
    menu->addSeparator();

    //*********************************
    menu->addAction(Unmute);
    menu->addAction(Unbun);
    menu->addSeparator();

    //*********************************
    menu->addAction(MuteAll);
    menu->addAction(UnMuteAll);

    /* Вызываем контекстное меню */
    menu->popup(ui->MessageBoardList->viewport()->mapToGlobal(pos));
}

// При соединении что-то пошло не так
void MainWindow::FailedConnect()
{
    disableBtnStyle(ui->Connect, ui->Disconnect);

    // Логическая блокировка кнопок Disconnect и разблокировка connect
    ui->Connect->setDisabled(false);
    ui->Disconnect->setDisabled(true);

    ui->lable_session_num->clear();
}

QString MainWindow::getHost()
{
    return ui->hostEdit->text();
}

unsigned int MainWindow::getPort()
{
    unsigned int port = ui->spinPort->value();
    return port;
}

void MainWindow::on_BtnUserControl_clicked() // Открытие/закрытие панельки со списком юзеров
{
    ui->sattingStackedWidget->setCurrentIndex(1);
}

void MainWindow::on_closeUserListPanel_clicked()
{
    ui->sattingStackedWidget->setCurrentIndex(0);
}

void MainWindow::on_btnSmile_clicked()
{
    if(ui->stackedWidgetForMessage->isVisible() == true)
        if(ui->stackedWidgetForMessage->currentIndex() == 1){
            ui->stackedWidgetForMessage->setSizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::Minimum);
            ui->stackedWidgetForMessage->setCurrentIndex(0);
        }
        else
            ui->stackedWidgetForMessage->hide();
    else{
        ui->stackedWidgetForMessage->setCurrentIndex(0);
        ui->stackedWidgetForMessage->setSizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::Minimum);
        ui->stackedWidgetForMessage->show();
    }
}

void MainWindow::on_btnClipImage_clicked()
{
    if(ui->stackedWidgetForMessage->isVisible() == true)
        if(ui->stackedWidgetForMessage->currentIndex() == 0){
            int w = ui->stackedWidgetForMessage->width();
            ui->stackedWidgetForMessage->setSizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::Maximum);
            ui->stackedWidgetForMessage->setCurrentIndex(1);
        }
        else
            ui->stackedWidgetForMessage->hide();
    else {
        ui->stackedWidgetForMessage->setCurrentIndex(1);
        ui->stackedWidgetForMessage->setSizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::Maximum);
        ui->stackedWidgetForMessage->show();
    }
}
