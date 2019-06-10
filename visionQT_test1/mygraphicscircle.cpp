#include "mygraphicscircle.h"

MyGraphicsCircle::MyGraphicsCircle(QPointF _p)
{
	this->setPos(_p);
	rect = QRectF(QPointF(-20, -20), QPointF(20, 20));
	centerPoint = QPointF(0, 0);
}

MyGraphicsCircle::~MyGraphicsCircle()
{

}

void MyGraphicsCircle::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
	painter->setPen(QPen(QColor(100, 170, 255), 2));
	painter->drawEllipse(rect);

	if (showMove == true)
	{
		painter->setPen(QPen(QColor(100, 200, 255), 4));
		painter->drawPoint(centerPoint);
	}

	if (showZoom == true)
	{
		painter->setPen(QPen(QColor(100, 200, 255), 4));
		painter->drawPoint(QPointF(rect.bottomRight().x(), centerPoint.y()));
		painter->setPen(QPen(QColor(100, 200, 255), 2));
		painter->drawLine(QLineF(centerPoint, QPointF(rect.bottomRight().x(), centerPoint.y())));
	}
}

QRectF MyGraphicsCircle::boundingRect() const
{
	return QRectF(0, 0, 100, 100);
}

int MyGraphicsCircle::type() const
{
	return 65536 + 5;
}

void MyGraphicsCircle::checkMove(QPointF mousePos)
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

void MyGraphicsCircle::checkZoom(QPointF mousePos)
{
	if ((pow(mousePos.x() - (this->pos().x() + rect.bottomRight().x()), 2) +
		pow(mousePos.y() - (this->pos().y() + centerPoint.y()), 2)) <= 100)
	{
		showZoom = true;
	}
	else
	{
		showZoom = false;
	}
}

//返回当前是否能move
bool MyGraphicsCircle::Movable()
{
	return canMove;
}

void MyGraphicsCircle::setMovable(bool status)
{
	canMove = status;
}

//返回当前是否能zoom
bool MyGraphicsCircle::Zoomable()
{
	return canZoom;
}

void MyGraphicsCircle::setZoomable(bool status)
{
	canZoom = status;
}

//设置放大缩小
void MyGraphicsCircle::setZoom(QPointF s, QPointF e)
{
	QPointF pos = QPointF(e.x() - s.x(), e.y() - s.y());
	rect.setBottomRight(QPointF(rect.bottomRight().x() + pos.x(),rect.bottomRight().y()+pos.x()));
	rect.setTopLeft(QPointF(rect.topLeft().x() - pos.x(),rect.topLeft().y()-pos.x()));

	centerPoint.setX((rect.bottomRight().x() + rect.topLeft().x()) / 2);
	centerPoint.setY((rect.bottomRight().y() + rect.topLeft().y()) / 2);
}
