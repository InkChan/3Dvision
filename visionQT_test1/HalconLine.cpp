#include "HalconLine.h"


HalconLine::HalconLine(double cx,double cy)
	:canMove(false),
	showMove(false),
	canZoom(false),
	showZoom(false)
{
	centerX = cx;
	centerY = cy;

	//起始点。终止点
	startPoint = QPointF(cx - 100, cy);
	endPoint = QPointF(cx + 100, cy);

	//中心rect
	GenCircle(&centerReg, centerY, centerX, centerWidth);
	//end端点rect
	GenCircle(&boundingReg, endPoint.y(), endPoint.x(), centerWidth);
}

void HalconLine::paint(HTuple wID)
{
	SetLineWidth(wID, 2);
	SetDraw(wID, "margin");
	SetColor(wID, "#64AAFF");
	DispLine(wID, startPoint.y(), startPoint.x(), endPoint.y(), endPoint.x());

	if (showMove == true)
	{
		SetColor(wID, "#64C8FF");
		DispObj(centerReg, wID);
	}

	if (showZoom == true)
	{
		SetColor(wID, "#64C8FF");
		DispObj(boundingReg, wID);
	}
}

void HalconLine::checkMove(QPoint mousePos)
{
	if (pow(mousePos.x() - centerX, 2) + pow(mousePos.y() - centerY, 2)
		<= 100)
	{
		showMove = true;
		showZoom = false;
	}
	else
	{
		showMove = false;
	}
}

void HalconLine::checkZoom(QPoint mousePos)
{
	if (pow(mousePos.x() - endPoint.x(), 2) + pow(mousePos.y() - endPoint.y(), 2) <= 100)
	{
		showZoom = true;
		showMove = false;
	}
	else
	{
		showZoom = false;
	}
}

bool HalconLine::Movable()
{
	return canMove;
}

void HalconLine::setMoveable(bool status)
{
	canMove = status;
}

void HalconLine::setMove(QPointF pos)
{
	//重新计算中心点
	centerX = centerX + pos.x();
	centerY = centerY + pos.y();

	//重新计算端点
	startPoint.setX(startPoint.x() + pos.x());
	startPoint.setY(startPoint.y() + pos.y());
	endPoint.setX(endPoint.x() + pos.x());
	endPoint.setY(endPoint.y() + pos.y());

	//中心rect
	GenCircle(&centerReg, centerY, centerX, centerWidth);
	//GenRectangle1(&centerRect, centerY - centerWidth, centerX - centerWidth,
	//	centerY + centerWidth, centerX + centerWidth);
	//end端点rect
	GenCircle(&boundingReg, endPoint.y(), endPoint.x(), centerWidth);
}

bool HalconLine::Zoomable()
{
	return canZoom;
}

void HalconLine::setZoomable(bool status)
{
	canZoom = status;
}

void HalconLine::setZoom(QPointF s,QPointF e)
{
	QPointF pos(e.x() - s.x(), e.y() - s.y());

	//重新设置endpoint
	endPoint.setX(endPoint.x() + pos.x());
	endPoint.setY(endPoint.y() + pos.y());
	//重新计算centerpoint
	centerX = (startPoint.x() + endPoint.x()) / 2;
	centerY = (startPoint.y() + endPoint.y()) / 2;
	//重新计算centerrect boundingrect
	//中心rect
	GenCircle(&centerReg, centerY, centerX, centerWidth);
	//GenRectangle1(&centerRect, centerY - centerWidth, centerX - centerWidth,
	//	centerY + centerWidth, centerX + centerWidth);
	//end端点rect
	GenCircle(&boundingReg, endPoint.y(), endPoint.x(), centerWidth);
}

int HalconLine::type() const
{
	return 65536 + 2;
}

bool HalconLine::getShowMove()
{
	return showMove;
}

bool HalconLine::getShowZoom()
{
	return showZoom;
}

HalconLine::~HalconLine()
{
}
