#pragma once
#include "HalconGraphics.h"
class HalconPoint :
	public HalconGraphics
{
public:
	HalconPoint(double,double);
	~HalconPoint();

	bool canMove,showMove;

	void paint(HTuple wID);
	void checkMove(QPoint);
	bool Movable();
	void setMoveable(bool);
	void setMove(QPointF);
	int type() const;
	bool getShowMove();

private:
	//���ĵ�
	double centerX = 0, centerY = 0;
	//���ľ���
	HRegion centerRect;
	int centerWidth = 25, lineWidth = 35;
	//������
	QLine centerLine1, centerLine2;
};

