#include "litcontrol.h"

LitControl::LitControl(QWidget *parent)
	: QWidget(parent)
	, rarowSize(QSize(15, 18))
	, larowSize(QSize(15, 18))
	, arrowSize(QSize(20, 18))
{
	this->setObjectName("LittleControl");
	controlSize = QSize(120, 20);
	comboSize = QSize(70, 18);
	comboItemWidth = comboSize.width();
	resize(controlSize);

	arrowButton = new QPushButton(this);
	arrowButton->setGeometry(0, 1, arrowSize.width(), arrowSize.height());
	arrowButton->setIcon(QIcon(":/visionQT_test/Resources/arrow.png"));
	arrowButton->setFlat(true);

	fline = QLine(QPoint(arrowSize.width(), 5), QPoint(arrowSize.width(), 15));

	larowButton = new QPushButton(this);
	larowButton->setGeometry(arrowSize.width(), 1, larowSize.width(), larowSize.height());
	larowButton->setIcon(QIcon(":/visionQT_test/Resources/larrow.png"));
	larowButton->setIconSize(QSize(larowSize.width() - 9, larowSize.height() - 7));
	larowButton->setFlat(true);

	sline = QLine(QPoint((arrowSize.width() + larowSize.width()), 5),
		QPoint((arrowSize.width() + larowSize.width()), 15));

	combo = new QComboBox(this);
	combo->setGeometry((arrowSize.width() + larowSize.width()), 1, comboSize.width(), comboSize.height());
	combo->insertItems(0, QStringList("..."));
	combo->setStyleSheet(QLatin1String("QComboBox {\n"
		"    border:2px;\n"
		"    border-radius: 3px;\n"
		"    padding: 1px 18px 1px 3px;\n"
		"}\n"
		"QComboBox::drop-down {\n"
		"    width: 0px;\n"
		"border-style: none;\n"
		"}\n"
		"QComboBox QAbstractItemView {\n"
		"    border: 1px solid darkgray;\n"
		"    selection-background-color: lightgray;\n"
		"}"));
	combo->view()->setMinimumWidth(comboItemWidth);

	tline = QLine(QPoint(arrowSize.width() + larowSize.width() + comboSize.width(), 5),
		QPoint(arrowSize.width() + larowSize.width() + comboSize.width(), 15));

	rarowButton = new QPushButton(this);
	rarowButton->setGeometry((arrowSize.width() + larowSize.width() + comboSize.width()),
		1, rarowSize.width(), rarowSize.height());
	rarowButton->setIcon(QIcon(":/visionQT_test/Resources/rarrow.png"));
	rarowButton->setIconSize(QSize(rarowSize.width() - 9, rarowSize.height() - 7));
	rarowButton->setFlat(true);

	connect(larowButton, SIGNAL(clicked()), this, SLOT(larowSlot()));
	connect(rarowButton, SIGNAL(clicked()), this, SLOT(rarowSlot()));

	this->setStyleSheet(QLatin1String("QPushButton:pressed {\n"
		"    border-style: inset;\n"
		"}"));
}

LitControl::LitControl(QWidget *parent, int coboWid, int coboitemWidth, QStringList itemList)
	:QWidget(parent)
	, rarowSize(QSize(15, 18))
	, larowSize(QSize(15, 18))
	, arrowSize(QSize(22, 18))
{
	this->setObjectName("LittleControl");
	this->setFixedHeight(20);

	comboSize = QSize(coboWid, 18);

	controlSize = QSize((coboWid + rarowSize.width() + larowSize.width() + arrowSize.width() + 5), 20);
	resize(controlSize);

	arrowButton = new QPushButton(this);
	arrowButton->setGeometry(0, 1, arrowSize.width(), arrowSize.height());
	arrowButton->setIcon(QIcon(":/visionQT_test/Resources/arrow.png"));
	arrowButton->setFlat(true);

	fline = QLine(QPoint(arrowSize.width(), 5), QPoint(arrowSize.width(), 15));

	larowButton = new QPushButton(this);
	larowButton->setGeometry(arrowSize.width() + 1, 1, larowSize.width(), larowSize.height());
	larowButton->setIcon(QIcon(":/visionQT_test/Resources/larrow.png"));
	larowButton->setIconSize(QSize(larowSize.width() - 9, larowSize.height() - 7));
	larowButton->setFlat(true);

	sline = QLine(QPoint((arrowSize.width() + larowSize.width() + 2), 5),
		QPoint((arrowSize.width() + larowSize.width() + 2), 15));

	combo = new QComboBox(this);
	combo->setGeometry((arrowSize.width() + larowSize.width()+3), 1, comboSize.width(), comboSize.height());
	combo->setStyleSheet(QLatin1String("QComboBox {\n"
		"    border:2px;\n"
		"    border-radius: 3px;\n"
		"    padding: 1px 18px 1px 3px;\n"
		"}\n"
		"QComboBox::drop-down {\n"
		"    width: 0px;\n"
		"border-style: none;\n"
		"}\n"
		"QComboBox QAbstractItemView {\n"
		"    border: 1px solid darkgray;\n"
		"    selection-background-color: lightgray;\n"
		"}"));
	combo->view()->setMinimumWidth(comboItemWidth);
	setComboItm(itemList);

	tline = QLine(QPoint(arrowSize.width() + larowSize.width() + comboSize.width() + 4, 5),
		QPoint(arrowSize.width() + larowSize.width() + comboSize.width() + 4, 15));

	rarowButton = new QPushButton(this);
	rarowButton->setGeometry((arrowSize.width() + larowSize.width() + comboSize.width() + 5),
		1, rarowSize.width(), rarowSize.height());
	rarowButton->setIcon(QIcon(":/visionQT_test/Resources/rarrow.png"));
	rarowButton->setIconSize(QSize(rarowSize.width() - 9, rarowSize.height() - 7));
	rarowButton->setFlat(true);

	connect(larowButton, SIGNAL(clicked()), this, SLOT(larowSlot()));
	connect(rarowButton, SIGNAL(clicked()), this, SLOT(rarowSlot()));

	this->setStyleSheet(QLatin1String("QPushButton:pressed {\n"
		"    border-style: inset;\n"
		"}"));
}

LitControl::~LitControl()
{

}

void LitControl::setComboItm(QStringList item)
{
	comboItemList = QStringList()
		<< QString::fromUtf8("<\346\234\252\350\277\236\346\216\245>")
		<< QString::fromUtf8("<\346\220\234\347\264\242\350\256\276\345\244\207>")
		<< QString::fromUtf8("<\344\275\277\347\224\250\347\254\254\344\270\200\344\270\252\345\217\257\347\224\250\347\233\270\346\234\272>");
	combo->insertItems(0, comboItemList);
}

void LitControl::paintEvent(QPaintEvent *event)
{
	QPainter painter(this);
	painter.setBrush(QBrush(QColor(255, 255, 255)));
	painter.setPen(Qt::transparent);
	QRect rect = QRect(0, 0, controlSize.width(), controlSize.height());
	painter.drawRoundedRect(rect, 7, 7);

	painter.setPen(QPen(Qt::gray, 1, Qt::SolidLine));
	painter.drawLine(sline);
	painter.drawLine(tline);
	painter.drawLine(fline);
}

void LitControl::larowSlot()
{
	if (comboItemList.count() > 0)
	{
		int index = combo->currentIndex();
		index = (index + combo->count() - 1) % combo->count();

		combo->setCurrentIndex(index);
		combo->setCurrentText(comboItemList[index]);
	}
}

void LitControl::rarowSlot()
{
	if (comboItemList.count() > 0)
	{
		int index = combo->currentIndex();
		index = (index + 1) % combo->count();

		combo->setCurrentIndex(index);
		combo->setCurrentText(comboItemList[index]);
	}	
}