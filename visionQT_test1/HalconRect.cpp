#include "HalconRect.h"


HalconRect::HalconRect(double cX, double cY)
	:canMove(false),
	showMove(false),
	canZoom(false),
	showZoom(false)
{
	centerX = cX;
	centerY = cY;
	GenRectangle1(&rect, centerY - height / 2, centerX - width / 2, centerY + height / 2, centerX + width / 2);
	GenRectangle1(&centerRect, centerY - lineWidth, centerX - lineWidth,
		centerY + lineWidth, centerX + lineWidth);
	GenRectangle1(&boundingRect, centerY - height / 2 - lineWidth, centerX - width / 2 - lineWidth,
		centerY + height / 2 + lineWidth, centerX + width / 2 + lineWidth);


	//四条线赋值
	line1 = QLine(centerX - width / 2, centerY - height / 2 - lineWidth,
		centerX - width / 2, centerY + height / 2 + lineWidth);
	line2 = QLine(centerX + width / 2, centerY - height / 2 - lineWidth,
		centerX + width / 2, centerY + height / 2 + lineWidth);
	line3 = QLine(centerX - width / 2 - lineWidth, centerY - height / 2,
		centerX + width / 2 + lineWidth, centerY - height / 2);
	line4 = QLine(centerX - width / 2 - lineWidth, centerY + height / 2,
		centerX + width / 2 + lineWidth, centerY + height / 2);

	//中心线赋值
	centerLine1 = QLine(centerX, centerY - lineWidth,
		centerX, centerY + lineWidth);
	centerLine2 = QLine(centerX - lineWidth, centerY,
		centerX + lineWidth, centerY);
}

void HalconRect::paint(HTuple wID)
{

	SetLineWidth(wID, 2);
	SetDraw(wID, "margin");
	SetColor(wID, "#64AAFF");	
	DispObj(rect, wID);

	if (showMove == true)
	{
		SetColor(wID, "#64C8FF");
		DispObj(centerRect, wID);
		DispLine(wID, centerLine1.p1().y(), centerLine1.p1().x(), 
			centerLine1.p2().y(), centerLine1.p2().x());
		DispLine(wID, centerLine2.p1().y(), centerLine2.p1().x(), 
			centerLine2.p2().y(), centerLine2.p2().x());
	}
	if (showZoom == true)
	{
		SetColor(wID, "#64C8FF");
		DispObj(boundingRect, wID);
		DispLine(wID, line1.p1().y(), line1.p1().x(), line1.p2().y(), line1.p2().x());
		DispLine(wID, line2.p1().y(), line2.p1().x(), line2.p2().y(), line2.p2().x());
		DispLine(wID, line3.p1().y(), line3.p1().x(), line3.p2().y(), line3.p2().x());
		DispLine(wID, line4.p1().y(), line4.p1().x(), line4.p2().y(), line4.p2().x());
	}
}

void HalconRect::checkMove(QPoint mousePos)
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

void HalconRect::setMove(QPointF pos)
{
	HTuple row1, row2, column1, column2;
	RegionFeatures(rect, "column1", &column1);
	RegionFeatures(rect, "row1", &row1);
	RegionFeatures(rect, "column2", &column2);
	RegionFeatures(rect, "row2", &row2);

	//重新计算中心点
	centerX = centerX + pos.x();
	centerY = centerY + pos.y();

	//重新生成矩形
	GenRectangle1(&rect, row1 + pos.y(), column1 + pos.x(),
		row2 + pos.y(), column2 + pos.x());

	//重新计算bounding rect
	RegionFeatures(boundingRect, "column1", &column1);
	RegionFeatures(boundingRect, "row1", &row1);
	RegionFeatures(boundingRect, "column2", &column2);
	RegionFeatures(boundingRect, "row2", &row2);
	GenRectangle1(&boundingRect, row1 + pos.y(), column1 + pos.x(),
		row2 + pos.y(), column2 + pos.x());

	//重新计算bounding line
	RegionFeatures(boundingRect, "column1", &column1);
	RegionFeatures(boundingRect, "row1", &row1);
	RegionFeatures(boundingRect, "column2", &column2);
	RegionFeatures(boundingRect, "row2", &row2);
	line1 = QLine(column1.D() + lineWidth, row1.D(), column1.D() + lineWidth, row2.D());
	line2 = QLine(column2.D() - lineWidth, row1.D(), column2.D() - lineWidth, row2.D());
	line3 = QLine(column1.D(), row1.D() + lineWidth, column2.D(), row1.D() + lineWidth);
	line4 = QLine(column1.D(), row2.D() - lineWidth, column2.D(), row2.D() - lineWidth);

	//重新计算center rect
	GenRectangle1(&centerRect, centerY - lineWidth, centerX - lineWidth,
		centerY + lineWidth, centerX + lineWidth);
	//重新计算center line
	centerLine1 = QLine(centerX, centerY - lineWidth,
		centerX, centerY + lineWidth);
	centerLine2 = QLine(centerX - lineWidth, centerY,
		centerX + lineWidth, centerY);
}

void HalconRect::setMoveable(bool status)
{
	canMove = status;
}

bool HalconRect::Movable()
{
	return canMove;
}

void HalconRect::setZoom(QPointF s,QPointF e)
{
	QPointF pos = QPointF(e.x() - s.x(), e.y() - s.y());

	HTuple row1, row2, column1, column2;
	RegionFeatures(rect, "column1", &column1);
	RegionFeatures(rect, "row1", &row1);
	RegionFeatures(rect, "column2", &column2);
	RegionFeatures(rect, "row2", &row2);

	GenRectangle1(&rect, row1, column1, row2 + pos.y(), column2 + pos.x());

	//重新计算中心点
	centerX = (column1.D() + column2.D() + pos.x()) / 2;
	centerY = (row1.D() + row2.D() + pos.y()) / 2;

	//重新计算bounding rect
	RegionFeatures(boundingRect, "column1", &column1);
	RegionFeatures(boundingRect, "row1", &row1);
	RegionFeatures(boundingRect, "column2", &column2);
	RegionFeatures(boundingRect, "row2", &row2);
	double temrow1 = row1.D();
	double temcol1 = column1.D();
	double temrow2 = row2.D();
	double temcol2 = column2.D();

	GenRectangle1(&boundingRect, row1, column1, row2 + pos.y(), column2 + pos.x());

	//重新计算bounding line
	RegionFeatures(boundingRect, "column1", &column1);
	RegionFeatures(boundingRect, "row1", &row1);
	RegionFeatures(boundingRect, "column2", &column2);
	RegionFeatures(boundingRect, "row2", &row2);
	line1 = QLine(column1.D() + lineWidth, row1.D(), column1.D() + lineWidth, row2.D());
	line2 = QLine(column2.D() - lineWidth, row1.D(), column2.D() - lineWidth, row2.D());
	line3 = QLine(column1.D(), row1.D() + lineWidth, column2.D(), row1.D() + lineWidth);
	line4 = QLine(column1.D(), row2.D() - lineWidth, column2.D(), row2.D() - lineWidth); 

	//重新计算center rect
	GenRectangle1(&centerRect, centerY - lineWidth, centerX - lineWidth,
		centerY + lineWidth, centerX + lineWidth);
	//重新计算center line
	centerLine1 = QLine(centerX, centerY - lineWidth,
		centerX, centerY + lineWidth);
	centerLine2 = QLine(centerX - lineWidth, centerY,
		centerX + lineWidth, centerY);
}

void HalconRect::checkZoom(QPoint mousePos)
{
	HTuple row1, row2, column1, column2;
	RegionFeatures(rect, "column1", &column1);
	RegionFeatures(rect, "row1", &row1);
	RegionFeatures(rect, "column2", &column2);
	RegionFeatures(rect, "row2", &row2);

	int brX = column2.D();
	int brY = row2.D();

	if (pow(mousePos.x() - brX, 2) + pow(mousePos.y() - brY, 2) <= 100)
	{
		showZoom = true;
		showMove = false;
	}
	else
	{
		showZoom = false;
	}
}

bool HalconRect::Zoomable()
{
	return canZoom;
}

void HalconRect::setZoomable(bool status)
{
	canZoom = status;
}

int HalconRect::type() const
{
	return 65536 + 3;
}

bool HalconRect::getShowMove()
{
	return showMove;
}

bool HalconRect::getShowZoom()
{
	return showZoom;
}

HalconRect::~HalconRect()
{
}
