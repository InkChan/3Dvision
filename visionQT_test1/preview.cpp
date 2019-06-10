#include "preview.h"

Preview::Preview(qint16 sizew, qint16 sizeh, QWidget *parent)
	: QWidget(parent), mW(sizew), mH(sizeh)
{
	highlightedRect = QRect();
	this->setAcceptDrops(true);
	this->setMinimumHeight(300);
	pieceButton = QList<MyLineEdit*>();
	connect(this, SIGNAL(triggerLine()), this, SLOT(AddLine()));
	connect(this, SIGNAL(dragLineSignal(int)), this, SLOT(dragLineSlot(int)));
}

Preview::~Preview()
{

}

void Preview::dragEnterEvent(QDragEnterEvent *event)
{
	if (event->mimeData()->hasFormat("moduletree"))// && findPiece(targetSquare2(event->pos())) == -1)
	{
		QString tempdata = event->mimeData()->text();
		event->accept();
	}
	else if (event->mimeData()->hasFormat("tool"))// && findPiece(targetSquare2(event->pos())) == -1)
	{
		QString tempdata = event->mimeData()->text();
		event->accept();
	}
	else
		event->ignore();
}

void Preview::dragMoveEvent(QDragMoveEvent *event)
{
	QRect updateRect = highlightedRect.united(targetSquare(event->pos()));

	if (event->mimeData()->hasFormat("moduletree")
		&& findPiece(targetSquare2(event->pos())) == -1) {

		highlightedRect = targetSquare(event->pos());
		event->setDropAction(Qt::MoveAction);
		event->accept();
	}
	else if (event->mimeData()->hasFormat("tool") && findPiece(targetSquare2(event->pos())) == -1)
	{
		highlightedRect = targetSquare(event->pos());
		event->setDropAction(Qt::MoveAction);
		event->accept();
	}
	else {
		highlightedRect = QRect();
		event->ignore();
	}
	//update(highlightedRect);
	update();
}

void Preview::paintEvent(QPaintEvent *event)
{
	QPainter painter;
	painter.begin(this);
	painter.fillRect(event->rect(), Qt::white);

	if (highlightedRect.isValid()) {
		//painter.setBrush(QColor(200,200,200));
		QPen mpen = painter.pen();
		mpen.setColor(QColor(0, 0, 200));
		mpen.setStyle(Qt::DotLine);
		mpen.setWidth(2);
		painter.setPen(mpen);
		//painter.setPen(Qt::DotLine);
		painter.drawRect(highlightedRect.adjusted(0, 0, -1, -1));
	}

	for (int i = 0; i < customControlLine.size(); ++i)
	{
		painter.drawLines(customControlLine[i]->getLinePoints());
	}
	

	painter.end();

}

void Preview::dropEvent(QDropEvent *event)
{
	if (event->mimeData()->hasFormat("moduletree") && findPiece(targetSquare2(event->pos())) == -1)
	{
		QString tempdata = event->mimeData()->text();
		QStringList myLocationLits = tempdata.split(':');
		qint16 mypa = myLocationLits[0].toInt();
		qint16 mych = myLocationLits[1].toInt();
		MyLineEdit *bt_1 = new MyLineEdit(this);
		bt_1->setTool(myLocationLits[2]);
		bt_1->setText(myLocationLits[2]);
		bt_1->setGeometry(highlightedRect);
		bt_1->centerPos = highlightedRect.center();
		
		
		pieceRects.push_back(targetSquare2(event->pos()));
		bt_1->show();
		connect(bt_1, SIGNAL(s_deletthis(MyLineEdit*)), this, SLOT(deleonebt(MyLineEdit *)));
		pieceButton.push_back(bt_1);	

		//触发添加线的信号
		triggerLine();
		event->accept();
	}
	else if (event->mimeData()->hasFormat("tool") && findPiece(targetSquare2(event->pos())) == -1)
	{
		for each (MyLineEdit* var in this->pieceButton)
		{
			if (var->Ischoose)
			{
				for (size_t i = 0; i < pieceRects.count(); i++)
				{
					if (pieceRects[i] == targetSquare2(QPoint(var->geometry().x(), var->geometry().y())))
					{
						pieceRects[i] = targetSquare2(event->pos());
						var->centerPos = highlightedRect.center();
						//拖拽信号
						dragLineSignal(i);
						break;
					}
				}
				
				var->setGeometry(highlightedRect);
				var->Ischoose = false;
			}
		}
		event->accept();
		//event->mimeData()->
	}
	else if (event->mimeData()->hasFormat("tool") && findPiece(targetSquare2(event->pos())) != -1)
	{
		for each (MyLineEdit* var in this->pieceButton)
		{
			var->Ischoose = false;
		}
		event->accept();
		//event->mimeData()->
	}
	else
		event->ignore();

	highlightedRect = QRect();
	//update(targetSquare(event->pos()));
	update();
}

void Preview::AddLine()
{
	flowLine *line = new flowLine(this);
	line->generateLine(pieceButton);
	customControlLine.push_back(line);
}

void Preview::dragLineSlot(int index)
{
	MyLineEdit *lineItem = pieceButton[index];
	flowLine *line = customControlLine.at(index);
	line->childMoveLine(lineItem->centerPos);

	if (lineItem->hasChild == true)
	{
		for (int k = 0; k < lineItem->childIndex.size(); ++k)
		{
			flowLine *templine = customControlLine.at(lineItem->childIndex[k]);
			templine->fatherMoveLine(lineItem->centerPos);
		}
	}

	connect(lineItem, SIGNAL(lineItem->destroyed(QObject*)), this, SLOT(test()));
}

//拖拽离开
void Preview::dragLeaveEvent(QDragLeaveEvent *event)
{
	QRect updateRect = highlightedRect;
	highlightedRect = QRect();
	update(updateRect);
	//update();
	event->accept();
}

//查找输入矩形与矩形库是否重合
int Preview::findPiece(const QRect &pieceRect) const
{
	for (int i = 0; i < pieceRects.size(); ++i) {
		if (pieceRect == pieceRects[i])
			return i;
	}
	return -1;
}

//以一点为中心的一片尺寸的矩形
const QRect Preview::targetSquare(const QPoint &position) const
{
	int dw = 10;
	int dh = 20;
	return QRect(position.x() / (mW + dw) * (mW + dw), position.y() / (mH+dh)* (mH+dh), mW, mH);
}

//以一点为中心的一片外尺寸的矩形
const QRect Preview::targetSquare2(const QPoint &position) const
{
	int dw = 10;
	int dh = 20;
	return QRect(position.x() / (mW + dw) * (mW + dw), position.y() / (mH + dh)* (mH + dh), mW + dw, mH + dh);
}

void Preview::mouseDoubleClickEvent(QMouseEvent *)
{
	litcontro = new LitControl();
	litcontro->show();
}

void Preview::deleonebt(MyLineEdit * bt)
{
	for each (MyLineEdit* var in this->pieceButton)
	{
		if (var->Ischoose)
		{
			for (size_t i = 0; i < pieceRects.count(); i++)
			{
				if (pieceRects[i] == targetSquare2(QPoint(var->geometry().x(), var->geometry().y())))
				{
					pieceRects.removeAt(i);
					customControlLine.removeAt(i);
					break;
				}
			}
			pieceButton.removeOne(var);		
		}
	}
	update();
}

void Preview::test(QObject* K)
{
	int l = 0;
}