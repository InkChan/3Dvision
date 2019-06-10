#include "mygraphicsline.h"

MyGraphicsLine::MyGraphicsLine(QPointF _p)
{
	this->setPos(_p);
	startPoint = QPointF(0, -20);
	centerPoint = QPointF(0, 0);
	endPoint = QPointF(0, 20);
	setFlag(ItemIsMovable);
	canMove = false;
	showMove = false;
	canZoom = false;
	showZoom = false;

	length = 40;
	border = 6;
}

MyGraphicsLine::~MyGraphicsLine()
{

}

QRectF MyGraphicsLine::boundingRect() const
{
	return QRectF(0, 0, 100, 100);
}

int MyGraphicsLine::type() const
{
	return 65536 + 2;
}

void MyGraphicsLine::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
	painter->setPen(QPen(QColor(100, 170, 255), 2));
	painter->drawLine(QLineF(startPoint,endPoint));

	//painter->setPen(QPen(QColor(100, 170, 255), 5));
	

	if (showMove == true)
	{
		painter->setPen(QPen(QColor(100, 200, 255), 2));
		painter->drawEllipse(QRectF(QPointF(centerPoint.x() - 7, centerPoint.y() - 7),
			QPointF(centerPoint.x() + 7, centerPoint.y() + 7)));
		
		painter->setPen(QPen(QColor(100, 200, 255), 4));
		painter->drawPoint(centerPoint);
	}

	if (showZoom == true)
	{
		painter->setPen(QPen(QColor(100, 200, 255), 2));
		painter->drawRect(QRectF(QPointF(endPoint.x() - 7, endPoint.y() - 7),
			QPointF(endPoint.x() + 7, endPoint.y() + 7)));

		painter->setPen(QPen(QColor(100, 200, 255), 4));
		painter->drawPoint(endPoint);
	}
}

void MyGraphicsLine::checkMove(QPointF mousePos)
{
	QPointF tem = this->pos();
	if ((pow(mousePos.x() - (this->pos().x() + centerPoint.x()), 2) +
		pow(mousePos.y() - (this->pos().y() + centerPoint.y()), 2)) <= 100)
	{
		showMove = true;
		showZoom = false;
	}
	else
	{
		showMove = false;
	}
}

void MyGraphicsLine::checkZoom(QPointF mousePos)
{
	if ((pow(mousePos.x() - (this->pos().x() + endPoint.x()), 2) +
		pow(mousePos.y() - (this->pos().y() + endPoint.y()), 2)) <= 100)
	{
		showZoom = true;
	}
	else
	{
		showZoom = false;
	}
}

//返回当前是否能move
bool MyGraphicsLine::Movable()
{
	return canMove;
}

void MyGraphicsLine::setMovable(bool status)
{
	canMove = status;
}

//返回当前是否能zoom
bool MyGraphicsLine::Zoomable()
{
	return canZoom;
}

void MyGraphicsLine::setZoomable(bool status)
{
	canZoom = status;
}

//设置放大缩小
void MyGraphicsLine::setZoom(QPointF s, QPointF e)
{
	QPointF pos = QPointF(e.x() - s.x(), e.y() - s.y());
	endPoint.setX(endPoint.x() + pos.x());
	endPoint.setY(endPoint.y() + pos.y());

	centerPoint.setX((endPoint.x() + startPoint.x()) / 2);
	centerPoint.setY((endPoint.y() + startPoint.y()) / 2);
}

