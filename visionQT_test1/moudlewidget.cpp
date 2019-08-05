#include "moudlewidget.h"

MoudleWidget::MoudleWidget(HImage img, QWidget *parent, int left)
	: QWidget(parent)
{
	WindowIDBuf = -1;
	ModelID = -1;
	setupUi(img,this,left);

	this->setStyleSheet("background-color:rgb(255, 255, 255);");
	this->setWindowModality(Qt::ApplicationModal);
	this->setWindowFlags(Qt::FramelessWindowHint);
	startP = QPointF(100, 100);
}

//MoudleWidget::MoudleWidget(QImage img, QWidget *parent, int left)
//	: QWidget(parent)
//{
//	WindowIDBuf = -1;
//	ModelID = -1;
//	setupUi(img, this, left);
//
//	this->setStyleSheet("background-color:rgb(255, 255, 255);");
//	this->setWindowModality(Qt::ApplicationModal);
//	this->setWindowFlags(Qt::FramelessWindowHint);
//	startP = QPointF(100, 100);
//}

MoudleWidget::~MoudleWidget()
{

}

//void MoudleWidget::setupUi(QImage img, QWidget *moudleWidget, int left)
//{
//	QRect deskRect = QApplication::desktop()->availableGeometry();
//	this->resize(deskRect.width() - 200, deskRect.height() - 200);
//
//	closeButton = new QPushButton(moudleWidget);
//	closeButton->setObjectName(QStringLiteral("closeButton"));
//	closeButton->setGeometry(QRect(this->width() - 50 - 31, 100, 31, 31));
//	closeButton->setFlat(true);
//	closeButton->setIcon(QIcon(":/visionQT_test/Resources/closeButton.png"));
//	closeButton->setStyleSheet(QLatin1String("QPushButton:pressed {\n"
//		"    border-style: inset;\n"
//		"}"));
//	this->connect(closeButton, SIGNAL(clicked()), this, SLOT(close()));
//
//	graphicsView = new ImageView(/*graphicsScene, */left, this);
//	graphicsView->setObjectName(QStringLiteral("graphicsView"));
//
//	double factor = min(double(graphicsView->width()) / double(img.width()),
//		double(graphicsView->height()) / double(img.height()));
//	//传图片参数
//	graphicsScene = new MyGraphicsScene(img, factor, this);
//	graphicsView->setScene(graphicsScene);
//
//
//	this->connect(graphicsView, SIGNAL(mouseMove(QPointF)), graphicsScene, SLOT(MymouseMoveEvent(QPointF)));
//	this->connect(graphicsView, SIGNAL(mousePress(QPointF)), graphicsScene, SLOT(MymousePressEvent(QPointF)));
//	this->connect(graphicsView, SIGNAL(mouseRelease(QPointF)), graphicsScene, SLOT(MymouseReleaseEvent(QPointF)));
//
//	centredImgButton = new QPushButton(moudleWidget);
//	centredImgButton->setObjectName(QStringLiteral("centredImgButton"));
//	centredImgButton->setGeometry(QRect(left - 31, 140, 31, 31));
//	centredImgButton->setFlat(true);
//	centredImgButton->setIcon(QIcon(":/visionQT_test/Resources/adjustButton.png"));
//	centredImgButton->setStyleSheet(QLatin1String("QPushButton:pressed {\n"
//		"    border-style: inset;\n"
//		"}"));
//	this->connect(centredImgButton, SIGNAL(clicked()), graphicsScene, SLOT(fitSize()));
//
//	zoomInButton = new QPushButton(moudleWidget);
//	zoomInButton->setObjectName(QStringLiteral("zoomInButton"));
//	zoomInButton->setGeometry(QRect(left - 31, 140 + 31 + 1, 31, 31));
//	zoomInButton->setFlat(true);
//	zoomInButton->setIcon(QIcon(":/visionQT_test/Resources/zoom-in.png"));
//	zoomInButton->setStyleSheet(QLatin1String("QPushButton:pressed {\n"
//		"    border-style: inset;\n"
//		"}"));
//	this->connect(zoomInButton, SIGNAL(clicked()), graphicsScene, SLOT(zoomIn()));
//
//	zoomOutButton = new QPushButton(moudleWidget);
//	zoomOutButton->setObjectName(QStringLiteral("zoomOutButton"));
//	zoomOutButton->setGeometry(QRect(left - 31, 140 + 31 * 2 + 2, 31, 31));
//	zoomOutButton->setFlat(true);
//	zoomOutButton->setIcon(QIcon(":/visionQT_test/Resources/zoom-out.png"));
//	zoomOutButton->setStyleSheet(QLatin1String("QPushButton:pressed {\n"
//		"    border-style: inset;\n"
//		"}"));
//	this->connect(zoomOutButton, SIGNAL(clicked()), graphicsScene, SLOT(zoomOut()));
//
//	midLine = QLine(QPoint(left - 31, 140 + 31 * 3 + 8), QPoint(left - 31 + 31, 140 + 31 * 3 + 8));
//
//	toolGroup = new QButtonGroup(this);
//	toolGroup->setExclusive(false);
//	this->connect(toolGroup, SIGNAL(buttonClicked(int)),
//		this, SLOT(buttonGroupClicked(int)));
//
//	QPushButton *pointButton = new QPushButton(moudleWidget);
//	pointButton->setObjectName(QStringLiteral("pointButton"));
//	pointButton->setGeometry(QRect(left - 31, 140 + 31 * 3 + 5 * 2, 31, 31));
//	pointButton->setFlat(true);
//	pointButton->setIcon(QIcon(":/visionQT_test/Resources/pointButton.png"));
//	pointButton->setStyleSheet(QLatin1String("QPushButton:pressed {\n"
//		"    border-style: inset;\n"
//		"}"));
//	toolGroup->addButton(pointButton, 0);
//
//	QPushButton *lineButton = new QPushButton(moudleWidget);
//	lineButton->setObjectName(QStringLiteral("lineButton"));
//	lineButton->setGeometry(QRect(left - 31, 140 + 31 * 4 + 5 * 2, 31, 31));
//	lineButton->setFlat(true);
//	lineButton->setIcon(QIcon(":/visionQT_test/Resources/lineButton.png"));
//	lineButton->setStyleSheet(QLatin1String("QPushButton:pressed {\n"
//		"    border-style: inset;\n"
//		"}"));
//	toolGroup->addButton(lineButton, 1);
//
//	QPushButton *rectButton = new QPushButton(moudleWidget);
//	rectButton->setObjectName(QStringLiteral("rectButton"));
//	rectButton->setGeometry(QRect(left - 31, 140 + 31 * 5 + 5 * 2, 31, 31));
//	rectButton->setFlat(true);
//	rectButton->setIcon(QIcon(":/visionQT_test/Resources/rectangleButton.png"));
//	rectButton->setStyleSheet(QLatin1String("QPushButton:pressed {\n"
//		"    border-style: inset;\n"
//		"}"));
//	this->connect(rectButton, SIGNAL(clicked()), graphicsScene, SLOT(setMode()));
//	toolGroup->addButton(rectButton, 2);
//
//	QPushButton *refectButton = new QPushButton(moudleWidget);
//	refectButton->setObjectName(QStringLiteral("rectButton"));
//	refectButton->setGeometry(QRect(left - 31, 140 + 31 * 6 + 5 * 2, 31, 31));
//	refectButton->setFlat(true);
//	refectButton->setIcon(QIcon(":/visionQT_test/Resources/refineRectButton.png"));
//	refectButton->setStyleSheet(QLatin1String("QPushButton:pressed {\n"
//		"    border-style: inset;\n"
//		"}"));
//	this->connect(refectButton, SIGNAL(clicked()), graphicsScene, SLOT(setMode()));
//	toolGroup->addButton(refectButton, 3);
//
//	QPushButton *circleButton = new QPushButton(moudleWidget);
//	circleButton->setObjectName(QStringLiteral("circleButton"));
//	circleButton->setGeometry(QRect(left - 31, 140 + 31 * 7 + 5 * 2, 31, 31));
//	circleButton->setFlat(true);
//	circleButton->setIcon(QIcon(":/visionQT_test/Resources/circleButton.png"));
//	circleButton->setStyleSheet(QLatin1String("QPushButton:pressed {\n"
//		"    border-style: inset;\n"
//		"}"));
//	this->connect(circleButton, SIGNAL(clicked()), graphicsScene, SLOT(setMode()));
//	toolGroup->addButton(circleButton, 4);
//}

void MoudleWidget::setupUi(HalconCpp::HObject img, QWidget *moudleWidget, int left)
{
	QRect deskRect = QApplication::desktop()->availableGeometry();
	this->resize(deskRect.width() - 500, deskRect.height() - 200);
	/*this->resize(1426, 816);*/

	closeButton = new QPushButton(moudleWidget);
	closeButton->setObjectName(QStringLiteral("closeButton"));
	closeButton->setGeometry(QRect(this->width() - 50-31, 100, 31, 31));
	closeButton->setFlat(true);
	closeButton->setIcon(QIcon(":/visionQT_test/Resources/closeButton.png"));
	closeButton->setStyleSheet(QLatin1String("QPushButton:pressed {\n"
		"    border-style: inset;\n"
		"}"));
	this->connect(closeButton, SIGNAL(clicked()), this, SLOT(close()));

	// Disp: Father widget for HALCON window in HBoxDispAndButtons
	Disp = new QHalconWindow(img, this, this->width() - left - halconRight,
		this->height() - halconTop - halconBottom, left, halconTop);

	centredImgButton = new QPushButton(moudleWidget);
	centredImgButton->setObjectName(QStringLiteral("centredImgButton"));
	centredImgButton->setGeometry(QRect(left - 31, halconTop, 31, 31));
	centredImgButton->setFlat(true);
	centredImgButton->setIcon(QIcon(":/visionQT_test/Resources/adjustButton.png"));
	centredImgButton->setStyleSheet(QLatin1String("QPushButton:pressed {\n"
		"    border-style: inset;\n"
		"}"));
	this->connect(centredImgButton, SIGNAL(clicked()), Disp, SLOT(fitSize()));

	zoomInButton = new QPushButton(moudleWidget);
	zoomInButton->setObjectName(QStringLiteral("zoomInButton"));
	zoomInButton->setGeometry(QRect(left - 31, halconTop + 31 + 1, 31, 31));
	zoomInButton->setFlat(true);
	zoomInButton->setIcon(QIcon(":/visionQT_test/Resources/zoom-in.png"));
	zoomInButton->setStyleSheet(QLatin1String("QPushButton:pressed {\n"
		"    border-style: inset;\n"
		"}"));
	this->connect(zoomInButton, SIGNAL(clicked()), Disp, SLOT(zoomIn()));

	zoomOutButton = new QPushButton(moudleWidget);
	zoomOutButton->setObjectName(QStringLiteral("zoomOutButton"));
	zoomOutButton->setGeometry(QRect(left - 31, halconTop + 31 * 2 + 2, 31, 31));
	zoomOutButton->setFlat(true);
	zoomOutButton->setIcon(QIcon(":/visionQT_test/Resources/zoom-out.png"));
	zoomOutButton->setStyleSheet(QLatin1String("QPushButton:pressed {\n"
		"    border-style: inset;\n"
		"}"));
	this->connect(zoomOutButton, SIGNAL(clicked()), Disp, SLOT(zoomOut()));

	midLine = QLine(QPoint(left - 31, halconTop + 31 * 3 + 8), QPoint(left - 31 + 31, halconTop + 31 * 3 + 8));

	toolGroup = new QButtonGroup(this);
	toolGroup->setExclusive(false);
	//this->connect(toolGroup, SIGNAL(buttonClicked(int)),
	//	this, SLOT(buttonGroupClicked(int)));

	QPushButton *pointButton = new QPushButton(moudleWidget);
	pointButton->setObjectName(QStringLiteral("pointButton"));
	pointButton->setGeometry(QRect(left - 31, halconTop + 31 * 3 + 5 * 2, 31, 31));
	pointButton->setFlat(true);
	pointButton->setIcon(QIcon(":/visionQT_test/Resources/pointButton.png"));
	pointButton->setStyleSheet(QLatin1String("QPushButton:pressed {\n"
		"    border-style: inset;\n"
		"}"));
	toolGroup->addButton(pointButton,0);
	this->connect(pointButton, SIGNAL(clicked()), Disp, SLOT(pointTool_Click()));

	QPushButton *lineButton = new QPushButton(moudleWidget);
	lineButton->setObjectName(QStringLiteral("lineButton"));
	lineButton->setGeometry(QRect(left - 31, halconTop + 31 * 4 + 5 * 2, 31, 31));
	lineButton->setFlat(true);
	lineButton->setIcon(QIcon(":/visionQT_test/Resources/lineButton.png"));
	lineButton->setStyleSheet(QLatin1String("QPushButton:pressed {\n"
		"    border-style: inset;\n"
		"}"));
	toolGroup->addButton(lineButton, 1);
	this->connect(lineButton, SIGNAL(clicked()), Disp, SLOT(lineTool_Click()));

	QPushButton *rectButton = new QPushButton(moudleWidget);
	rectButton->setObjectName(QStringLiteral("rectButton"));
	rectButton->setGeometry(QRect(left - 31, halconTop + 31 * 5 + 5 * 2, 31, 31));
	rectButton->setFlat(true);
	rectButton->setIcon(QIcon(":/visionQT_test/Resources/rectangleButton.png"));
	rectButton->setStyleSheet(QLatin1String("QPushButton:pressed {\n"
		"    border-style: inset;\n"
		"}"));
	toolGroup->addButton(rectButton, 2);
	this->connect(rectButton, SIGNAL(clicked()), Disp, SLOT(rectangleTool_Click()));

	QPushButton *refectButton = new QPushButton(moudleWidget);
	refectButton->setObjectName(QStringLiteral("rectButton"));
	refectButton->setGeometry(QRect(left - 31, halconTop + 31 * 6 + 5 * 2, 31, 31));
	refectButton->setFlat(true);
	refectButton->setIcon(QIcon(":/visionQT_test/Resources/refineRectButton.png"));
	refectButton->setStyleSheet(QLatin1String("QPushButton:pressed {\n"
		"    border-style: inset;\n"
		"}"));
	toolGroup->addButton(refectButton, 3);
	this->connect(refectButton, SIGNAL(clicked()), Disp, SLOT(rectangle2Tool_Click()));

	QPushButton *circleButton = new QPushButton(moudleWidget);
	circleButton->setObjectName(QStringLiteral("circleButton"));
	circleButton->setGeometry(QRect(left - 31, halconTop + 31 * 7 + 5 * 2, 31, 31));
	circleButton->setFlat(true);
	circleButton->setIcon(QIcon(":/visionQT_test/Resources/circleButton.png"));
	circleButton->setStyleSheet(QLatin1String("QPushButton:pressed {\n"
		"    border-style: inset;\n"
		"}"));
	toolGroup->addButton(circleButton, 4);
	this->connect(circleButton, SIGNAL(clicked()), Disp, SLOT(circleTool_Click()));
}

void MoudleWidget::paintEvent(QPaintEvent *event)
{
	QPainter *painter = new QPainter(this);

	painter->setBrush(QBrush(QColor(240, 240, 240)));
	painter->setPen(Qt::transparent);

	QRect rect = QRect(50, 100, this->width()-100, this->height()-150);
	painter->drawRoundedRect(rect, 6, 6);

	painter->setPen(QPen(Qt::lightGray, 2, Qt::SolidLine));
	painter->drawLine(midLine);
}

void MoudleWidget::SetImage(QImage img)
{

}

//插入点、线、矩形、圆等
void MoudleWidget::buttonGroupClicked(int id)
{    
	QList<QAbstractButton*> buttons = toolGroup->buttons();
	foreach (QAbstractButton *button, buttons)
	{
		if (toolGroup->button(id) != button)
			button->setChecked(false);
	}
	if (id == 0)
	{
		graphicsScene->setMode(MyGraphicsScene::InsertPoint);
	}
	else if (id == 1)
	{
		graphicsScene->setMode(MyGraphicsScene::InsertLine);
	}
	else if (id == 2)
	{
		graphicsScene->setMode(MyGraphicsScene::InsertRect);
	}
	else if (id == 3)
	{
		graphicsScene->setMode(MyGraphicsScene::InsertRefrect);
	}
	else if (id == 4)
	{
		graphicsScene->setMode(MyGraphicsScene::InsertCircle);
	}
	else
	{}
}

