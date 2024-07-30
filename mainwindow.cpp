#include "mainwindow.h"
#include "ui_mainwindow.h"
extern unsigned char fpTemplate[512];
extern QString Token;
//bool NetWorkIsOk=0;
int PageNum=1;
extern QString UserID;
extern QString IPAddress;
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setWindowTitle("指纹录入工具");
    networkManager = new QNetworkAccessManager(this);
    QUrl url(IPAddress+"/api/system/user/dynamicList?pageNum=1&pageSize=30&sortField=&sortType=");
    QNetworkRequest request(url);
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");
    request.setRawHeader("Connection", "Keep-Alive");
    request.setRawHeader("Authorization", QString("Bearer %1").arg(Token).toUtf8());
    //do{
        reply=networkManager->get(request);
    // 处理HTTP响应
        QObject::connect(reply, &QNetworkReply::finished, [&]() {
        if (reply->error() != QNetworkReply::NoError) {
            qDebug() << "Error: " << reply->errorString();
            reply->deleteLater();
            return;
        }
        //NetWorkIsOk=1;
    // 读取响应数据
    QByteArray responseData = reply->readAll();
    QString strData=reply->readAll();
    reply->deleteLater();

    // 解析JSON数据
    QJsonDocument jsonDoc = QJsonDocument::fromJson(responseData);
    if (!jsonDoc.isObject()) {
        qDebug() << "Error: Response is not in JSON object format.";
        return;
    }

    QJsonObject jsonObject = jsonDoc.object();
    if (!jsonObject.contains("data")) {
        qDebug() << "Error: JSON object does not contain 'data' key.";
        return;
    }
    QJsonValue dataValue = jsonObject.value("data");
    if (!dataValue.isObject()) {
        qDebug() << "Error: 'data' key does not contain an object.";
        return;
    }

    QJsonObject innerDataObject = dataValue.toObject();
    if (!innerDataObject.contains("data")) {
        qDebug() << "Error: Inner 'data' object does not contain 'data' key.";
        return;
    }

    QJsonValue dataArrayValue = innerDataObject.value("data");
    if (!dataArrayValue.isArray()) {
        qDebug() << "Error: 'data' key within inner object is not an array.";
        return;
    }

    QJsonArray jsonArray = dataArrayValue.toArray();
    if (jsonArray.isEmpty()) {
        qDebug() << "Error: JSON array is empty.";
        return;
    }
    ui->lineEdit_2->setText(QString::number(PageNum));
    ui->tableWidget->setSelectionBehavior(QTableWidget::SelectRows);
    ui->tableWidget->setColumnCount(7);
    ui->tableWidget->setHorizontalHeaderLabels({"ID","登录名","姓名","电话","工号","部门","角色权限"});
    // 设置表格行数为JSON数组的大小
    int numRows = jsonArray.size();
    ui->tableWidget->setRowCount(numRows);
    for (int i = 0; i < jsonArray.size(); ++i) {
        QJsonObject dataObject = jsonArray.at(i).toObject();
        QTableWidgetItem *userIdItem = new QTableWidgetItem(QString::number(dataObject.value("userId").toInt()));
        QTableWidgetItem *nickNameItem = new QTableWidgetItem(dataObject.value("nickName").toString());
        QTableWidgetItem *jobNoItem = new QTableWidgetItem(dataObject.value("jobNo").toString());
        QTableWidgetItem *phonenumber = new QTableWidgetItem(dataObject.value("phonenumber").toString());
        QTableWidgetItem *deptNameItem = new QTableWidgetItem(dataObject.value("deptName").toString());
        QTableWidgetItem *LoginNameItem = new QTableWidgetItem(dataObject.value("certificateNo").toString());
        QTableWidgetItem *RoleNamesItem = new QTableWidgetItem(dataObject.value("roleNames").toString());

        ui->tableWidget->setItem(i, 0, userIdItem);   // userId
         ui->tableWidget->setItem(i, 1, LoginNameItem);   // LoginName
        ui->tableWidget->setItem(i, 2, nickNameItem); // nickName
        ui->tableWidget->setItem(i, 3, phonenumber);    // phonenumber
        ui->tableWidget->setItem(i, 4, jobNoItem);    // jobNo
        ui->tableWidget->setItem(i, 5, deptNameItem);    // deptName
        ui->tableWidget->setItem(i, 6, RoleNamesItem);
    }

    // 调整列宽以适应内容
    ui->tableWidget->resizeColumnsToContents();

    // 设置表格为只读
    ui->tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);
        });
        //}while(!NetWorkIsOk);
    }

MainWindow::~MainWindow()
{
    delete ui;
}



void MainWindow::on_pushButton_3_released()
{
    QUrl url(QString(IPAddress+"/api/system/user/dynamicList?pageNum=1&pageSize=30&nickName=%1&sortField=&sortType=").arg(ui->lineEdit->text()));
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
        QString strData=reply->readAll();
        reply->deleteLater();

        // 解析JSON数据
        QJsonDocument jsonDoc = QJsonDocument::fromJson(responseData);
        if (!jsonDoc.isObject()) {
            qDebug() << "Error: Response is not in JSON object format.";
            return;
        }

        QJsonObject jsonObject = jsonDoc.object();
        if (!jsonObject.contains("data")) {
            qDebug() << "Error: JSON object does not contain 'data' key.";
            return;
        }
        QJsonValue dataValue = jsonObject.value("data");
        if (!dataValue.isObject()) {
            qDebug() << "Error: 'data' key does not contain an object.";
            return;
        }

        QJsonObject innerDataObject = dataValue.toObject();
        if (!innerDataObject.contains("data")) {
            qDebug() << "Error: Inner 'data' object does not contain 'data' key.";
            return;
        }

        QJsonValue dataArrayValue = innerDataObject.value("data");
        if (!dataArrayValue.isArray()) {
            qDebug() << "Error: 'data' key within inner object is not an array.";
            return;
        }

        QJsonArray jsonArray = dataArrayValue.toArray();
        if (jsonArray.isEmpty()) {
            qDebug() << "Error: JSON array is empty.";
            return;
        }
        ui->tableWidget->setSelectionBehavior(QTableWidget::SelectRows);
        ui->tableWidget->setColumnCount(7);
        ui->tableWidget->setHorizontalHeaderLabels({"ID","登录名","姓名","电话","工号","部门","角色权限"});
        // 设置表格行数为JSON数组的大小
        int numRows = jsonArray.size();
        ui->tableWidget->setRowCount(numRows);
        for (int i = 0; i < jsonArray.size(); ++i) {
            QJsonObject dataObject = jsonArray.at(i).toObject();
            QTableWidgetItem *userIdItem = new QTableWidgetItem(QString::number(dataObject.value("userId").toInt()));
            QTableWidgetItem *nickNameItem = new QTableWidgetItem(dataObject.value("nickName").toString());
            QTableWidgetItem *jobNoItem = new QTableWidgetItem(dataObject.value("jobNo").toString());
            QTableWidgetItem *phonenumber = new QTableWidgetItem(dataObject.value("phonenumber").toString());
            QTableWidgetItem *deptNameItem = new QTableWidgetItem(dataObject.value("deptName").toString());
            QTableWidgetItem *LoginNameItem = new QTableWidgetItem(dataObject.value("certificateNo").toString());
            QTableWidgetItem *RoleNamesItem = new QTableWidgetItem(dataObject.value("roleNames").toString());

            ui->tableWidget->setItem(i, 0, userIdItem);   // userId
            ui->tableWidget->setItem(i, 1, LoginNameItem);   // LoginName
            ui->tableWidget->setItem(i, 2, nickNameItem); // nickName
            ui->tableWidget->setItem(i, 3, phonenumber);    // phonenumber
            ui->tableWidget->setItem(i, 4, jobNoItem);    // jobNo
            ui->tableWidget->setItem(i, 5, deptNameItem);    // deptName
            ui->tableWidget->setItem(i, 6, RoleNamesItem);
        }

        // 调整列宽以适应内容
        ui->tableWidget->resizeColumnsToContents();

        // 设置表格为只读
        ui->tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);
    });
}


void MainWindow::on_pushButton_4_released()
{
    if(PageNum==30)
        return;
    PageNum++;
    ui->lineEdit_2->setText(QString::number(PageNum));
    QUrl url(QString(IPAddress+"/api/system/user/dynamicList?pageNum=%1&pageSize=30&sortField=&sortType=").arg(QString::number(PageNum)));
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
        QString strData=reply->readAll();
        reply->deleteLater();

        // 解析JSON数据
        QJsonDocument jsonDoc = QJsonDocument::fromJson(responseData);
        if (!jsonDoc.isObject()) {
            qDebug() << "Error: Response is not in JSON object format.";
            return;
        }

        QJsonObject jsonObject = jsonDoc.object();
        if (!jsonObject.contains("data")) {
            qDebug() << "Error: JSON object does not contain 'data' key.";
            return;
        }
        QJsonValue dataValue = jsonObject.value("data");
        if (!dataValue.isObject()) {
            qDebug() << "Error: 'data' key does not contain an object.";
            return;
        }

        QJsonObject innerDataObject = dataValue.toObject();
        if (!innerDataObject.contains("data")) {
            qDebug() << "Error: Inner 'data' object does not contain 'data' key.";
            return;
        }

        QJsonValue dataArrayValue = innerDataObject.value("data");
        if (!dataArrayValue.isArray()) {
            qDebug() << "Error: 'data' key within inner object is not an array.";
            return;
        }

        QJsonArray jsonArray = dataArrayValue.toArray();
        if (jsonArray.isEmpty()) {
            qDebug() << "Error: JSON array is empty.";
            return;
        }
        ui->tableWidget->setSelectionBehavior(QTableWidget::SelectRows);
        ui->tableWidget->setColumnCount(7);
        ui->tableWidget->setHorizontalHeaderLabels({"ID","登录名","姓名","电话","工号","部门","角色权限"});
        // 设置表格行数为JSON数组的大小
        int numRows = jsonArray.size();
        ui->tableWidget->setRowCount(numRows);
        for (int i = 0; i < jsonArray.size(); ++i) {
            QJsonObject dataObject = jsonArray.at(i).toObject();
            QTableWidgetItem *userIdItem = new QTableWidgetItem(QString::number(dataObject.value("userId").toInt()));
            QTableWidgetItem *nickNameItem = new QTableWidgetItem(dataObject.value("nickName").toString());
            QTableWidgetItem *jobNoItem = new QTableWidgetItem(dataObject.value("jobNo").toString());
            QTableWidgetItem *phonenumber = new QTableWidgetItem(dataObject.value("phonenumber").toString());
            QTableWidgetItem *deptNameItem = new QTableWidgetItem(dataObject.value("deptName").toString());
            QTableWidgetItem *LoginNameItem = new QTableWidgetItem(dataObject.value("certificateNo").toString());
            QTableWidgetItem *RoleNamesItem = new QTableWidgetItem(dataObject.value("roleNames").toString());

            ui->tableWidget->setItem(i, 0, userIdItem);   // userId
            ui->tableWidget->setItem(i, 1, LoginNameItem);   // LoginName
            ui->tableWidget->setItem(i, 2, nickNameItem); // nickName
            ui->tableWidget->setItem(i, 3, phonenumber);    // phonenumber
            ui->tableWidget->setItem(i, 4, jobNoItem);    // jobNo
            ui->tableWidget->setItem(i, 5, deptNameItem);    // deptName
            ui->tableWidget->setItem(i, 6, RoleNamesItem);
        }
        // 调整列宽以适应内容
        ui->tableWidget->resizeColumnsToContents();

        // 设置表格为只读
        ui->tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);
    });
}


void MainWindow::on_pushButton_5_released()
{
    if(PageNum==1)
        return;
    PageNum--;
    ui->lineEdit_2->setText(QString::number(PageNum));
    QUrl url(QString(IPAddress+"/api/system/user/dynamicList?pageNum=%1&pageSize=30&sortField=&sortType=").arg(QString::number(PageNum)));
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
        QString strData=reply->readAll();
        reply->deleteLater();

        // 解析JSON数据
        QJsonDocument jsonDoc = QJsonDocument::fromJson(responseData);
        if (!jsonDoc.isObject()) {
            qDebug() << "Error: Response is not in JSON object format.";
            return;
        }

        QJsonObject jsonObject = jsonDoc.object();
        if (!jsonObject.contains("data")) {
            qDebug() << "Error: JSON object does not contain 'data' key.";
            return;
        }
        QJsonValue dataValue = jsonObject.value("data");
        if (!dataValue.isObject()) {
            qDebug() << "Error: 'data' key does not contain an object.";
            return;
        }

        QJsonObject innerDataObject = dataValue.toObject();
        if (!innerDataObject.contains("data")) {
            qDebug() << "Error: Inner 'data' object does not contain 'data' key.";
            return;
        }

        QJsonValue dataArrayValue = innerDataObject.value("data");
        if (!dataArrayValue.isArray()) {
            qDebug() << "Error: 'data' key within inner object is not an array.";
            return;
        }

        QJsonArray jsonArray = dataArrayValue.toArray();
        if (jsonArray.isEmpty()) {
            qDebug() << "Error: JSON array is empty.";
            return;
        }
        ui->tableWidget->setSelectionBehavior(QTableWidget::SelectRows);
        ui->tableWidget->setColumnCount(7);
        ui->tableWidget->setHorizontalHeaderLabels({"ID","登录名","姓名","电话","工号","部门","角色权限"});
        // 设置表格行数为JSON数组的大小
        int numRows = jsonArray.size();
        ui->tableWidget->setRowCount(numRows);
        for (int i = 0; i < jsonArray.size(); ++i) {
            QJsonObject dataObject = jsonArray.at(i).toObject();
            QTableWidgetItem *userIdItem = new QTableWidgetItem(QString::number(dataObject.value("userId").toInt()));
            QTableWidgetItem *nickNameItem = new QTableWidgetItem(dataObject.value("nickName").toString());
            QTableWidgetItem *jobNoItem = new QTableWidgetItem(dataObject.value("jobNo").toString());
            QTableWidgetItem *phonenumber = new QTableWidgetItem(dataObject.value("phonenumber").toString());
            QTableWidgetItem *deptNameItem = new QTableWidgetItem(dataObject.value("deptName").toString());
            QTableWidgetItem *LoginNameItem = new QTableWidgetItem(dataObject.value("certificateNo").toString());
            QTableWidgetItem *RoleNamesItem = new QTableWidgetItem(dataObject.value("roleNames").toString());

            ui->tableWidget->setItem(i, 0, userIdItem);   // userId
            ui->tableWidget->setItem(i, 1, LoginNameItem);   // LoginName
            ui->tableWidget->setItem(i, 2, nickNameItem); // nickName
            ui->tableWidget->setItem(i, 3, phonenumber);    // phonenumber
            ui->tableWidget->setItem(i, 4, jobNoItem);    // jobNo
            ui->tableWidget->setItem(i, 5, deptNameItem);    // deptName
            ui->tableWidget->setItem(i, 6, RoleNamesItem);
        }

        // 调整列宽以适应内容
        ui->tableWidget->resizeColumnsToContents();

        // 设置表格为只读
        ui->tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);
    });
}


void MainWindow::on_pushButton_6_released()
{
    QModelIndex currentIndex = ui->tableWidget->currentIndex();
    if (currentIndex.isValid()) {
        int currentRow = ui->tableWidget->currentIndex().row();
        UserID=ui->tableWidget->item(currentRow,0)->text();
        Finger* FingerWidget= new Finger(this);
        FingerWidget->show();
    } else {
        QMessageBox::about(nullptr, "提示", "请先选中你要修改的指纹");
        return;
    }

}


void MainWindow::on_pushButton_released()
{
    PageNum=ui->lineEdit_2->text().toInt();
    QUrl url(QString(IPAddress+"/api/system/user/dynamicList?pageNum=%1&pageSize=30&sortField=&sortType=").arg(QString::number(PageNum)));
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
        QString strData=reply->readAll();
        reply->deleteLater();

        // 解析JSON数据
        QJsonDocument jsonDoc = QJsonDocument::fromJson(responseData);
        if (!jsonDoc.isObject()) {
            qDebug() << "Error: Response is not in JSON object format.";
            return;
        }

        QJsonObject jsonObject = jsonDoc.object();
        if (!jsonObject.contains("data")) {
            qDebug() << "Error: JSON object does not contain 'data' key.";
            return;
        }
        QJsonValue dataValue = jsonObject.value("data");
        if (!dataValue.isObject()) {
            qDebug() << "Error: 'data' key does not contain an object.";
            return;
        }

        QJsonObject innerDataObject = dataValue.toObject();
        if (!innerDataObject.contains("data")) {
            qDebug() << "Error: Inner 'data' object does not contain 'data' key.";
            return;
        }

        QJsonValue dataArrayValue = innerDataObject.value("data");
        if (!dataArrayValue.isArray()) {
            qDebug() << "Error: 'data' key within inner object is not an array.";
            return;
        }

        QJsonArray jsonArray = dataArrayValue.toArray();
        if (jsonArray.isEmpty()) {
            qDebug() << "Error: JSON array is empty.";
            return;
        }
        ui->tableWidget->setSelectionBehavior(QTableWidget::SelectRows);
        ui->tableWidget->setColumnCount(7);
        ui->tableWidget->setHorizontalHeaderLabels({"ID","登录名","姓名","电话","工号","部门","角色权限"});
        // 设置表格行数为JSON数组的大小
        int numRows = jsonArray.size();
        ui->tableWidget->setRowCount(numRows);
        for (int i = 0; i < jsonArray.size(); ++i) {
            QJsonObject dataObject = jsonArray.at(i).toObject();
            QTableWidgetItem *userIdItem = new QTableWidgetItem(QString::number(dataObject.value("userId").toInt()));
            QTableWidgetItem *nickNameItem = new QTableWidgetItem(dataObject.value("nickName").toString());
            QTableWidgetItem *jobNoItem = new QTableWidgetItem(dataObject.value("jobNo").toString());
            QTableWidgetItem *phonenumber = new QTableWidgetItem(dataObject.value("phonenumber").toString());
            QTableWidgetItem *deptNameItem = new QTableWidgetItem(dataObject.value("deptName").toString());
            QTableWidgetItem *LoginNameItem = new QTableWidgetItem(dataObject.value("certificateNo").toString());
            QTableWidgetItem *RoleNamesItem = new QTableWidgetItem(dataObject.value("roleNames").toString());

            ui->tableWidget->setItem(i, 0, userIdItem);   // userId
            ui->tableWidget->setItem(i, 1, LoginNameItem);   // LoginName
            ui->tableWidget->setItem(i, 2, nickNameItem); // nickName
            ui->tableWidget->setItem(i, 3, phonenumber);    // phonenumber
            ui->tableWidget->setItem(i, 4, jobNoItem);    // jobNo
            ui->tableWidget->setItem(i, 5, deptNameItem);    // deptName
            ui->tableWidget->setItem(i, 6, RoleNamesItem);
        }

        // 调整列宽以适应内容
        ui->tableWidget->resizeColumnsToContents();

        // 设置表格为只读
        ui->tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);
    });
}

