#ifndef ADDLOCK_H
#define ADDLOCK_H

#include <QDialog>
#include <QNetworkAccessManager>
#include <QJsonDocument>
#include <QJsonObject>
#include <QNetworkReply>
#include <QJsonArray>
namespace Ui {
class AddLock;
}

class AddLock : public QDialog
{
    Q_OBJECT

public:
    explicit AddLock(QWidget *parent = nullptr);
    ~AddLock();

private slots:
    void on_pushButton_released();

    void on_pushButton_2_released();

private:
    Ui::AddLock *ui;
    QNetworkAccessManager *networkManager;
    QNetworkReply *reply;
    QJsonArray FingerData;
};

#endif // ADDLOCK_H
