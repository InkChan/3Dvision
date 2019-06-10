#ifndef LITCONTROL_H
#define LITCONTROL_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QFrame>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QPushButton>
#include <QtDesigner\qdesignerexportwidget.h>
#include <qtimer.h>
#include <qpainter.h>
#include <qcombobox.h>
#include <qfontcombobox.h>
#include <qabstractscrollarea.h>
#include <qlineedit.h>

class LitControl : public QWidget
{
	Q_OBJECT

public:
	LitControl(QWidget *parent = 0);
	LitControl(QWidget *parent, int coboWid, int coboitemWidth, QStringList itemList);
	QSize controlSize;
	virtual ~LitControl();

public:
	void setComboItm(QStringList item);

	public Q_SLOTS:
	void larowSlot();
	void rarowSlot();


protected:
	void paintEvent(QPaintEvent *event);

private:
	QSize arrowSize;
	QSize larowSize;
	QSize rarowSize;
	QSize comboSize;
	QPushButton *arrowButton;
	QPushButton *larowButton;
	QPushButton *rarowButton;
	QComboBox *combo;

	QLine fline;
	QLine sline;
	QLine tline;

	//combo item width;
	int comboItemWidth;
	QStringList comboItemList;
};

#endif // LITCONTROL_H