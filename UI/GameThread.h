#ifndef _GAMETHREAD_H
#define _GAMETHREAD_H

#include <qthread.h>
#include <qstring.h>

#include <thread>

#include "Vector.h"
#include "Grid.h"
#include "Player.h"
#include "HumanPlayer.h"
#include "AIPlayer.h"
#include "OnlinePlayer.h"

class GameThread
	: public QThread
{
public:
	GameThread(Player *PlayerOne, Player *PlayerTwo, QObject *Parent=NULL);

	virtual void run();
signals:
	void SetButtonText(const Vector &Button, const QString &Text);
	void SetButtonEnabled(const Vector &Button, const bool &Enabled);

	Vector WaitForButtonPress();

	void SetPressableButtonsEnabled(const bool &Enabled);

	void SetStatusText(const QString &Text);

private:
	Grid Board;
	std::vector<Player *> Players;
};

#endif