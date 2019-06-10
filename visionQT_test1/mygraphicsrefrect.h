#ifndef MYGRAPHICSREFRECT_H
#define MYGRAPHICSREFRECT_H

#include <qgraphicsitem.h>
#include <qpainter.h>
#include <qdebug.h>
#include "mygraphicsitem.h"
#define PI 3.14159265358
class MyGraphicsRefrect:public MyGraphicsItem
{
public:
	MyGraphicsRefrect(QPointF _p);
	~MyGraphicsRefrect();
	QRectF boundingRect() const;
	int type() const;
	void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

	void checkMove(QPointF);
	void checkZoom(QPointF);
	bool Movable();
	void setMovable(bool);
	bool Zoomable();
	void setZoomable(bool);
	void setZoom(QPointF, QPointF);

private:
	QPointF getVertex(QPointF Origin, double O);
	//QLineF getLine(QPointF p1, QPointF p2, QPointF q1, QPointF q2, QPointF m1, QPointF m2);
private:
	QPointF centerPoint;
	QPolygonF polygon,zoomPolygon,centePolygon;
	double width, height, angle, border,resizeangle,sx,sy;
	QPointF rotateCenter;
	QLineF lineOne, lineTwo, lineThree, lineFour;
	bool topLeftZoom, topRightZoom, bottomLeftZoom, bottomRightZoom,rotateFlag;
	QTransform t;
};

#endif // MYGRAPHICSREFRECT_H
