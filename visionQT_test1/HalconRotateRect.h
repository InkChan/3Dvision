#pragma once
#include "HalconGraphics.h"
class HalconRotateRect
	: public HalconGraphics
{
public:
	HalconRotateRect(double,double);
	~HalconRotateRect();

	bool canMove, showMove, canZoom, showZoom, showRotate, showScale;

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
	QPointF getVertex(QPointF a, double O);

private:
	double centerX = 0, centerY = 0;
	double height = 200, width = 600;
	double rad = 0;
	int centerWidth = 7, lineWidth = 40;

	//¾Øxing
	HRegion rect;
	HRegion centerRect;
	HRegion boundingRect;
	HRegion rotateRect;
	//Ïß
	QLineF line1, line2, line3, line4;
	QLineF centerLine1, centerLine2;
};

