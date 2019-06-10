#include "setsensor.h"

SetSensor::SetSensor(QWidget *parent)
	: QWidget(parent)
{
	this->setObjectName("SetSensorWindow");
	this->setWindowTitle("Ink Vision");
	this->setWindowIcon(QIcon(":/visionQT_test/Resources/blink.jpeg"));
	//ui.setupUi(this);
	setupUi(this);
	SensorType_comboBox->addItem("LMI");
	SensorType_comboBox->addItem("Wenglor");
	this->setStyleSheet("background-color:rgb(250, 250, 250);");
	this->setWindowModality(Qt::ApplicationModal);
	this->setWindowFlags(windowFlags()&~Qt::WindowMinMaxButtonsHint);
	this->setFixedSize(this->width(), this->height());
	connect(Cancel_pushButton, SIGNAL(clicked()), this, SLOT(close()));
}

void SetSensor::setupUi(QWidget *SetSensor)
{
	if (SetSensor->objectName().isEmpty())
		SetSensor->setObjectName(QStringLiteral("SetSensor"));
	SetSensor->resize(479, 278);
	QFont font;
	font.setFamily(QStringLiteral("Microsoft Tai Le"));
	font.setPointSize(10);
	font.setBold(false);
	font.setWeight(50);
	SetSensor->setFont(font);
	label = new QLabel(SetSensor);
	label->setObjectName(QStringLiteral("label"));
	label->setGeometry(QRect(20, 25, 41, 21));
	label->setTextFormat(Qt::AutoText);
	label->setWordWrap(false);
	SensorName_lineEdit = new QLineEdit(SetSensor);
	SensorName_lineEdit->setObjectName(QStringLiteral("SensorName_lineEdit"));
	SensorName_lineEdit->setGeometry(QRect(60, 19, 271, 31));
	SensorName_lineEdit->setStyleSheet(QLatin1String("QLineEdit{\n"
		"    border: 2px solid #8f8f91;\n"
		"    border-radius: 2px;\n"
		"}"));
	Invert_checkBox = new QCheckBox(SetSensor);
	Invert_checkBox->setObjectName(QStringLiteral("Invert_checkBox"));
	Invert_checkBox->setGeometry(QRect(20, 70, 51, 16));
	Invert_checkBox->setStyleSheet(QStringLiteral(""));
	Master_checkBox = new QCheckBox(SetSensor);
	Master_checkBox->setObjectName(QStringLiteral("Master_checkBox"));
	Master_checkBox->setGeometry(QRect(20, 110, 61, 16));
	Trigger_groupBox = new QGroupBox(SetSensor);
	Trigger_groupBox->setObjectName(QStringLiteral("Trigger_groupBox"));
	Trigger_groupBox->setGeometry(QRect(210, 80, 251, 61));
	Trigger_groupBox->setLayoutDirection(Qt::LeftToRight);
	Trigger_groupBox->setStyleSheet(QLatin1String("QGroupBox\n"
		"{\n"
		"    border: 2px solid #8f8f91;\n"
		"    border-radius: 2px;\n"
		"}"));
	IS_radioButton = new QRadioButton(Trigger_groupBox);
	IS_radioButton->setObjectName(QStringLiteral("IS_radioButton"));
	IS_radioButton->setGeometry(QRect(10, 30, 41, 16));
	HW_radioButton = new QRadioButton(Trigger_groupBox);
	HW_radioButton->setObjectName(QStringLiteral("HW_radioButton"));
	HW_radioButton->setGeometry(QRect(60, 30, 41, 16));
	Encode_radioButton = new QRadioButton(Trigger_groupBox);
	Encode_radioButton->setObjectName(QStringLiteral("Encode_radioButton"));
	Encode_radioButton->setGeometry(QRect(110, 30, 71, 16));
	Time_radioButton = new QRadioButton(Trigger_groupBox);
	Time_radioButton->setObjectName(QStringLiteral("Time_radioButton"));
	Time_radioButton->setGeometry(QRect(190, 30, 50, 16));

	label_2 = new QLabel(SetSensor);
	label_2->setObjectName(QStringLiteral("label_2"));
	label_2->setGeometry(QRect(20, 150, 91, 16));
	label_3 = new QLabel(SetSensor);
	label_3->setObjectName(QStringLiteral("label_3"));
	label_3->setGeometry(QRect(20, 200, 54, 16));
	IPAddress_lineEdit = new QLineEdit(SetSensor);
	IPAddress_lineEdit->setObjectName(QStringLiteral("IPAddress_lineEdit"));
	IPAddress_lineEdit->setGeometry(QRect(80, 190, 381, 31));
	IPAddress_lineEdit->setStyleSheet(QLatin1String("QLineEdit\n"
		"{\n"
		"    border: 2px solid #8f8f91;\n"
		"    border-radius: 2px;\n"
		"}"));
	label_4 = new QLabel(SetSensor);
	label_4->setObjectName(QStringLiteral("label_4"));
	label_4->setGeometry(QRect(90, 70, 31, 16));
	SensorType_comboBox = new QComboBox(SetSensor);
	SensorType_comboBox->setObjectName(QStringLiteral("SensorType_comboBox"));
	SensorType_comboBox->setGeometry(QRect(130, 70, 69, 22));
	SensorType_comboBox->setStyleSheet(QLatin1String("QComboBox\n"
		"{\n"
		"    border: 2px solid #8f8f91;\n"
		"    border-radius: 2px;\n"
		"}\n"
		));
	setStyleSheet(
		"QComboBox QAbstractItemView::item { min-height: 20px; min-width: 60px; }");

	label_5 = new QLabel(SetSensor);
	label_5->setObjectName(QStringLiteral("label_5"));
	label_5->setGeometry(QRect(90, 110, 31, 16));
	spinBox = new QSpinBox(SetSensor);
	spinBox->setObjectName(QStringLiteral("spinBox"));
	spinBox->setGeometry(QRect(130, 110, 71, 22));
	spinBox->setStyleSheet(QLatin1String("QSpinBox\n"
		"{\n"
		"    border: 2px solid #8f8f91;\n"
		"    border-radius: 2px;\n"
		"}"));
	SeqIndex_spinBox = new QSpinBox(SetSensor);
	SeqIndex_spinBox->setObjectName(QStringLiteral("SeqIndex_spinBox"));
	SeqIndex_spinBox->setGeometry(QRect(120, 150, 71, 22));
	SeqIndex_spinBox->setStyleSheet(QLatin1String("QSpinBox\n"
		"{\n"
		"    border: 2px solid #8f8f91;\n"
		"    border-radius: 2px;\n"
		"}"));
	ColorSensor_pushButton = new QPushButton(SetSensor);
	ColorSensor_pushButton->setObjectName(QStringLiteral("ColorSensor_pushButton"));
	ColorSensor_pushButton->setGeometry(QRect(350, 20, 101, 31));
	QFont font1;
	font1.setFamily(QStringLiteral("Microsoft NeoGothic"));
	font1.setPointSize(11);
	font1.setBold(true);
	font1.setWeight(75);
	ColorSensor_pushButton->setFont(font1);
	ColorSensor_pushButton->setStyleSheet(QStringLiteral("QPushButton { color: white; background-color: rgb(0,125,200) }"));
	ColorSensor_pushButton->setAutoDefault(false);
	ColorSensor_pushButton->setDefault(false);
	ColorSensor_pushButton->setFlat(false);
	Edit_pushButton = new QPushButton(SetSensor);
	Edit_pushButton->setObjectName(QStringLiteral("Edit_pushButton"));
	Edit_pushButton->setGeometry(QRect(260, 240, 75, 23));
	QFont font2;
	font2.setFamily(QStringLiteral("Microsoft Tai Le"));
	font2.setPointSize(10);
	Edit_pushButton->setFont(font2);
	Edit_pushButton->setAutoFillBackground(false);
	Edit_pushButton->setStyleSheet(QLatin1String("QPushButton {\n"
		"    border: 2px solid #8f8f91;\n"
		"    border-radius: 2px;\n"
		"}\n"
		"QPushButton:pressed {\n"
		"	border:2px solid rgb(0,125,200);\n"
		"}"));
	Edit_pushButton->setDefault(false);
	Cancel_pushButton = new QPushButton(SetSensor);
	Cancel_pushButton->setObjectName(QStringLiteral("Cancel_pushButton"));
	Cancel_pushButton->setGeometry(QRect(370, 240, 75, 23));
	Cancel_pushButton->setStyleSheet(QLatin1String("QPushButton {\n"
		"    border: 2px solid #8f8f91;\n"
		"    border-radius: 2px;\n"
		"}\n"
		"QPushButton:pressed {\n"
		"	border:2px solid rgb(0,125,200);\n"
		"}"));

	retranslateUi(SetSensor);

	QMetaObject::connectSlotsByName(SetSensor);
} // setupUi

void SetSensor::retranslateUi(QWidget *SetSensor)
{
	SetSensor->setWindowTitle(QApplication::translate("SetSensor", "SetSensor", 0));
	label->setText(QApplication::translate("SetSensor", "Name", 0));
	Invert_checkBox->setText(QApplication::translate("SetSensor", "Invert", 0));
	Master_checkBox->setText(QApplication::translate("SetSensor", "Master", 0));
	Trigger_groupBox->setTitle(QApplication::translate("SetSensor", "Trigger", 0));
	IS_radioButton->setText(QApplication::translate("SetSensor", "IS", 0));
	HW_radioButton->setText(QApplication::translate("SetSensor", "HW", 0));
	Encode_radioButton->setText(QApplication::translate("SetSensor", "Encoder", 0));
	Time_radioButton->setText(QApplication::translate("SetSensor", "Time", 0));
	label_2->setText(QApplication::translate("SetSensor", "Sequence Index:", 0));
	label_3->setText(QApplication::translate("SetSensor", "IP address", 0));
	label_4->setText(QApplication::translate("SetSensor", "Type:", 0));
	label_5->setText(QApplication::translate("SetSensor", "E/A:", 0));
	ColorSensor_pushButton->setText(QApplication::translate("SetSensor", "Color", 0));
	Edit_pushButton->setText(QApplication::translate("SetSensor", "Edit", 0));
	Cancel_pushButton->setText(QApplication::translate("SetSensor", "Cancel", 0));
} // retranslateUi


SetSensor::~SetSensor()
{

}
