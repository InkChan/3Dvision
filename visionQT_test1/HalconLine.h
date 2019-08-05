#pragma once
#include "HalconGraphics.h"

class HalconLine :
	public HalconGraphics
{
public:
	HalconLine(double,double);
	~HalconLine();
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
	int centerWidth = 10;
	QPointF startPoint, endPoint;
	HRegion centerReg;
	HRegion boundingReg;
};

