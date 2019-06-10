#ifndef QMAINTABWIDGET_H
#define QMAINTABWIDGET_H

#include <QTabWidget>
#include <qcustomplot.h>
#include "openglwindow.h"

class QMainTabWidget : public QTabWidget
{
	Q_OBJECT

public:
	QMainTabWidget(QWidget *parent);
	void resizeEvent(QResizeEvent *);
	~QMainTabWidget();

private slots:
	void setCurrentGlWidget();
	void rotateOneStep();

private:
	enum { NumRows = 2, NumColumns = 3 };

	//Ö÷´°Ìå
	QWidget *pointcloudPlot;
	OpenGLWindow *glWidgets[NumRows][NumColumns];
	OpenGLWindow *currentGlWidget;
	QCustomPlot *coordinateSystem;
};

#endif // QMAINTABWIDGET_H
