#include "getlock.h"
#include "ui_getlock.h"
#include <QJsonArray>
#include <QMessageBox>
extern QString IPAddress;
extern QString Token;
extern QVector<QString> GetLockID;
GetLock::GetLock(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::GetLock)
{
    ui->setupUi(this);
    RowCount=0;
    m_AddLock=NULL;
    networkManager = new QNetworkAccessManager(this);
    QUrl url(IPAddress+"/lock/door/lock/get/locks");
    QNetworkRequest request(url);
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");
    request.setRawHeader("Connection", "Keep-Alive");
    request.setRawHeader("Authorization", QString("Bearer %1").arg(Token).toUtf8());
    reply=networkManager->get(request);
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
        if (!dataValue.isArray()) {
            qDebug() << "Error: 'data' key within inner object is not an array.";
            return;
        }
        QJsonArray jsonArray = dataValue.toArray();
        if (jsonArray.isEmpty()) {
            qDebug() << "Error: JSON array is empty.";
            return;
        }
        ui->tableWidget->setSelectionBehavior(QTableWidget::SelectRows);
        ui->tableWidget->setColumnCount(5);
        ui->tableWidget->setRowCount(jsonArray.size());
        ui->tableWidget->setHorizontalHeaderLabels({"ID","楼名","层数","房间名","房号"});
        ui->tableWidget_2->setSelectionBehavior(QTableWidget::SelectRows);
        ui->tableWidget_2->setColumnCount(5);
        ui->tableWidget_2->setHorizontalHeaderLabels({"ID","楼名","层数","房间名","房号"});
        // 设置表格行数为JSON数组的大小
        int numRows = jsonArray.size();
        ui->tableWidget->setRowCount(numRows);
        for (int i = 0; i < jsonArray.size(); ++i) {
            QJsonObject dataObject = jsonArray.at(i).toObject();
            QTableWidgetItem *IDItem = new QTableWidgetItem(QString::number(dataObject.value("id").toInt()));
            QTableWidgetItem *BuildNameItem = new QTableWidgetItem(dataObject.value("regionBuildingName").toString());
            QTableWidgetItem *FloorItem = new QTableWidgetItem(dataObject.value("regionFloorName").toString());
            QTableWidgetItem *RoomNameItem = new QTableWidgetItem(dataObject.value("regionRoomName").toString());
            QTableWidgetItem *RoomNoItem = new QTableWidgetItem(dataObject.value("roomNo").toString());
            ui->tableWidget->setItem(i, 0, IDItem);          // ID
            ui->tableWidget->setItem(i, 1, BuildNameItem);   // BuildName
            ui->tableWidget->setItem(i, 2, FloorItem);       // Floor
            ui->tableWidget->setItem(i, 3, RoomNameItem);    // RoomName
            ui->tableWidget->setItem(i, 4, RoomNoItem);      // RoomNo
        }

        // 调整列宽以适应内容
        ui->tableWidget->resizeColumnsToContents();
        ui->tableWidget_2->resizeColumnsToContents();

        // 设置表格为只读
        ui->tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);
        ui->tableWidget_2->setEditTriggers(QAbstractItemView::NoEditTriggers);
    });
}

GetLock::~GetLock()
{
    delete ui;
}

void GetLock::on_pushButton_released()
{
    QModelIndex currentIndex = ui->tableWidget->currentIndex();
    if (currentIndex.isValid())
    {
        // ui->tableWidget_2->setRowCount(++RowCount);
        int RowNum=ui->tableWidget->currentRow();
        ui->tableWidget_2->insertRow(0);
        QTableWidgetItem* item0=new QTableWidgetItem;
        QTableWidgetItem* item1=new QTableWidgetItem;
        QTableWidgetItem* item2=new QTableWidgetItem;
        QTableWidgetItem* item3=new QTableWidgetItem;
        QTableWidgetItem* item4=new QTableWidgetItem;
        *item0=*ui->tableWidget->item(RowNum,0);
        *item1=*ui->tableWidget->item(RowNum,1);
        *item2=*ui->tableWidget->item(RowNum,2);
        *item3=*ui->tableWidget->item(RowNum,3);
        *item4=*ui->tableWidget->item(RowNum,4);

        ui->tableWidget_2->setItem(0, 0, item0);    // ID
        ui->tableWidget_2->setItem(0, 1, item1);    // BuildName
        ui->tableWidget_2->setItem(0, 2, item2);    // Floor
        ui->tableWidget_2->setItem(0, 3, item3);    // RoomName
        ui->tableWidget_2->setItem(0, 4, item4);    // RoomNo
        ui->tableWidget_2->resizeColumnsToContents();
    }
    else
    {
        QMessageBox::about(nullptr, "提示", "请先选择左侧要添加的门锁");
        return;
    }
}


void GetLock::on_pushButton_2_released()
{
    QModelIndex currentIndex = ui->tableWidget_2->currentIndex();
    if (currentIndex.isValid())
    {
        int RowNum=ui->tableWidget_2->currentRow();
        ui->tableWidget_2->removeRow(RowNum);
        // ui->tableWidget_2->setRowCount(--RowCount);
    }
    else
    {
        QMessageBox::about(nullptr, "提示", "请先选中右侧要删除的门锁");
        return;
    }
}


void GetLock::on_pushButton_3_released()
{
    for(int i=0;i<ui->tableWidget_2->rowCount();i++)
    {
        GetLockID.append(ui->tableWidget_2->item(i,0)->text());
    }
    if(GetLockID.empty())
    {
        QMessageBox::about(nullptr, "提示", "至少有一个要添加的门锁");
        return;
    }
    if(m_AddLock!=NULL)
    {
        delete m_AddLock;
    }
    m_AddLock=new AddLock(this);
    m_AddLock->show();
    this->close();
}

