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
	//中心点
	double centerX = 0, centerY = 0;
	//中心矩形
	HRegion centerRect;
	int centerWidth = 25, lineWidth = 35;
	//中心线
	QLine centerLine1, centerLine2;
};

