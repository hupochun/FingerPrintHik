#include "Setting.h"
#include "ui_Setting.h"
#include "qsettings.h"
extern QString IPAddress;
Setting::Setting(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Setting)
{
    ui->setupUi(this);

    ui->lineEdit->setText(IPAddress);
}

Setting::~Setting()
{
    delete ui;
}

void Setting::on_pushButton_released()
{
    IPAddress = ui->lineEdit->text();
    QSettings settings("IniData/server.ini", QSettings::IniFormat);

    settings.beginGroup("server");
    settings.setValue("ip", IPAddress);    // 设置ini文件中的IP
    settings.endGroup();
    this->close();
}

