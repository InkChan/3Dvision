#ifndef MOUDLEWIDGET_H
#define MOUDLEWIDGET_H

#include <QWidget>
#include <qtoolbar.h>
#include <qaction.h>
#include "ui_moudlewidget.h"
#include "qline.h"
#include "litcontrol.h"
#include "imageview.h"

class MoudleWidget : public QWidget
{
	Q_OBJECT

public:
	MoudleWidget(QImage img, QWidget *parent = 0);
	~MoudleWidget();
	public slots:
	void buttonGroupClicked(int id);

protected:
	void setupUi(QImage img, QWidget *MoudleWidget);
	void paintEvent(QPaintEvent *event);
	//void mouseMoveEvent(QMouseEvent *event);

private:
	/*Ui::MoudleWidget ui;*/
	LitControl *litControl;				//小控件
	QPushButton *closeButton;			//窗口关闭
	ImageView *graphicsView;			//显示图
	MyGraphicsScene *graphicsScene;		//场景

	QPushButton *centredImgButton;		//居中图片
	QPushButton *zoomInButton;			//放大图片
	QPushButton *zoomOutButton;			//缩小图片
	QLine midLine;						//分隔（做显示用）

	QButtonGroup *toolGroup;

	QPointF startP;

	//QPushButton *pointButton;
	//QPushButton *lineButton;
	//QPushButton *rectButton;
	//QPushButton *refectButton;
	//QPushButton *circleButton;
};

#endif // MOUDLEWIDGET_H
