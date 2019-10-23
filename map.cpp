#include "map.h"
#include "ui_map.h"
#include <iostream>
#include <QTime>
#include <QToolButton>
using namespace std;

Map::Map(QWidget *parent) :
	QWidget(parent),
	ui(new Ui::Map)
{
	ui->setupUi(this);
	setWindowFlags(windowFlags()&~Qt::WindowMaximizeButtonHint);	//禁止最大化按钮
	setFixedSize(this->width(),this->height());
	for(int i =0;i<11;i++)//行
	{
		vector<Button*> temp1;
		MainMap.push_back(temp1);
		for(int j = 0;j<11;j++)//列
		{
			Button *temp2 = new Button;
			if(i%2==0)
			{
				temp2->x = j*40+100;
				if((i!=0&&i!=10)&&(j!=0&&j!=10))
				{
					matrix[i*11+j][(i-1)*11+j-1] = 1;
					matrix[i*11+j][(i-1)*11+j] = 1;
					matrix[i*11+j][i*11+j-1] = 1;
					matrix[i*11+j][i*11+j+1] = 1;
					matrix[i*11+j][(i+1)*11+j-1] = 1;
					matrix[i*11+j][(i+1)*11+j] = 1;
				}
			}
			else {
				temp2->x = j*40+120;
				if((i!=0&&i!=10)&&(j!=0&&j!=10))
				{
					matrix[i*11+j][(i-1)*11+j] = 1;
					matrix[i*11+j][(i-1)*11+j+1] = 1;
					matrix[i*11+j][i*11+j-1] = 1;
					matrix[i*11+j][i*11+j+1] = 1;
					matrix[i*11+j][(i+1)*11+j] = 1;
					matrix[i*11+j][(i+1)*11+j+1] = 1;
				}
			}
			temp2->y = i*40+50;
			temp2->SeqX = i;
			temp2->SeqY = j;
			temp2->enable = true;
			temp2->setParent(this);
			temp2->move(temp2->x,temp2->y);
			temp2->show();
			MainMap[i].push_back(temp2);
		}
	}
	for(int i=1;i<10;i++)
	{
		matrix[i][i+10]=1;
		matrix[i][i+11]=1;
		matrix[i][i-1]=1;
		matrix[i][i+1]=1;
		matrix[110+i][98+i]=1;
		matrix[110+i][99+i]=1;
		matrix[110+i][110+i-1]=1;
		matrix[110+i][110+i+1]=1;
		if(i%2==0)
		{
			matrix[11*i][11*i-11]=1;
			matrix[11*i][11*i+11]=1;
			matrix[11*i+10][11*i-1]=1;
			matrix[11*i+10][11*1+21]=1;
			matrix[11*i+10][11*i-2]=1;
			matrix[11*i+10][11*1+20]=1;
			matrix[11*i+10][11*i+9]=1;
		}
		else {
			matrix[11*i][11*i-11]=1;
			matrix[11*i][11*i+11]=1;
			matrix[11*i][11*i+1]=1;
			matrix[11*i][11*i-10]=1;
			matrix[11*i][11*i+12]=1;
			matrix[11*i+10][11*i-1]=1;
			matrix[11*i+10][11*1+21]=1;
		}
	}
	matrix[0][1]=1;
	matrix[0][11]=1;
	matrix[10][9]=1;
	matrix[10][21]=1;
	matrix[10][20]=1;
	matrix[110][99]=1;
	matrix[110][111]=1;
	matrix[120][119]=1;
	matrix[120][109]=1;
	matrix[120][108]=1;
	//qsrand(QTime(0,0,0).secsTo(QTime::currentTime()));
	qsrand((quint32)time(0));
	for(int i = 0;i<8;i++)
	{
		int a = generateRandomNumber(10);
		int b = generateRandomNumber(10);
		if((a==b&&a==5)||(MainMap[a][b]->enable == false))
		{
			i--;
			continue;
		}
		MainMap[a][b]->enable = false;
		MainMap[a][b]->setStyleSheet("border-image: url(:/img/button2.png);");
	}
	Cat->resize(30,30);
	Cat->setStyleSheet("border-image: url(:/img/cat.png);");
	Cat->move(MainMap[5][5]->x,MainMap[5][5]->y);
	Cat->setParent(this);
	Cat->show();

	for(int i =0;i<11;i++)
	{
		for(int j =0;j<11;j++)
		{
			connect(MainMap[i][j], SIGNAL(send_cat_move(int,int)), this, SLOT(receive_cat_move(int,int)));
		}
	}


}

Map::~Map()
{
	delete ui;
}

int Map::generateRandomNumber(int n)
{
	int res =qrand()%n;
	return res;
}

void Map::on_pushButton_clicked()
{
	for(int i = 0;i<10;i++)
	{
		for(int j = 0;j<10;j++)
		{
			MainMap[i][j]->Init();
		}
	}
	//qsrand(QTime(0,0,0).secsTo(QTime::currentTime()));
	qsrand((quint32)time(0));
	for(int i = 0;i<8;i++)
	{
		int a = generateRandomNumber(10);
		int b = generateRandomNumber(10);
		if((a==b&&a==5)||(MainMap[a][b]->enable == false))
		{
			i--;
			continue;
		}
		MainMap[a][b]->enable = false;
		MainMap[a][b]->setStyleSheet("border-image: url(:/img/button2.png);");
	}
	Cat->move(MainMap[5][5]->x,MainMap[5][5]->y);
}

void Map::receive_cat_move(int x,int y)
{
	int direct = generateRandomNumber(6);
	int temX=CatX;
	int temY=CatY;
	int temp = CatX%2;
	cout<<"dir="<<direct<<endl;
	switch (direct) {
	case 0:
		CatX--;
		CatY = CatY+temp-1;
		break;
	case 1:
		CatX--;
		CatY = CatY+temp;
		break;
	case 2:
		CatY--;
		break;
	case 3:
		CatY++;
		break;
	case 4:
		CatX++;
		CatY = CatY+temp-1;
		break;
	case 5:
		CatX++;
		CatY = CatY+temp;
		break;
	}
	if(MainMap[CatX][CatY]->enable==false||(CatX==x&&CatY==y))
	{
		CatX = temX;
		CatY = temY;
		receive_cat_move(x,y);
		return;
	}
	Cat->move(MainMap[CatX][CatY]->x,MainMap[CatX][CatY]->y);
}
