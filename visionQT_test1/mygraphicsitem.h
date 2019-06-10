#ifndef MYGRAPHICSITEM_H
#define MYGRAPHICSITEM_H
#include <qgraphicsitem.h>
#include <qpainter.h>

class MyGraphicsItem:public QGraphicsItem
{
public:
	MyGraphicsItem();
	virtual ~MyGraphicsItem();
	QRectF boundingRect() const;
	virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, 
		QWidget *widget);
	bool canMove, showMove, canZoom, showZoom;

	virtual void checkMove(QPointF);
	virtual void checkZoom(QPointF);
	virtual bool Movable();
	virtual void setMovable(bool);
	virtual bool Zoomable();
	virtual void setZoomable(bool);
	virtual void setZoom(QPointF,QPointF);
	virtual int type()const;

private:
	
};

#endif // MYGRAPHICSITEM_H
