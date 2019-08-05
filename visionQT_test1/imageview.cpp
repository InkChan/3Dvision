#include "imageview.h"

ImageView::ImageView(QGraphicsScene *scene, QWidget *parent)
	: QGraphicsView(scene,parent)
{
	this->setMouseTracking(true);
	this->setGeometry(QRect(400, 140, parent->width() - 500, parent->height() - 200));

	this->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
	this->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

	this->setStyleSheet(QLatin1String("QGraphicsView{\n"
		"background-color:rgb(150,150,150);\n"
		"}"));  
	this->setSceneRect(this->rect());
}

ImageView::ImageView(int left, QWidget *parent)
	: QGraphicsView(parent)
{
	this->setMouseTracking(true);
	this->setGeometry(QRect(left, 140, parent->width() - left - 100, parent->height() - 200));

	this->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
	this->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

	this->setStyleSheet(QLatin1String("QGraphicsView{\n"
		"background-color:rgb(150,150,150);\n"
		"}"));
	this->setSceneRect(this->rect());
}

ImageView::~ImageView()
{

}

void ImageView::mousePressEvent(QMouseEvent *event)
{
	if (event->button() == Qt::LeftButton)
	{
		mousePress(mapToScene(event->pos()));
		return;
	}
	event->ignore();
	
}

void ImageView::mouseMoveEvent(QMouseEvent *event)
{
	mouseMove(mapToScene(event->pos()));
}

void ImageView::mouseReleaseEvent(QMouseEvent *event)
{
	if (event->button() == Qt::LeftButton)
	{
		mouseRelease(mapToScene(event->pos()));
		event->accept();
		return;
	}
	event->ignore();
}

QPointF ImageView::getScenePos(QPoint point)
{
	return mapToScene(point);
}
