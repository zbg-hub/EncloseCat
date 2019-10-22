#ifndef BUTTON_H
#define BUTTON_H

#include <QObject>
#include <QPushButton>
#include <QObject>
#include <iostream>
#include <QAbstractButton>
using namespace std;

class Button : public QPushButton
{
	Q_OBJECT
public:
	explicit Button(QPushButton *parent = nullptr);
	void Init();

public:
	int SeqX;
	int SeqY;
	int x;
	int y;
	bool enable;

signals:
	void send_cat_move(int x, int y);

public slots:
	void receive_clicked();
};

#endif // BUTTON_H
