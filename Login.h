#ifndef LOGIN_H
#define LOGIN_H

#include <QDialog>
#include <QUrl>
#include <QNetworkAccessManager>
#include <QJsonDocument>
#include <QJsonObject>
#include <QNetworkReply>
#include <QDebug>
#include "mainwindow.h"
#include <QMessageBox>
#include <QAction>
namespace Ui {
class Login;
}

class Login : public QDialog
{
    Q_OBJECT

public:
    explicit Login(QWidget *parent = nullptr);
    ~Login();
    QString GetToken();

private slots:
    void on_pushButton_released();
    void replyFinished();

    void on_pushButton_2_released();

private:
    Ui::Login *ui;
    QNetworkAccessManager *networkManager;
    QNetworkReply *reply;
    QString token;
};

#endif // LOGIN_H
