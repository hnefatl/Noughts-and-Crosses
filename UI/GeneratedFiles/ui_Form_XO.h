/********************************************************************************
** Form generated from reading UI file 'MainWindow.ui'
**
** Created by: Qt User Interface Compiler version 5.1.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

#include <vector>
#include <string>
#include <sstream>
#include "Globals.h"

QT_BEGIN_NAMESPACE

class Ui_Form_XO
{
public:
    QWidget *centralwidget;
    QLineEdit *Text_Status;
	std::vector<std::vector<QPushButton *>> Buttons;

    void setupUi(QMainWindow *Form_XO)
    {
        if (Form_XO->objectName().isEmpty())
            Form_XO->setObjectName(QStringLiteral("Form_XO"));
        Form_XO->resize(255, 285);
        centralwidget = new QWidget(Form_XO);
        centralwidget->setObjectName(QStringLiteral("centralwidget"));
        Text_Status = new QLineEdit(centralwidget);
        Text_Status->setObjectName(QStringLiteral("Text_Status"));
        Text_Status->setEnabled(false);
        Text_Status->setGeometry(QRect(10, 10, 231, 20));

		// Size out the buttons
		Buttons.resize(GridSize);
		for(unsigned int x=0; x<GridSize; x++)
		{
			Buttons[x].resize(GridSize);
		}
		for(unsigned int y=0; y<GridSize; y++)
		{
			for(unsigned int x=0; x<GridSize; x++)
			{
				// Create name
				std::stringstream Name;
				Name<<"Button"<<x<<y;

				// Set parent
				Buttons[y][x]=new QPushButton(centralwidget);
				// Set name
				Buttons[y][x]->setObjectName(Name.str().c_str());
				// Set size and location
				Buttons[y][x]->setGeometry(10+(80*x), 40+(80*y), 75, 75);
				// Disable to start with
				Buttons[y][x]->setEnabled(false);
			}
		}

        Form_XO->setCentralWidget(centralwidget);

        retranslateUi(Form_XO);

        QMetaObject::connectSlotsByName(Form_XO);
    } // setupUi

    void retranslateUi(QMainWindow *Form_XO)
    {
        Form_XO->setWindowTitle(QApplication::translate("Form_XO", "XO", 0));
		for(unsigned int y=0; y<Buttons.size(); y++)
		{
			for(unsigned int x=0; x<Buttons[y].size(); x++)
			{
				Buttons[y][x]->setText(QString());
			}
		}
    } // retranslateUi
};

namespace Ui {
    class Form_XO: public Ui_Form_XO {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
