#include "dialog.h"
#include "ui_dialog.h"

Dialog::Dialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::Dialog)
{
    ui->setupUi(this);
    setWindowTitle("指纹录入工具");
    Qt::WindowFlags flags = windowFlags();

    // 移除帮助按钮标志
    flags &= ~Qt::WindowContextHelpButtonHint;

    // 设置新的窗口标志
    setWindowFlags(flags);
}

Dialog::~Dialog()
{
    delete ui;
}

void Dialog::PromptPush()
{
    ui->label->setText("请放上你的手指");
}
void Dialog::PromptUp()
{
    ui->label->setText("请抬起你的手指");

}
void Dialog::PromptErr()
{
    ui->label->setText("指纹质量低请重新录入");

}

void Dialog::on_pushButton_released()
{
    this->close();
}

