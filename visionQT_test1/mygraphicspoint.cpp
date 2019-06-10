#include "mygraphicspoint.h"

MyGraphicsPoint::MyGraphicsPoint(QPointF _p)
{
	this->setPos(_p);
	centerPoint = QPointF(0, 0);
	setFlag(ItemIsMovable);
	canMove = false;
	showMove = false;
}

MyGraphicsPoint::~MyGraphicsPoint()
{

}

QRectF MyGraphicsPoint::boundingRect() const
{
	return QRectF(0, 0, 100, 100);
}

void MyGraphicsPoint::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
	painter->setPen(QPen(QColor(100,170,255),2));
	painter->drawLine(QPointF(centerPoint.x() - 10, centerPoint.y()), 
		QPointF(centerPoint.x() + 10, centerPoint.y()));
	painter->drawLine(QPointF(centerPoint.x(), centerPoint.y() - 10), 
		QPointF(centerPoint.x(), centerPoint.y() + 10));

	if (showMove == true)
	{
		painter->setPen(QPen(QColor(100, 200, 255),2));
		painter->drawRect(QRectF(QPointF(centerPoint.x() - 7, centerPoint.y() - 7),
			QPointF(centerPoint.x() + 7, centerPoint.y() + 7)));
	}
}

void MyGraphicsPoint::checkMove(QPointF mousePos)
{
	if ((pow(mousePos.x() - this->pos().x(), 2) + pow(mousePos.y() - this->pos().y(), 2)) <= 100)
	{
		showMove = true;
	}
	else
	{
		showMove = false;
	}
}

bool MyGraphicsPoint::Movable()
{
	return canMove;
}

void MyGraphicsPoint::setMovable(bool status)
{
	canMove = status;
}

int MyGraphicsPoint::type() const
{
	return 65536 + 1;
}
