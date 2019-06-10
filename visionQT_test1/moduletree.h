#ifndef MODULETREE_H
#define MODULETREE_H

#include <QTreeView>
#include <QMouseEvent>
#include <QDrag>
#include <QMimeData>
#include <qstandarditemmodel.h>
#include <qicon.h>

class moduleTree : public QTreeView
{
	Q_OBJECT

public:
	moduleTree(QWidget *parent);
	~moduleTree();
	static int selectedIndex;

protected:
	void mousePressEvent(QMouseEvent *event) Q_DECL_OVERRIDE;

private:
	QStandardItem *item;
	QStandardItemModel *moduleModel;
};

#endif // MODULETREE_H