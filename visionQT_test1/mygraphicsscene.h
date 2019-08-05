#ifndef MYGRAPHICSSCENE_H
#define MYGRAPHICSSCENE_H

#include <QGraphicsScene>
#include <qevent.h>
#include <qgraphicssceneevent.h>
#include <qgraphicsitem.h>
#include <qpen.h>
#include <qpainter.h>
#include <qgraphicssceneevent.h>
#include <qgraphicsview.h>
#include <qobject.h>
#include "mygraphicspoint.h"
#include "mygraphicsrect.h"
#include "mygraphicsline.h"
#include "mygraphicscircle.h"
#include "mygraphicsrefrect.h"

class MyGraphicsScene : public QGraphicsScene
{
	Q_OBJECT

public:
	enum Mode{ InsertPoint, InsertLine, InsertRect, InsertRefrect, InsertCircle, None };
	MyGraphicsScene(QImage _img, double, QObject *parent);
	~MyGraphicsScene();
	void setImage(QImage _img);
	Mode myMode;						//插入类型

/*protected:
	void mousePressEvent(QGraphicsSceneMouseEvent *event);
	void mouseMoveEvent(QGraphicsSceneMouseEvent *event);
	void mouseReleaseEvent(QGraphicsSceneMouseEvent *event)*/;


	public slots:
	void setMode(Mode mode);
	void drawItems(QPointF scenePos);
	void zoomIn();
	void zoomOut();
	void fitSize();
	void MymousePressEvent(QPointF pos);
	void MymouseMoveEvent(QPointF pos);
	void MymouseReleaseEvent(QPointF pos);

private:
	bool _pan;
	int _panStartX, _panStartY;
	QVector<MyGraphicsItem*> graphicsItems;
	double fitFactor;					//图片适应比率
	double scaleFactor;					//图片显示比率
	double zoomInFactor;				//图片放大比率
	double zoomOutFactor;				//图片缩小比率

};

#endif // MYGRAPHICSSCENE_H
