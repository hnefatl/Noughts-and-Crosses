/********************************************************************************
** Form generated from reading UI file 'NetworkSettings.ui'
**
** Created by: Qt User Interface Compiler version 5.1.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_NETWORKSETTINGS_H
#define UI_NETWORKSETTINGS_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Form_NetworkSettings
{
public:
    QLabel *label;
    QLineEdit *Text_Username;
    QLabel *label_2;
    QLineEdit *Text_ServerIP;
    QLabel *label_3;
    QLineEdit *Text_ServerPort;
    QPushButton *Button_Connect;

    void setupUi(QWidget *Form_NetworkSettings)
    {
        if (Form_NetworkSettings->objectName().isEmpty())
            Form_NetworkSettings->setObjectName(QStringLiteral("Form_NetworkSettings"));
        Form_NetworkSettings->resize(250, 150);
        label = new QLabel(Form_NetworkSettings);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(10, 10, 111, 16));
        Text_Username = new QLineEdit(Form_NetworkSettings);
        Text_Username->setObjectName(QStringLiteral("Text_Username"));
        Text_Username->setGeometry(QRect(120, 10, 113, 20));
        Text_Username->setMaxLength(25);
        label_2 = new QLabel(Form_NetworkSettings);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setGeometry(QRect(10, 40, 111, 16));
        Text_ServerIP = new QLineEdit(Form_NetworkSettings);
        Text_ServerIP->setObjectName(QStringLiteral("Text_ServerIP"));
        Text_ServerIP->setGeometry(QRect(120, 40, 113, 20));
        label_3 = new QLabel(Form_NetworkSettings);
        label_3->setObjectName(QStringLiteral("label_3"));
        label_3->setGeometry(QRect(10, 70, 111, 16));
        Text_ServerPort = new QLineEdit(Form_NetworkSettings);
        Text_ServerPort->setObjectName(QStringLiteral("Text_ServerPort"));
        Text_ServerPort->setGeometry(QRect(120, 70, 113, 20));
        Button_Connect = new QPushButton(Form_NetworkSettings);
        Button_Connect->setObjectName(QStringLiteral("Button_Connect"));
        Button_Connect->setGeometry(QRect(90, 110, 75, 23));

        retranslateUi(Form_NetworkSettings);

        QMetaObject::connectSlotsByName(Form_NetworkSettings);
    } // setupUi

    void retranslateUi(QWidget *Form_NetworkSettings)
    {
        Form_NetworkSettings->setWindowTitle(QApplication::translate("Form_NetworkSettings", "Network Settings", 0));
        label->setText(QApplication::translate("Form_NetworkSettings", "Enter your username: ", 0));
        label_2->setText(QApplication::translate("Form_NetworkSettings", "Enter the server IP: ", 0));
        label_3->setText(QApplication::translate("Form_NetworkSettings", "Enter the server port: ", 0));
        Button_Connect->setText(QApplication::translate("Form_NetworkSettings", "Connect", 0));
    } // retranslateUi

};

namespace Ui {
    class Form_NetworkSettings: public Ui_Form_NetworkSettings {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_NETWORKSETTINGS_H
