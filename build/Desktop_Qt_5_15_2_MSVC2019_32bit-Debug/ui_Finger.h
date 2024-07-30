/********************************************************************************
** Form generated from reading UI file 'Finger.ui'
**
** Created by: Qt User Interface Compiler version 5.15.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_FINGER_H
#define UI_FINGER_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QTableWidget>

QT_BEGIN_NAMESPACE

class Ui_Finger
{
public:
    QGridLayout *gridLayout;
    QSpacerItem *horizontalSpacer;
    QPushButton *pushButton;
    QSpacerItem *horizontalSpacer_3;
    QPushButton *pushButton_2;
    QSpacerItem *horizontalSpacer_2;
    QTableWidget *tableWidget;

    void setupUi(QDialog *Finger)
    {
        if (Finger->objectName().isEmpty())
            Finger->setObjectName(QString::fromUtf8("Finger"));
        Finger->resize(563, 413);
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/\345\276\256\344\277\241\345\233\276\347\211\207_20240728123250.png"), QSize(), QIcon::Normal, QIcon::Off);
        Finger->setWindowIcon(icon);
        gridLayout = new QGridLayout(Finger);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        horizontalSpacer = new QSpacerItem(121, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer, 1, 0, 1, 1);

        pushButton = new QPushButton(Finger);
        pushButton->setObjectName(QString::fromUtf8("pushButton"));

        gridLayout->addWidget(pushButton, 1, 1, 1, 1);

        horizontalSpacer_3 = new QSpacerItem(120, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer_3, 1, 2, 1, 1);

        pushButton_2 = new QPushButton(Finger);
        pushButton_2->setObjectName(QString::fromUtf8("pushButton_2"));

        gridLayout->addWidget(pushButton_2, 1, 3, 1, 1);

        horizontalSpacer_2 = new QSpacerItem(121, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer_2, 1, 4, 1, 1);

        tableWidget = new QTableWidget(Finger);
        tableWidget->setObjectName(QString::fromUtf8("tableWidget"));

        gridLayout->addWidget(tableWidget, 0, 0, 1, 5);


        retranslateUi(Finger);

        QMetaObject::connectSlotsByName(Finger);
    } // setupUi

    void retranslateUi(QDialog *Finger)
    {
        Finger->setWindowTitle(QCoreApplication::translate("Finger", "Dialog", nullptr));
        pushButton->setText(QCoreApplication::translate("Finger", "\346\267\273\345\212\240\346\214\207\347\272\271", nullptr));
        pushButton_2->setText(QCoreApplication::translate("Finger", "\344\277\256\346\224\271\346\214\207\347\272\271", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Finger: public Ui_Finger {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_FINGER_H
