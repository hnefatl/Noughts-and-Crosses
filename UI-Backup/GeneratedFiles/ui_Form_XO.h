/********************************************************************************
** Form generated from reading UI file 'Form_XO.ui'
**
** Created by: Qt User Interface Compiler version 5.1.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_FORM_XO_H
#define UI_FORM_XO_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Form_XO
{
public:
    QAction *Menu_File_NewGame;
    QWidget *centralwidget;
    QPushButton *Button11;
    QLineEdit *Text_Status;
    QPushButton *Button12;
    QPushButton *Button13;
    QPushButton *Button21;
    QPushButton *Button22;
    QPushButton *Button23;
    QPushButton *Button31;
    QPushButton *Button32;
    QPushButton *Button33;
    QMenuBar *menuBar;
    QMenu *menuFile;

    void setupUi(QMainWindow *Form_XO)
    {
        if (Form_XO->objectName().isEmpty())
            Form_XO->setObjectName(QStringLiteral("Form_XO"));
        Form_XO->resize(255, 305);
        Menu_File_NewGame = new QAction(Form_XO);
        Menu_File_NewGame->setObjectName(QStringLiteral("Menu_File_NewGame"));
        centralwidget = new QWidget(Form_XO);
        centralwidget->setObjectName(QStringLiteral("centralwidget"));
        Button11 = new QPushButton(centralwidget);
        Button11->setObjectName(QStringLiteral("Button11"));
        Button11->setEnabled(false);
        Button11->setGeometry(QRect(10, 40, 75, 75));
        Text_Status = new QLineEdit(centralwidget);
        Text_Status->setObjectName(QStringLiteral("Text_Status"));
        Text_Status->setEnabled(false);
        Text_Status->setGeometry(QRect(10, 10, 231, 20));
        Text_Status->setReadOnly(true);
        Button12 = new QPushButton(centralwidget);
        Button12->setObjectName(QStringLiteral("Button12"));
        Button12->setEnabled(false);
        Button12->setGeometry(QRect(90, 40, 75, 75));
        Button13 = new QPushButton(centralwidget);
        Button13->setObjectName(QStringLiteral("Button13"));
        Button13->setEnabled(false);
        Button13->setGeometry(QRect(170, 40, 75, 75));
        Button21 = new QPushButton(centralwidget);
        Button21->setObjectName(QStringLiteral("Button21"));
        Button21->setEnabled(false);
        Button21->setGeometry(QRect(10, 120, 75, 75));
        Button22 = new QPushButton(centralwidget);
        Button22->setObjectName(QStringLiteral("Button22"));
        Button22->setEnabled(false);
        Button22->setGeometry(QRect(90, 120, 75, 75));
        Button23 = new QPushButton(centralwidget);
        Button23->setObjectName(QStringLiteral("Button23"));
        Button23->setEnabled(false);
        Button23->setGeometry(QRect(170, 120, 75, 75));
        Button31 = new QPushButton(centralwidget);
        Button31->setObjectName(QStringLiteral("Button31"));
        Button31->setEnabled(false);
        Button31->setGeometry(QRect(10, 200, 75, 75));
        Button32 = new QPushButton(centralwidget);
        Button32->setObjectName(QStringLiteral("Button32"));
        Button32->setEnabled(false);
        Button32->setGeometry(QRect(90, 200, 75, 75));
        Button33 = new QPushButton(centralwidget);
        Button33->setObjectName(QStringLiteral("Button33"));
        Button33->setEnabled(false);
        Button33->setGeometry(QRect(170, 200, 75, 75));
        Form_XO->setCentralWidget(centralwidget);
        menuBar = new QMenuBar(Form_XO);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 255, 21));
        menuFile = new QMenu(menuBar);
        menuFile->setObjectName(QStringLiteral("menuFile"));
        Form_XO->setMenuBar(menuBar);
        QWidget::setTabOrder(Text_Status, Button11);
        QWidget::setTabOrder(Button11, Button12);
        QWidget::setTabOrder(Button12, Button13);
        QWidget::setTabOrder(Button13, Button21);
        QWidget::setTabOrder(Button21, Button22);
        QWidget::setTabOrder(Button22, Button23);
        QWidget::setTabOrder(Button23, Button31);
        QWidget::setTabOrder(Button31, Button32);
        QWidget::setTabOrder(Button32, Button33);

        menuBar->addAction(menuFile->menuAction());
        menuFile->addAction(Menu_File_NewGame);

        retranslateUi(Form_XO);

        QMetaObject::connectSlotsByName(Form_XO);
    } // setupUi

    void retranslateUi(QMainWindow *Form_XO)
    {
        Form_XO->setWindowTitle(QApplication::translate("Form_XO", "XO", 0));
        Menu_File_NewGame->setText(QApplication::translate("Form_XO", "New Game", 0));
        Menu_File_NewGame->setShortcut(QApplication::translate("Form_XO", "Ctrl+N", 0));
        Button11->setText(QString());
        Text_Status->setText(QApplication::translate("Form_XO", "Start a new game from the menu.", 0));
        Button12->setText(QString());
        Button13->setText(QString());
        Button21->setText(QString());
        Button22->setText(QString());
        Button23->setText(QString());
        Button31->setText(QString());
        Button32->setText(QString());
        Button33->setText(QString());
        menuFile->setTitle(QApplication::translate("Form_XO", "File", 0));
    } // retranslateUi

};

namespace Ui {
    class Form_XO: public Ui_Form_XO {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_FORM_XO_H
