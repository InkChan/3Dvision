#ifndef VISIONQT_TEST_H
#define VISIONQT_TEST_H

#include <QtWidgets/QMainWindow>
#include <qtextedit.h>
#include <qdockwidget.h>
#include <qlistwidget.h>
#include <qmaintabwidget.h>
#include <QDesktopWidget>
#include <qgraphicsview.h>
#include <qtreeview.h>
#include <QAbstractItemModel>
#include "Sensor.h"
#include "sensortreemodel.h"
#include "sensorproperty.h"
#include "LMISensor.h"
#include "WenglorSensor.h"
#include "SensorsVector.h"
#include "moduletree.h"
#include "preview.h"


QT_BEGIN_NAMESPACE
class QAction;
class QListWidget;
class QMenu;
class QTextEdit;
QT_END_NAMESPACE

class visionQT_test : public QMainWindow
{
	Q_OBJECT
		QWidget *baseWidget;
		QMainTabWidget *mainW;				//main tab widget

public:
	visionQT_test(QWidget *parent = 0);
	~visionQT_test();

private slots:
void open();

private:
//	Ui::visionQT_testClass ui;
	//¹¤¾ßÀ¸
	QAction *openAct;					//open file Act
	QAction *saveAct;					//save file Act
	QAction *setAct;					//set Act
	QAction *connectAct;				//connect camera Act
	QAction *disconnectAct;				//disconnect carmera Act
	QToolBar *fileToolBar;				//tool Bar

	//²Ëµ¥À¸ Menus
	QMenu *fileMenu;
	QMenu *toolMenu;
	QMenu *moduleMenu;
	QMenu *viewMenu;
	QMenu *windowMenu;
	QMenu *helpMenu;

	//×´Ì¬À¸ status bars
	QStatusBar *vision_statusBar;
	QRadioButton *on_offButton;					//On/Off
	QLabel *coordinaryText;						//(x,y)

	//Í£¿¿´°ÌåDock windows
	SensorTreeModel *sensorTreeModel;
	SensorProperty *sensor_Properties;
	Preview *previewsList;
	moduleTree *sensorModuleTree;


private:
	void createMainWidow();						//create the mian window
	void createActions();
	void createMenus();							//create Menus
	void createToolBars();						//create tool bars
	void createDockWindows();					//create Dock Windows
	void createStatusBar();						//create Status Bars
};

#endif // VISIONQT_TEST_H
