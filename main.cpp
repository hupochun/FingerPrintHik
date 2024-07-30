#include "mainwindow.h"
#include "Login.h"
#include <QApplication>
#include <qsettings.h>
QString IPAddress("http://192.168.100.114:5173");
QString Token;
unsigned char fpTemplate[512];
QString UserID;
QMessageBox* msgBox;

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QFont font("Microsoft YaHei", 10);
    a.setFont(font);
    QSettings settings("IniData/server.ini", QSettings::IniFormat);
    settings.beginGroup("server");
    IPAddress = settings.value("ip").toString();
    settings.endGroup();
    Login* login=new Login;
    login->show();
    return a.exec();
}
