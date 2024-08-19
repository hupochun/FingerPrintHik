/********************************************************************************
** Form generated from reading UI file 'Login.ui'
**
** Created by: Qt User Interface Compiler version 5.15.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_LOGIN_H
#define UI_LOGIN_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>

QT_BEGIN_NAMESPACE

class Ui_Login
{
public:
    QGridLayout *gridLayout;
    QSpacerItem *horizontalSpacer;
    QLabel *label;
    QLineEdit *UserName;
    QSpacerItem *horizontalSpacer_2;
    QLabel *label_2;
    QLineEdit *PassWord;
    QSpacerItem *horizontalSpacer_5;
    QPushButton *pushButton;
    QSpacerItem *horizontalSpacer_6;
    QPushButton *pushButton_2;
    QSpacerItem *horizontalSpacer_4;
    QSpacerItem *horizontalSpacer_3;

    void setupUi(QDialog *Login)
    {
        if (Login->objectName().isEmpty())
            Login->setObjectName(QString::fromUtf8("Login"));
        Login->resize(571, 420);
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/ico.png"), QSize(), QIcon::Normal, QIcon::Off);
        Login->setWindowIcon(icon);
        gridLayout = new QGridLayout(Login);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        horizontalSpacer = new QSpacerItem(150, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer, 0, 0, 1, 1);

        label = new QLabel(Login);
        label->setObjectName(QString::fromUtf8("label"));
        label->setLayoutDirection(Qt::LeftToRight);

        gridLayout->addWidget(label, 0, 1, 1, 1);

        UserName = new QLineEdit(Login);
        UserName->setObjectName(QString::fromUtf8("UserName"));
        UserName->setLayoutDirection(Qt::LeftToRight);
        UserName->setStyleSheet(QString::fromUtf8("QLineEdit {\n"
"    color: black;                /* \346\226\207\345\255\227\351\242\234\350\211\262 */\n"
"    border-radius: 10px;         /* \345\234\206\350\247\222\345\215\212\345\276\204 */\n"
"    padding: 10px 20px;          /* \345\206\205\350\276\271\350\267\235 */\n"
"    border: 1px solid ;   /* \350\276\271\346\241\206\350\256\276\347\275\256 */\n"
"    selection-background-color: #66B1FF;  /* \351\200\211\344\270\255\346\226\207\346\234\254\350\203\214\346\231\257\350\211\262 */\n"
"}"));
        UserName->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);

        gridLayout->addWidget(UserName, 0, 2, 1, 1);

        horizontalSpacer_2 = new QSpacerItem(150, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer_2, 1, 0, 1, 1);

        label_2 = new QLabel(Login);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setLayoutDirection(Qt::LeftToRight);
        label_2->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);

        gridLayout->addWidget(label_2, 1, 1, 1, 1);

        PassWord = new QLineEdit(Login);
        PassWord->setObjectName(QString::fromUtf8("PassWord"));
        PassWord->setLayoutDirection(Qt::LeftToRight);
        PassWord->setStyleSheet(QString::fromUtf8("QLineEdit {\n"
"    color: black;                /* \346\226\207\345\255\227\351\242\234\350\211\262 */\n"
"    border-radius: 10px;         /* \345\234\206\350\247\222\345\215\212\345\276\204 */\n"
"    padding: 10px 20px;          /* \345\206\205\350\276\271\350\267\235 */\n"
"    border: 1px solid ;   /* \350\276\271\346\241\206\350\256\276\347\275\256 */\n"
"    selection-background-color: #66B1FF;  /* \351\200\211\344\270\255\346\226\207\346\234\254\350\203\214\346\231\257\350\211\262 */\n"
"}"));
        PassWord->setEchoMode(QLineEdit::Password);
        PassWord->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);

        gridLayout->addWidget(PassWord, 1, 2, 1, 1);

        horizontalSpacer_5 = new QSpacerItem(192, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer_5, 2, 0, 1, 1);

        pushButton = new QPushButton(Login);
        pushButton->setObjectName(QString::fromUtf8("pushButton"));
        pushButton->setMinimumSize(QSize(100, 0));
        pushButton->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"    background-color: #409EFF;   /* \346\214\211\351\222\256\350\203\214\346\231\257\350\211\262 */\n"
"    color: white;                /* \346\226\207\345\255\227\351\242\234\350\211\262 */\n"
"    border-radius: 10px;         /* \345\234\206\350\247\222\345\215\212\345\276\204 */\n"
"    padding: 10px 20px;          /* \345\206\205\350\276\271\350\267\235 */\n"
"    border: none;                /* \345\216\273\351\231\244\350\276\271\346\241\206 */\n"
"}"));

        gridLayout->addWidget(pushButton, 2, 2, 1, 1);

        horizontalSpacer_6 = new QSpacerItem(207, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer_6, 2, 3, 1, 2);

        pushButton_2 = new QPushButton(Login);
        pushButton_2->setObjectName(QString::fromUtf8("pushButton_2"));
        pushButton_2->setMaximumSize(QSize(50, 30));

        gridLayout->addWidget(pushButton_2, 3, 4, 1, 1);

        horizontalSpacer_4 = new QSpacerItem(149, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer_4, 1, 3, 1, 2);

        horizontalSpacer_3 = new QSpacerItem(149, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer_3, 0, 3, 1, 2);


        retranslateUi(Login);

        QMetaObject::connectSlotsByName(Login);
    } // setupUi

    void retranslateUi(QDialog *Login)
    {
        Login->setWindowTitle(QCoreApplication::translate("Login", "Dialog", nullptr));
        label->setText(QCoreApplication::translate("Login", "\347\224\250\346\210\267\345\220\215", nullptr));
        UserName->setPlaceholderText(QCoreApplication::translate("Login", "\347\224\250\346\210\267\345\220\215", nullptr));
        label_2->setText(QCoreApplication::translate("Login", "\345\257\206\347\240\201", nullptr));
        PassWord->setPlaceholderText(QCoreApplication::translate("Login", "\345\257\206\347\240\201", nullptr));
        pushButton->setText(QCoreApplication::translate("Login", "\347\231\273\345\275\225", nullptr));
        pushButton_2->setText(QCoreApplication::translate("Login", "\350\256\276\347\275\256", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Login: public Ui_Login {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_LOGIN_H
