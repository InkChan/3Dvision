#include "HalconPoint.h"


HalconPoint::HalconPoint(double cX, double cY)
	:canMove(false),
	showMove(false)
{
	centerX = cX;
	centerY = cY;
	GenRectangle1(&centerRect, centerY - centerWidth, centerX - centerWidth,
		centerY + centerWidth, centerX + centerWidth);

	centerLine1 = QLine(centerX, centerY - lineWidth,
		centerX, centerY + lineWidth);
	centerLine2 = QLine(centerX - lineWidth, centerY,
		centerX + lineWidth, centerY);
}

void HalconPoint::paint(HTuple wID)
{
	SetLineWidth(wID, 2);
	SetDraw(wID, "margin");
	SetColor(wID, "#64AAFF");
	DispLine(wID, centerLine1.p1().y(), centerLine1.p1().x(),
		centerLine1.p2().y(), centerLine1.p2().x());
	DispLine(wID, centerLine2.p1().y(), centerLine2.p1().x(),
		centerLine2.p2().y(), centerLine2.p2().x());

	if (showMove == true)
	{
		SetColor(wID, "#64C8FF");
		DispObj(centerRect, wID);
	}
}

void HalconPoint::checkMove(QPoint mousePos)
{
	if (pow(mousePos.x() - centerX, 2) + pow(mousePos.y() - centerY, 2)
		<= 100)
	{
		showMove = true;
	}
	else
	{
		showMove = false;
	}
}

void HalconPoint::setMove(QPointF pos)
{
	//重新计算中心点
	centerX = centerX + pos.x();
	centerY = centerY + pos.y();

	//重新计算center rect
	GenRectangle1(&centerRect, centerY - centerWidth, centerX - centerWidth,
		centerY + centerWidth, centerX + centerWidth);
	//重新计算center line
	centerLine1 = QLine(centerX, centerY - lineWidth,
		centerX, centerY + lineWidth);
	centerLine2 = QLine(centerX - lineWidth, centerY,
		centerX + lineWidth, centerY);
}

void HalconPoint::setMoveable(bool status)
{
	canMove = status;
}

bool HalconPoint::Movable()
{
	return canMove;;
}

bool HalconPoint::getShowMove()
{
	return showMove;
}

int HalconPoint::type() const
{
	return 65536 + 1;
}

HalconPoint::~HalconPoint()
{
}
