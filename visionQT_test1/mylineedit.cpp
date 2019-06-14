#include "mylineedit.h"

MyLineEdit::MyLineEdit(QWidget *parent)
	: QLineEdit(parent)
{
	this->setStyleSheet("QLineEdit{\n"
		"backgroud-color:rgb(245,240,240);\n"
		"border-style:solid;\n"
		"border-width:3px;\n"
		"border-radius:10px;\n"
		"border-color:rgb(95,95,95);\n"
		"font:bold 14px;\n"
		"min-width:8em;\n"
		"padding:6px;}");
	this->setReadOnly(true);
	Act_Dele = new QAction(this);
	this->connect(this->Act_Dele, SIGNAL(triggered()), this, SLOT(delet()));
	//connect(Act_Dele, SIGNAL(triggered()), this, SLOT(delet()));
}

MyLineEdit::~MyLineEdit()
{
}

void MyLineEdit::setTool(SensorTool _tool)
{
	this->Tool = _tool;
}

void MyLineEdit::setTool(QString _toolname)
{
	SensorTool _tool;
	if (_toolname == "Get From File")
	{
		_tool = SensorTool::get_from_file;
	}
	if (_toolname == "Get From Camera")
	{
		_tool = SensorTool::get_from_camera;
	}
	if (_toolname == "Calibration Camera")
	{
		_tool = SensorTool::calibration_camera;
	}
	if (_toolname == "Align Images")
	{
		_tool = SensorTool::align_images;
	}
	if (_toolname == "Delete Outlier")
	{
		_tool = SensorTool::delete_outlier;
	}
	if (_toolname == "Leveling Surface")
	{
		_tool = SensorTool::leveling_surface;
	}
	if (_toolname == "Altitude Differ")
	{
		_tool = SensorTool::altitude_differ;
	}
	if (_toolname == "Flatness")
	{
		_tool = SensorTool::flatness;
	}
	if (_toolname == "Zone Transfer")
	{
		_tool = SensorTool::zone_transfer;
	}
	if (_toolname == "Conditional Branching")
	{
		_tool = SensorTool::conditional_branching;
	}
	if (_toolname == "Valuation Area")
	{
		_tool = SensorTool::valuation_area;
	}
	if (_toolname == "Evaluate Expressions")
	{
		_tool = SensorTool::evaluate_expressions;
	}
	if (_toolname == "File Read")
	{
		_tool = SensorTool::file_read;
	}
	if (_toolname == "File Write")
	{
		_tool = SensorTool::file_write;
	}
	if (_toolname == "Visa Read")
	{
		_tool = SensorTool::visa_read;
	}
	if (_toolname == "Socket Read")
	{
		_tool = SensorTool::socket_read;
	}
	if (_toolname == "Visa Write")
	{
		_tool = SensorTool::visa_write;
	}
	if (_toolname == "Socket Write")
	{
		_tool = SensorTool::socket_write;
	}
	if (_toolname == "Deferred Context")
	{
		_tool = SensorTool::deferred_context;
	}
	if (_toolname == "Get Execution Info")
	{
		_tool = SensorTool::get_execution_info;
	}
	this->Tool = _tool;
}

void MyLineEdit::mousePressEvent(QMouseEvent *event)
{
	Ischoose = true;
	if (event->button() == Qt::LeftButton)
	{
		QDrag *drag = new QDrag(this);
		Ischoose = true;
		QMimeData *mimeData = new QMimeData;
		QByteArray encodedData;
		QByteArray data;
		QDataStream stream(&data, QIODevice::WriteOnly);
		//QDataStream stream(&encodedData, QIODevice::WriteOnly);
		mimeData->setData("tool", encodedData);
		mimeData->setText("");
		drag->setMimeData(mimeData);
		drag->exec(Qt::MoveAction);
	}
}

void MyLineEdit::contextMenuEvent(QContextMenuEvent* e)
{
	Act_Dele->setText("Delet");
	QMenu *menu = new QMenu();
	menu->addSeparator();
	menu->addSeparator();
	menu->addAction(Act_Dele);
	menu->addSeparator();
	menu->addSeparator();
	menu->exec(e->globalPos());
	delete menu;
}

void MyLineEdit::delet()
{
	s_deletthis(this);
	delete this;
}

void MyLineEdit::mouseDoubleClickEvent(QMouseEvent *e)
{
	QImage _img = QImage(QString("D:\\Program\\visionQT_test1\\visionQT_test1\\Resources\\average.png"));
	switch (Tool)
	{
	case 0:
		break;
	case 1:
	{
		MoudleWidget *moudleWidget = new MoudleWidget(_img);
		moudleWidget->show();
		break;
	}	
	case 4:
	{
		RemoveOutliers *removeOutliers = new RemoveOutliers(_img);
		removeOutliers->show();
		break;
	}		
	default:
		break;
	}
}