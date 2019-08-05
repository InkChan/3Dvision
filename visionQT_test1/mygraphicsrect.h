#ifndef MYGRAPHICSRECT_H
#define MYGRAPHICSRECT_H
#include <qgraphicsitem.h>
#include <qpainter.h>
#include "mygraphicsitem.h"

class MyGraphicsRect :public MyGraphicsItem
{
public:
	MyGraphicsRect(QPointF _p);
	~MyGraphicsRect();
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
	double width, height, border;
};

#endif // MYGRAPHICSRECT_H
