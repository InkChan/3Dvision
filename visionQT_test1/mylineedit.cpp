#include "mylineedit.h"
#include <HImage.h>

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
	QImage _img, to;
	_img = QImage(QDir::currentPath()+"\\Resources\\pipe_joint.tif");

	HalconCpp::HImage img;
	QString ImageFileName = QDir::currentPath() + "\\Resources\\pipe_joint_01.png";
	ReadImage(&img, ImageFileName.toStdString().c_str());
	switch (Tool)
	{
	case 0:
		break;
	case 1:
	{
		MoudleWidget *moudleWidget = new MoudleWidget(img);
		moudleWidget->show();
		break;
	}	
	case 4:
	{
		RemoveOutliers *removeOutliers = new RemoveOutliers(img);
		removeOutliers->show();
		break;
	}		
	default:
		break;
	}
}

QImage MyLineEdit::HImageToQImage(HalconCpp::HImage)
{
	return QImage();
}

HalconCpp::HImage MyLineEdit::QImageToHImage(QImage *inImage)
{
	//ensure image is valid
	if (inImage->isNull())
	{
		return HalconCpp::HImage();
	}

	switch (inImage->format())
	{
	case QImage::Format_RGB32:
	{
		int ptrSize = inImage->width()*inImage->height();
		/*for (int i = 0;i<_img.b)*/

		uchar *ptrR = new uchar[ptrSize];
		uchar *ptrG = new uchar[ptrSize];
		uchar *ptrB = new uchar[ptrSize];
		for (int y = 0; y < inImage->height(); y++)
		{
			for (int x = 0; x < inImage->width(); x++)
			{
				QColor c(inImage->pixel(x, y));
				ptrR[y*inImage->width() + x] = c.red();
				ptrG[y*inImage->width() + x] = c.green();
				ptrB[y*inImage->width() + x] = c.blue();
			}
		}
		HalconCpp::HImage* img = new HalconCpp::HImage();
		img->GenImage3("byte", inImage->width(), inImage->height(), ptrR, ptrG, ptrB);
		return *img;
	}
	case QImage::Format_ARGB32:
	{
		int ptrSize = inImage->width()*inImage->height();

		uchar *ptr = new uchar[ptrSize];
		for (int y = 0; y < inImage->height(); y++)
		{
			for (int x = 0; x < inImage->width(); x++)
			{
				QRgb c(inImage->pixel(x, y));
				ptr[y*inImage->width() + x] = c;
			}
		}

		HalconCpp::HImage* img = new HalconCpp::HImage();
		img->GenImage1("byte", inImage->width(), inImage->height(), ptr);
		return *img;
		/*Hlong	 width, height;
		img->GetImageSize(&width, &height);
		HalconCpp::HSystem::SetWindowAttr("border_width", HalconCpp::HTuple(0));
		HalconCpp::HWindow	window(100, 100, width / 1.5, height / 1.5, 0, "visible", "");
		window.SetLineWidth(3);
		window.DispObj(*img);*/
	}
	default:
		return HalconCpp::HImage();
	}
}


void MyLineEdit::rgb3_to_interleaved(HObject ho_ImageRGB, HObject *ho_ImageInterleaved)
{
	// Local iconic variables
	HObject  ho_ImageAffineTrans, ho_ImageRed, ho_ImageGreen;
	HObject  ho_ImageBlue, ho_RegionGrid, ho_RegionMoved, ho_RegionClipped;

	// Local control variables
	HTuple  hv_PointerRed, hv_PointerGreen, hv_PointerBlue;
	HTuple  hv_Type, hv_Width, hv_Height, hv_HomMat2DIdentity;
	HTuple  hv_HomMat2DScale;

	GetImagePointer3(ho_ImageRGB, &hv_PointerRed, &hv_PointerGreen, &hv_PointerBlue,
		&hv_Type, &hv_Width, &hv_Height);
	GenImageConst(&(*ho_ImageInterleaved), "byte", hv_Width * 3, hv_Height);
	//
	HomMat2dIdentity(&hv_HomMat2DIdentity);
	HomMat2dScale(hv_HomMat2DIdentity, 1, 3, 0, 0, &hv_HomMat2DScale);
	AffineTransImageSize(ho_ImageRGB, &ho_ImageAffineTrans, hv_HomMat2DScale, "constant",
		hv_Width * 3, hv_Height);
	//
	Decompose3(ho_ImageAffineTrans, &ho_ImageRed, &ho_ImageGreen, &ho_ImageBlue);
	GenGridRegion(&ho_RegionGrid, 2 * hv_Height, 3, "lines", hv_Width * 3, hv_Height + 1);
	MoveRegion(ho_RegionGrid, &ho_RegionMoved, -1, 0);
	ClipRegion(ho_RegionMoved, &ho_RegionClipped, 0, 0, hv_Height - 1, (3 * hv_Width) - 1);
	//NOTE: Due to internal limitations, the images ImageRed, ImageGreen, and ImageBlue
	//cannot be displayed by HDevelop.Trying to display one of these images results in the
	//error message 'Internal error: number of chords too big for num_max'. However, this
	//affects by no means the continuation or the results of this example program, and
	//therefore, is no reason to be alarmed !
	ReduceDomain(ho_ImageRed, ho_RegionClipped, &ho_ImageRed);
	MoveRegion(ho_RegionGrid, &ho_RegionMoved, -1, 1);
	ClipRegion(ho_RegionMoved, &ho_RegionClipped, 0, 0, hv_Height - 1, (3 * hv_Width) - 1);
	ReduceDomain(ho_ImageGreen, ho_RegionClipped, &ho_ImageGreen);
	MoveRegion(ho_RegionGrid, &ho_RegionMoved, -1, 2);
	ClipRegion(ho_RegionMoved, &ho_RegionClipped, 0, 0, hv_Height - 1, (3 * hv_Width) - 1);
	ReduceDomain(ho_ImageBlue, ho_RegionClipped, &ho_ImageBlue);
	OverpaintGray((*ho_ImageInterleaved), ho_ImageRed);
	OverpaintGray((*ho_ImageInterleaved), ho_ImageGreen);
	OverpaintGray((*ho_ImageInterleaved), ho_ImageBlue);
	return;



	//QImage::Format format;
	//HalconCpp::HTuple htChannels;
	//HalconCpp::CountChannels(img, &htChannels);
	//if (htChannels[0].I() == 1)
	//{
	//	HalconCpp::HTuple hv_pointer;
	//	format = QImage::Format_ARGB32;
	//	GetImagePointer1(img, &hv_pointer, &htype, &width, &height);
	//	uchar *ptr;
	//	ptr = (uchar*)hv_pointer[0].L();
	//	int qwidth = width, qheight = height;
	//	//to = QImage(qwidth, qheight, format);
	//	to = QImage(ptr, qwidth, qheight, qwidth, format);
	//	/*for (int i = 0; i<qheight; i++)
	//	{
	//	memcpy(to.bits() + qwidth*i, ptr + qwidth*i, qwidth);
	//	}*/
	//}
	//if (htChannels[0].I() == 3)
	//{
	//	format = QImage::Format_RGB32;
	//	uchar *ptr3;
	//	HImage hImageInterleaved;
	//	HalconCpp::HTuple hv_pointer;
	//	rgb3_to_interleaved(img, &hImageInterleaved);
	//	GetImagePointer1(hImageInterleaved, &hv_pointer, &htype, &width, &height);
	//	ptr3 = (uchar*)hv_pointer[0].L();
	//	int qwidth = width, qheight = height;
	//	for (int i = 0; i<qheight; i++)
	//	{
	//		memcpy(to.bits() + qwidth*i, ptr3 + qwidth*i, qwidth);
	//	}
	//}

}