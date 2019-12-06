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
    delete popUp;
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

    cursorTracking(); // отслеживание курсора
    shadowEffect(); // эффект тени для растягивания окна приложения

    // позволяет нажать кнопку send с помощью Enter
    ui->send->setShortcut(Qt::Key_Return);

    ui->label->setDisabled(true);

    ui->Connect->setDisabled(false);
    ui->Disconnect->setDisabled(true);

    // Только для чтения информации
    ui->messageBoard->setReadOnly(true);

    // Скрыл блэк лист
    ui->ShowBlacklist->hide();
    ui->To_Ban_Button->hide();

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
    unsigned int port = ui->spinPort->value();

    ui->messageBoard->append("Connection attempt...");

    client->connectSocket(ui->hostEdit->text(), port);

    qDebug() << "FAILURE_CONNECT1";
}

void MainWindow::onDisconnectBtnClick() // Слот для кнопки отключения от сервера
{
    // Логическая блокировка кнопок Disconnect и разблокировка connect
    ui->Connect->setDisabled(false);
    ui->Disconnect->setDisabled(true);

    disableBtnStyle(ui->Connect, ui->Disconnect);

    client->sendMessage("Disconnect");

    checkConnect = FAILURE_CONNECT;
    qDebug() << "FAILURE_CONNECT3";

    ui->listViewUser->clear();
    userList.clear();
    qDebug() << userList;
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

    flagMsg = showMessage;

    QRegExp re( "[%]{3}([\\S ]+)[$]{3}" );

    int lastPos = 0;
    while( ( lastPos = re.indexIn( message, lastPos ) ) != -1)
    {
        lastPos += re.matchedLength();
        user_in_list = new QListWidgetItem(QIcon(StyleApp::getLogoStudent()), re.cap( 1 ));
        userList.push_back(re.cap( 1 ));
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

        ui->messageBoard->append("Сессия №" + num_session);
        ui->lable_session_num->setText(num_session);

        popUp->show();

        flagMsg = hideMessage;

        qDebug() << "SUCCESS_CONNECT";
    }

    if(flagMsg == showMessage)
    {
        popUpТotification(message, "написал сообщение!");
        ui->messageBoard->append(fullMessage); // отображение пришедшего сообщения
    }
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
    ui->messageEdt->setStyleSheet(StyleApp::getDarkBtnStyle());
    ui->StartSession->setStyleSheet(StyleApp::getDarkBtnStyle());
    ui->StopSession->setStyleSheet(StyleApp::getDarkBtnStyle());
    ui->verticalSp->setStyleSheet(StyleApp::getInvisibleStyle());

    ui->btn_maximize->setStyleSheet(StyleApp::getDarkBtnMaximize());
    ui->btn_minimize->setStyleSheet(StyleApp::getDarkBtnMinimize());
    ui->btn_close->setStyleSheet(StyleApp::getDarkBtnClose());

    ui->label->setText(StyleApp::getLogoPolytech());

    ui->ChatBtn->setIcon(QIcon(StyleApp::getBtnShowChatIcon()));
    ui->ChatBtn->setIconSize(QSize(45,45));

    ui->Settings->setIcon(QIcon(StyleApp::getBtnShowSettingIcon()));
    ui->Settings->setIconSize(QSize(35,35));

    ui->messageEdt->setPlaceholderText("Message...");
    ui->lable_session_num->setText("#STREAM");
}

void MainWindow::on_BtnUserControl_clicked() // Открытие/закрытие панельки со списком юзеров
{
    if(ui->GroupUserListWidget->isVisible()){
        ui->GroupUserListWidget->hide();
//        ui->To_Ban_Button->hide();
        ui->Mute_Button->hide();
        ui->verticalSp->show();
    }
    else
    {
        ui->GroupUserListWidget->show();
//        ui->To_Ban_Button->show();
        ui->Mute_Button->show();
        ui->verticalSp->hide();
    }

}

void MainWindow::on_To_Ban_Button_clicked() // Панелька со списком юзеров со статусом бан
{
    // to do
    // Реализовать запрос на сервер для бана пользователя с трансляции
    if(ui->listViewUser->currentItem())
    {
        QString status = "BAN: " + ui->listViewUser->currentItem()->text(); // само сообщение
        client->sendMessage(status); // отправка оповещения на сервер

        QString username = ui->listViewUser->currentItem()->text();
        user_in_list = new QListWidgetItem(QIcon(StyleApp::getLogoBan()), username);
        ui->user_blacklist->addItem(user_in_list);

        bun_user_list.push_back(username);

        delete ui->listViewUser->currentItem();
    }
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

void MainWindow::on_ShowBlacklist_clicked() // Открытие/закрытие панельки с забаненными пользователями
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

void MainWindow::slot_UnbrokenUser(QListWidgetItem* item) // Метод для разбана пользователя
{
    QString username = ui->user_blacklist->currentItem()->text();

    QString status = "UNBROKEN: " + ui->listViewUser->currentItem()->text();
    client->sendMessage(status); // отправка оповещения на сервер

    item = new QListWidgetItem(QIcon(StyleApp::getLogoStudent()), username);
    ui->listViewUser->addItem(item);

    bun_user_list.remove(username);// Удаляем user-a из списка ban_user_list

    delete ui->user_blacklist->currentItem();
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
}

void MainWindow::on_lineSearchUserList_textChanged(const QString &arg1) // поиск в списке пользователей
{
    hide_all(ui->listViewUser);
    QList<QListWidgetItem*> matches ( ui->listViewUser->findItems(arg1, Qt::MatchFlag::MatchContains) );
    for(QListWidgetItem* item : matches)
        item->setHidden(false);
}

void MainWindow::on_lineSearchBanUserList_textChanged(const QString &arg1) // поиск в списке забаненных
{
    hide_all(ui->user_blacklist);
    QList<QListWidgetItem*> matches ( ui->user_blacklist->findItems(arg1, Qt::MatchFlag::MatchContains) );
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

void MainWindow::on_messageBoard_textChanged()
{
    if(statusBell == hideChat) // Если статус чата hideChat то
    {
        // делаем оповещение о наличии нового сообщения
        ui->ChatBtn->setIcon(QIcon(StyleApp::getLogoNewMessage()));
        ui->ChatBtn->setIconSize(QSize(45,45));
    }

    if(checkConnect == FAILURE_CONNECT){
        qDebug() << "FAILURE_CONNECT2";
        FailedConnect();
    }
}

// отоброжение номера трансляции
void MainWindow::onNumberSession(QString num_session)
{
    this->num_session = num_session;
}

// При соединении что-то пошло не так
void MainWindow::FailedConnect()
{
    popUp = new PopUp();
    popUp->setPopupText("Соединение разорвано!");
    popUp->show();

    disableBtnStyle(ui->Connect, ui->Disconnect);

    // Логическая блокировка кнопок Disconnect и разблокировка connect
    ui->Connect->setDisabled(false);
    ui->Disconnect->setDisabled(true);

    ui->lable_session_num->setText("#STREAM");
}

void MainWindow::disableBtnStyle(QPushButton *btn, QPushButton *disableBtn)
{
    btn->setStyleSheet(StyleApp::getDarkBtnStyle());
    disableBtn->setStyleSheet(StyleApp::getDarkBtnDisable());
}

