/********************************************************************************
** Form generated from reading UI file 'options.ui'
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
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_OptionsClass
{
public:

    void setupUi(QWidget *OptionsClass)
    {
        if (OptionsClass->objectName().isEmpty())
            OptionsClass->setObjectName(QStringLiteral("OptionsClass"));
        OptionsClass->resize(600, 400);

        retranslateUi(OptionsClass);

        QMetaObject::connectSlotsByName(OptionsClass);
    } // setupUi

    void retranslateUi(QWidget *OptionsClass)
    {
        OptionsClass->setWindowTitle(QApplication::translate("OptionsClass", "Options", 0));
    } // retranslateUi

};

namespace Ui {
    class OptionsClass: public Ui_OptionsClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_OPTIONS_H
