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
    delete user_in_list;
    delete popUp;
}

void MainWindow::settingDesigner() // Вид и проверки для hostEdit, spinPort, connect;
{
    ui->GroupUserListWidget->hide();
    ui->Mute_Button->hide();
    ui->pnlLogs->hide();
    ui->TitleEdit->setPlaceholderText("Title");

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
//    ui->hostEdit->setText("127.0.0.1");

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

    cursorTracking(); // отслеживание курсора
    shadowEffect(); // эффект тени для растягивания окна приложения

    // позволяет нажать кнопку send с помощью Enter
    ui->label->setDisabled(true);

    ui->Connect->setDisabled(false);
    ui->Disconnect->setDisabled(true);

    // Только для чтения информации
    ui->logBoard->setReadOnly(true);
    ui->MessageBoardList->setContextMenuPolicy(Qt::CustomContextMenu);
    ui->MessageBoardList->setStyleSheet(StyleApp::getDarkMessageBoardItem());
    ui->MessageBoardList->verticalScrollBar()->setStyleSheet(StyleApp::getInvisibleStyle());

    // дефолтная тема приложения
    on_DarkDesign_clicked();

    // дефолтный статус о состоянии окна чата
    statusBell = showChat;
}

void MainWindow::cursorTracking()
{
    // Разрешаем остлеживание курсора по всему приложению (блокам)
    ui->centralWidget->setMouseTracking(true);
    ui->titleBar->setMouseTracking(true);
    ui->pnlSettings->setMouseTracking(true);
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

    ui->logBoard->append("Connection attempt...");
    if (ui->TitleEdit->text() == "")
    {
        popUp = new PopUp();
        popUp->setPopupText("Введите название стрима!");
        popUp->show();
    }
    else if (ui->hostEdit->text() == "")
    {
        popUp = new PopUp();
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
    FailedConnect("Disconnected");
}

void MainWindow::onSendMessageBtnClick() // Слот для кнопки отправки сообщения
{
    QString test = ui->textEdit->toPlainText();

    // to do
    // Сделать регулярку для проверки на множество пробелов
    if(ui->textEdit->toPlainText() != "") // Проверка на пустое сообщение
    {
        client->sendMessage(ui->textEdit->toPlainText()); // отправка сообщения
        ui->textEdit->clear(); // очищение отправленного сообщения
    }
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
        user_in_list = new QListWidgetItem(QIcon(StyleApp::getLogoStudent()), re.cap( 1 ));
        userList.push_front(re.cap( 1 ));
        ui->listViewUser->addItem(user_in_list);
        flagMsg = hideMessage;
        popUpТotification(re.cap( 1 ), "подключился!");
    }

    if (message == "Pong")
    {
        checkConnect = SUCCESS_CONNECT;
        // Логическая блокировка кнопок connect и разблокировка Disconnect
        ui->Connect->setDisabled(true);
        ui->Disconnect->setDisabled(false);

        disableBtnStyle(ui->Disconnect, ui->Connect);

        popUp = new PopUp();
        popUp->setPopupText("Успешное соединение!");

        ui->logBoard->append("Сессия №" + num_session);
        ui->lable_session_num->setText(num_session);

        popUp->show();

        client->sendMessage("%%%NAME&&" + ui->TitleEdit->text() + "$$$");

        flagMsg = hideMessage;
    }

    if (message == "Streamer: Disconnect")
    {
        flagMsg = hideMessage;
        ui->logBoard->append("Disconected...");
    }


    if(flagMsg == showMessage)
    {
        // Создаем модель и присваеваем delegate для QListView
        ListMessageModel * modelMsg = new ListMessageModel(this);
        ui->MessageBoardList->setModel(modelMsg);
        ui->MessageBoardList->setWordWrap(true);
        ui->MessageBoardList->setItemDelegate(new MessageViewDelegate(this));

        QRegExp re( "([A-zА-я0-9]+)([:]{1})(([\\S+)([\n ]{0,}))" );

        // Парсинг сообщения для получения имени и основного текста
        int lastPos = 0;
        while( ( lastPos = re.indexIn( message, lastPos ) ) != -1)
        {
            lastPos += re.matchedLength();
            listCounterName.push_back(re.cap(1));
            ui->logBoard->append(re.cap(1)+" написал сообщение!"); // Ведём логи....
            popUpТotification(re.cap(1), " написал сообщение!");
            listCounterMsg.push_back(re.cap(3) + " \n");
        }

        // добавление сообщения в QlistView
        for (int index = 0; index < listCounterMsg.length(); index++)
        {
            modelMsg->list.push_front("1"); // Щетчик
            modelMsg->listName << listCounterName[index]; // Добаляем name
            modelMsg->listDescription<< listCounterMsg[index]; // Добаляем message
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

void MainWindow::popUpТotification(QString msg, QString totification)
{
    if(statusBell == hideChat)
    {
        popUp = new PopUp();

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
        QPropertyAnimation *animation = new QPropertyAnimation(ui->pnlSettings, "maximumWidth"); //wdgSMS is your widget
        animation->setDuration(100);
        animation->setStartValue(302);
        animation->setEndValue(0);
        animation->start();
    }
    else
    {
        QPropertyAnimation *animation = new QPropertyAnimation(ui->pnlSettings, "maximumWidth");
        animation->setDuration(100);
        animation->setStartValue(0);
        animation->setEndValue(302);
        animation->start();
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

    ui->hostEdit->setStyleSheet(StyleApp::getDarkBtnStyle());
    ui->spinPort->setStyleSheet(StyleApp::getDarkBtnStyle());
    ui->Connect->setStyleSheet(StyleApp::getDarkBtnStyle());
    ui->ChatBtn->setStyleSheet(StyleApp::getDarkBtnStyle());
    ui->Settings->setStyleSheet(StyleApp::getDarkBtnStyle());
    ui->Disconnect->setStyleSheet(StyleApp::getDarkBtnDisable());
    ui->StartSession->setStyleSheet(StyleApp::getDarkBtnStyle());
    ui->StopSession->setStyleSheet(StyleApp::getDarkBtnStyle());
    ui->send->setStyleSheet(StyleApp::getDarkBtnStyle());

    ui->btn_maximize->setStyleSheet(StyleApp::getDarkBtnMaximize());
    ui->btn_minimize->setStyleSheet(StyleApp::getDarkBtnMinimize());
    ui->btn_close->setStyleSheet(StyleApp::getDarkBtnClose());

    ui->label->setText(StyleApp::getLogoPolytech());

    ui->ChatBtn->setIcon(QIcon(StyleApp::getBtnShowChatIcon()));
    ui->ChatBtn->setIconSize(QSize(45,45));

    ui->Settings->setIcon(QIcon(StyleApp::getBtnShowSettingIcon()));
    ui->Settings->setIconSize(QSize(35,35));

    ui->textEdit->setPlaceholderText("Message...");
    ui->lable_session_num->setText("#STREAM");
}

void MainWindow::on_BtnUserControl_clicked() // Открытие/закрытие панельки со списком юзеров
{
    if(ui->GroupUserListWidget->isVisible()){
        ui->GroupUserListWidget->hide();
//        ui->To_Ban_Button->hide();
        ui->Mute_Button->hide();
    }
    else
    {
        ui->GroupUserListWidget->show();
//        ui->To_Ban_Button->show();
        ui->Mute_Button->show();
    }

}

void MainWindow::on_To_Ban_Button_clicked() // Панелька со списком юзеров со статусом бан
{
//    if(ui->listViewUser->currentItem())
//    {
//        QString status = "BAN " + ui->listViewUser->currentItem()->text(); // само сообщение
//        client->sendMessage(status); // отправка оповещения на сервер

//        QString username = ui->listViewUser->currentItem()->text();
//        user_in_list = new QListWidgetItem(QIcon(StyleApp::getLogoBan()), username);
//        ui->listViewUser->addItem(user_in_list);

//        bun_user_list.push_back(username);

//        delete ui->listViewUser->currentItem();
//    }
}

void MainWindow::on_Mute_Button_clicked() // Сигнал о мьюте пользователя
{
    if(ui->listViewUser->currentItem())
    {
        QString status = "MUTE " + ui->listViewUser->currentItem()->text();
        QString mute = "%%%MUTE&&" + ui->listViewUser->currentItem()->text() + "$$$";
        client->sendMessage(status); // отправка оповещения на сервер
        client->sendMessage(mute); // отправка оповещения на сервер

        QString username = ui->listViewUser->currentItem()->text();
        user_in_list = new QListWidgetItem(QIcon(StyleApp::getLogoMute()), username);
        ui->listViewUser->addItem(user_in_list);

        mute_user_list.push_back(username);

        delete ui->listViewUser->currentItem();
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

        item = new QListWidgetItem(QIcon(StyleApp::getLogoStudent()), username);
        ui->listViewUser->addItem(item);

        mute_user_list.remove(username); // Удаляем user-a из списка mute_user_list

        delete ui->listViewUser->currentItem();
    }
    if (checkUserInList(bun_user_list, username) == true)
    {
        QString un_mute = "%%%UNBROKEN&&" + ui->listViewUser->currentItem()->text() + "$$$";
        QString status = "UNBROKEN: " + ui->listViewUser->currentItem()->text();
        client->sendMessage(status); // отправка оповещения на сервер
        client->sendMessage(un_mute); // отправка оповещения на сервер

        item = new QListWidgetItem(QIcon(StyleApp::getLogoStudent()), username);
        ui->listViewUser->addItem(item);

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
    QPropertyAnimation *animation = new QPropertyAnimation(ui->pnlChat, "maximumWidth");

    static int ShowOrHide = 0;

    if(++ShowOrHide % 2) // Если открыт то закрываем, иначе отображаем
    {
        animation->setDuration(100);
        animation->setStartValue(500);
        animation->setEndValue(0);
        animation->start();

        statusBell = hideChat; // Статус для оповещения
    }
    else
    {
        animation->setDuration(100);
        animation->setStartValue(0);
        animation->setEndValue(500);
        animation->start();

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
            if (checkUserInList(mute_user_list, username) == false)
            {
                QString status = "MUTE " + username;
                QString mute = "%%%MUTE&&" + username + "$$$";
                client->sendMessage(status); // отправка оповещения на сервер
                client->sendMessage(mute); // отправка оповещения на сервер
                mute_user_list.push_back(username);
            }
            else
            {
                QString status = "UNMUTE " + username;
                QString un_mute = "%%%UNMUTE&&" + username + "$$$";
                client->sendMessage(status); // отправка оповещения на сервер
                client->sendMessage(un_mute); // отправка оповещения на сервер

                mute_user_list.remove(username); // Удаляем user-a из списка mute_user_list
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
        qDebug() << muteAll;
        qDebug() << muteAll;
        client->sendMessage(muteAll);
    }
}

void MainWindow::slot_unMuteAllUser()
{
    if (!listCounterName.isEmpty() && !userList.empty())
    {
        QString UnMuteAll = "%%%UNMUTE&&";
        QString lastUser = userList.back();
        qDebug() << UnMuteAll;
        UnMuteAll = muteOrUnMute(userList, UnMuteAll, lastUser);
        qDebug() << UnMuteAll;
        client->sendMessage(UnMuteAll);
    }
}

void MainWindow::on_MessageBoardList_customContextMenuRequested(const QPoint &pos)
{
    /* Создаем объект контекстного меню */
        QMenu * menu = new QMenu();
        /* Создаём действия для контекстного меню */
        menu->setStyleSheet(StyleApp::getDarkContextMenu());

        QAction * Mute = new QAction(trUtf8("Mute / Unmute"), this);
        QAction * MuteAll = new QAction(trUtf8("Mute All"), this);
        QAction * UnMuteAll = new QAction(trUtf8("Unmute All"), this);
        QAction * Bun = new QAction(trUtf8("Bun / Allow"), this);
        /* Подключаем СЛОТы обработчики для действий контекстного меню */

        Mute->setIcon(QIcon(StyleApp::getLogoMute()));
        MuteAll->setIcon(QIcon(":/image/muteAll.png"));
        UnMuteAll->setIcon(QIcon(":/image/unMuteAll.png"));
        Bun->setIcon(QIcon(StyleApp::getLogoBan()));



        connect(Mute, SIGNAL(triggered()), this, SLOT(slot_muteUser()));     // Обработчик вызова диалога редактирования
        connect(MuteAll, SIGNAL(triggered()), this, SLOT(slot_muteAllUser()));     // Обработчик вызова диалога редактирования
        connect(UnMuteAll, SIGNAL(triggered()), this, SLOT(slot_unMuteAllUser()));
        /* Устанавливаем действия в меню */
        menu->addAction(Mute);
        menu->addAction(Bun);
        menu->addAction(MuteAll);
        menu->addAction(UnMuteAll);

        /* Вызываем контекстное меню */
        menu->popup(ui->MessageBoardList->viewport()->mapToGlobal(pos));
}

// При соединении что-то пошло не так
void MainWindow::FailedConnect(QString Error)
{
    popUp = new PopUp();
    popUp->setPopupText(Error);
    popUp->show();

    disableBtnStyle(ui->Connect, ui->Disconnect);

    // Логическая блокировка кнопок Disconnect и разблокировка connect
    ui->Connect->setDisabled(false);
    ui->Disconnect->setDisabled(true);

    ui->lable_session_num->setText("#STREAM");
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


void MainWindow::on_btnShowLogs_clicked()
{
    if(ui->pnlLogs->isVisible())
    {
        ui->pnlLogs->hide();
    }
    else
    {
        ui->pnlLogs->show();
    }
}
