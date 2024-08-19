/********************************************************************************
** Form generated from reading UI file 'addlock.ui'
**
** Created by: Qt User Interface Compiler version 5.15.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_ADDLOCK_H
#define UI_ADDLOCK_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_AddLock
{
public:
    QGridLayout *gridLayout;
    QWidget *widget;
    QGridLayout *gridLayout_7;
    QWidget *widget_2;
    QGridLayout *gridLayout_2;
    QLabel *label;
    QLabel *label_2;
    QWidget *widget_3;
    QGridLayout *gridLayout_3;
    QLabel *label_3;
    QLabel *label_4;
    QWidget *widget_4;
    QGridLayout *gridLayout_4;
    QLabel *label_5;
    QLabel *label_6;
    QWidget *widget_5;
    QGridLayout *gridLayout_5;
    QLabel *label_7;
    QSpacerItem *horizontalSpacer;
    QPushButton *pushButton;
    QWidget *widget_6;
    QGridLayout *gridLayout_6;
    QSpacerItem *horizontalSpacer_2;
    QPushButton *pushButton_2;
    QSpacerItem *horizontalSpacer_3;

    void setupUi(QDialog *AddLock)
    {
        if (AddLock->objectName().isEmpty())
            AddLock->setObjectName(QString::fromUtf8("AddLock"));
        AddLock->resize(464, 430);
        gridLayout = new QGridLayout(AddLock);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        widget = new QWidget(AddLock);
        widget->setObjectName(QString::fromUtf8("widget"));
        gridLayout_7 = new QGridLayout(widget);
        gridLayout_7->setObjectName(QString::fromUtf8("gridLayout_7"));
        widget_2 = new QWidget(widget);
        widget_2->setObjectName(QString::fromUtf8("widget_2"));
        gridLayout_2 = new QGridLayout(widget_2);
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        label = new QLabel(widget_2);
        label->setObjectName(QString::fromUtf8("label"));

        gridLayout_2->addWidget(label, 0, 0, 1, 1);

        label_2 = new QLabel(widget_2);
        label_2->setObjectName(QString::fromUtf8("label_2"));

        gridLayout_2->addWidget(label_2, 0, 1, 1, 1);


        gridLayout_7->addWidget(widget_2, 0, 0, 1, 1);

        widget_3 = new QWidget(widget);
        widget_3->setObjectName(QString::fromUtf8("widget_3"));
        gridLayout_3 = new QGridLayout(widget_3);
        gridLayout_3->setObjectName(QString::fromUtf8("gridLayout_3"));
        label_3 = new QLabel(widget_3);
        label_3->setObjectName(QString::fromUtf8("label_3"));

        gridLayout_3->addWidget(label_3, 0, 0, 1, 1);

        label_4 = new QLabel(widget_3);
        label_4->setObjectName(QString::fromUtf8("label_4"));

        gridLayout_3->addWidget(label_4, 0, 1, 1, 1);


        gridLayout_7->addWidget(widget_3, 1, 0, 1, 1);

        widget_4 = new QWidget(widget);
        widget_4->setObjectName(QString::fromUtf8("widget_4"));
        gridLayout_4 = new QGridLayout(widget_4);
        gridLayout_4->setObjectName(QString::fromUtf8("gridLayout_4"));
        label_5 = new QLabel(widget_4);
        label_5->setObjectName(QString::fromUtf8("label_5"));

        gridLayout_4->addWidget(label_5, 0, 0, 1, 1);

        label_6 = new QLabel(widget_4);
        label_6->setObjectName(QString::fromUtf8("label_6"));

        gridLayout_4->addWidget(label_6, 0, 1, 1, 1);


        gridLayout_7->addWidget(widget_4, 2, 0, 1, 1);

        widget_5 = new QWidget(widget);
        widget_5->setObjectName(QString::fromUtf8("widget_5"));
        gridLayout_5 = new QGridLayout(widget_5);
        gridLayout_5->setObjectName(QString::fromUtf8("gridLayout_5"));
        label_7 = new QLabel(widget_5);
        label_7->setObjectName(QString::fromUtf8("label_7"));

        gridLayout_5->addWidget(label_7, 0, 0, 1, 1);

        horizontalSpacer = new QSpacerItem(296, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_5->addItem(horizontalSpacer, 0, 1, 1, 1);

        pushButton = new QPushButton(widget_5);
        pushButton->setObjectName(QString::fromUtf8("pushButton"));

        gridLayout_5->addWidget(pushButton, 0, 2, 1, 1);


        gridLayout_7->addWidget(widget_5, 3, 0, 1, 1);

        widget_6 = new QWidget(widget);
        widget_6->setObjectName(QString::fromUtf8("widget_6"));
        gridLayout_6 = new QGridLayout(widget_6);
        gridLayout_6->setObjectName(QString::fromUtf8("gridLayout_6"));
        horizontalSpacer_2 = new QSpacerItem(159, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_6->addItem(horizontalSpacer_2, 0, 0, 1, 1);

        pushButton_2 = new QPushButton(widget_6);
        pushButton_2->setObjectName(QString::fromUtf8("pushButton_2"));

        gridLayout_6->addWidget(pushButton_2, 0, 1, 1, 1);

        horizontalSpacer_3 = new QSpacerItem(158, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_6->addItem(horizontalSpacer_3, 0, 2, 1, 1);


        gridLayout_7->addWidget(widget_6, 4, 0, 1, 1);


        gridLayout->addWidget(widget, 0, 0, 1, 1);


        retranslateUi(AddLock);

        QMetaObject::connectSlotsByName(AddLock);
    } // setupUi

    void retranslateUi(QDialog *AddLock)
    {
        AddLock->setWindowTitle(QCoreApplication::translate("AddLock", "Dialog", nullptr));
        label->setText(QCoreApplication::translate("AddLock", "\346\211\200\345\261\236\344\272\272\345\221\230ID", nullptr));
        label_2->setText(QCoreApplication::translate("AddLock", "TextLabel", nullptr));
        label_3->setText(QCoreApplication::translate("AddLock", "\346\211\200\345\261\236\344\272\272\345\221\230\347\224\250\346\210\267\345\220\215", nullptr));
        label_4->setText(QCoreApplication::translate("AddLock", "TextLabel", nullptr));
        label_5->setText(QCoreApplication::translate("AddLock", "\346\211\200\345\261\236\351\203\250\351\227\250", nullptr));
        label_6->setText(QCoreApplication::translate("AddLock", "TextLabel", nullptr));
        label_7->setText(QCoreApplication::translate("AddLock", "\346\214\207\347\272\271", nullptr));
        pushButton->setText(QCoreApplication::translate("AddLock", "\345\275\225\345\205\245", nullptr));
        pushButton_2->setText(QCoreApplication::translate("AddLock", "\345\256\214\346\210\220", nullptr));
    } // retranslateUi

};

namespace Ui {
    class AddLock: public Ui_AddLock {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_ADDLOCK_H
