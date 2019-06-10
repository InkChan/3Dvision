#ifndef MYGRAPHICSPOINT_H
#define MYGRAPHICSPOINT_H
#include <qpainter.h>
#include <qgraphicsitem.h>
#include <qobject.h>
#include "mygraphicsitem.h"

class MyGraphicsPoint :public MyGraphicsItem
{
public:
	MyGraphicsPoint(QPointF);
	~MyGraphicsPoint();
	QRectF boundingRect() const;
	int type() const;
	void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
	/*bool canMove,showMove;*/
	void checkMove(QPointF);
	bool Movable();
	void setMovable(bool);

private:
	QPointF centerPoint;
	double border;
};

#endif // MYGRAPHICSPOINT_H
