#include "visionqt_test.h"

visionQT_test::visionQT_test(QWidget *parent)
	: QMainWindow(parent)
{
	this->setObjectName("MainWindow");
	this->setWindowTitle("Ink Vision");
	this->setWindowIcon(QIcon(":/visionQT_test/Resources/blink.jpeg"));

	//get current resolution
	QDesktopWidget *desktopWidget = QApplication::desktop();
	QRect deskRect = desktopWidget->availableGeometry();
	//Adaptive mainwidow size
	this->setGeometry(100,100,deskRect.width()-200,deskRect.height()-200);


	mainW = new QMainTabWidget(parent);
	mainW->setObjectName("MainView");
	
	setCentralWidget(mainW);

	createMainWidow();
	createActions();
	createMenus();

	createToolBars();
	createStatusBar();
	createDockWindows();
	this->connect(sensorTreeModel, SIGNAL(mouseClick(Sensor*)), sensor_Properties, 
		SLOT(showProperties(Sensor*)));
	connect(connectAct, SIGNAL(triggered()), sensorTreeModel, SLOT(connectSensor()));
	connect(disconnectAct, SIGNAL(triggered()), sensorTreeModel, SLOT(disconnectSensor()));
}

void visionQT_test::createMainWidow()
{
}

void visionQT_test::createActions()
{
	openAct = new QAction(QIcon(":/visionQT_test/Resources/open.jpg"), tr("&OpenFile"), this);
	openAct->setShortcut(QKeySequence::Open);
	openAct->setStatusTip(tr("Open file"));
	connect(openAct, SIGNAL(triggered()), this, SLOT(open()));

	saveAct = new QAction(QIcon(":/visionQT_test/Resources/save.png"), tr("&SaveFile"), this);
	saveAct->setShortcut(QKeySequence::Save);
	saveAct->setStatusTip(tr("save file"));
	//connect(saveAct, SIGNAL(QAction::triggered()), this, SLOT(save()));

	connectAct = new QAction(QIcon(":/visionQT_test/Resources/connected.png"), tr("&Connect"), this);
	

	disconnectAct = new QAction(QIcon(":/visionQT_test/Resources/disconnected.png"), tr("&Disconnected"), this);
	
	setAct = new QAction(QIcon(":/visionQT_test/Resources/wheels.png"), tr("&Settings"), this);

}

void visionQT_test::createMenus()
{
	menuBar()->setStyle(QStyleFactory::create("fusion"));
	//bind Menus with MenuBar
	fileMenu = menuBar()->addMenu(tr("File"));
	fileMenu->addAction(openAct);
	fileMenu->addAction(saveAct);

	toolMenu = menuBar()->addMenu(tr("Tool"));
	windowMenu = menuBar()->addMenu(tr("Window"));
	moduleMenu = menuBar()->addMenu(tr("Moudle"));
	viewMenu = menuBar()->addMenu(tr("View"));
	helpMenu = menuBar()->addMenu(tr("Help"));
}

void visionQT_test::createToolBars()
{
	//bind tools with ToolBar
	fileToolBar = addToolBar(tr("File"));
	fileToolBar->addAction(openAct);
	fileToolBar->addAction(saveAct);
	fileToolBar->addAction(setAct);
	fileToolBar->addAction(connectAct);
	fileToolBar->addAction(disconnectAct);
}

void visionQT_test::createStatusBar()
{
	//show (x,y) on statusBar
	on_offButton = new QRadioButton();
	on_offButton->setText("Stopped");
	coordinaryText = new QLabel();
	coordinaryText->setText("            x:|z: ");

	vision_statusBar = statusBar();
	vision_statusBar->addWidget(on_offButton);
	vision_statusBar->addWidget(coordinaryText);
}

void visionQT_test::createDockWindows()
{
	//create QDockWidget *dock
	QDockWidget *dock = new QDockWidget(tr("Sensors"), this);
	dock->setAllowedAreas(Qt::LeftDockWidgetArea | Qt::RightDockWidgetArea);

	//bind the sensorsList Widget with dock and viewMenu
	sensorTreeModel = new SensorTreeModel(dock);
	dock->setWidget(sensorTreeModel);
	addDockWidget(Qt::LeftDockWidgetArea, dock);
	sensorTreeModel->setMaximumHeight(200);
	viewMenu->addAction(dock->toggleViewAction());
	//this->connect(sensorTreeModel->setSensorUI->Edit_pushButton, SIGNAL(clicked()), sensor_Properties,
	//	SLOT(showProperties(Sensor*)));
	//createSensors();

	//bind the sensor_propertiesList Widget with dock and viewMenu
	dock = new QDockWidget(tr("Sensor Properties"), this);
	sensor_Properties = new SensorProperty(dock);
	dock->setWidget(sensor_Properties);
	addDockWidget(Qt::LeftDockWidgetArea, dock);
	viewMenu->addAction(dock->toggleViewAction());

	//bind the previewsList Widget with dock and viewMenu
	dock = new QDockWidget(tr("Previews"), this);
	previewsList = new Preview(130,30,dock);
	dock->setWidget(previewsList);
	addDockWidget(Qt::RightDockWidgetArea, dock);
	viewMenu->addAction(dock->toggleViewAction());

	//bind the modulesList Widget with dock and viewMenu
	dock = new QDockWidget(tr("Modules"), this);
	sensorModuleTree = new moduleTree(dock);
	dock->setWidget(sensorModuleTree);
	addDockWidget(Qt::RightDockWidgetArea, dock);
	viewMenu->addAction(dock->toggleViewAction());
}

void visionQT_test::open()
{
	
}

visionQT_test::~visionQT_test()
{
	if (this->sensorTreeModel->setSensorUI == NULL)
	{
		this->sensorTreeModel->setSensorUI->close();
	}
	
}
