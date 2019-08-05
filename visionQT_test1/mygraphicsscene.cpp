#include "mygraphicsscene.h"


MyGraphicsScene::MyGraphicsScene(QImage _img, double factor, QObject *parent)
	: QGraphicsScene(parent),
	_pan (false),
	scaleFactor(1.0),
	zoomInFactor(1.05),
	zoomOutFactor(1 / 1.05)
{
	fitFactor = factor;
	setImage(_img);

	
	QRectF temp = this->sceneRect();
	addRect(this->sceneRect(), QPen(QColor(100,150,255),3));
	myMode = Mode::None;

	fitSize();
}

MyGraphicsScene::~MyGraphicsScene()
{

}

void MyGraphicsScene::setImage(QImage _img)
{
	if (!_img.isNull())
	{
		int i = _img.depth();
		_img.convertToFormat(QImage::Format::Format_Mono);
		this->addPixmap(QPixmap::fromImage(_img));
	}
}

void MyGraphicsScene::drawItems(QPointF scenePos)
{
	switch (myMode)
	{
	case InsertPoint:
	{
		MyGraphicsPoint *pointItem = new MyGraphicsPoint(scenePos);
		graphicsItems.push_back(pointItem);

		//connect(test, SIGNAL(clicked()), test, SLOT(showMenu()));
		addItem(graphicsItems.last());
		update(QRect(0, 0, this->width(), this->height()));

		break;
	}
	case InsertRect:
	{
		MyGraphicsRect *rectItem = new MyGraphicsRect(scenePos);
		graphicsItems.push_back(rectItem);

		//connect(test, SIGNAL(clicked()), test, SLOT(showMenu()));
		addItem(graphicsItems.last());
		update(QRect(0, 0, this->width(), this->height()));

		break;
	}
	case InsertLine:
	{
		MyGraphicsLine *lineItem = new MyGraphicsLine(scenePos);
		graphicsItems.push_back(lineItem);

		addItem(graphicsItems.last());
		update(QRect(0, 0, this->width(), this->height()));
		break;
	}
	case InsertCircle:
	{
		MyGraphicsCircle *circleItem = new MyGraphicsCircle(scenePos);
		graphicsItems.push_back(circleItem);

		addItem(graphicsItems.last());
		update(QRect(0, 0, this->width(), this->height()));
		break;
	}
	case InsertRefrect:
	{
		MyGraphicsRefrect *refrectItem = new MyGraphicsRefrect(scenePos);
		graphicsItems.push_back(refrectItem);

		addItem(graphicsItems.last());
		update(QRect(0, 0, this->width(), this->height()));
		break;
	}
	default:
		break;
	}
}

void MyGraphicsScene::setMode(Mode mode)
{
	myMode = mode;
}


void MyGraphicsScene::MymousePressEvent(QPointF pos)
{
	//QList<QGraphicsView*> myvview = this->views();	
	//myvview[0]->setScene(this);
	////myvview[0]->updateSceneRect(this->sceneRect());
	//pos = myvview[0]->mapToScene()

	//记录当前坐标
	_panStartX = pos.x();
	_panStartY = pos.y();

	//坐标落在图片上才可移动
	if (_panStartX >= 0 && _panStartY >= 0)
	{
		_pan = true;
	}

	//判断鼠标点击时，图形是否是可以移动的状态
	for each (MyGraphicsItem *var in graphicsItems)
	{
		if (var->showMove == true)
		{
			//如果showMove=true,设置图形为可移动的（此时场景不可移动）
			var->setMovable(true);
			_pan = false;
			return;
		}

		if (var->showZoom == true)
		{
			var->setZoomable(true);
			_pan = false;
			return;
		}
	}

	//对图形操作的状态
	if (myMode != Mode::None)
	{
		//如果图形不可移动，理解为添加图形
		drawItems(pos);
	}
}

void MyGraphicsScene::MymouseMoveEvent(QPointF pos)
{	
	//平移场景元素；
	if (_pan)
	{
		int k = (pos.x() - _panStartX);
		int t = (pos.y() - _panStartY);
		for each (QGraphicsItem *var in this->items())
		{
			var->setPos(var->scenePos().x() + k, var->scenePos().y() + t);	
		}
		/*for each (MyGraphicsPoint *var in graphicsItems)
		{			
			var->setLastPos(QPointF(k, t));
		}*/
		_panStartX = pos.x();
		_panStartY = pos.y();
		return;
	}


	for each (MyGraphicsItem *var in graphicsItems)
	{
		//检查鼠标当前位置是否可拖动图形移动
		var->checkMove(pos);

		if (var->Movable() == true)
		{
			int k = (pos.x() - _panStartX);
			int t = (pos.y() - _panStartY);
			var->setPos(var->scenePos().x() + k, var->scenePos().y() + t);
////			var->setLastPos(QPointF(k, t));
			_panStartX = pos.x();
			_panStartY = pos.y();
			break;
		}

		var->checkZoom(pos);
		if (var->Zoomable() == true)
		{
			var->setZoom(QPointF(_panStartX,_panStartY),pos);
			_panStartX = pos.x();
			_panStartY = pos.y();
			break;
		}

	}

	update(QRect(0, 0, this->width(), this->height()));
}

void MyGraphicsScene::MymouseReleaseEvent(QPointF pos)
{
	_pan = false;

	for each (MyGraphicsRect *var in graphicsItems)
	{
		var->setMovable(false);
		var->setZoomable(false);
	}

	myMode = Mode::None;
}


void MyGraphicsScene::zoomIn()
{
	scaleFactor +=0.05;
	for each (QGraphicsItem *var in this->items())
	{
		if (var->type() < 65536)
		{
			var->setScale(scaleFactor);
		}
	}
}

void MyGraphicsScene::zoomOut()
{
	scaleFactor -= 0.05;
	for each (QGraphicsItem *var in this->items())
	{
		int k = var->type();
		if (var->type() < 65536)
		{
			var->setScale(scaleFactor);
		}		
	}
}

void MyGraphicsScene::fitSize()
{
	scaleFactor = fitFactor;
	for each (QGraphicsItem *var in this->items())
	{
		if (var->type() < 65536)
		{
			var->setScale(scaleFactor);
		}
	}
}