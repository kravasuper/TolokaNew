#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTimer>
#include <QNetworkReply>
#include <QNetworkRequest>
#include <QNetworkAccessManager>
#include <QSystemTrayIcon>
#include <QSettings>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    QSystemTrayIcon *m_ptrTrayIcon;
    QTimer *timer;
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

public slots:
    void GetRequest();
    void GetReplyFinished(QNetworkReply* reply);
    void trayShowMessage(QString content);

    void writeSettings();
    void readSettings();

private:
    Ui::MainWindow *ui;

private slots:

};

#endif // MAINWINDOW_H
