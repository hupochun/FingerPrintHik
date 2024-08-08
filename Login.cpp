#include "Login.h"
#include "ui_Login.h"
#include "Setting.h"
extern QString Token;
extern QString IPAddress;

Login::Login(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::Login)
{
    ui->setupUi(this);
    Qt::WindowFlags flags = windowFlags();
    setWindowTitle("指纹录入工具");
    // 移除帮助按钮标志
    flags &= ~Qt::WindowContextHelpButtonHint;
    QAction * searchAction = new QAction(ui->UserName); searchAction->setIcon(QIcon(":/sangangy.png"));
    ui->UserName->addAction(searchAction,QLineEdit::LeadingPosition);//表示action所在方位（左侧）。
    QAction * searchAction2 = new QAction(ui->PassWord);
    searchAction2->setIcon(QIcon(":/suo.png"));
    ui->PassWord->addAction(searchAction2,QLineEdit::LeadingPosition);//表示action所在方位（左侧）。
    // 设置新的窗口标志
    setWindowFlags(flags);
    networkManager = new QNetworkAccessManager(this);
    connect(networkManager, &QNetworkAccessManager::finished, this, &Login::replyFinished);
}

Login::~Login()
{
    delete ui;
}

void Login::on_pushButton_released()
{
    QString User=ui->UserName->text();
    QString PassWD=ui->PassWord->text();
    if(User.isEmpty()==1||PassWD.isEmpty()==1)
    {
        QMessageBox::StandardButton result=QMessageBox::warning(this, "错误","账号或密码不能为空");
    }
    QUrl url(IPAddress+"/auth/login");
    QNetworkRequest request(url);
    QJsonObject json;
    json["username"] = User;
    json["password"] = PassWD;
    QJsonDocument jsonDoc(json);
    QByteArray jsonData = jsonDoc.toJson();
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");
    request.setRawHeader("Connection", "Keep-Alive");
    reply=networkManager->post(request, jsonData);
    qDebug()<<jsonData;
}

void Login::replyFinished()
{
    if (reply->error() == QNetworkReply::NoError) {
        QByteArray responseData = reply->readAll();
        qDebug() << "Response data:" << responseData;
        QJsonObject json1;
        json1 =QJsonDocument::fromJson(responseData).object();
        auto flag=json1.value("code").toVariant();
        if(flag=="0")
        {
            json1=json1.value("data").toObject();
            token=json1.value("access_token").toString();
            Token=token;
            MainWindow* main_window=new MainWindow;
            main_window->show();
            this->hide();
        }
        else
        {
            qDebug()<<"账号或密码错误";
            QMessageBox::StandardButton result=QMessageBox::warning(this, "错误","账号或密码错误");
        }
    } else {
        qDebug() << "Network error:" << reply->errorString();
        QMessageBox::StandardButton result=QMessageBox::warning(this, "错误","请检查网络");


    }
    reply->deleteLater();
}

QString Login::GetToken()
{
    return token;
}


void Login::on_pushButton_2_released()
{
    Setting* SettingWidget=new Setting;
    SettingWidget->show();
}

