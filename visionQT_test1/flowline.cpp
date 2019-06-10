#include "flowline.h"

flowLine::flowLine(QObject *parent)
	: QObject(parent)
{

}

QVector<QPoint> flowLine::getLinePoints()
{
	return linePoints;
}

void flowLine::generateLine(QList<MyLineEdit*> lineItemList)
{
	linePoints.clear();
	int finalIndex = -1;

	if (lineItemList.size() > 1)
	{
		//x方向最小差值
		int difvalue = 100000000;

		QPoint currentPoint = lineItemList[lineItemList.size() - 1]->centerPos;
		QPoint fatherPoint(0, 0);
		
		for (int i = 0; i < lineItemList.size() - 1; ++i)
		{
			//相差50
			if ((currentPoint.y() - lineItemList[i]->centerPos.y()) == (gridH + gapH))
			{
				int temp = abs(currentPoint.x() - lineItemList[i]->centerPos.x());

				//小于difvalue就计算
				if (temp < difvalue)
				{
					fatherPoint = lineItemList[i]->centerPos;
					finalIndex = i;
					difvalue = temp;
				}
			}
		}

		if (difvalue != 100000000)
		{
			lineItemList[finalIndex]->childIndex.push_back(lineItemList.size() - 1);
			lineItemList[finalIndex]->hasChild = true;
			linePoints.push_back(QPoint(fatherPoint.x(), fatherPoint.y() + gridH / 2));
			linePoints.push_back(QPoint(fatherPoint.x(), fatherPoint.y() + gridH / 2 + gapH / 2));
			linePoints.push_back(QPoint(fatherPoint.x(), fatherPoint.y() + gridH / 2 + gapH / 2));
			linePoints.push_back(QPoint(currentPoint.x(), fatherPoint.y() + gridH / 2 + gapH / 2));
			linePoints.push_back(QPoint(currentPoint.x(), fatherPoint.y() + gridH / 2 + gapH / 2));
			linePoints.push_back(QPoint(currentPoint.x(), currentPoint.y() - gridH / 2));
		}	
	}
}

void flowLine::childMoveLine(QPoint currentPoint)
{
	if (linePoints.size() > 0)
	{
		int fatherPosY = linePoints.at(4).y();

		linePoints.pop_back();
		linePoints.pop_back();
		linePoints.pop_back();

		linePoints.push_back(QPoint(currentPoint.x(), fatherPosY));
		linePoints.push_back(QPoint(currentPoint.x(), fatherPosY));
		linePoints.push_back(QPoint(currentPoint.x(), currentPoint.y() - gridH / 2));
	}

}

void flowLine::fatherMoveLine(QPoint currentPoint)
{
	if (linePoints.size() > 0)
	{
		linePoints.pop_front();
		linePoints.pop_front();
		linePoints.pop_front();

		linePoints.push_front(QPoint(currentPoint.x(), currentPoint.y() + gridH / 2 + gapH / 2));
		linePoints.push_front(QPoint(currentPoint.x(), currentPoint.y() + gridH / 2 + gapH / 2));
		linePoints.push_front(QPoint(currentPoint.x(), currentPoint.y() + gridH / 2));
		
	}
}

flowLine::~flowLine()
{

}
