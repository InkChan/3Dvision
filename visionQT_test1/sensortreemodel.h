#ifndef SENSORTREEMODEL_H
#define SENSORTREEMODEL_H

#include <qtreeview.h>
#include <QAbstractItemModel>
#include <qstandarditemmodel.h>
#include <qsignalmapper.h>
#include <qevent.h>
#include <qcolor.h>
#include "Sensor.h"
#include "setsensor.h"
#include "SensorsVector.h"

class SensorTreeModel:public QTreeView
{
	Q_OBJECT

public:
	SensorTreeModel(QWidget *parent);
	QStandardItemModel *getSensorsModel();
	~SensorTreeModel();

	Sensor* getCurrentSensor();

	static int selectedIndex;
	SetSensor *setSensorUI;

	public Q_SLOTS:
	void changeColor();
	void editSensor();
	void connectSensor();
	void disconnectSensor();

protected:
	void mouseDoubleClickEvent(QMouseEvent *event);
	void mousePressEvent(QMouseEvent *event);

signals:
	void mouseClick(Sensor*);


private:
	void setSensor();
	QStandardItemModel *sensorsModel;
	static int sensorN;					//sensor counts
	QStandardItem *item;
};

#endif // SENSORTREEMODEL_H
