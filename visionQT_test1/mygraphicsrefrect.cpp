#include "mygraphicsrefrect.h"

MyGraphicsRefrect::MyGraphicsRefrect(QPointF _p)
{
	this->setPos(_p);
	centerPoint = QPointF(0, 0);
	canMove = false;
	showMove = false;
	canZoom = false;
	showZoom = false;
	angle = 60;
	resizeangle = angle;
	width = 100;
	height = 100;
	border = 6;
	rotateCenter = QPointF(0, 0);
	topLeftZoom = false;
	topRightZoom = false; 
	bottomLeftZoom = false; 
	bottomRightZoom = false;
	rotateFlag = false;
	sx = 1;
	sy = 1;

	polygon.push_back(getVertex(QPointF(-width / 2, -height / 2),angle));
	polygon.push_back(getVertex(QPointF(width / 2, -height / 2), angle));
	polygon.push_back(getVertex(QPointF(width / 2, height / 2), angle));
	polygon.push_back(getVertex(QPointF(-width / 2, height / 2), angle));

	zoomPolygon.push_back(getVertex(QPointF(-(width / 2 + border), -(height / 2 + border)), angle));;
	zoomPolygon.push_back(getVertex(QPointF((width / 2 + border), -(height / 2 + border)), angle));
	zoomPolygon.push_back(getVertex(QPointF((width / 2 + border), (height / 2 + border)), angle));
	zoomPolygon.push_back(getVertex(QPointF(-(width / 2 + border), (height / 2 + border)), angle));

	centePolygon.push_back(getVertex(QPointF(-border, -border), angle));
	centePolygon.push_back(getVertex(QPointF(border, -border), angle));
	centePolygon.push_back(getVertex(QPointF(border, border), angle));
	centePolygon.push_back(getVertex(QPointF(-border, border), angle));

	lineOne = QLineF(getVertex(QPointF(-(width / 2 + border), -height / 2), angle), getVertex(QPointF(width / 2 + border, -height / 2), angle));
	lineTwo = QLineF(getVertex(QPointF(-(width / 2 + border), height / 2), angle), getVertex(QPointF(width / 2 + border, height / 2), angle));
	lineThree = QLineF(getVertex(QPointF(-width / 2, -(height / 2 + border)), angle), getVertex(QPointF(-width / 2, height / 2 + border), angle));
	lineFour = QLineF(getVertex(QPointF(width / 2, -(height / 2 + border)), angle), getVertex(QPointF(width / 2, height / 2 + border), angle));
}

MyGraphicsRefrect::~MyGraphicsRefrect()
{

}

QRectF MyGraphicsRefrect::boundingRect() const
{
	return polygon.boundingRect();;
}

int MyGraphicsRefrect::type() const
{
	return 65536 + 4;
}

void MyGraphicsRefrect::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{	
	painter->setPen(QPen(QColor(100, 170, 255), 3));
	painter->drawPolygon(polygon);
	
	if (showMove == true)
	{
		painter->setPen(QPen(QColor(100, 200, 255), 2));
		painter->drawPolygon(centePolygon);
		painter->drawLine(QPointF((centePolygon[0].x() + centePolygon[1].x()) / 2,
			(centePolygon[0].y() + centePolygon[1].y()) / 2),
			QPointF((centePolygon[2].x() + centePolygon[3].x()) / 2,
			(centePolygon[2].y() + centePolygon[3].y()) / 2));

		painter->drawLine(QPointF((centePolygon[1].x() + centePolygon[2].x()) / 2,
			(centePolygon[1].y() + centePolygon[2].y()) / 2),
			QPointF((centePolygon[0].x() + centePolygon[3].x()) / 2,
			(centePolygon[0].y() + centePolygon[3].y()) / 2));
	}
	
	if (showZoom == true)
	{
		painter->setPen(QPen(QColor(100, 200, 255), 2));
		painter->drawPolygon(zoomPolygon);
		painter->drawLine(lineOne);
		painter->drawLine(lineTwo);
		painter->drawLine(lineThree);
		painter->drawLine(lineFour);
	}
}

void MyGraphicsRefrect::checkMove(QPointF mousePos)
{
	QPointF tem = this->pos();
	if ((pow(mousePos.x() - (this->pos().x() + polygon.boundingRect().center().x()), 2) +
		pow(mousePos.y() - (this->pos().y() + polygon.boundingRect().center().y()), 2)) <= 100)
	{
		showMove = true;
		showZoom = false;
	}
	else
	{
		showMove = false;
	}
}

void MyGraphicsRefrect::checkZoom(QPointF mousePos)
{	
	if ((pow((mousePos.x() - (this->pos().x() + polygon.at(2).x())),2)+
		pow((mousePos.y() - (this->pos().y() + polygon.at(2).y())),2)) <= 100 )
	{
		showZoom = true;
		bottomRightZoom = true;
		topLeftZoom = false;
		topRightZoom = false;
		bottomLeftZoom = false;
		rotateFlag = false;
	}
	else if ((pow((mousePos.x() - (this->pos().x() + polygon.at(3).x())), 2) +
		pow((mousePos.y() - (this->pos().y() + polygon.at(3).y())), 2)) <= 100)
	{
		showZoom = true;
		bottomLeftZoom = true;
		topLeftZoom = false;
		topRightZoom = false;
		bottomRightZoom = false;
		rotateFlag = false;
	}

	else if ((pow(mousePos.x() - (this->pos().x() + (polygon[1].x()+polygon[2].x())/2), 2) +
		pow(mousePos.y() - (this->pos().y() + (polygon[1].y() + polygon[2].y()) / 2), 2)) <= 100)
	{
		showZoom = true;
		rotateFlag = true;
		topLeftZoom = false;
		topRightZoom = false;
		bottomLeftZoom = false;
		bottomRightZoom = false;
	}
	else
	{
		showZoom = false;
	}
}

//返回当前是否能move
bool MyGraphicsRefrect::Movable()
{
	return canMove;
}

void MyGraphicsRefrect::setMovable(bool status)
{
	canMove = status;
}

//返回当前是否能zoom
bool MyGraphicsRefrect::Zoomable()
{
	return canZoom;
}

void MyGraphicsRefrect::setZoomable(bool status)
{
	//rotateCenter = rect.center();
	canZoom = status;
}

//设置放大缩小
void MyGraphicsRefrect::setZoom(QPointF s, QPointF e)
{
	QPointF pos = QPointF(e.x() - s.x(), e.y() - s.y());

	if (bottomRightZoom == true)
	{
		double temp1 = atan2f(polygon[1].y() - polygon[0].y(), polygon[1].x() - polygon[0].x());
		double temp3 = atan2f(polygon[3].y() - polygon[0].y(), polygon[3].x() - polygon[0].x());
		double temp = atan2f(polygon[2].y() + pos.y() - polygon[0].y(), polygon[2].x() + pos.x() - polygon[0].x());

		if (temp <= temp1 || temp >= temp3)
		{
			return;
		}

		polygon[2] = QPointF(polygon[2].x() + pos.x(), polygon[2].y() + pos.y());
		
		centerPoint = QPointF((polygon[2].x() + polygon[0].x()) / 2, (polygon[2].y() + polygon[0].y()) / 2);

		double temRadian = atan2(polygon[2].y() - polygon[0].y(), polygon[2].x() - polygon[0].x()) - angle / 180 * PI;

		height = abs(sinf(temRadian)*sqrtf(powf(polygon[2].x() - polygon[0].x(), 2) + powf(polygon[2].y() - polygon[0].y(), 2)));
		width = abs(cosf(temRadian)*sqrtf(powf(polygon[2].x() - polygon[0].x(), 2) + powf(polygon[2].y() - polygon[0].y(), 2)));

		polygon[1] = getVertex(QPointF(centerPoint.x() + width / 2, centerPoint.y() + (-height / 2)), angle);
		polygon[3] = getVertex(QPointF(centerPoint.x() - width / 2, centerPoint.y() + (height / 2)), angle);

		centePolygon[0] = getVertex(QPointF(centerPoint.x() - border, centerPoint.y()- border), angle);
		centePolygon[1] = getVertex(QPointF(centerPoint.x() + border, centerPoint.y() - border), angle);
		centePolygon[2] = getVertex(QPointF(centerPoint.x() + border, centerPoint.y() + border), angle);
		centePolygon[3] = getVertex(QPointF(centerPoint.x() - border, centerPoint.y() + border), angle);

		zoomPolygon[0] = getVertex(QPointF(centerPoint.x() - (width / 2 + border), centerPoint.y() - (height / 2 + border)), angle);
		zoomPolygon[1] = getVertex(QPointF(centerPoint.x() + (width / 2 + border), centerPoint.y() - (height / 2 + border)), angle);
		zoomPolygon[2] = getVertex(QPointF(centerPoint.x() + (width / 2 + border), centerPoint.y() + (height / 2 + border)), angle);
		zoomPolygon[3] = getVertex(QPointF(centerPoint.x() - (width / 2 + border), centerPoint.y() + (height / 2 + border)), angle);

		lineOne = QLineF(getVertex(QPointF(centerPoint.x() - (width / 2 + border), centerPoint.y() - height / 2), angle), 
			getVertex(QPointF(centerPoint.x() + width / 2 + border, centerPoint.y() - height / 2), angle));
		lineTwo = QLineF(getVertex(QPointF(centerPoint.x() - (width / 2 + border), centerPoint.y() + height / 2), angle),
			getVertex(QPointF(centerPoint.x() + width / 2 + border, centerPoint.y() + height / 2), angle));
		lineThree = QLineF(getVertex(QPointF(centerPoint.x() - width / 2, centerPoint.y() - (height / 2 + border)), angle),
			getVertex(QPointF(centerPoint.x() - width / 2, centerPoint.y() + height / 2 + border), angle));
		lineFour = QLineF(getVertex(QPointF(centerPoint.x() + width / 2, centerPoint.y() - (height / 2 + border)), angle),
			getVertex(QPointF(centerPoint.x() + width / 2, centerPoint.y() + height / 2 + border), angle));
	}
	else if (bottomLeftZoom == true)
	{
		double temp0 = atan2f(polygon[0].y() - polygon[1].y(), polygon[0].x() - polygon[1].x());
		double temp2 = atan2f(polygon[2].y() - polygon[1].y(), polygon[2].x() - polygon[1].x());
		double temp = atan2f(polygon[3].y() + pos.y() - polygon[1].y(), polygon[3].x() + pos.x() - polygon[1].x());

		if (temp <= temp2&&temp >= temp0)
		{
			return;
		}
	

		polygon[3] = QPointF(polygon[3].x() + pos.x(), polygon[3].y() + pos.y());
		centerPoint = QPointF((polygon[1].x() + polygon[3].x()) / 2, (polygon[1].y() + polygon[3].y()) / 2);

		double temRadian = atan2(polygon[3].y() - polygon[1].y(), polygon[3].x() - polygon[1].x()) - angle / 180 * PI;

		height = abs(sinf(temRadian)*sqrtf(powf(polygon[3].x() - polygon[1].x(), 2) + powf(polygon[3].y() - polygon[1].y(), 2)));
		width = abs(cosf(temRadian)*sqrtf(powf(polygon[3].x() - polygon[1].x(), 2) + powf(polygon[3].y() - polygon[1].y(), 2)));

		polygon[0] = getVertex(QPointF(centerPoint.x() - width / 2, centerPoint.y() + (-height / 2)), angle);
		polygon[2] = getVertex(QPointF(centerPoint.x() + width / 2, centerPoint.y() + (height / 2)), angle);

		centePolygon[0] = getVertex(QPointF(centerPoint.x() - border, centerPoint.y() - border), angle);
		centePolygon[1] = getVertex(QPointF(centerPoint.x() + border, centerPoint.y() - border), angle);
		centePolygon[2] = getVertex(QPointF(centerPoint.x() + border, centerPoint.y() + border), angle);
		centePolygon[3] = getVertex(QPointF(centerPoint.x() - border, centerPoint.y() + border), angle);

		zoomPolygon[0] = getVertex(QPointF(centerPoint.x() - (width / 2 + border), centerPoint.y() - (height / 2 + border)), angle);
		zoomPolygon[1] = getVertex(QPointF(centerPoint.x() + (width / 2 + border), centerPoint.y() - (height / 2 + border)), angle);
		zoomPolygon[2] = getVertex(QPointF(centerPoint.x() + (width / 2 + border), centerPoint.y() + (height / 2 + border)), angle);
		zoomPolygon[3] = getVertex(QPointF(centerPoint.x() - (width / 2 + border), centerPoint.y() + (height / 2 + border)), angle);

		lineOne = QLineF(getVertex(QPointF(centerPoint.x() - (width / 2 + border), centerPoint.y() - height / 2), angle),
			getVertex(QPointF(centerPoint.x() + width / 2 + border, centerPoint.y() - height / 2), angle));
		lineTwo = QLineF(getVertex(QPointF(centerPoint.x() - (width / 2 + border), centerPoint.y() + height / 2), angle),
			getVertex(QPointF(centerPoint.x() + width / 2 + border, centerPoint.y() + height / 2), angle));
		lineThree = QLineF(getVertex(QPointF(centerPoint.x() - width / 2, centerPoint.y() - (height / 2 + border)), angle),
			getVertex(QPointF(centerPoint.x() - width / 2, centerPoint.y() + height / 2 + border), angle));
		lineFour = QLineF(getVertex(QPointF(centerPoint.x() + width / 2, centerPoint.y() - (height / 2 + border)), angle),
			getVertex(QPointF(centerPoint.x() + width / 2, centerPoint.y() + height / 2 + border), angle));
	}

	else if (rotateFlag == true)
	{
		s.setX(s.x() - this->pos().x());
		s.setY(s.y() - this->pos().y());
		e.setX(e.x() - this->pos().x());
		e.setY(e.y() - this->pos().y());

		float ux = s.x() - centerPoint.x();
		float uy = s.y() - centerPoint.y();

		float vx = e.x() - centerPoint.x();
		float vy = e.y() - centerPoint.y();

		float modu = sqrtf(ux*ux + uy*uy);
		float modv = sqrtf(vx*vx + vy*vy);

		if (modu<0.00001f || modv<0.00001f)
		{
			return;
		}
		double O = (atan2f(vy, vx) - atan2f(uy, ux)) * 180 / PI;
		angle += O;

		polygon[0] = getVertex(polygon[0], O);
		polygon[1] = getVertex(polygon[1], O);
		polygon[2] = getVertex(polygon[2], O);
		polygon[3] = getVertex(polygon[3], O);

		zoomPolygon[0] = getVertex(zoomPolygon[0], O);
		zoomPolygon[1] = getVertex(zoomPolygon[1], O);
		zoomPolygon[2] = getVertex(zoomPolygon[2], O);
		zoomPolygon[3] = getVertex(zoomPolygon[3], O);

		centePolygon[0] = getVertex(centePolygon[0], O);
		centePolygon[1] = getVertex(centePolygon[1], O);
		centePolygon[2] = getVertex(centePolygon[2], O);
		centePolygon[3] = getVertex(centePolygon[3], O);

		lineOne = QLineF(getVertex(lineOne.p1(),O), getVertex(lineOne.p2(),O));
		lineTwo = QLineF(getVertex(lineTwo.p1(), O), getVertex(lineTwo.p2(), O));
		lineThree = QLineF(getVertex(lineThree.p1(), O), getVertex(lineThree.p2(), O));
		lineFour = QLineF(getVertex(lineFour.p1(), O), getVertex(lineFour.p2(), O));
	}

	else
	{ }
}

QPointF MyGraphicsRefrect::getVertex(QPointF a, double O)
{
	double radian = O / 180 * PI;
	
	return QPointF((a.x() - centerPoint.x())*cosf(radian) - (a.y() - centerPoint.y())*sinf(radian) + centerPoint.x(),
		(a.x() - centerPoint.x())*sinf(radian) + (a.y() - centerPoint.y())*cosf(radian) + centerPoint.y());
}
