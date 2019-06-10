#ifndef FLOWLINE_H
#define FLOWLINE_H

#include <QObject>
#include <qvector.h>
#include <qpainter.h>
#include <mylineedit.h>

class flowLine : public QObject
{
	Q_OBJECT

public:
	flowLine(QObject *parent);
	QVector<QPoint> getLinePoints();

	~flowLine();

	void generateLine(QList<MyLineEdit*>);
	void childMoveLine(QPoint currentPoint);
	void fatherMoveLine(QPoint currentPoint);

	bool has_child = false;

private:
	QVector<QPoint> linePoints;
	
	int gridH = 30, girdW = 130, gapH = 20, gapW = 10;
};

#endif // FLOWLINE_H
