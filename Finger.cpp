#include "Finger.h"
#include "ui_Finger.h"
#include <QThread>
#include <QTimer>
#include "dialog.h"
extern QString Token;
extern QString UserID;
extern unsigned char fpTemplate[100000];
extern QString IPAddress;
bool isPost=0;
QString FingerID;
QString FingerName;
unsigned char* Fingerdata=new unsigned char[100000];
int* FingerStatus=new int;
int* FingerWidth=new int;
int* FingerHeight=new int;
Dialog* Prompt;

void __stdcall MessageHandler(FP_MSG_TYPE_T enMsgType, void *pMsgData) {
    switch (enMsgType) {
    case FP_MSG_PRESS_FINGER:
    {
        printf("请按下手指...\n");
        Prompt->PromptPush();
        Prompt->setVisible(true);
        QCoreApplication::processEvents();
        //QMessageBox::about(nullptr, "提示", "请放上手指");
        // msgBox->setText("请按下手指");
        break;
    }
    case FP_MSG_RISE_FINGER:
    {
        printf("请抬起手指...\n");
        Prompt->PromptUp();
        Prompt->setVisible(true);
        QCoreApplication::processEvents();
        //QMessageBox::about(nullptr, "提示", "请抬起手指");
        // msgBox->setText("请抬起手指");
        break;
    }
    case FP_MSG_ENROLL_TIME: {
        int dwEnrollTime = *((int *)pMsgData);
        printf("当前采集次数：%d\n", dwEnrollTime);
        break;
    }
    case FP_MSG_CAPTURED_IMAGE: {

        FP_IMAGE_DATA *imageData = (FP_IMAGE_DATA *)pMsgData;
        printf("录入的指纹图像大小：%d x %d\n", imageData->dwWidth, imageData->dwHeight);
        // 在这里可以处理 imageData->pbyImage 指纹图像数据

        break;
    }
    default:
        break;
    }
}

Finger::Finger(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::Finger)
{
    ui->setupUi(this);
    setWindowTitle("指纹录入工具");
    Qt::WindowFlags flags = windowFlags();

    // 移除帮助按钮标志
    flags &= ~Qt::WindowContextHelpButtonHint;

    // 设置新的窗口标志
    setWindowFlags(flags);
    FPModule_SetTimeout(5);
    Prompt=new Dialog;
    networkManager = new QNetworkAccessManager(this);
    QUrl url(IPAddress+"/gwise-hik/hik-fingerprint/list?personId="+UserID);
    QNetworkRequest request(url);
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");
    request.setRawHeader("Connection", "Keep-Alive");
    request.setRawHeader("Authorization", QString("Bearer %1").arg(Token).toUtf8());
    reply=networkManager->get(request);
    // 处理HTTP响应
    QObject::connect(reply, &QNetworkReply::finished, [&]() {
        if (reply->error() != QNetworkReply::NoError) {
            qDebug() << "Error: " << reply->errorString();
            reply->deleteLater();
            return;
        }
        // 读取响应数据
        QByteArray responseData = reply->readAll();
        reply->deleteLater();
        QJsonDocument jsonDocument = QJsonDocument::fromJson(responseData);
        if (!jsonDocument.isObject()) {
            qDebug() << "JSON document is not an object.";
            return;
        }

        QJsonObject jsonObj = jsonDocument.object();

        // 获取 list 数组
        QJsonArray jsonArray = jsonObj.value("list").toArray();
        ui->tableWidget->setSelectionBehavior(QTableWidget::SelectRows);
        ui->tableWidget->setColumnCount(3);
        ui->tableWidget->setHorizontalHeaderLabels({"指纹ID","指纹名称","UserID"});
        // 设置表格行数为JSON数组的大小
        int numRows = jsonArray.size();
        ui->tableWidget->setRowCount(numRows);
        for (int i = 0; i < jsonArray.size(); ++i) {
            QJsonObject listObject = jsonArray.at(i).toObject();
            QTableWidgetItem *FingerIdItem = new QTableWidgetItem(listObject.value("fingerPrintIndexCode").toString());
            QTableWidgetItem *FingerNameItem = new QTableWidgetItem(listObject.value("fingerPrintName").toString());
            QTableWidgetItem *UserIDItem = new QTableWidgetItem(listObject.value("personId").toString());
            ui->tableWidget->setItem(i, 0, FingerIdItem);
            ui->tableWidget->setItem(i, 1, FingerNameItem);
            ui->tableWidget->setItem(i, 2, UserIDItem);
        }

        // 调整列宽以适应内容
        ui->tableWidget->resizeColumnsToContents();

        // 设置表格为只读
        ui->tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);
    });
}

Finger::~Finger()
{
    delete ui;
}

void Finger::on_pushButton_released()
{
    if(FPModule_OpenDevice()==1)
    {
        QMessageBox::about(nullptr, "提示", "设备未连接");
        return;
    }
    else
    {
        FPModule_InstallMessageHandler(MessageHandler);
        int isComplete = FPModule_FpEnroll(fpTemplate);
        if (isComplete!=0)
        {
            QMessageBox::about(nullptr, "提示", "录入失败请重试");
            return;
        }

        if(FPModule_GetQuality(fpTemplate)<65)
        {
            Prompt->PromptErr();
            Prompt->setVisible(true);
            return;
        }
        Prompt->close();
        QUrl url(IPAddress+"/gwise-hik/hik-fingerprint");
        QNetworkRequest request(url);
        QJsonObject json;
        // QString hexString;
        // for (int i = 0; i < 512; ++i) {
        //     // Convert each byte to a 2-character hexadecimal string
        //     hexString.append(QString("%1").arg(fpTemplate[i], 2, 16, QChar('0')).toUpper());
        // }
        QByteArray byteArray(reinterpret_cast<char*>(fpTemplate), 512);

        // 2. 将 QByteArray 转换为 Base64 编码的 QByteArray
        QByteArray base64Data = byteArray.toBase64();

        // 3. 将 Base64 编码的 QByteArray 转换为 QString，如果需要的话
        QString hexString = QString::fromUtf8(base64Data);
            json["personId"] = UserID;
            QDateTime currentDateTime = QDateTime::currentDateTime();
            json["fingerprintName"] = currentDateTime.toString();
            json["fingerprintData"]=hexString;
            QJsonDocument jsonDoc(json);
            QByteArray jsonData = jsonDoc.toJson();
            request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");
            request.setRawHeader("Authorization", QString("Bearer %1").arg(Token).toUtf8());
            qDebug()<<jsonData;
            reply=networkManager->post(request, jsonData);
            QObject::connect(reply, &QNetworkReply::finished, [&]() {
            if (reply->error() != QNetworkReply::NoError) {
                    qDebug() << "Error: " << reply->errorString()<<reply->error();
                QMessageBox::about(nullptr, "提示", "上传失败请检查网络");
                reply->deleteLater();
                return;
            }
            else
            {
                QString replymsg=reply->readAll();
                qDebug()<<replymsg;
                QMessageBox::about(nullptr, "提示", "上传成功");


            }
        });
            // networkManager=new QNetworkAccessManager(this);
            // QUrl urlflash(IPAddress+"/gwise-hik/hik-fingerprint/list?personId="+UserID);
            // QNetworkRequest requestflash(urlflash);
            // requestflash.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");
            // requestflash.setRawHeader("Connection", "Keep-Alive");
            // requestflash.setRawHeader("Authorization", QString("Bearer %1").arg(Token).toUtf8());
            // reply=networkManager->get(requestflash);
            // // 处理HTTP响应
            // QObject::connect(reply, &QNetworkReply::finished, [&]() {
            //     if (reply->error() != QNetworkReply::NoError) {
            //         qDebug() << "Error: " << reply->errorString();
            //         reply->deleteLater();
            //         return;
            //     }
            //     // 读取响应数据
            //     QByteArray responseData = reply->readAll();
            //     reply->deleteLater();
            //     QJsonDocument jsonDocument = QJsonDocument::fromJson(responseData);
            //     if (!jsonDocument.isObject()) {
            //         qDebug() << "JSON document is not an object.";
            //         return;
            //     }

            //     QJsonObject jsonObj = jsonDocument.object();

            //     // 获取 list 数组
            //     QJsonArray jsonArray = jsonObj.value("list").toArray();
            //     ui->tableWidget->clearContents();
            //     ui->tableWidget->setSelectionBehavior(QTableWidget::SelectRows);
            //     ui->tableWidget->setColumnCount(3);
            //     ui->tableWidget->setHorizontalHeaderLabels({"指纹ID","指纹名称","UserID"});
            //     // 设置表格行数为JSON数组的大小
            //     int numRows = jsonArray.size();
            //     ui->tableWidget->setRowCount(numRows);
            //     for (int i = 0; i < jsonArray.size(); ++i) {
            //         QJsonObject listObject = jsonArray.at(i).toObject();
            //         QTableWidgetItem *FingerIdItem = new QTableWidgetItem(listObject.value("fingerPrintIndexCode").toString());
            //         QTableWidgetItem *FingerNameItem = new QTableWidgetItem(listObject.value("fingerPrintName").toString());
            //         QTableWidgetItem *UserIDItem = new QTableWidgetItem(listObject.value("personId").toString());
            //         ui->tableWidget->setItem(i, 0, FingerIdItem);
            //         ui->tableWidget->setItem(i, 1, FingerNameItem);
            //         ui->tableWidget->setItem(i, 2, UserIDItem);
            //     }

            //     // 调整列宽以适应内容
            //     ui->tableWidget->resizeColumnsToContents();

            //     // 设置表格为只读
            //     ui->tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);
            // });

    }
    FlashTable();
}


void Finger::on_pushButton_2_released()
{
    QModelIndex currentIndex = ui->tableWidget->currentIndex();
    if (currentIndex.isValid()) {
        int currentRow = ui->tableWidget->currentIndex().row();
        FingerID=ui->tableWidget->item(currentRow,0)->text();
        FingerName=ui->tableWidget->item(currentRow,1)->text();
    } else {
        QMessageBox::about(nullptr, "提示", "请先选中你要修改的指纹");
        return;
    }
    if(FPModule_OpenDevice()==1)
    {
        QMessageBox::about(nullptr, "提示", "设备未连接");
        return;
    }
    else
    {
        FPModule_InstallMessageHandler(MessageHandler);
        int isComplete = FPModule_FpEnroll(fpTemplate);
        if (isComplete!=0)
        {
            QMessageBox::about(nullptr, "提示", "录入失败请重试");
            return;
        }
        if(FPModule_GetQuality(fpTemplate)<65)
        {
            Prompt->PromptErr();
            Prompt->setVisible(true);
            return;
        }
        Prompt->close();
        // QString hexString;
        // for (int i = 0; i < 512; ++i) {
        //     // Convert each byte to a 2-character hexadecimal string
        //     hexString.append(QString("%1").arg(fpTemplate[i], 2, 16, QChar('0')).toUpper());
        // }
        QByteArray byteArray(reinterpret_cast<char*>(fpTemplate), 512);

        // 2. 将 QByteArray 转换为 Base64 编码的 QByteArray
        QByteArray base64Data = byteArray.toBase64();

        // 3. 将 Base64 编码的 QByteArray 转换为 QString，如果需要的话
        QString hexString = QString::fromUtf8(base64Data);
        networkManager=new QNetworkAccessManager(this);
        QUrl url(IPAddress+"/gwise-hik/hik-fingerprint");
        QNetworkRequest request(url);
        QJsonObject json;
            json["fingerprintId"] = FingerID;
            json["personId"] = UserID;
            QDateTime currentDateTime = QDateTime::currentDateTime();
            json["fingerprintName"] = currentDateTime.toString();
            json["fingerprintData"] = hexString;
            QJsonDocument jsonDoc(json);
            QByteArray jsonData = jsonDoc.toJson();
            request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");
            request.setRawHeader("Connection", "Keep-Alive");
            request.setRawHeader("Authorization", QString("Bearer %1").arg(Token).toUtf8());
            reply=networkManager->put(request, jsonData);
        QObject::connect(reply, &QNetworkReply::finished, [&]() {
            if (reply->error() != QNetworkReply::NoError) {
                qDebug() << "Error: " << reply->errorString();
                QMessageBox::about(nullptr, "提示", "上传失败请检查网络");

                reply->deleteLater();
                return;
            }
            else
            {
                QString replymsg=reply->readAll();
                qDebug()<<replymsg;
                QMessageBox::about(nullptr, "提示", "上传成功");


            }
        });
    }
    FlashTable();
}

void Finger::FlashTable()
{
    QNetworkAccessManager* FlashNetworkManager=new QNetworkAccessManager(this);
    QUrl urlflash(IPAddress+"/gwise-hik/hik-fingerprint/list?personId="+UserID);
    QNetworkRequest requestflash(urlflash);
    QNetworkReply* replyflash;
    requestflash.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");
    requestflash.setRawHeader("Connection", "Keep-Alive");
    requestflash.setRawHeader("Authorization", QString("Bearer %1").arg(Token).toUtf8());
    replyflash=FlashNetworkManager->get(requestflash);
    // 处理HTTP响应
    QObject::connect(replyflash, &QNetworkReply::finished, [=]() {
        if (replyflash->error() != QNetworkReply::NoError) {
            qDebug() << "Error: " << replyflash->errorString();
            replyflash->deleteLater();
            return;
        }
        // 读取响应数据
        QByteArray responseData = replyflash->readAll();
        replyflash->deleteLater();
        QJsonDocument jsonDocument = QJsonDocument::fromJson(responseData);
        if (!jsonDocument.isObject()) {
            qDebug() << "JSON document is not an object.";
            return;
        }

        QJsonObject jsonObj = jsonDocument.object();

        // 获取 list 数组
        QJsonArray jsonArray = jsonObj.value("list").toArray();
        ui->tableWidget->clearContents();
        ui->tableWidget->setSelectionBehavior(QTableWidget::SelectRows);
        ui->tableWidget->setColumnCount(3);
        ui->tableWidget->setHorizontalHeaderLabels({"指纹ID","指纹名称","UserID"});
        // 设置表格行数为JSON数组的大小
        int numRows = jsonArray.size();
        ui->tableWidget->setRowCount(numRows);
        for (int i = 0; i < jsonArray.size(); ++i) {
            QJsonObject listObject = jsonArray.at(i).toObject();
            QTableWidgetItem *FingerIdItemFlash = new QTableWidgetItem(listObject.value("fingerPrintIndexCode").toString());
            QTableWidgetItem *FingerNameItemFlash = new QTableWidgetItem(listObject.value("fingerPrintName").toString());
            QTableWidgetItem *UserIDItemFlash = new QTableWidgetItem(listObject.value("personId").toString());
            ui->tableWidget->setItem(i, 0, FingerIdItemFlash);
            ui->tableWidget->setItem(i, 1, FingerNameItemFlash);
            ui->tableWidget->setItem(i, 2, UserIDItemFlash);
        }

    });
}
