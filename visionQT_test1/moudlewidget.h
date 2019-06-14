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
	LitControl *litControl;				//С�ؼ�
	QPushButton *closeButton;			//���ڹر�
	ImageView *graphicsView;			//��ʾͼ
	MyGraphicsScene *graphicsScene;		//����

	QPushButton *centredImgButton;		//����ͼƬ
	QPushButton *zoomInButton;			//�Ŵ�ͼƬ
	QPushButton *zoomOutButton;			//��СͼƬ
	QLine midLine;						//�ָ�������ʾ�ã�

	QButtonGroup *toolGroup;

	QPointF startP;

	//QPushButton *pointButton;
	//QPushButton *lineButton;
	//QPushButton *rectButton;
	//QPushButton *refectButton;
	//QPushButton *circleButton;
};

#endif // MOUDLEWIDGET_H
