#ifndef SETSENSOR_H
#define SETSENSOR_H

#include <QWidget>
#include "Sensor.h"
#include "ui_setsensor.h"

class SetSensor : public QWidget
{
	Q_OBJECT

public:
	QLabel *label;
	QLineEdit *SensorName_lineEdit;
	QCheckBox *Invert_checkBox;
	QCheckBox *Master_checkBox;
	QGroupBox *Trigger_groupBox;
	QRadioButton *IS_radioButton;
	QRadioButton *HW_radioButton;
	QRadioButton *Encode_radioButton;
	QRadioButton *Time_radioButton;
	QLabel *label_2;
	QLabel *label_3;
	QLineEdit *IPAddress_lineEdit;
	QLabel *label_4;
	QComboBox *SensorType_comboBox;
	QLabel *label_5;
	QSpinBox *spinBox;
	QSpinBox *SeqIndex_spinBox;
	QPushButton *ColorSensor_pushButton;
	QPushButton *Edit_pushButton;
	QPushButton *Cancel_pushButton;

public:
	SetSensor(QWidget *parent = 0);
	void setupUi(QWidget *SetSensor);
	void retranslateUi(QWidget *SetSensor);

	//Ui::SetSensor ui;
	~SetSensor();

signals:
	void myclick(Sensor*);

private:
	
};

#endif // SETSENSOR_H
