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
	//�жϵ��Ƿ���OBB��;
	bool pointInOBB(double oldx, double oldy,
		double centerx, double centery, double width, double height, double angle);

	bool Pan(double mouseX, double mouseY);

	HalconCpp::HTuple WinID;
	HalconCpp::HImage Img;
	//ͼƬ�Ƿ��ƶ��ı�־
	bool _pan;
	//ͼƬ��ȡ��߶�
	Hlong imgWidth, imgHeight;
	
	//ͼƬ������׳���,�ϲ����׳���
	int leftPos = 0, topPos = 0;
	int winWidth = 0, winHeight = 0;
	HalconCpp::HObject imgRect;

	//setpart
	double m_dDispImagePartRow0 = 0, m_dDispImagePartCol0 = 0, m_dDispImagePartRow1 = 0, m_dDispImagePartCol1 = 0;
	//move
	int _panStartX, _panStartY;

	double scaleFactor;					//ͼƬ��ʾ����

	double pw, ph;                      //halcon������ʾ�ĳߴ�����ʾ���еĳߴ�ı�ֵ

	std::vector<HalconCpp::HDrawingObject> drawing_objects;
	std::vector<HalconGraphics*> graphics_objects;
};

#endif // QHALCONWINDOW_H
