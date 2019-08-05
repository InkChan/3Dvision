#include "HalconCircle.h"


HalconCircle::HalconCircle(double cx, double cy)
	:canMove(false),
	showMove(false),
	canZoom(false),
	showZoom(false)
{
	centerX = cx;
	centerY = cy;

	//圆
	GenCircle(&circleReg, centerY, centerX, circleRad);
	//中心圆
	GenCircle(&centerReg, centerY, centerX, centerWidth);
	//boundary 圆
	GenCircle(&zoomReg, centerY, centerX + circleRad, centerWidth);

	radLine = QLineF(QPointF(centerX, centerY), QPointF(centerX + circleRad, centerY));
}

void HalconCircle::paint(HTuple wID)
{
	SetLineWidth(wID, 2);
	SetDraw(wID, "margin");
	SetColor(wID, "#64AAFF");
	DispObj(circleReg, wID);

	if (showMove == true)
	{
		SetColor(wID, "#64C8FF");
		DispObj(centerReg, wID);
	}
	if (showZoom == true)
	{
		SetColor(wID, "#64C8FF");
		DispObj(zoomReg, wID);
		DispLine(wID, radLine.p1().y(), radLine.p1().x(), radLine.p2().y(), radLine.p2().x());
	}
}

void HalconCircle::checkMove(QPoint mousePos)
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

void HalconCircle::checkZoom(QPoint mousePos)
{
	if (pow(mousePos.x() - (centerX + circleRad), 2) + pow(mousePos.y() - centerY, 2) <= centerWidth*centerWidth)
	{
		showZoom = true;
		showMove = false;
	}
	else
	{
		showZoom = false;
	}
}

bool HalconCircle::Movable()
{
	return canMove;
}

void HalconCircle::setMoveable(bool status)
{
	canMove = status;
}

void HalconCircle::setMove(QPointF pos)
{
	//重新计算中心点
	centerX = centerX + pos.x();
	centerY = centerY + pos.y();

	//圆
	GenCircle(&circleReg, centerY, centerX, circleRad);
	//中心圆
	GenCircle(&centerReg, centerY, centerX, centerWidth);
	//boundary 圆
	GenCircle(&zoomReg, centerY, centerX + circleRad, centerWidth);

	radLine = QLineF(QPointF(centerX, centerY), QPointF(centerX + circleRad, centerY));
}

bool HalconCircle::Zoomable()
{
	return canZoom;
}

void HalconCircle::setZoomable(bool status)
{
	canZoom = status;
}

void HalconCircle::setZoom(QPointF s, QPointF e)
{
	QPointF pos(e.x() - s.x(), e.y() - s.y());
	//重新设置
	circleRad = circleRad + pos.x();
	GenCircle(&circleReg, centerY, centerX, circleRad);
	//boundary 圆
	GenCircle(&zoomReg, centerY, centerX + circleRad, centerWidth);
	radLine = QLineF(QPointF(centerX, centerY), QPointF(centerX + circleRad, centerY));
}

int HalconCircle::type() const
{
	return 65536 + 5;
}

bool HalconCircle::getShowMove()
{
	return showMove;
}

bool HalconCircle::getShowZoom()
{
	return showZoom;
}

HalconCircle::~HalconCircle()
{
}
