#include "HalconGraphics.h"


HalconGraphics::HalconGraphics():
canMove(false),
showMove(false),
canZoom(false),
showZoom(false)
{
}


HalconGraphics::~HalconGraphics()
{
}

void HalconGraphics::checkMove(QPoint)
{
}

void HalconGraphics::checkZoom(QPoint)
{
}

bool HalconGraphics::Movable()
{
	return false;
}

void HalconGraphics::setMoveable(bool)
{
}

void HalconGraphics::setMove(QPointF)
{}

bool HalconGraphics::Zoomable()
{
	return false;
}

void HalconGraphics::setZoomable(bool)
{}

void HalconGraphics::setZoom(QPointF, QPointF)
{
}

void HalconGraphics::paint(HTuple wID)
{}

int HalconGraphics::type() const
{
	return 65536;
}

bool HalconGraphics::getShowMove()
{
	return showMove;
}

bool HalconGraphics::getShowZoom()
{
	return showZoom;
}