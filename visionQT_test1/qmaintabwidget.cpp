#include "qmaintabwidget.h"

QMainTabWidget::QMainTabWidget(QWidget *parent)
	: QTabWidget(parent)
{
	this->setMaximumSize(1920, 1080);
	this->setAutoFillBackground(true);

	QWidget *curvePlot;
	curvePlot = new QWidget(this);
	curvePlot->setMaximumSize(1920, 1080);

	//create coordinary system for curvePlot
	coordinateSystem = new QCustomPlot(curvePlot);

	coordinateSystem->addGraph();
	coordinateSystem->xAxis->setLabel("x");
	coordinateSystem->xAxis->setRange(-10, 10);
	coordinateSystem->xAxis->grid()->setSubGridVisible(true);
	coordinateSystem->xAxis->setTickLabelSide(QCPAxis::lsInside);
	coordinateSystem->xAxis->setUpperEnding(QCPLineEnding::esSpikeArrow);

	coordinateSystem->yAxis->setLabel("z");
	coordinateSystem->yAxis->setRange(-1, 1);
	coordinateSystem->yAxis->grid()->setSubGridVisible(true);
	coordinateSystem->yAxis->setTickLabelSide(QCPAxis::lsInside);
	coordinateSystem->yAxis->setUpperEnding(QCPLineEnding::esSpikeArrow);

	coordinateSystem->replot();
	coordinateSystem->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom | QCP::iSelectPlottables);
	
	this->addTab(coordinateSystem, tr("Global Coordinate System"));

	//openGl window
	pointcloudPlot = new QWidget(this);
	this->addTab(pointcloudPlot, tr("3D System"));

	QGridLayout *mainLayout = new QGridLayout(pointcloudPlot);

	for (int i = 0; i < NumRows; ++i) {
		for (int j = 0; j < NumColumns; ++j) {
			QColor clearColor;
			clearColor.setHsv(((i * NumColumns) + j) * 255
				/ (NumRows * NumColumns - 1),
				255, 63);

			glWidgets[i][j] = new OpenGLWindow(0);
			glWidgets[i][j]->setClearColor(clearColor);
			glWidgets[i][j]->rotateBy(+42 * 16, +42 * 16, -21 * 16);
			mainLayout->addWidget(glWidgets[i][j], i, j);

			connect(glWidgets[i][j], SIGNAL(clicked()),
				this, SLOT(setCurrentGlWidget()));
		}
	}
	
	currentGlWidget = glWidgets[0][0];

	QTimer *timer = new QTimer(this);
	connect(timer, SIGNAL(timeout()), this, SLOT(rotateOneStep()));
	timer->start(20);

}

void QMainTabWidget::resizeEvent(QResizeEvent *event)
{
	QTabWidget::resizeEvent(event);
	coordinateSystem->setGeometry(0, 2, this->width() - 4,
		this->height() - 22);
	//openGLWindow->setGeometry(0, 2, this->width() - 4,
	//	this->height() - 12);
}

void QMainTabWidget::setCurrentGlWidget()
{
	currentGlWidget = qobject_cast<OpenGLWindow *>(sender());
}

void QMainTabWidget::rotateOneStep()
{
	if (currentGlWidget)
		currentGlWidget->rotateBy(+2 * 16, +2 * 16, -1 * 16);
}

QMainTabWidget::~QMainTabWidget()
{

}
