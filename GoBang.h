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
	bool hasItem(QPoint &point);		//�жϸ�λ���Ƿ��������

	int countOfItem(Item item, QPoint point);	//ͬɫ���Ӽ������ж�pointλ�÷����Ƿ������m_items��

private:
    Ui::GoBangClass ui;

	QVector<Item> m_items;	//����¹�������
	bool m_isBlack;			//�жϸ�ʲô����
};
