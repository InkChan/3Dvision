#ifndef REMOVEOUTLIERS_H
#define REMOVEOUTLIERS_H

#include "moudleWidget.h"

class RemoveOutliers : public MoudleWidget
{
	Q_OBJECT

public:
	RemoveOutliers(QImage img, QWidget *parent = 0);
	~RemoveOutliers();

private:
};

#endif // REMOVEOUTLIERS_H
