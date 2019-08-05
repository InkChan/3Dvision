#ifndef REMOVEOUTLIERS_H
#define REMOVEOUTLIERS_H

#include "moudleWidget.h"
#include "litcontrol.h"
#include "qlabel.h"
#include "HalconCpp.h"
#include "HDevThread.h"

class RemoveOutliers : public MoudleWidget
{
	Q_OBJECT

public:
	RemoveOutliers(HImage img, QWidget *parent = 0);
	~RemoveOutliers();

	void process(HImage img);
	/*HalconCpp::HImage QImageToHImage(QImage *inImage);*/

private:
	LitControl *algorithmControl;				//�㷨
	LitControl *fillHolesControl;				//�׶����
	LitControl *maskSizeControl;				//����ߴ�
	QLabel *algorithmLabel;						//�㷨��ǩ
	QLabel *fillHolesLabel;						//�׶���ǩ
	QLabel *maskLabel;							//��Ĥ��ǩ
};

#endif // REMOVEOUTLIERS_H
