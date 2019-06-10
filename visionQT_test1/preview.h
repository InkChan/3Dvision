#ifndef PREVIEW_H
#define PREVIEW_H

#include <QGraphicsView>
#include <QDragEnterEvent>
#include <QMimeData>
#include <qpushbutton.h>
#include <qrubberband.h>
#include "mylineedit.h"
#include "flowline.h"
#include "litcontrol.h"
#include "customwidget.h"

class Preview : public QWidget//QGraphicsView
{
	Q_OBJECT

public:
	Preview(qint16 sizew, qint16 sizeh, QWidget *parent);
	~Preview();

signals:
	void triggerLine();
	void dragLineSignal(int);
	void deleteLine();

protected:
	void dragEnterEvent(QDragEnterEvent *event) Q_DECL_OVERRIDE;
	void dragMoveEvent(QDragMoveEvent *event) Q_DECL_OVERRIDE;
	void dropEvent(QDropEvent *event) Q_DECL_OVERRIDE;
	void paintEvent(QPaintEvent *event) Q_DECL_OVERRIDE;
	void dragLeaveEvent(QDragLeaveEvent *event) Q_DECL_OVERRIDE;

	void mouseDoubleClickEvent(QMouseEvent *);

	void test(QObject*);

	//void mousePressEvent(QMouseEvent *event);
	//void mouseMoveEvent(QMouseEvent *event);
	//void mouseReleaseEvent(QMouseEvent *event);

private slots:
	void deleonebt(MyLineEdit *);
	void AddLine();
	void dragLineSlot(int);

private:
	int findPiece(const QRect &pieceRect) const;
	const QRect targetSquare(const QPoint &position) const;
	const QRect targetSquare2(const QPoint &position) const;
	QList<QRect> pieceRects;
	QList<MyLineEdit*> pieceButton;
	QList<flowLine*> customControlLine;
	QRect highlightedRect;
	qint16 mW;
	qint16 mH;
	QString lastObjName;
	LitControl *litcontro;
};

#endif // PREVIEW_H