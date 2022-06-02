#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_GoBang.h"
#include <qevent.h>
#include "Item.h"
#include <QVector>
#include <QPainter>
#include <QMouseEvent>

const int Chess_Rows = 15;
const int Chess_Colums = 15;
const int Rect_Width = 30;
const int Rect_Height = 30;

class GoBang : public QMainWindow
{
    Q_OBJECT

public:
    GoBang(QWidget *parent = Q_NULLPTR);

protected:
	void paintEvent(QPaintEvent *);
	void mousePressEvent(QMouseEvent *);

private:
	void drawChessMap();
	void drawItem();
	void drawMouseItem();

	void drawChessAtPoint(QPainter &painter, QPoint &point);
	bool hasItem(QPoint &point);		//判断该位置是否存在棋子

	int countOfItem(Item item, QPoint point);	//同色棋子计数，判断point位置方向是否包含在m_items中

private:
    Ui::GoBangClass ui;

	QVector<Item> m_items;	//存放下过的棋子
	bool m_isBlack;			//判断该什么棋下
};
