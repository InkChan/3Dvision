#pragma once
#include <HalconCpp.h>
#include <qpainter.h>
using namespace HalconCpp;

class HalconGraphics
{
public:
	HalconGraphics();
	virtual ~HalconGraphics();
	
	bool canMove, showMove, canZoom, showZoom;

	virtual void checkMove(QPoint);
	virtual void checkZoom(QPoint);
	virtual bool Movable();
	virtual void setMoveable(bool);
	virtual void setMove(QPointF);

	virtual bool Zoomable();
	virtual void setZoomable(bool);
	virtual void setZoom(QPointF, QPointF);

	virtual void paint(HTuple wID);
	virtual bool getShowMove();
	virtual bool getShowZoom();

	virtual int type()const;
};

