#include "sensortreemodel.h"

SensorTreeModel::SensorTreeModel(QWidget *parent)
	:QTreeView(parent)
{
	sensorsModel = new QStandardItemModel(1, 1);
	item = new QStandardItem("Project Calibration");

	for (int i = 0; i < SensorVector.size(); ++i)
	{
		QStandardItem *child = new QStandardItem(QString("Scanner %0").arg(i));
		child->setEditable(false);
		child->setForeground(QBrush(SensorVector.at(i)->getColor()));
		item->appendRow(child);
		
		//////////可能有错
		delete(child);
	}
	sensorsModel->setItem(0, 0, item);

	this->setModel(sensorsModel);
	this->setHeaderHidden(true);

	this->setStyleSheet(QLatin1String("QTreeView{ \n"
		"    show-decoration-selected: 0;\n"
		"}\n"
		"\n"
		"QTreeView{ \n"
		"font-size:13px;\n"
		"}\n"
		"\n"
		"QTreeView::branch:has-siblings:!adjoins-item {\n"
		"    border-image: url(:/visionQT_test/Resources/branch-closed.png) 0;\n"
		"}\n"
		"\n"
		"QTreeView::branch:has-siblings:adjoins-item {\n"
		"    border-image: url(:/visionQT_test/Resources/branch-more.png) 0;\n"
		"}\n"
		"\n"
		"QTreeView::branch:!has-children:!has-siblings:adjoins-item {\n"
		"    border-image: url(:/visionQT_test/Resources/branch-end.png) 0;\n"
		"}\n"
		"\n"
		"QTreeView::branch:has-children:!has-siblings:closed,\n"
		"QTreeView::branch:closed:has-children:has-siblings {\n"
		"        border-image: none;\n"
		"        image: url(:/visionQT_test/Resources/branch-closed.png);\n"
		"}\n"
		"\n"
		"QTreeView::branch:open:has-children:!has-siblings,\n"
		"QTreeView::branch:open:has-children:has-siblings  {\n"
		"        border-image: none;\n"
		"        image: url(:/visionQT_test/Resources/branch-ope"
		"n.png);\n"
		"}"));

	/*setSensorUI = new SetSensor();*/
	//connect(this, SIGNAL(mouseClick()),)

	/*
		"QTreeView::item:hover {\n"
		"    background: qlineargradient(x1: 0, y1: 0, x2: 0, y2: 1, stop: 0 #e7effd, stop: 1 #cbdaf1);\n"
		"}\n"
		"\n"
		"QTreeView::item:selected:active{\n"
		"    background: qlineargradient(x1: 0, y1: 0, x2: 0, y2: 1, stop: 0 #6ea1f1, stop: 1 #567dbc);\n"
		"}\n"
		"\n"
	*/
	/*this->setStyleSheet("font-size:15px;");*/
}

int SensorTreeModel::selectedIndex = -1;

void SensorTreeModel::mouseDoubleClickEvent(QMouseEvent *event)
{
	if (!indexAt(event->pos()).child(0, 0).isValid())
	{
//		selectionIndex = indexAt(event->pos()).parent().row();
		if (indexAt(event->pos()).parent().row() >= 0)
		{
			setSensorUI = new SetSensor();
			selectedIndex = this->selectedIndexes()[0].row();
			setSensorUI->show();
			connect(setSensorUI->ColorSensor_pushButton, SIGNAL(clicked()), this, SLOT(changeColor()), Qt::UniqueConnection);
			connect(setSensorUI->Edit_pushButton, SIGNAL(clicked()), this, SLOT(editSensor()), Qt::UniqueConnection);
		}		
	}
	
}

void SensorTreeModel::connectSensor()
{
	if (selectedIndex != -1)
	{
		if (getCurrentSensor()->connect() == 0)
		{
			SensorVector.at(selectedIndex)->setColor(QColor(34, 190, 34));
			item->child(selectedIndex)->setForeground(QBrush(SensorVector.at(selectedIndex)->getColor()));
		}
	}
}

void SensorTreeModel::disconnectSensor()
{
	if (selectedIndex != -1)
	{
		if (getCurrentSensor()->disconnect() == 0)
		{
			SensorVector.at(selectedIndex)->setColor(QColor(Qt::red));
			item->child(selectedIndex)->setForeground(QBrush(SensorVector.at(selectedIndex)->getColor()));
		}
	}
}

Sensor* SensorTreeModel::getCurrentSensor()
{
	return (SensorVector.at(selectedIndex));
}

void SensorTreeModel::changeColor()
{
	if (selectedIndex == 0)
	{
		SensorVector.at(selectedIndex)->setColor(QColor(255, 128, 0));
	}
	else if (selectedIndex == 1)
	{
		SensorVector.at(selectedIndex)->setColor(QColor(107, 142, 35));
	}
	else if (selectedIndex == 3)
	{
		SensorVector.at(selectedIndex)->setColor(QColor(138, 43, 226));
	}
	else if (selectedIndex == 4)
	{
		SensorVector.at(selectedIndex)->setColor(QColor(0, 199, 140));
	}
	else
	{

	}
	
	item->child(selectedIndex)->setForeground(QBrush(SensorVector.at(selectedIndex)->getColor()));
}

void SensorTreeModel::mousePressEvent(QMouseEvent *event)
{
	QTreeView::mousePressEvent(event);

	if (!indexAt(event->pos()).child(0, 0).isValid())
	{
		if (indexAt(event->pos()).parent().row() >= 0)
		{
			selectedIndex = this->selectedIndexes()[0].row();
			mouseClick(getCurrentSensor());
		}
		else
		{
			selectedIndex = -1;
		}
	}
	else
	{
		selectedIndex = -1;
	}
}

//////////////////需要改写
void SensorTreeModel::editSensor()
{
	SensorVector.at(selectedIndex)->setSensorName(this->setSensorUI->
		SensorName_lineEdit->text().toStdString());
	
	SensorVector.at(selectedIndex)->setSensorIP(this->setSensorUI->
		IPAddress_lineEdit->text().toStdString());

	if (this->setSensorUI->IS_radioButton->isChecked())
	{
		SensorVector.at(selectedIndex)->setSensorTriggerMode(SensorTriggerMode::IS);
	}

	if (this->setSensorUI->HW_radioButton->isChecked())
	{
		SensorVector.at(selectedIndex)->setSensorTriggerMode(SensorTriggerMode::HW);
	}
	
	if (this->setSensorUI->Encode_radioButton->isChecked())
	{
		SensorVector.at(selectedIndex)->setSensorTriggerMode(SensorTriggerMode::Encoder);
	}

	if (this->setSensorUI->Time_radioButton->isChecked())
	{
		SensorVector.at(selectedIndex)->setSensorTriggerMode(SensorTriggerMode::Time);
	}

	if (this->setSensorUI->Master_checkBox->isChecked())
	{
		SensorVector.at(selectedIndex)->setMaster();
	}

	SensorVector.at(selectedIndex)->setSequenceIndex(this->setSensorUI->SeqIndex_spinBox->value());
	
	SensorVector.at(selectedIndex)->setSensorType(this->setSensorUI->SensorType_comboBox->currentText().toStdString());

	mouseClick(SensorVector.at(selectedIndex));
}

void SensorTreeModel::setSensor()
{

}

QStandardItemModel *SensorTreeModel::getSensorsModel()
{
	return sensorsModel;
}


SensorTreeModel::~SensorTreeModel()
{

}
