#ifndef OPENGLWINDOW_H
#define OPENGLWINDOW_H
#include <qopenglwidget.h>
#include <qopenglfunctions.h>
#include <qopenglbuffer.h>
#include <qopengltexture.h>
#include <qopenglshaderprogram.h>
#include <qevent.h>

#define PROGRAM_VERTEX_ATTRIBUTE 0
#define PROGRAM_TEXCOORD_ATTRIBUTE 1

class OpenGLWindow : public QOpenGLWidget, protected QOpenGLFunctions
{
	Q_OBJECT

public:
	explicit OpenGLWindow(QWidget *parent);
	~OpenGLWindow();

	QSize minimumSizeHint() const Q_DECL_OVERRIDE;
	QSize sizeHint() const Q_DECL_OVERRIDE;
	void setClearColor(const QColor &color);
	void rotateBy(int xAngle, int yAnlge, int zAnlge);

signals:
	void clicked();

protected:
	void initializeGL() Q_DECL_OVERRIDE;
	void paintGL() Q_DECL_OVERRIDE;
	void resizeGL(int width, int height) Q_DECL_OVERRIDE;
	void mousePressEvent(QMouseEvent *event) Q_DECL_OVERRIDE;
	void mouseMoveEvent(QMouseEvent *event) Q_DECL_OVERRIDE;
	void mouseReleaseEvent(QMouseEvent *event) Q_DECL_OVERRIDE;

private:
	void makeObject();

	QColor clearColor;
	QPoint lastPos;
	int xRot;
	int yRot;
	int zRot;
	QOpenGLTexture *textures[6];
	QOpenGLShaderProgram *program;
	QOpenGLBuffer vbo;
};

#endif // OPENGLWINDOW_H
