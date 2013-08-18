/********************************************************************************
** Form generated from reading UI file 'Options.ui'
**
** Created by: Qt User Interface Compiler version 5.1.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_OPTIONS_H
#define UI_OPTIONS_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Dialog_Options
{
public:
    QGroupBox *Box_PlayerType;
    QRadioButton *Radio_PlayerType_Human;
    QRadioButton *Radio_PlayerType_AI;
    QGroupBox *Box_OpponentType;
    QRadioButton *Radio_OpponentType_Human;
    QRadioButton *Radio_OpponentType_AI;
    QRadioButton *Radio_OpponentType_Online;
    QPushButton *Button_Start;

    void setupUi(QWidget *Dialog_Options)
    {
        if (Dialog_Options->objectName().isEmpty())
            Dialog_Options->setObjectName(QStringLiteral("Dialog_Options"));
        Dialog_Options->resize(300, 150);
        Box_PlayerType = new QGroupBox(Dialog_Options);
        Box_PlayerType->setObjectName(QStringLiteral("Box_PlayerType"));
        Box_PlayerType->setGeometry(QRect(10, 10, 120, 91));
        Radio_PlayerType_Human = new QRadioButton(Box_PlayerType);
        Radio_PlayerType_Human->setObjectName(QStringLiteral("Radio_PlayerType_Human"));
        Radio_PlayerType_Human->setGeometry(QRect(10, 20, 82, 17));
        Radio_PlayerType_Human->setChecked(true);
        Radio_PlayerType_AI = new QRadioButton(Box_PlayerType);
        Radio_PlayerType_AI->setObjectName(QStringLiteral("Radio_PlayerType_AI"));
        Radio_PlayerType_AI->setGeometry(QRect(10, 40, 82, 17));
        Box_OpponentType = new QGroupBox(Dialog_Options);
        Box_OpponentType->setObjectName(QStringLiteral("Box_OpponentType"));
        Box_OpponentType->setGeometry(QRect(150, 10, 120, 91));
        Radio_OpponentType_Human = new QRadioButton(Box_OpponentType);
        Radio_OpponentType_Human->setObjectName(QStringLiteral("Radio_OpponentType_Human"));
        Radio_OpponentType_Human->setGeometry(QRect(10, 20, 82, 17));
        Radio_OpponentType_Human->setChecked(true);
        Radio_OpponentType_AI = new QRadioButton(Box_OpponentType);
        Radio_OpponentType_AI->setObjectName(QStringLiteral("Radio_OpponentType_AI"));
        Radio_OpponentType_AI->setGeometry(QRect(10, 40, 82, 17));
        Radio_OpponentType_Online = new QRadioButton(Box_OpponentType);
        Radio_OpponentType_Online->setObjectName(QStringLiteral("Radio_OpponentType_Online"));
        Radio_OpponentType_Online->setGeometry(QRect(10, 60, 82, 17));
        Button_Start = new QPushButton(Dialog_Options);
        Button_Start->setObjectName(QStringLiteral("Button_Start"));
        Button_Start->setGeometry(QRect(125, 110, 50, 23));

        retranslateUi(Dialog_Options);
        QObject::connect(Button_Start, SIGNAL(clicked()), Dialog_Options, SLOT(close()));

        QMetaObject::connectSlotsByName(Dialog_Options);
    } // setupUi

    void retranslateUi(QWidget *Dialog_Options)
    {
        Dialog_Options->setWindowTitle(QApplication::translate("Dialog_Options", "Options", 0));
        Box_PlayerType->setTitle(QApplication::translate("Dialog_Options", "Player Type", 0));
        Radio_PlayerType_Human->setText(QApplication::translate("Dialog_Options", "Human", 0));
        Radio_PlayerType_AI->setText(QApplication::translate("Dialog_Options", "AI", 0));
        Box_OpponentType->setTitle(QApplication::translate("Dialog_Options", "Opponent Type", 0));
        Radio_OpponentType_Human->setText(QApplication::translate("Dialog_Options", "Human", 0));
        Radio_OpponentType_AI->setText(QApplication::translate("Dialog_Options", "AI", 0));
        Radio_OpponentType_Online->setText(QApplication::translate("Dialog_Options", "Online", 0));
        Button_Start->setText(QApplication::translate("Dialog_Options", "Start", 0));
    } // retranslateUi

};

namespace Ui {
    class Dialog_Options: public Ui_Dialog_Options {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_OPTIONS_H
