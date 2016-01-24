#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QSettings settings(QSettings::IniFormat, QSettings::UserScope, "kravasuper", "TolokaNew");
    settings.setValue("editor/wrapMargin", 68);

    QIcon icon(":/tray_icon.png");
    m_ptrTrayIcon = new QSystemTrayIcon(this);
    m_ptrTrayIcon->setIcon(icon);
    m_ptrTrayIcon->setVisible(true);

    timer = new QTimer;
    QObject::connect(timer, SIGNAL(timeout()),this, SLOT(GetRequest()));
    timer->start(10000);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::writeSettings()
{
    QSettings settings(QSettings::IniFormat, QSettings::UserScope, "kravasuper", "TolokaNew");
    settings.beginGroup("Settings");
    settings.setValue("size", size());
    settings.setValue("pos", pos());
    settings.endGroup();
}

void MainWindow::readSettings()
{
    QSettings settings(QSettings::IniFormat, QSettings::UserScope, "kravasuper", "TolokaNew");
    settings.beginGroup("Settings");
    settings.value("size", QSize(400, 400)).toSize();
    settings.value("pos", QPoint(200, 200)).toPoint();
    settings.endGroup();
}

void MainWindow::GetRequest()
{
    QNetworkRequest request;
    request.setUrl(QUrl("https://toloka.yandex.ru/api/pools"));
    request.setHeader(QNetworkRequest::ContentTypeHeader,"application/json;charset=UTF-8");
    request.setRawHeader("Cookie","");

    QNetworkAccessManager *manager = new QNetworkAccessManager(this);
    connect(manager, SIGNAL(finished(QNetworkReply*)), this, SLOT(GetReplyFinished(QNetworkReply*)));
    manager->get(request);
}

//https://oauth.yandex.ru/authorize?response_type=token&client_id=4249a57ad4a444b0ae2b1e30778eeaba&state=toloka.yandex.ru

void MainWindow::GetReplyFinished(QNetworkReply* reply)
{
    QString content = reply->readAll();
    ui->label->setText(content);
    if (content != "[ ]") {
        emit trayShowMessage(content);
    } else {
        qDebug() <<"Ответ: " << "нет заданий";
    }
}

void MainWindow::trayShowMessage(QString content)
{
    qDebug() <<"Ответ: " << content;
    m_ptrTrayIcon->showMessage("Toloka", "Есть новое задание", QSystemTrayIcon::Information, 5000);
}
