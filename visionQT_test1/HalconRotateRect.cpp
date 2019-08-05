#include "HalconRotateRect.h"


HalconRotateRect::HalconRotateRect(double cx, double cy)
	:canMove(false),
	showMove(false),
	canZoom(false),
	showZoom(false),
	showRotate(false),
	showScale(false)
{
	centerX = cx;
	centerY = cy;

	//生成rect,centerRect,boundingRect
	GenRectangle2(&rect, centerY, centerX, rad, width / 2, height / 2);
	GenRectangle2(&centerRect, centerY, centerX, rad, lineWidth, lineWidth);
	GenRectangle2(&boundingRect, centerY, centerX, rad, width / 2 + lineWidth, 
		height / 2 + lineWidth);
	QPointF Rcenter = getVertex(QPointF(centerX - width / 2, centerY), rad);
	GenRectangle2(&rotateRect, Rcenter.y(), Rcenter.x(), rad, lineWidth, lineWidth);

	
	//计算边框线
	line1 = QLineF(getVertex(QPointF(centerX - (width / 2 + lineWidth), centerY - height / 2),
		rad), getVertex(QPointF(centerX + (width / 2 + lineWidth), centerY - height / 2), rad));
	line2 = QLineF(getVertex(QPointF(centerX - (width / 2 + lineWidth), centerY + height / 2),
		rad), getVertex(QPointF(centerX + (width / 2 + lineWidth), centerY + height / 2), rad));
	line3 = QLineF(getVertex(QPointF(centerX - width / 2, centerY - (height / 2 + lineWidth)),
		rad), getVertex(QPointF(centerX - width / 2, centerY + (height / 2 + lineWidth)), rad)); 
	line4 = QLineF(getVertex(QPointF(centerX + width / 2, centerY - (height / 2 + lineWidth)),
		rad), getVertex(QPointF(centerX + width / 2, centerY + (height / 2 + lineWidth)), rad));

	//中心线赋值
	HTuple cosV, sinV;
	TupleCos(rad, &cosV);
	TupleSin(rad, &sinV);
	double Length1 = lineWidth / 2, Length2 = lineWidth / 2;
	QPointF LT, LB, RT, RB;
	LB.setY(centerY - (-Length1*sinV - Length2*cosV));
	LB.setX(centerX + (-Length1*cosV + Length2*sinV));
	RB.setX(centerX + (Length1*cosV + Length2*sinV));
	RB.setY(centerY - (Length1*sinV - Length2*cosV));
	LT.setX(centerX + (-Length1*cosV - Length2*sinV));
	LT.setY(centerY - (-Length1*sinV + Length2*cosV));
	RT.setX(centerX + (Length1*cosV - Length2*sinV));
	RT.setY(centerY - (Length1*sinV + Length2*cosV));

	centerLine1 = QLineF(QPointF((LT.x() + LB.x()) / 2, (LT.y() + LB.y()) / 2),
		QPointF((RT.x() + RB.x()) / 2, (RT.y() + RB.y()) / 2));
	centerLine2 = QLineF(QPointF((LT.x() + RT.x()) / 2, (LT.y() + RT.y()) / 2),
		QPointF((LB.x() + RB.x()) / 2, (LB.y() + RB.y()) / 2));

	
}

void HalconRotateRect::paint(HTuple wID)
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
		if (showRotate == true)
		{
			DispObj(rotateRect, wID);
		}
		else
		{
			DispObj(boundingRect, wID);
			DispLine(wID, line1.p1().y(), line1.p1().x(), line1.p2().y(), line1.p2().x());
			DispLine(wID, line2.p1().y(), line2.p1().x(), line2.p2().y(), line2.p2().x());
			DispLine(wID, line3.p1().y(), line3.p1().x(), line3.p2().y(), line3.p2().x());
			DispLine(wID, line4.p1().y(), line4.p1().x(), line4.p2().y(), line4.p2().x());
		}		
	}
}

void HalconRotateRect::checkMove(QPoint mousePos)
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

void HalconRotateRect::checkZoom(QPoint mousePos)
{
	HTuple cosV, sinV;
	TupleCos(rad, &cosV);
	TupleSin(rad, &sinV);
	double Length1 = width / 2, Length2 = height / 2;
	QPointF LT, LB, RT, RB;
	LB.setY(centerY - (-Length1*sinV - Length2*cosV));
	LB.setX(centerX + (-Length1*cosV + Length2*sinV));
	RB.setX(centerX + (Length1*cosV + Length2*sinV));
	RB.setY(centerY - (Length1*sinV - Length2*cosV));
	LT.setX(centerX + (-Length1*cosV - Length2*sinV));
	LT.setY(centerY - (-Length1*sinV + Length2*cosV));
	RT.setX(centerX + (Length1*cosV - Length2*sinV));
	RT.setY(centerY - (Length1*sinV + Length2*cosV));

	QPointF Rcenter = getVertex(QPointF(centerX - width / 2, centerY), rad);

	//showScale
	if (pow(mousePos.x() - RB.x(), 2) + pow(mousePos.y() - RB.y(), 2) <= lineWidth*lineWidth)
	{
		showZoom = true;		
		showScale = true;
		showMove = false;
		showRotate = false;
	}
	//showRotate
	else if (pow(mousePos.x() - Rcenter.x(), 2) + pow(mousePos.y() - Rcenter.y(), 2) <= lineWidth*lineWidth)
	{
		showZoom = true;
		showRotate = true;
		showMove = false;
		showScale = false;
	}
	else
	{
		showZoom = false;
		showScale = false;
		showRotate = false;
	}
}

bool HalconRotateRect::Movable()
{
	return canMove;
}

void HalconRotateRect::setMoveable(bool status)
{
	canMove = status;
}

void HalconRotateRect::setMove(QPointF pos)
{
	//重新计算中心点
	centerX = centerX + pos.x();
	centerY = centerY + pos.y();

	//重新计算矩形
	GenRectangle2(&rect, centerY, centerX, rad, width / 2, height / 2);
	GenRectangle2(&centerRect, centerY, centerX, rad, lineWidth, lineWidth);
	GenRectangle2(&boundingRect, centerY, centerX, rad, width / 2 + lineWidth,
		height / 2 + lineWidth);
	QPointF Rcenter = getVertex(QPointF(centerX - width / 2, centerY), rad);
	GenRectangle2(&rotateRect, Rcenter.y(), Rcenter.x(), rad, lineWidth, lineWidth);

	//重新计算边框线
	line1 = QLineF(getVertex(QPointF(centerX - (width / 2 + lineWidth), centerY - height / 2),
		rad), getVertex(QPointF(centerX + (width / 2 + lineWidth), centerY - height / 2), rad));
	line2 = QLineF(getVertex(QPointF(centerX - (width / 2 + lineWidth), centerY + height / 2),
		rad), getVertex(QPointF(centerX + (width / 2 + lineWidth), centerY + height / 2), rad));
	line3 = QLineF(getVertex(QPointF(centerX - width / 2, centerY - (height / 2 + lineWidth)),
		rad), getVertex(QPointF(centerX - width / 2, centerY + (height / 2 + lineWidth)), rad));
	line4 = QLineF(getVertex(QPointF(centerX + width / 2, centerY - (height / 2 + lineWidth)),
		rad), getVertex(QPointF(centerX + width / 2, centerY + (height / 2 + lineWidth)), rad));

	//重新计算中心线
	HTuple cosV, sinV;
	TupleCos(rad, &cosV);
	TupleSin(rad, &sinV);
	double Length1 = lineWidth / 2, Length2 = lineWidth / 2;
	QPointF LT, LB, RT, RB;
	LB.setY(centerY - (-Length1*sinV - Length2*cosV));
	LB.setX(centerX + (-Length1*cosV + Length2*sinV));
	RB.setX(centerX + (Length1*cosV + Length2*sinV));
	RB.setY(centerY - (Length1*sinV - Length2*cosV));
	LT.setX(centerX + (-Length1*cosV - Length2*sinV));
	LT.setY(centerY - (-Length1*sinV + Length2*cosV));
	RT.setX(centerX + (Length1*cosV - Length2*sinV));
	RT.setY(centerY - (Length1*sinV + Length2*cosV));

	centerLine1 = QLineF(QPointF((LT.x() + LB.x()) / 2, (LT.y() + LB.y()) / 2),
		QPointF((RT.x() + RB.x()) / 2, (RT.y() + RB.y()) / 2));
	centerLine2 = QLineF(QPointF((LT.x() + RT.x()) / 2, (LT.y() + RT.y()) / 2),
		QPointF((LB.x() + RB.x()) / 2, (LB.y() + RB.y()) / 2));
}

bool HalconRotateRect::Zoomable()
{
	return canZoom;
}

void HalconRotateRect::setZoomable(bool status)
{
	canZoom = status;
}

void HalconRotateRect::setZoom(QPointF s,QPointF e)
{
	QPointF pos = QPointF(e.x() - s.x(), e.y() - s.y());

	if (showScale == true)
	{
		HTuple cosV, sinV;
		TupleCos(rad, &cosV);
		TupleSin(rad, &sinV);
		double Length1 = width / 2, Length2 = height / 2;
		QPointF LT, LB, RT, RB;
		LB.setY(centerY - (-Length1*sinV - Length2*cosV));
		LB.setX(centerX + (-Length1*cosV + Length2*sinV));
		RB.setX(centerX + (Length1*cosV + Length2*sinV));
		RB.setY(centerY - (Length1*sinV - Length2*cosV));
		LT.setX(centerX + (-Length1*cosV - Length2*sinV));
		LT.setY(centerY - (-Length1*sinV + Length2*cosV));
		RT.setX(centerX + (Length1*cosV - Length2*sinV));
		RT.setY(centerY - (Length1*sinV + Length2*cosV));

		//Right-Bottom点偏移
		RB.setX(RB.x() + pos.x());
		RB.setY(RB.y() + pos.y());

		centerX = (LT.x() + RB.x()) / 2;
		centerY = (LT.y() + RB.y()) / 2;

		double temRadian = atan2(RB.y() - LT.y(), RB.x() - LT.x())+rad;
		height = abs(sinf(temRadian)*sqrtf(powf(RB.x() - LT.x(), 2) + powf(RB.y() - LT.y(), 2)));
		width = abs(cosf(temRadian)*sqrtf(powf(RB.x() - LT.x(), 2) + powf(RB.y() - LT.y(), 2)));

		//生成rect,centerRect,boundingRect
		GenRectangle2(&rect, centerY, centerX, rad, width / 2, height / 2);
		GenRectangle2(&centerRect, centerY, centerX, rad, lineWidth, lineWidth);
		GenRectangle2(&boundingRect, centerY, centerX, rad, width / 2 + lineWidth,
			height / 2 + lineWidth);
		QPointF Rcenter = getVertex(QPointF(centerX - width / 2, centerY), rad);
		GenRectangle2(&rotateRect, Rcenter.y(), Rcenter.x(), rad, lineWidth, lineWidth);

		//重新计算边框线
		line1 = QLineF(getVertex(QPointF(centerX - (width / 2 + lineWidth), centerY - height / 2),
			rad), getVertex(QPointF(centerX + (width / 2 + lineWidth), centerY - height / 2), rad));
		line2 = QLineF(getVertex(QPointF(centerX - (width / 2 + lineWidth), centerY + height / 2),
			rad), getVertex(QPointF(centerX + (width / 2 + lineWidth), centerY + height / 2), rad));
		line3 = QLineF(getVertex(QPointF(centerX - width / 2, centerY - (height / 2 + lineWidth)),
			rad), getVertex(QPointF(centerX - width / 2, centerY + (height / 2 + lineWidth)), rad));
		line4 = QLineF(getVertex(QPointF(centerX + width / 2, centerY - (height / 2 + lineWidth)),
			rad), getVertex(QPointF(centerX + width / 2, centerY + (height / 2 + lineWidth)), rad));

		//重新计算中心线
		Length1 = lineWidth / 2;
		Length2 = lineWidth / 2;
		LB.setY(centerY - (-Length1*sinV - Length2*cosV));
		LB.setX(centerX + (-Length1*cosV + Length2*sinV));
		RB.setX(centerX + (Length1*cosV + Length2*sinV));
		RB.setY(centerY - (Length1*sinV - Length2*cosV));
		LT.setX(centerX + (-Length1*cosV - Length2*sinV));
		LT.setY(centerY - (-Length1*sinV + Length2*cosV));
		RT.setX(centerX + (Length1*cosV - Length2*sinV));
		RT.setY(centerY - (Length1*sinV + Length2*cosV));

		centerLine1 = QLineF(QPointF((LT.x() + LB.x()) / 2, (LT.y() + LB.y()) / 2),
			QPointF((RT.x() + RB.x()) / 2, (RT.y() + RB.y()) / 2));
		centerLine2 = QLineF(QPointF((LT.x() + RT.x()) / 2, (LT.y() + RT.y()) / 2),
			QPointF((LB.x() + RB.x()) / 2, (LB.y() + RB.y()) / 2));

		return;
	}
	
	if (showRotate == true)
	{
		float ux = s.x() - centerX;
		float uy = s.y() - centerY;

		float vx = e.x() - centerX;
		float vy = e.y() - centerY;

		float modu = sqrtf(ux*ux + uy*uy);
		float modv = sqrtf(vx*vx + vy*vy);

		if (modu<0.00001f || modv<0.00001f)
		{
			return;
		}

		double tempRad = (atan2f(vy, vx) - atan2f(uy, ux));
		rad -= tempRad;

		//生成rect,centerRect,boundingRect
		GenRectangle2(&rect, centerY, centerX, rad, width / 2, height / 2);
		GenRectangle2(&centerRect, centerY, centerX, rad, lineWidth, lineWidth);
		GenRectangle2(&boundingRect, centerY, centerX, rad, width / 2 + lineWidth,
			height / 2 + lineWidth);
		QPointF Rcenter = getVertex(QPointF(centerX - width / 2, centerY), rad);
		GenRectangle2(&rotateRect, Rcenter.y(), Rcenter.x(), rad, lineWidth, lineWidth);

		//重新计算边框线
		line1 = QLineF(getVertex(QPointF(centerX - (width / 2 + lineWidth), centerY - height / 2),
			rad), getVertex(QPointF(centerX + (width / 2 + lineWidth), centerY - height / 2), rad));
		line2 = QLineF(getVertex(QPointF(centerX - (width / 2 + lineWidth), centerY + height / 2),
			rad), getVertex(QPointF(centerX + (width / 2 + lineWidth), centerY + height / 2), rad));
		line3 = QLineF(getVertex(QPointF(centerX - width / 2, centerY - (height / 2 + lineWidth)),
			rad), getVertex(QPointF(centerX - width / 2, centerY + (height / 2 + lineWidth)), rad));
		line4 = QLineF(getVertex(QPointF(centerX + width / 2, centerY - (height / 2 + lineWidth)),
			rad), getVertex(QPointF(centerX + width / 2, centerY + (height / 2 + lineWidth)), rad));

		//重新计算中心线
		HTuple cosV, sinV;
		TupleCos(rad, &cosV);
		TupleSin(rad, &sinV);
		double Length1 = lineWidth / 2, Length2 = lineWidth / 2;
		QPointF LT, LB, RT, RB;
		LB.setY(centerY - (-Length1*sinV - Length2*cosV));
		LB.setX(centerX + (-Length1*cosV + Length2*sinV));
		RB.setX(centerX + (Length1*cosV + Length2*sinV));
		RB.setY(centerY - (Length1*sinV - Length2*cosV));
		LT.setX(centerX + (-Length1*cosV - Length2*sinV));
		LT.setY(centerY - (-Length1*sinV + Length2*cosV));
		RT.setX(centerX + (Length1*cosV - Length2*sinV));
		RT.setY(centerY - (Length1*sinV + Length2*cosV));

		centerLine1 = QLineF(QPointF((LT.x() + LB.x()) / 2, (LT.y() + LB.y()) / 2),
			QPointF((RT.x() + RB.x()) / 2, (RT.y() + RB.y()) / 2));
		centerLine2 = QLineF(QPointF((LT.x() + RT.x()) / 2, (LT.y() + RT.y()) / 2),
			QPointF((LB.x() + RB.x()) / 2, (LB.y() + RB.y()) / 2));
	}
	
}

int HalconRotateRect::type() const
{
	return 65536 + 4;
}

bool HalconRotateRect::getShowMove()
{
	return showMove;
}

bool HalconRotateRect::getShowZoom()
{
	return showZoom;
}

QPointF HalconRotateRect::getVertex(QPointF a, double radian)
{	
	radian = PI - radian;
	return QPointF((a.x() - centerX)*cosf(radian) - (a.y() - centerY)*sinf(radian) + centerX,
		(a.x() - centerX)*sinf(radian) + (a.y() - centerY)*cosf(radian) + centerY);
}

HalconRotateRect::~HalconRotateRect()
{
}
