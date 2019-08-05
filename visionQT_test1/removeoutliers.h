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
	LitControl *algorithmControl;				//Ëã·¨
	LitControl *fillHolesControl;				//¿×¶´Ìî³ä
	LitControl *maskSizeControl;				//ÑÚÂë³ß´ç
	QLabel *algorithmLabel;						//Ëã·¨±êÇ©
	QLabel *fillHolesLabel;						//¿×¶´±êÇ©
	QLabel *maskLabel;							//ÑÚÄ¤±êÇ©
};

#endif // REMOVEOUTLIERS_H
