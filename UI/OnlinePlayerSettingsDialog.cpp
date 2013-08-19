#include "OnlinePlayerSettingDialogs.h"

#include <sstream>
#include <vector>
#include <string>

#include "Util.h"

OnlinePlayerSettingsDialog::OnlinePlayerSettingsDialog(QWidget *Parent)
	:QDialog(Parent),
	ExitedLegally(false)
{
	Initialise();
}
OnlinePlayerSettingsDialog::~OnlinePlayerSettingsDialog()
{
}

void OnlinePlayerSettingsDialog::Exit()
{
	// If the entries are valid
	if(CheckValidEntries())
	{
		// This is a legal exit
		ExitedLegally=true;
		IP=TextIP->text().toStdString();
		Port=TextPort->text().toStdString();
		accept();
	}
}

void OnlinePlayerSettingsDialog::SlotCheckValidEntries(const QString& Template)
{
	CheckValidEntries();

	if(ValidIP)
	{
		LabelValidIP->hide();
	}
	else
	{
		LabelValidIP->show();
	}
	if(ValidPort)
	{
		LabelValidPort->hide();
	}
	else
	{
		LabelValidPort->show();
	}

	LabelValidIP->repaint();
	LabelPort->repaint();
}

void OnlinePlayerSettingsDialog::Initialise()
{
	resize(250, 90);
	setWindowTitle(QString("Online settings"));

	LabelIP=new QLabel(QString("Server IP: "), this);
	LabelIP->setGeometry(10, 10, 70, 10);

	LabelPort=new QLabel(QString("Server Port: "), this);
	LabelPort->setGeometry(10, 30, 70, 10);

	TextIP=new QLineEdit(this);
	TextIP->setGeometry(75, 6, 100, 20);
	connect(TextIP, &QLineEdit::textChanged, this, &OnlinePlayerSettingsDialog::SlotCheckValidEntries);

	TextPort=new QLineEdit(this);
	TextPort->setGeometry(75, 28, 100, 20);
	connect(TextPort, &QLineEdit::textChanged, this, &OnlinePlayerSettingsDialog::SlotCheckValidEntries);

	LabelValidIP=new QLabel(QString("Invalid IP."), this);
	LabelValidIP->setGeometry(180, 10, 100, 10);

	LabelValidPort=new QLabel(QString("Invalid Port."), this);
	LabelValidPort->setGeometry(180, 30, 100, 10);

	ButtonStart=new QPushButton(QString("Start"), this);
	ButtonStart->setGeometry(100, 58, 50, 25);
	connect(ButtonStart, &QPushButton::clicked, this, &OnlinePlayerSettingsDialog::Exit);
}

bool OnlinePlayerSettingsDialog::CheckValidEntries()
{
	// Check valid IP
	// Split the IP into segments, split from the '.' character
	std::vector<std::string> Segments=Split(TextIP->text().toStdString(), '.');
	bool Failed=false;
	// If there aren't exactly four segments
	if(Segments.size()!=4)
	{
		// Failed test
		Failed=true;
	}
	for(unsigned int x=0; x<Segments.size(); x++)
	{
		std::stringstream IPChecker;
		IPChecker<<Segments[x];
		int Out;
		IPChecker>>Out;
		// If Out is less than 0 or greater than 255
		if(!(Out>=0 && Out<256))
		{
			// Failed test
			Failed=true;
			break;
		}
	}
	ValidIP=!Failed;

	// Check valid port (is a number)
	std::stringstream PortStream;
	PortStream<<TextPort->text().toStdString();
	int Out=-1;
	PortStream>>Out;
	// If Out is less than 0 or greater than 65535
	if(Out<0 && Out<65536)
	{
		// Failed test
		ValidPort=false;
	}
	else
	{
		ValidPort=true;
	}

	return ValidIP && ValidPort;
}