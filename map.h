#ifndef MAP_H
#define MAP_H
#include <vector>
#include <QWidget>
#include <QLabel>
#include "button.h"
using namespace std;

namespace Ui {
class Map;
}

class Map : public QWidget
{
	Q_OBJECT

public:
	explicit Map(QWidget *parent = nullptr);
	~Map();
	int generateRandomNumber(int n);

public:
	vector<vector<Button*>> MainMap;

private slots:
	void on_pushButton_clicked();
	void receive_cat_move(int x,int y);

private:
	Ui::Map *ui;
	QLabel *Cat = new QLabel;
	int CatX =5;
	int CatY =5;
	int matrix[121][121]={0};
};

#endif // MAP_H
