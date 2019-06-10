#ifndef GETDATAFC_H
#define GETDATAFC_H

#include <QWidget>
#include <qcombobox.h>
#include "ui_getdatafc.h"

class GetDataFC : public QWidget
{
	Q_OBJECT

public:
	GetDataFC(QWidget *parent = 0);
	~GetDataFC();

private:
	/*QComboBox deviceCombo;*/
	Ui::GetDataFC ui;
};

#endif // GETDATAFC_H
