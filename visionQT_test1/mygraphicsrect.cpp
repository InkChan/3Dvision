#include "mygraphicsrect.h"

MyGraphicsRect::MyGraphicsRect(QPointF _p)
{
	this->setPos(_p);
	centerPoint = QPointF(0, 0);
	canMove = false;
	showMove = false;
	canZoom = false;
	showZoom = false;
	width = 50;
	height = 50;
	border = 6;

	rect = QRectF(QPointF(-width / 2, -height / 2), QPointF(width / 2, height / 2));
}

MyGraphicsRect::~MyGraphicsRect()
{

}

QRectF MyGraphicsRect::boundingRect() const
{
	return QRectF(0, 0, 100, 100);
}

int MyGraphicsRect::type() const
{
	return 65536 + 3;
}

void MyGraphicsRect::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
	painter->setPen(QPen(QColor(100, 170, 255), 2));

	painter->drawRect(rect);

	if (showMove == true)
	{
		painter->setPen(QPen(QColor(100, 200, 255), 2));

		painter->drawRect(QRectF(QPointF(rect.center().x() - 7, rect.center().y() - 7),
			QPointF(rect.center().x() + 7, rect.center().y() + 7)));

		painter->drawLine(QPointF(rect.center().x() - 5, rect.center().y()),
			QPointF(rect.center().x() + 5, rect.center().y()));
		painter->drawLine(QPointF(rect.center().x(), rect.center().y() - 5),
			QPointF(rect.center().x(), rect.center().y() + 5));
	}

	if (showZoom == true)
	{
		painter->setPen(QPen(QColor(100, 200, 255), 2));

		painter->drawRect(QRectF(QPointF(rect.topLeft().x() - border, rect.topLeft().y()-border), 
			QPointF(rect.bottomRight().x()+border,rect.bottomRight().y()+border)));

		painter->drawLine(QPointF(rect.topLeft().x(), rect.topLeft().y() - border),
			QPointF(QPointF(rect.topLeft().x(), rect.bottomRight().y() + border)));
		painter->drawLine(QPointF(rect.bottomRight().x(), rect.topLeft().y() - border),
			QPointF(QPointF(rect.bottomRight().x(), rect.bottomRight().y() + border)));
		painter->drawLine(QPointF(rect.topLeft().x() - border, rect.topLeft().y()),
			QPointF(rect.bottomRight().x() + border, rect.topLeft().y()));
		painter->drawLine(QPointF(rect.topLeft().x() - border, rect.bottomRight().y()),
			QPointF(rect.bottomRight().x() + border, rect.bottomRight().y()));
	}
}

void MyGraphicsRect::checkMove(QPointF mousePos)
{
	QPointF tem = this->pos();
	if ((pow(mousePos.x() - (this->pos().x() + rect.center().x()), 2) +
		pow(mousePos.y() - (this->pos().y() + rect.center().y()), 2)) <= 100)
	{
		showMove = true;
		showZoom = false;
	}
	else
	{
		showMove = false;
	}
}

void MyGraphicsRect::checkZoom(QPointF mousePos)
{
	if ((mousePos.x() - (this->pos().x() + rect.bottomRight().x())) <= 5 &&
		(mousePos.x() - (this->pos().x() + rect.bottomRight().x())) >= 0 &&
		(mousePos.y() - (this->pos().y() + rect.bottomRight().y())) <= 5 &&
		(mousePos.y() - (this->pos().y() + rect.bottomRight().y())) >= 0)
	{  
		showZoom = true;
		showMove = false;
	}
	else
	{
		showZoom = false;
	}
}

//返回当前是否能move
bool MyGraphicsRect::Movable()
{
	return canMove;
}

void MyGraphicsRect::setMovable(bool status)
{
	canMove = status;
}

//返回当前是否能zoom
bool MyGraphicsRect::Zoomable()
{
	return canZoom;
}

void MyGraphicsRect::setZoomable(bool status)
{
	canZoom = status;
}

//设置放大缩小
void MyGraphicsRect::setZoom(QPointF s, QPointF e)
{
	QPointF pos = QPointF(e.x() - s.x(), e.y() - s.y());
	width += pos.x();
	height += pos.y();

	QPointF bottomRight(rect.bottomRight().x() + pos.x(), rect.bottomRight().y() + pos.y());

	//保证矩形
	if (bottomRight.x() - rect.topLeft().x() > 0 && bottomRight.y() - rect.topLeft().y() > 0)
	{
		rect.setBottomRight(bottomRight);
	}
	
}