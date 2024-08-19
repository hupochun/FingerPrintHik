#ifndef GETLOCK_H
#define GETLOCK_H

#include <QDialog>
#include <QNetworkAccessManager>
#include <QJsonDocument>
#include <QJsonObject>
#include <QNetworkReply>
#include "addlock.h"
namespace Ui {
class GetLock;
}

class GetLock : public QDialog
{
    Q_OBJECT

public:
    explicit GetLock(QWidget *parent = nullptr);
    ~GetLock();

private slots:
    void on_pushButton_released();

    void on_pushButton_2_released();

    void on_pushButton_3_released();

private:
    Ui::GetLock *ui;
    QNetworkAccessManager *networkManager;
    QNetworkReply *reply;
    int RowCount;
    AddLock* m_AddLock;
};

#endif // GETLOCK_H
