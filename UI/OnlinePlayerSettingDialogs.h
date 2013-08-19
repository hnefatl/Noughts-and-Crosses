#ifndef _ONLINEPLAYERSETTINGSDIALOG_H
#define _ONLINEPLAYERSETTINGSDIALOG_H

#include <QtWidgets\qwidget.h>
#include <QtWidgets\qdialog.h>
#include <QtWidgets\qlineedit.h>
#include <QtWidgets\qlabel.h>
#include <QtWidgets\qpushbutton.h>

class OnlinePlayerSettingsDialog
	: public QDialog
{
public:
	OnlinePlayerSettingsDialog(QWidget *Parent=NULL);
	~OnlinePlayerSettingsDialog();

	QLabel *LabelIP;
	QLabel *LabelPort;
	QLineEdit *TextIP;
	QLineEdit *TextPort;
	QLabel *LabelValidIP;
	QLabel *LabelValidPort;
	QPushButton *ButtonStart;

	bool ExitedLegally;
	std::string IP;
	std::string Port;

	bool ValidIP;
	bool ValidPort;

private slots:
	void Exit();

	void SlotCheckValidEntries(const QString& Template);

private:
	void Initialise();

	bool CheckValidEntries();
};

#endif