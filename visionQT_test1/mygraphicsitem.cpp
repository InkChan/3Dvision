#include "mygraphicsitem.h"

MyGraphicsItem::MyGraphicsItem():
canMove(false), 
showMove(false), 
canZoom(false), 
showZoom(false)
{
}

MyGraphicsItem::~MyGraphicsItem()
{}

QRectF MyGraphicsItem::boundingRect() const
{
	return QRectF(0, 0, 0, 0);
}

void MyGraphicsItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{}

void MyGraphicsItem::checkMove(QPointF)
{}

void MyGraphicsItem::checkZoom(QPointF)
{}

bool MyGraphicsItem::Movable()
{
	return false;
}

void MyGraphicsItem::setMovable(bool)
{}

bool MyGraphicsItem::Zoomable()
{
	return false;
}

void MyGraphicsItem::setZoomable(bool)
{}

void MyGraphicsItem::setZoom(QPointF,QPointF)
{}

int MyGraphicsItem::type()const
{
	return 65536;
}