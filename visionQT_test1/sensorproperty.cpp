#include "sensorproperty.h"

SensorProperty::SensorProperty(QWidget *parent)
	: QTableView(parent)
{
	propertyModel = new QStandardItemModel(17,2);
	propertyModel->setItem(0, 0, new QStandardItem("Name"));
	propertyModel->setItem(1, 0, new QStandardItem("Type"));
	propertyModel->setItem(2, 0, new QStandardItem("Serial Number"));

	propertyModel->setItem(3, 0, new QStandardItem("Laser Active"));
	propertyModel->setItem(4, 0, new QStandardItem("Is Master"));
	propertyModel->setItem(5, 0, new QStandardItem("Sequence Index"));

	propertyModel->setItem(6, 0, new QStandardItem("Exposure Mode"));
	propertyModel->setItem(7, 0, new QStandardItem("Exposure Time[us]"));

	propertyModel->setItem(8, 0, new QStandardItem("Meas. Min[mm]"));
	propertyModel->setItem(9, 0, new QStandardItem("Meas. Value[mm]"));
	propertyModel->setItem(10, 0, new QStandardItem("Meas. Max[mm]"));
	propertyModel->setItem(11, 0, new QStandardItem("Z-Start Min[mm]"));
	propertyModel->setItem(12, 0, new QStandardItem("Z-Start Value[mm]"));
	propertyModel->setItem(13, 0, new QStandardItem("Z-Start Max[mm]"));
	propertyModel->setItem(14, 0, new QStandardItem("Transform[mm]"));

	propertyModel->setItem(15, 0, new QStandardItem("Trigger Mode"));
	propertyModel->setItem(16, 0, new QStandardItem("Trigger Delay"));

	this->setModel(propertyModel);
	this->setColumnWidth(0, 120);
	this->setColumnWidth(1, 117);
	this->horizontalHeader()->setVisible(false);
	this->verticalHeader()->setVisible(false);
	this->setEditTriggers(NoEditTriggers);
}

void SensorProperty::showProperties(Sensor *sensor)
{
	propertyModel->setItem(0, 1, new QStandardItem(QString::fromStdString(sensor->getSensorName())));
	propertyModel->setItem(1, 1, new QStandardItem(QString::fromStdString(sensor->getSensorType())));
	propertyModel->setItem(2, 1, new QStandardItem(QString::fromStdString(sensor->getSerialNumber())));

	propertyModel->setItem(3, 1, new QStandardItem(QString::number(sensor->getStatus())));
	propertyModel->setItem(4, 1, new QStandardItem(QString::number(sensor->IsMaster())));
	propertyModel->setItem(5, 1, new QStandardItem(QString::number(sensor->getSequenceIndex())));

	propertyModel->setItem(6, 1, new QStandardItem(QString::fromStdString(sensor->getSensorExposureMode())));
	propertyModel->setItem(7, 1, new QStandardItem(QString::number(sensor->getSensorExposureTime())));

	propertyModel->setItem(8, 1, new QStandardItem(QString::number(sensor->getMeasureRange().minValue)));
	propertyModel->setItem(9, 1, new QStandardItem(QString::number(sensor->getMeasureRange().Value)));
	propertyModel->setItem(10, 1, new QStandardItem(QString::number(sensor->getMeasureRange().maxValue)));
	propertyModel->setItem(11, 1, new QStandardItem(QString::number(sensor->getzStartRange().minValue)));
	propertyModel->setItem(12, 1, new QStandardItem(QString::number(sensor->getzStartRange().Value)));
	propertyModel->setItem(13, 1, new QStandardItem(QString::number(sensor->getzStartRange().maxValue)));
	propertyModel->setItem(14, 1, new QStandardItem(QString::number(sensor->getTransformation())));

	propertyModel->setItem(15, 1, new QStandardItem(QString::fromStdString(sensor->getSensorTriggerMode())));
	propertyModel->setItem(16, 1, new QStandardItem(QString::number(sensor->getSensorTriggerDelay())));
}

SensorProperty::~SensorProperty()
{

}
