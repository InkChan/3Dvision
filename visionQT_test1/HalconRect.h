#pragma once
#include <HalconCpp.h>
#include <QObject>
#include <qline.h>
#include "HalconGraphics.h"
using namespace HalconCpp;

class HalconRect:public HalconGraphics
{
public:
	///中心点
	HalconRect(double , double);
	~HalconRect();

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
	double height = 200, width = 600;
	int centerWidth = 7, lineWidth = 40;

	//矩xing
	HRegion rect;
	HRegion centerRect;
	HRegion boundingRect;
	//线
	QLine line1, line2, line3, line4;
	QLine centerLine1, centerLine2;
};

