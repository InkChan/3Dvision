#ifndef CUSTOMWIDGET_H
#define CUSTOMWIDGET_H

#include <QWidget>
#include <qtimer.h>
#include <QtDesigner\qdesignerexportwidget.h>
#include <qpainter.h>
#include <qdatetime.h>

class customWidget : public QWidget
{
	Q_OBJECT

public:
	customWidget(QWidget *parent = 0);
	~customWidget();

protected:
	void paintEvent(QPaintEvent *event);
private:
	
};

#endif // CUSTOMWIDGET_H
