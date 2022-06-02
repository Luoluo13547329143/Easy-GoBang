#include "GoBang.h"
#include <QMessageBox>

GoBang::GoBang(QWidget *parent)
    : QMainWindow(parent)
{
    ui.setupUi(this);

	ui.mainToolBar->hide();
	ui.menuBar->hide();
	
	setFixedSize((Chess_Colums + 1) * Rect_Width, (Chess_Rows + 1) * Rect_Height);

	setWindowFlags(Qt::WindowCloseButtonHint);
	setWindowTitle(QString::fromLocal8Bit("简易五子棋"));

	m_isBlack = true;	//黑棋先行
}

void GoBang::paintEvent(QPaintEvent *)
{
	drawChessMap();	//画棋盘
	drawItem();		//画棋子
	drawMouseItem();//画鼠标

	update();
}

void GoBang::mousePressEvent(QMouseEvent *e)
{
	QPoint point;
	point.setX(e->pos().x() / Rect_Width);
	point.setY(e->pos().y() / Rect_Height);
	//如果该位置已经有棋则返回
	if (hasItem(point)) {
		return;
	}

	Item item(point, m_isBlack);
	m_items.append(item);
	//判断游戏是否结束
	//前九子跳过判断
	if (m_items.count() > 8) {
		int up = countOfItem(item, QPoint(0, 1));
		int down = countOfItem(item, QPoint(0, -1));
		int left = countOfItem(item, QPoint(-1, 0));
		int right = countOfItem(item, QPoint(1, 0));
		int upLeft = countOfItem(item, QPoint(-1, 1));
		int upRight = countOfItem(item, QPoint(1, 1));
		int downLeft = countOfItem(item, QPoint(-1, -1));
		int downRight = countOfItem(item, QPoint(1, -1));

		if ((up + down >= 4) || (left + right >= 4) || (upLeft + downRight >= 4) || (upRight + downLeft >= 4) ){
			QString str = m_isBlack ? "Black" : "White";
			QMessageBox::information(nullptr, "GameOver", str + " win");
			m_items.clear();
			m_isBlack = true;
			return;
		}
	}

	m_isBlack = !m_isBlack;
}

void GoBang::drawChessMap()
{
	QPainter painter(this);
	QPen pen;
	pen.setWidth(3);
	pen.setColor(Qt::black);
	painter.setRenderHint(QPainter::HighQualityAntialiasing);
	painter.setBrush(Qt::darkYellow);
	painter.setPen(pen);

	for (int i = 0; i < Chess_Colums; i++) {
		for (int j = 0; j < Chess_Rows; j++) {
			painter.drawRect((i + 0.5)*Rect_Width, (j + 0.5) * Rect_Height, Rect_Width, Rect_Height);
		}
		//painter.drawLine((i * Rect_Width), 0, (i * Rect_Width), (Chess_Rows * Rect_Height));
	}
}

void GoBang::drawItem()
{
	QPainter painter(this);
	painter.setPen(QPen(Qt::transparent));		//边线透明

	for (int i = 0; i < m_items.count(); i++) {
		Item item = m_items[i];
		if (item.m_black) {
			painter.setBrush(Qt::black);
		}
		else {
			painter.setBrush(Qt::white);
		}

		drawChessAtPoint(painter, item.m_point);
	}

}

void GoBang::drawMouseItem()
{
	QPainter painter(this);
	painter.setPen(Qt::transparent);

	if (m_isBlack) {
		painter.setBrush(Qt::black);
	}
	else {
		painter.setBrush(Qt::white);
	}

	painter.drawEllipse(mapFromGlobal(QCursor::pos()), Rect_Width / 2, Rect_Height / 2);
}

void GoBang::drawChessAtPoint(QPainter & painter, QPoint & point)
{
	//对点的坐标取整
	point.setX((point.x()+0.5) * Rect_Width);
	point.setY((point.y()+0.5) * Rect_Height);
	painter.drawEllipse(point, Rect_Width / 2, Rect_Width / 2);
}
//开销太大 有待优化
bool GoBang::hasItem(QPoint & point)
{
	for (int i = 0; i < m_items.count(); i++) {
		Item item = m_items[i];
		if (item.m_point == point) {
			return true;
		}
	}
	return false;
}

int GoBang::countOfItem(Item item, QPoint point)
{
	int count = 0;
	item.m_point += point;
	while (m_items.contains(item)) {
		count++;
		item.m_point += point;
	}

	return count;
}
