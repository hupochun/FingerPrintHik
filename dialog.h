#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>

namespace Ui {
class Dialog;
}

class Dialog : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog(QWidget *parent = nullptr);
    void PromptPush();
    void PromptUp();
    void PromptErr();
    ~Dialog();

private slots:
    void on_pushButton_released();

private:
    Ui::Dialog *ui;
};

#endif // DIALOG_H
