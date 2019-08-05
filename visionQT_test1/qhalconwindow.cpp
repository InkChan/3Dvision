#include "qhalconwindow.h"

QHalconWindow::QHalconWindow(HalconCpp::HImage Image, QWidget *parent, long Width, long Height,
	int halconLeft,int halconTop)
	: QWidget(parent)
{
	leftPos = 0;
	winWidth = Width;
	winHeight = Height;
	Img = Image;
	Image.GetImageSize(&imgWidth, &imgHeight);
	_pan = false;

	this->setMouseTracking(true);
	this->setGeometry(QRect(halconLeft, halconTop, winWidth, winHeight));
	show();
	OpenWindow();
}

QHalconWindow::~QHalconWindow(void)
{
	using namespace HalconCpp;

	CloseWindow(WindowID());
}

// Open a HALCON window inside the QHalconWindow widget
void QHalconWindow::OpenWindow(void)
{
	using namespace HalconCpp;
	SetWindowAttr("border_width", 0);
	HalconCpp::OpenWindow(topPos, leftPos, winWidth, winHeight, (Hlong)winId(), "visible", "", &WinID);
}

// Resize the HALCON window whenever the QHalconWindow widget is resized
void QHalconWindow::resizeEvent(QResizeEvent*)
{
	using namespace HalconCpp;
	SetWindowExtents(WindowID(), topPos, leftPos, winWidth, winHeight);
	showPicture(Img);
}

//显示图片
void QHalconWindow::showPicture(HalconCpp::HImage Image)
{
	using namespace HalconCpp;

	double imgWHRatio = double(imgWidth) / double(imgHeight);
	double winWHRatio = double(winWidth) / double(winHeight);

	if (imgWidth > winWidth || imgHeight > winHeight)
	{
		if (imgWHRatio >= winWHRatio)
		{
			m_dDispImagePartRow1 = imgWidth / winWHRatio;
			m_dDispImagePartCol1 = imgWidth;

			SetPart(WindowID(), m_dDispImagePartRow0, m_dDispImagePartCol0, m_dDispImagePartRow1 - 1, m_dDispImagePartCol1 - 1);
			SetPartStyle(WindowID(), 1);
			DispObj(Image, WindowID());

			//绘制图片区域
			GenRectangle1(&imgRect, 0, 0, imgHeight, imgWidth);
			SetLineWidth(WindowID(), 2);
			SetColor(WindowID(), "blue");
			SetDraw(WindowID(), "margin");
			DispObj(imgRect, WindowID());
		}
		else
		{	
			m_dDispImagePartRow1 = imgHeight;
			m_dDispImagePartCol1 = imgHeight*winWHRatio;

			SetPart(WindowID(), m_dDispImagePartRow0, m_dDispImagePartCol0, m_dDispImagePartRow1 - 1, m_dDispImagePartCol1 - 1);
			SetPartStyle(WindowID(), 1);

			DispObj(Image, WindowID());

			//绘制图片区域
			GenRectangle1(&imgRect, 0, 0, imgHeight, imgWidth);
			SetLineWidth(WindowID(), 2);
			SetColor(WindowID(), "blue");
			SetDraw(WindowID(), "margin");
			DispObj(imgRect, WindowID());
		}
	}
	else
	{
		m_dDispImagePartRow1 = winHeight;
		m_dDispImagePartCol1 = winWidth;
		SetPart(WindowID(), m_dDispImagePartRow0, m_dDispImagePartCol0, m_dDispImagePartRow1 - 1, m_dDispImagePartCol1 - 1);
		SetPartStyle(WindowID(), 1);

		DispObj(Image, WindowID());
		//绘制图片区域
		GenRectangle1(&imgRect, 0, 0, imgHeight, imgWidth);
		SetLineWidth(WindowID(), 2);
		SetColor(WindowID(), "blue");
		SetDraw(WindowID(), "margin");
		DispObj(imgRect, WindowID());
	}

	pw = (m_dDispImagePartCol1 - m_dDispImagePartCol0) / (double)winWidth;
	ph = (m_dDispImagePartRow1 - m_dDispImagePartRow0) / (double)winHeight;
	scaleFactor = 1;
}

void QHalconWindow::mousePressEvent(QMouseEvent *event)
{
	using namespace HalconCpp;
	if (event->button() == Qt::LeftButton)
	{
		if (event->pos().x() > leftPos&&event->pos().x() < leftPos + winWidth
			&&event->pos().y() > topPos&&event->pos().y() < topPos + winHeight)
		{
			_pan = true;;

			//记录当前坐标
			_panStartX = event->pos().x();
			_panStartY = event->pos().y();

			for each (HalconGraphics *var in graphics_objects)
			{
				if (var->getShowMove() == true)
				{
					var->setMoveable(true);
					_pan = false;
					return;
				}
				if (var->getShowZoom() == true)
				{
					var->setZoomable(true);
					_pan = false;
					return;
				}
			}
		}
	}
	event->ignore();

}

void QHalconWindow::mouseMoveEvent(QMouseEvent *event)
{	
	using namespace HalconCpp;

	HTuple mouseX, mouseY, button;
	GetMposition(WindowID(), &mouseY, &mouseX, &button);

	if (_pan)
	{
		int k = (event->pos().x() - _panStartX);
		int t = (event->pos().y() - _panStartY);

		m_dDispImagePartRow0 = m_dDispImagePartRow0 - t*ph;
		m_dDispImagePartCol0 = m_dDispImagePartCol0 - k*pw;
		m_dDispImagePartRow1 = m_dDispImagePartRow1 - t*ph;
		m_dDispImagePartCol1 = m_dDispImagePartCol1 - k*pw;
		
		_panStartX = event->pos().x();
		_panStartY = event->pos().y();
		repaint();
		return;
	}

	for each (HalconGraphics *var in graphics_objects)
	{
		//检查鼠标当前位置是否可拖动图形移动

		var->checkMove(QPoint(mouseX.I(),mouseY.I()));

		if (var->Movable() == true)
		{
			int k = (event->pos().x() - _panStartX);
			int t = (event->pos().y() - _panStartY);
			var->setMove(QPointF(k*pw, t*ph));
			_panStartX = event->pos().x();
			_panStartY = event->pos().y();
			break;
		}

		var->checkZoom(QPoint(mouseX.I(), mouseY.I()));
		if (var->Zoomable() == true)
		{
			//int k = (event->pos().x() - _panStartX);
			//int t = (event->pos().y() - _panStartY);

			var->setZoom(QPointF(_panStartX*pw, _panStartY*ph), 
				QPointF(event->pos().x()*pw, event->pos().y()*ph));
			_panStartX = event->pos().x();
			_panStartY = event->pos().y();

			break;
		}
	}
	repaint();
}

void QHalconWindow::mouseReleaseEvent(QMouseEvent *event)
{
	
	if (event->button() == Qt::LeftButton)
	{
		_pan = false;
		for each (HalconGraphics *var in graphics_objects)
		{
			var->setMoveable(false);
			var->setZoomable(false);
		}

		event->accept();
		return;
	}
	event->ignore();
}

//视野缩小
void QHalconWindow::zoomIn()
{
	using namespace HalconCpp;

	scaleFactor -= 0.02;
	m_dDispImagePartRow1 *= 0.98;
	m_dDispImagePartCol1 *= 0.98;

	repaint();
}

//视野放大
void QHalconWindow::zoomOut()
{
	using namespace HalconCpp;

	m_dDispImagePartRow1 *= 1.02;
	m_dDispImagePartCol1 *= 1.02;

	repaint();
}

//图片保持纵横比自适应窗口大小；
void QHalconWindow::fitSize()
{
	using namespace HalconCpp;

	double imgWHRatio = double(imgWidth) / double(imgHeight);
	double winWHRatio = double(winWidth) / double(winHeight);

	m_dDispImagePartRow0 = 0;
	m_dDispImagePartCol0 = 0;

	if (imgWidth > winWidth || imgHeight > winHeight)
	{
		if (imgWHRatio >= winWHRatio)
		{
			m_dDispImagePartRow1 = imgWidth / winWHRatio;
			m_dDispImagePartCol1 = imgWidth;

			SetSystem("flush_graphic", "false");
			ClearWindow(WindowID());
			SetPart(WindowID(), m_dDispImagePartRow0, m_dDispImagePartCol0, m_dDispImagePartRow1 - 1, m_dDispImagePartCol1 - 1);
			SetPartStyle(WindowID(), 1);
			//DispObj(Img, WindowID());
			SetSystem("flush_graphic", "true");
			DispImage(Img, WindowID());
			SetLineWidth(WindowID(), 2);
			SetColor(WindowID(), "blue");
			SetDraw(WindowID(), "margin");
			DispObj(imgRect, WindowID());
		}
		else
		{
			m_dDispImagePartRow1 = imgHeight;
			m_dDispImagePartCol1 = imgHeight*winWHRatio;

			SetSystem("flush_graphic", "false");
			ClearWindow(WindowID());
			SetPart(WindowID(), m_dDispImagePartRow0, m_dDispImagePartCol0, m_dDispImagePartRow1 - 1, m_dDispImagePartCol1 - 1);
			SetPartStyle(WindowID(), 1);
			//DispObj(Img, WindowID());
			SetSystem("flush_graphic", "true");
			DispImage(Img, WindowID());
			SetLineWidth(WindowID(), 2);
			SetColor(WindowID(), "blue");
			SetDraw(WindowID(), "margin");
			DispObj(imgRect, WindowID());
		}
	}
	else
	{
		m_dDispImagePartRow1 = winHeight;
		m_dDispImagePartCol1 = winWidth;

		SetSystem("flush_graphic", "false");
		ClearWindow(WindowID());
		SetPart(WindowID(), m_dDispImagePartRow0, m_dDispImagePartCol0, m_dDispImagePartRow1 - 1, m_dDispImagePartCol1 - 1);
		SetPartStyle(WindowID(), 1);

		//DispObj(Img, WindowID());
		SetSystem("flush_graphic", "true");
		DispImage(Img, WindowID());
		SetLineWidth(WindowID(), 2);
		SetColor(WindowID(), "blue");
		SetDraw(WindowID(), "margin");
		DispObj(imgRect, WindowID());
	}
}

void QHalconWindow::pointTool_Click()
{
	HalconPoint *point1 = new HalconPoint(300, 300);
	graphics_objects.push_back(point1);

	repaint();
}

void QHalconWindow::rectangleTool_Click()
{
	HalconRect *rect1 = new HalconRect(600, 600);
	graphics_objects.push_back(rect1);
	
	repaint();
}

void QHalconWindow::rectangle2Tool_Click()
{
	HalconRotateRect *rect2 = new HalconRotateRect(700, 700);
	graphics_objects.push_back(rect2);

	repaint();
}

void QHalconWindow::circleTool_Click()
{
	HalconCircle *circle = new HalconCircle(500, 800);
	graphics_objects.push_back(circle);

	repaint();
}

void QHalconWindow::lineTool_Click()
{
	HalconLine *line = new HalconLine(500, 500);
	graphics_objects.push_back(line);

	repaint();
}

//添加绘制对象;
void QHalconWindow::AttachDrawObj(HalconCpp::HDrawingObject obj)
{
	using namespace HalconCpp;

	drawing_objects.push_back(obj);

	SetSystem("flush_graphic", "false");
	ClearWindow(WindowID());
	SetPart(WindowID(), m_dDispImagePartRow0, m_dDispImagePartCol0, m_dDispImagePartRow1 - 1, m_dDispImagePartCol1 - 1);
	AttachDrawingObjectToWindow(WindowID(), obj);
	SetSystem("flush_graphic", "true");
	DispImage(Img, WindowID());
	SetLineWidth(WindowID(), 2);
	SetColor(WindowID(), "blue");
	SetDraw(WindowID(), "margin");
	DispObj(imgRect, WindowID());

}

//重绘
void QHalconWindow::repaint()
{
	using namespace HalconCpp;

	SetSystem("flush_graphic", "false");
	ClearWindow(WindowID());
	SetPart(WindowID(), m_dDispImagePartRow0, m_dDispImagePartCol0, m_dDispImagePartRow1 - 1, m_dDispImagePartCol1 - 1);
	//SetPartStyle(WindowID(), 1);
	SetColor(WindowID(), "blue");
	SetDraw(WindowID(), "margin");
	DispImage(Img, WindowID());
	for each (HalconGraphics *var in graphics_objects)
	{
		var->paint(WindowID());
	}

	SetSystem("flush_graphic", "true");
	DispObj(imgRect, WindowID());
	SetLineWidth(WindowID(), 2);

}

//判断点是否在OBB内；
bool QHalconWindow::pointInOBB(double oldx, double oldy,
	double centerx,double centery,double width,double height,double angle)
{
	int newy = sin(angle) * (oldy - centery) + cos(angle) * (oldx - centerx);
	int newx = cos(angle) * (oldx - centerx) - sin(angle) * (oldy - centery);

	return (newy > centery - height / 2) && (newy < centery + height / 2)
		&& (newx > centerx - width / 2) && (newx < centerx + width / 2);
}

bool QHalconWindow::Pan(double mouseX,double mouseY)
{
	return true;
}