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

	//��д==����  �ж��Ƿ���������ʱʹ��
	bool operator==(const Item &item) const{
		return (this->m_point == item.m_point) && (this->m_black == item.m_black);
	}

	QPoint m_point;
	bool m_black;

private:

};