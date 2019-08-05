#ifndef QHALCONWINDOW_H
#define QHALCONWINDOW_H

#include <QWidget>
#include <qevent.h>
#include <halconcpp\HalconCpp.h>
#include "HalconRect.h"
#include "HalconPoint.h"
#include "HalconGraphics.h"
#include "HalconLine.h"
#include "HalconCircle.h"
#include "HalconRotateRect.h"


class QHalconWindow : public QWidget
{
	Q_OBJECT

public:
	QHalconWindow(HalconCpp::HImage Image, QWidget *parent, long Width, long Height,
		int halconLeft, int halconTop);
	virtual ~QHalconWindow(void);

	HalconCpp::HTuple WindowID(void) { return WinID; }
	void showPicture(HalconCpp::HImage Image);

	public slots:
	void zoomIn();
	void zoomOut();
	void fitSize();
	void pointTool_Click();
	void rectangleTool_Click();
	void rectangle2Tool_Click();
	void circleTool_Click();
	void lineTool_Click();

protected:
	void resizeEvent(QResizeEvent*);
	void mousePressEvent(QMouseEvent *event);
	void mouseMoveEvent(QMouseEvent *event);
	void mouseReleaseEvent(QMouseEvent *event);

private:
	void OpenWindow(void);
	void AttachDrawObj(HalconCpp::HDrawingObject obj);
	void repaint();
	//判断点是否在OBB中;
	bool pointInOBB(double oldx, double oldy,
		double centerx, double centery, double width, double height, double angle);

	bool Pan(double mouseX, double mouseY);

	HalconCpp::HTuple WinID;
	HalconCpp::HImage Img;
	//图片是否移动的标志
	bool _pan;
	//图片宽度、高度
	Hlong imgWidth, imgHeight;
	
	//图片左测留白长度,上测留白长度
	int leftPos = 0, topPos = 0;
	int winWidth = 0, winHeight = 0;
	HalconCpp::HObject imgRect;

	//setpart
	double m_dDispImagePartRow0 = 0, m_dDispImagePartCol0 = 0, m_dDispImagePartRow1 = 0, m_dDispImagePartCol1 = 0;
	//move
	int _panStartX, _panStartY;

	double scaleFactor;					//图片显示比率

	double pw, ph;                      //halcon窗口显示的尺寸与显示器中的尺寸的比值

	std::vector<HalconCpp::HDrawingObject> drawing_objects;
	std::vector<HalconGraphics*> graphics_objects;
};

#endif // QHALCONWINDOW_H
