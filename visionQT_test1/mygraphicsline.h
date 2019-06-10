#ifndef MYGRAPHICSLINE_H
#define MYGRAPHICSLINE_H

#include <mygraphicsitem.h>

class MyGraphicsLine:public MyGraphicsItem
{
public:
	MyGraphicsLine(QPointF _p);
	~MyGraphicsLine();
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
	QPointF startPoint,endPoint,centerPoint;
	double length, border;
};

#endif // MYGRAPHICSLINE_H
