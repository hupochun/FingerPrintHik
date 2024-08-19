#include "addlock.h"
#include "ui_addlock.h"
#include <QMessageBox>
#include <QJsonArray>
extern QString IPAddress;
extern QString Token;
extern QVector<QString> GetLockID;
extern QString UserID;
extern QString UserName;
extern QString DeptID;
extern QString DeptName;
QString jsonArrayToString(const QJsonArray &jsonArray) {
    QString result;

    for (const QJsonValue &value : jsonArray) {
        if (value.isString()) {
            result += value.toString();
        }
    }

    return result;
}
QJsonArray vectorToJsonArray(const QVector<QString> &vector) {
    QJsonArray jsonArray;

    for (const QString &str : vector) {
        jsonArray.append(QJsonValue(str));
    }

    return jsonArray;
}

AddLock::AddLock(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::AddLock)
{
    ui->setupUi(this);
    ui->label_2->setText(UserID);
    ui->label_4->setText(UserName);
    ui->label_6->setText(DeptName);
}

AddLock::~AddLock()
{
    delete ui;
}

void AddLock::on_pushButton_released()
{
    networkManager = new QNetworkAccessManager(this);
    QUrl url("http://localhost:8712/enter_finger");
    QNetworkRequest request(url);
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");
    request.setRawHeader("Connection", "Keep-Alive");
    QByteArray QJsondata;
    reply=networkManager->post(request,QJsondata);
        QObject::connect(reply, &QNetworkReply::finished, [&]() {
            if (reply->error() != QNetworkReply::NoError) {
                qDebug() << "Error: " << reply->errorString()<<reply->error();
                QMessageBox::about(nullptr, "提示", "请先打开奔智客户端");
                reply->deleteLater();
                return;
            }

            QByteArray responseData = reply->readAll();
            reply->deleteLater();
            QJsonDocument jsonDocument = QJsonDocument::fromJson(responseData);
            FingerData=jsonDocument.object().value("data").toArray();
            if(FingerData.empty())
            {
                QMessageBox::about(nullptr, "提示", "录入失败请重试");
                return;
            }
    });
}



void AddLock::on_pushButton_2_released()
{
    networkManager = new QNetworkAccessManager(this);
    QUrl url(IPAddress+"/lock/door/lock/key/add");
    QNetworkRequest request(url);
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");
    request.setRawHeader("Authorization", QString("Bearer %1").arg(Token).toUtf8());
    request.setRawHeader("Connection", "Keep-Alive");
    QJsonObject json;
    json["lockIds"]=vectorToJsonArray(GetLockID);
    json["userId"]=UserID;
    json["userName"]=UserName;
    json["depId"]=DeptID;
    json["depName"]=DeptName;
    json["keyType"]=3;
    json["agingType"]=1;
    json["keyValue"]=jsonArrayToString(FingerData);
    json["enableState"]=1;
    QByteArray QJsondata=QJsonDocument(json).toJson();
    reply=networkManager->post(request,QJsondata);
        QObject::connect(reply, &QNetworkReply::finished, [&]() {
            if (reply->error() != QNetworkReply::NoError) {
                qDebug() << "Error: " << reply->errorString()<<reply->error();
                QMessageBox::about(nullptr, "提示", "请检查网络连接");
                reply->deleteLater();
                return;
            }

            QByteArray responseData = reply->readAll();
            reply->deleteLater();
            qDebug()<<responseData;
            QMessageBox::about(nullptr, "提示", "上传成功");
            this->close();
    });
}

