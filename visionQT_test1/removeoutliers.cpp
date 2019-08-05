#include "removeoutliers.h"

RemoveOutliers::RemoveOutliers(HImage img, QWidget *parent)
	: MoudleWidget(img, parent, 131)
{
	QStringList algorithmItem = QStringList()
		<< QString::fromStdWString(L"自动抑制离群值");
	algorithmControl = new LitControl(this, 104, algorithmItem);
	algorithmControl->setGeometry(QRect(120, 100 - algorithmControl->controlSize.height() / 2,
		algorithmControl->controlSize.width(), algorithmControl->controlSize.height()));
	algorithmLabel = new QLabel(QString::fromStdWString(L"方法"), this);
	algorithmLabel->setGeometry(QRect(190, 100 + algorithmControl->controlSize.height() / 2,
		60, 20));
	algorithmLabel->setStyleSheet("QLabel{\n"
		"background-color:transparent;}");

	QStringList fillHolesItem = QStringList()
		<< QString("true")
		<< QString("false");
	fillHolesControl = new LitControl(this, 45, fillHolesItem);
	fillHolesControl->setGeometry(QRect(284, 100 - fillHolesControl->controlSize.height() / 2,
		fillHolesControl->controlSize.width(), fillHolesControl->controlSize.height()));
	fillHolesLabel = new QLabel(QString::fromStdWString(L"孔洞填充"), this);
	fillHolesLabel->setGeometry(310, 100 + fillHolesControl->controlSize.height() / 2,
		80, 20);
	fillHolesLabel->setStyleSheet("QLabel{\n"
		"background-color:transparent;}");

	QStringList maskSizeItem = QStringList()
		<< QString("1.5")
		<< QString("2.5")
		<< QString("3.5")
		<< QString("4.5")
		<< QString("5.5")
		<< QString("6.5")
		<< QString("7.5");
	maskSizeControl = new LitControl(this, 38, maskSizeItem);
	maskSizeControl->setGeometry(QRect(390, 100 - maskSizeControl->controlSize.height() / 2,
		maskSizeControl->controlSize.width(), maskSizeControl->controlSize.height()));
	maskLabel = new QLabel(QString::fromStdWString(L"掩码尺寸"), this);
	maskLabel->setGeometry(415, 100 + maskSizeControl->controlSize.height() / 2,
		80, 20);
	maskLabel->setStyleSheet("QLabel{\n"
		"background-color:transparent;}");

	QString tem = fillHolesControl->getStatus();

	process(img);
	/*fillHolesLabel=*/
}

void RemoveOutliers::process(HImage img)
{
	if (!img.IsInitialized())
	{
		return;
	}

	if (fillHolesControl->getStatus() == "true")
	{

	}
}

//HalconCpp::HImage RemoveOutliers::QImageToHImage(QImage *inImage)
//{
//	if (inImage ->isNull()==false)
//	{
//		return HalconCpp::HImage();
//	}
//	switch (inImage->format())
//	{
//	case QImage::Format_RGB32:
//	{
//		int ptrSize = inImage->width()*inImage->height();
//		/*for (int i = 0;i<_img.b)*/
//
//		uchar *ptrR = new uchar[ptrSize];
//		uchar *ptrG = new uchar[ptrSize];
//		uchar *ptrB = new uchar[ptrSize];
//		for (int y = 0; y < inImage->height(); y++)
//		{
//			for (int x = 0; x < inImage->width(); x++)
//			{
//				QColor c(inImage->pixel(x, y));
//				ptrR[y*inImage->width() + x] = c.red();
//				ptrG[y*inImage->width() + x] = c.green();
//				ptrB[y*inImage->width() + x] = c.blue();
//			}
//		}
//		HalconCpp::HImage* img = new HalconCpp::HImage();
//		img->GenImage3("byte", inImage->width(), inImage->height(), ptrR, ptrG, ptrB);
//		return *img;
//	}
//	case QImage::Format_ARGB32:
//	{
//		int ptrSize = inImage->width()*inImage->height();
//
//		uchar *ptr = new uchar[ptrSize];
//		for (int y = 0; y < inImage->height(); y++)
//		{
//			for (int x = 0; x < inImage->width(); x++)
//			{
//				QRgb c(inImage->pixel(x, y));
//				ptr[y*inImage->width() + x] = c;
//			}
//		}
//
//		HalconCpp::HImage* img = new HalconCpp::HImage();
//		img->GenImage1("byte", inImage->width(), inImage->height(), ptr);
//		return *img;
//	}
//	default:
//		return HalconCpp::HImage();
//	}
//
//	return HalconCpp::HImage();
//}

RemoveOutliers::~RemoveOutliers()
{

}
