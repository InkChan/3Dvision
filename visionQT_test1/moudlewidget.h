#ifndef MOUDLEWIDGET_H
#define MOUDLEWIDGET_H

#include <QWidget>
#include <qtoolbar.h>
#include <qaction.h>
#include "ui_moudlewidget.h"
#include "qline.h"
#include "litcontrol.h"
#include "imageview.h"
#include "qhalconwindow.h"
#include <QDesktopWidget>
using namespace HalconCpp;

class MoudleWidget : public QWidget
{
	Q_OBJECT

public:
	MoudleWidget(HImage img, QWidget *parent = 0, int left = 400);
	//MoudleWidget(QImage img, QWidget *parent, int left = 400);
	~MoudleWidget();
	void SetImage(QImage img);

	public slots:
	void buttonGroupClicked(int id);


protected:
	void setupUi(HalconCpp::HObject img, QWidget *MoudleWidget, int left);
	//void setupUi(QImage img, QWidget *moudleWidget, int left);
	void paintEvent(QPaintEvent *event);
	//void mouseMoveEvent(QMouseEvent *event);

private:
	/*Ui::MoudleWidget ui;*/
	QPushButton *closeButton;			//窗口关闭
	ImageView *graphicsView;			//显示图
	MyGraphicsScene *graphicsScene;		//场景

	QPushButton *centredImgButton;		//居中图片
	QPushButton *zoomInButton;			//放大图片
	QPushButton *zoomOutButton;			//缩小图片
	QLine midLine;						//分隔（做显示用）

	QButtonGroup *toolGroup;

	QPointF startP;

	//设置qhalconWindow上部留白
	int halconTop = 152;
	int halconRight = 60;
	int halconBottom = 70;

	// HALCON variables
	HalconCpp::HTuple WindowIDBuf, FGHandle, Width, Height, Area;
	HalconCpp::HTuple ModelID, WindowWidth, WindowHeight;
	HalconCpp::HTuple Row, Column;
	HalconCpp::HTuple Row1, Column1, Row2, Column2;
	HalconCpp::HTuple Rect1Row, Rect1Col, Rect2Row, Rect2Col;
	HalconCpp::HTuple RectPhi, RectLength1, RectLength2;
	HalconCpp::HObject Image, ImageReduced, ShapeModelImage, ShapeModel;
	HalconCpp::HObject Rectangle0, Rectangle1, Rectangle2;


	QHalconWindow *Disp;
};

#endif // MOUDLEWIDGET_H
