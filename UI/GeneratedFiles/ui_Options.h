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

class Ui_Options
{
public:
    QGroupBox *Box_OpponentType;
    QRadioButton *OpponentType_Online;
    QRadioButton *OpponentType_AI;
    QRadioButton *OpponentType_Human;
    QGroupBox *Box_PlayerType;
    QRadioButton *PlayerType_Human;
    QRadioButton *PlayerType_AI;
    QPushButton *Button_Play;

    void setupUi(QWidget *Options)
    {
        if (Options->objectName().isEmpty())
            Options->setObjectName(QStringLiteral("Options"));
        Options->resize(300, 150);
        Box_OpponentType = new QGroupBox(Options);
        Box_OpponentType->setObjectName(QStringLiteral("Box_OpponentType"));
        Box_OpponentType->setGeometry(QRect(140, 10, 120, 91));
        OpponentType_Online = new QRadioButton(Box_OpponentType);
        OpponentType_Online->setObjectName(QStringLiteral("OpponentType_Online"));
        OpponentType_Online->setGeometry(QRect(10, 60, 61, 17));
        OpponentType_Online->setChecked(false);
        OpponentType_AI = new QRadioButton(Box_OpponentType);
        OpponentType_AI->setObjectName(QStringLiteral("OpponentType_AI"));
        OpponentType_AI->setGeometry(QRect(10, 40, 61, 17));
        OpponentType_Human = new QRadioButton(Box_OpponentType);
        OpponentType_Human->setObjectName(QStringLiteral("OpponentType_Human"));
        OpponentType_Human->setGeometry(QRect(10, 20, 61, 17));
        OpponentType_Human->setChecked(true);
        Box_PlayerType = new QGroupBox(Options);
        Box_PlayerType->setObjectName(QStringLiteral("Box_PlayerType"));
        Box_PlayerType->setGeometry(QRect(10, 10, 120, 71));
        PlayerType_Human = new QRadioButton(Box_PlayerType);
        PlayerType_Human->setObjectName(QStringLiteral("PlayerType_Human"));
        PlayerType_Human->setGeometry(QRect(10, 20, 61, 17));
        PlayerType_Human->setChecked(true);
        PlayerType_AI = new QRadioButton(Box_PlayerType);
        PlayerType_AI->setObjectName(QStringLiteral("PlayerType_AI"));
        PlayerType_AI->setGeometry(QRect(10, 40, 61, 17));
        Button_Play = new QPushButton(Options);
        Button_Play->setObjectName(QStringLiteral("Button_Play"));
        Button_Play->setGeometry(QRect(110, 120, 75, 23));

        retranslateUi(Options);

        QMetaObject::connectSlotsByName(Options);
    } // setupUi

    void retranslateUi(QWidget *Options)
    {
        Options->setWindowTitle(QApplication::translate("Options", "Options", 0));
        Box_OpponentType->setTitle(QApplication::translate("Options", "Opponent Type", 0));
        OpponentType_Online->setText(QApplication::translate("Options", "Online", 0));
        OpponentType_AI->setText(QApplication::translate("Options", "AI", 0));
        OpponentType_Human->setText(QApplication::translate("Options", "Human", 0));
        Box_PlayerType->setTitle(QApplication::translate("Options", "Player Type", 0));
        PlayerType_Human->setText(QApplication::translate("Options", "Human", 0));
        PlayerType_AI->setText(QApplication::translate("Options", "AI", 0));
        Button_Play->setText(QApplication::translate("Options", "Start", 0));
    } // retranslateUi

};

namespace Ui {
    class Options: public Ui_Options {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_OPTIONS_H
