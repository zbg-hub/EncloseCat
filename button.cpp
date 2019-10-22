#include "button.h"
#include <QTime>

Button::Button(QPushButton *parent) : QPushButton(parent)
{
	setWindowFlags (Qt::FramelessWindowHint);
	this->resize(35,35);
	this->setStyleSheet("border-image: url(:/img/button1.png);");
	setMask(QRegion(0,0,35,35,QRegion::Ellipse));
	connect(this, SIGNAL(clicked()), this, SLOT(receive_clicked()));
}

void Button::Init()
{
	enable = true;
	this->setStyleSheet("border-image: url(:/img/button1.png);");
}

void Button::receive_clicked()
{
	enable = false;
	this->setStyleSheet("border-image: url(:/img/button2.png);");
	qsrand(QTime(0,0,0).secsTo(QTime::currentTime()));
	emit send_cat_move(SeqX, SeqY);
}
