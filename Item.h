#pragma once
#include <QPoint>

class Item {
public:
	Item() {};
	Item(QPoint point, bool mBlack) {
		m_black = mBlack;
		m_point = point;
	};
	~Item() {};

	//重写==函数  判断是否五子相连时使用
	bool operator==(const Item &item) const{
		return (this->m_point == item.m_point) && (this->m_black == item.m_black);
	}

	QPoint m_point;
	bool m_black;

private:

};