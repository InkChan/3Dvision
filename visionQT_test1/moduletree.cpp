#include "moduletree.h"

moduleTree::moduleTree(QWidget *parent)
	: QTreeView(parent)
{
	moduleModel = new QStandardItemModel(10, 1);

	item = new QStandardItem("Grabber");
	item->setIcon(QIcon(":/visionQT_test/Resources/Grabber.png"));
	QStandardItem* child = new QStandardItem("Get From File");
	child->setIcon(QIcon(":/visionQT_test/Resources/symbol.png"));
	child->setEditable(false);
	child->setForeground(QBrush(QColor(21, 67, 96)));
	item->appendRow(child);
	child = new QStandardItem("Get From Camera");
	child->setIcon(QIcon(":/visionQT_test/Resources/symbol.png"));
	child->setForeground(QBrush(QColor(21, 67, 96)));
	item->appendRow(child);
	moduleModel->setItem(0, 0, item);

	item = new QStandardItem("Calibration");
	item->setIcon(QIcon(":/visionQT_test/Resources/calibration.png"));
	child = new QStandardItem("Calibration Camera");
	child->setIcon(QIcon(":/visionQT_test/Resources/symbol.png"));
	child->setForeground(QBrush(QColor(21, 67, 96)));
	item->appendRow(child);
	moduleModel->setItem(1, 0, item);

	item = new QStandardItem("Alignment");
	item->setIcon(QIcon(":/visionQT_test/Resources/align.png"));
	child = new QStandardItem("Align Images");
	child->setIcon(QIcon(":/visionQT_test/Resources/symbol.png"));
	child->setForeground(QBrush(QColor(21, 67, 96)));
	item->appendRow(child);
	moduleModel->setItem(2, 0, item);

	item = new QStandardItem("Preprocessing");
	item->setIcon(QIcon(":/visionQT_test/Resources/preprocessing.png"));
	child = new QStandardItem("Delete Outlier");
	child->setIcon(QIcon(":/visionQT_test/Resources/symbol.png"));
	child->setForeground(QBrush(QColor(21, 67, 96)));
	item->appendRow(child);
	child = new QStandardItem("Leveling Surface");
	child->setIcon(QIcon(":/visionQT_test/Resources/symbol.png"));
	child->setForeground(QBrush(QColor(21, 67, 96)));
	item->appendRow(child);
	moduleModel->setItem(3, 0, item);

	item = new QStandardItem("Processing");
	item->setIcon(QIcon(":/visionQT_test/Resources/processing.png"));
	child = new QStandardItem("Altitude Differ");
	child->setIcon(QIcon(":/visionQT_test/Resources/symbol.png"));
	child->setForeground(QBrush(QColor(21, 67, 96)));
	item->appendRow(child);
	child = new QStandardItem("Flatness");
	child->setIcon(QIcon(":/visionQT_test/Resources/symbol.png"));
	child->setForeground(QBrush(QColor(21, 67, 96)));
	item->appendRow(child);
	moduleModel->setItem(4, 0, item);

	item = new QStandardItem("Postprocessing");
	item->setIcon(QIcon(":/visionQT_test/Resources/postprocessing.png"));
	child = new QStandardItem("Zone Transfer");
	child->setIcon(QIcon(":/visionQT_test/Resources/symbol.png"));
	child->setForeground(QBrush(QColor(21, 67, 96)));
	item->appendRow(child);
	moduleModel->setItem(5, 0, item);

	item = new QStandardItem("Evaluation");
	item->setIcon(QIcon(":/visionQT_test/Resources/evaluate.png"));
	child = new QStandardItem("Conditional Branching");
	child->setIcon(QIcon(":/visionQT_test/Resources/symbol.png"));
	child->setForeground(QBrush(QColor(21, 67, 96)));
	item->appendRow(child);
	child = new QStandardItem("Valuation Area");
	child->setIcon(QIcon(":/visionQT_test/Resources/symbol.png"));
	child->setForeground(QBrush(QColor(21, 67, 96)));
	item->appendRow(child);
	child = new QStandardItem("Evaluate Expressions");
	child->setIcon(QIcon(":/visionQT_test/Resources/symbol.png"));
	child->setForeground(QBrush(QColor(21, 67, 96)));
	item->appendRow(child);
	moduleModel->setItem(6, 0, item);

	item = new QStandardItem("File Access");
	item->setIcon(QIcon(":/visionQT_test/Resources/fileaccess.png"));
	child = new QStandardItem("File Read");
	child->setIcon(QIcon(":/visionQT_test/Resources/symbol.png"));
	child->setForeground(QBrush(QColor(21, 67, 96)));
	item->appendRow(child);
	child = new QStandardItem("File Write");
	child->setIcon(QIcon(":/visionQT_test/Resources/symbol.png"));
	child->setForeground(QBrush(QColor(21, 67, 96)));
	item->appendRow(child);
	moduleModel->setItem(7, 0, item);

	item = new QStandardItem("Communication");
	item->setIcon(QIcon(":/visionQT_test/Resources/communication.png"));
	child = new QStandardItem("VISA Read");
	child->setIcon(QIcon(":/visionQT_test/Resources/symbol.png"));
	child->setForeground(QBrush(QColor(21, 67, 96)));
	item->appendRow(child);
	child = new QStandardItem("Socket Read");
	child->setIcon(QIcon(":/visionQT_test/Resources/symbol.png"));
	child->setForeground(QBrush(QColor(21, 67, 96)));
	item->appendRow(child);
	child = new QStandardItem("VISA Write");
	child->setIcon(QIcon(":/visionQT_test/Resources/symbol.png"));
	child->setForeground(QBrush(QColor(21, 67, 96)));
	item->appendRow(child);
	child = new QStandardItem("Socket Write");
	child->setIcon(QIcon(":/visionQT_test/Resources/symbol.png"));
	child->setForeground(QBrush(QColor(21, 67, 96)));
	item->appendRow(child);
	moduleModel->setItem(8, 0, item);

	item = new QStandardItem("System");
	item->setIcon(QIcon(":/visionQT_test/Resources/system.png"));
	child = new QStandardItem("Deferred Context");
	child->setIcon(QIcon(":/visionQT_test/Resources/symbol.png"));
	child->setForeground(QBrush(QColor(21, 67, 96)));
	item->appendRow(child);
	child = new QStandardItem("Get Execution Info");
	child->setIcon(QIcon(":/visionQT_test/Resources/symbol.png"));
	child->setForeground(QBrush(QColor(21, 67, 96)));
	item->appendRow(child);
	moduleModel->setItem(9, 0, item);

	this->setModel(moduleModel);
	this->setStyleSheet("font-size:13px;");
	this->setHeaderHidden(true);
}

moduleTree::~moduleTree()
{

}

int moduleTree::selectedIndex = -1;

void moduleTree::mousePressEvent(QMouseEvent *event)
{
	QTreeView::mousePressEvent(event);
	if (!indexAt(event->pos()).child(0, 0).isValid())
	{
		if (indexAt(event->pos()).parent().row() >= 0)
		{
			int row = indexAt(event->pos()).parent().row();
			selectedIndex = this->selectedIndexes()[0].row();
			if (event->button() == Qt::LeftButton)
			{
				QDrag *drag = new QDrag(this);
				QMimeData *mimeData = new QMimeData;
				QByteArray encodedData;
				//QDataStream stream(&encodedData, QIODevice::WriteOnly);
				mimeData->setData("moduletree", encodedData);
				mimeData->setText(QString::number(row) + ":" + QString::number(selectedIndex) +
					":" + moduleModel->item(row, 0)->child(selectedIndex, 0)->text());
				drag->setMimeData(mimeData);
				drag->exec(Qt::MoveAction);
			}
		}
		else
		{
			selectedIndex = -1;
		}
	}
	else
	{
		selectedIndex = -1;
	}

}
