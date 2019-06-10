#ifndef MYLINEEDIT_H
#define MYLINEEDIT_H

#include <QMouseEvent>
#include <QDrag>
#include <QMimeData>
#include <QLineEdit>
#include <QAction>
#include <QContextMenuEvent>
#include <QMenu>
#include <moudlewidget.h>

enum SensorTool
{
	get_from_file = 0,
	get_from_camera = 1,
	calibration_camera = 2,
	align_images = 3,
	delete_outlier = 4,
	leveling_surface = 5,
	altitude_differ = 6,
	flatness = 7,
	zone_transfer = 8,
	conditional_branching = 9,
	valuation_area = 10,
	evaluate_expressions = 11,
	file_read = 12,
	file_write = 13,
	visa_read = 14,
	socket_read = 15,
	visa_write = 16,
	socket_write = 17,
	deferred_context = 18,
	get_execution_info = 19
};

class MyLineEdit : public QLineEdit
{
	Q_OBJECT

public:
	MyLineEdit(QWidget *parent);
	~MyLineEdit();
	bool Ischoose = false;
	bool hasChild = false;
	QPoint centerPos;
	QList<int> childIndex;

	void setTool(SensorTool _tool);
	void setTool(QString _toolname);

protected:
	void mousePressEvent(QMouseEvent *event) Q_DECL_OVERRIDE;
	void contextMenuEvent(QContextMenuEvent* e) Q_DECL_OVERRIDE;
	void mouseDoubleClickEvent(QMouseEvent *);

signals:
	void s_deletthis(MyLineEdit *);

public slots:
	void delet();

private:
	QAction *Act_Dele;
	SensorTool Tool;
};

#endif // MYLINEEDIT_H
