#ifndef FINGER_H
#define FINGER_H

#include <QDialog>
#include <QUrl>
#include <QNetworkAccessManager>
#include <QJsonDocument>
#include <QJsonObject>
#include <QNetworkReply>
#include <QString>
#include "FPModule_SDK.h"
#include <QJsonArray>
#include <QMessageBox>
#include "FPModule_SDK.h"
#include <QDateTime>

namespace Ui {
class Finger;
}

class Finger : public QDialog
{
    Q_OBJECT

public:
    explicit Finger(QWidget *parent = nullptr);
    void FlashTable();
    ~Finger();

private slots:
    void on_pushButton_released();

    void on_pushButton_2_released();

private:
    Ui::Finger *ui;
    QNetworkAccessManager *networkManager;
    QNetworkReply *reply;
};

#endif // FINGER_H
