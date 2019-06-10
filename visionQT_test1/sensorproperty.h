#ifndef SENSORPROPERTY_H
#define SENSORPROPERTY_H

#include <qstandarditemmodel.h>
#include <qtableview.h>
#include <QAbstractItemModel>
#include <qabstractitemview.h>
#include <qheaderview.h>
#include "Sensor.h"

class SensorProperty : public QTableView
{
	Q_OBJECT

public:
	SensorProperty(QWidget *parent);
	~SensorProperty();
	
	public Q_SLOTS:
	void showProperties(Sensor*);

private:
	QStandardItemModel *propertyModel;
};

#endif // SENSORPROPERTY_H
