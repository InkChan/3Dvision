#ifndef MYGRAPHICSCIRCLE_H
#define MYGRAPHICSCIRCLE_H
#include <qgraphicsitem.h>
#include "mygraphicsitem.h"


class MyGraphicsCircle:public MyGraphicsItem
{
public:
	MyGraphicsCircle(QPointF _p);
	~MyGraphicsCircle();
	QRectF boundingRect() const;
	int type() const;
	void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
	/*bool canMove, showMove, canZoom, showZoom;*/

	void checkMove(QPointF);
	void checkZoom(QPointF);
	bool Movable();
	void setMovable(bool);
	bool Zoomable();
	void setZoomable(bool);
	void setZoom(QPointF,QPointF);

private:
	QPointF centerPoint;
	QRectF rect;
};

#endif // MYGRAPHICSCIRCLE_H
