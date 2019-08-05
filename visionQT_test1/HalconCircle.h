#pragma once
#include "HalconGraphics.h"

class HalconCircle:
	public HalconGraphics
{
public:
	HalconCircle(double ,double);
	~HalconCircle();
	bool canMove, showMove, canZoom, showZoom;

	void paint(HTuple wID);
	void checkMove(QPoint);
	void checkZoom(QPoint);
	bool Movable();
	void setMoveable(bool);
	void setMove(QPointF);

	bool Zoomable();
	void setZoomable(bool);
	void setZoom(QPointF,QPointF);
	int type() const;
	bool getShowMove();
	bool getShowZoom();

private:
	double centerX = 0, centerY = 0;
	int centerWidth = 20, circleRad = 100;
	HRegion circleReg;
	HRegion centerReg;
	HRegion zoomReg;
	QLineF radLine;
};

