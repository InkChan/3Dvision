#ifndef IMAGEVIEW_H
#define IMAGEVIEW_H

#include <qgraphicsview.h>
#include <qevent.h>
#include <qscrollbar.h>
#include <qgraphicsitem.h>
#include <qstyleoption.h>
#include "mygraphicsscene.h"

class ImageView : public QGraphicsView
{
	Q_OBJECT

public:
	ImageView(QGraphicsScene *scene,QWidget *parent);
	~ImageView();

signals:
	void mousePress(QPointF);
	void mouseMove(QPointF);
	void mouseRelease(QPointF);

protected:
	void mousePressEvent(QMouseEvent *event);
	void mouseMoveEvent(QMouseEvent *event);
	void mouseReleaseEvent(QMouseEvent *event);
};

#endif // IMAGEVIEW_H
