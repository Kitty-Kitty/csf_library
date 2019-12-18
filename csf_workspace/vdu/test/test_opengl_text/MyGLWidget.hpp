#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <iostream>

#include "QtCore/QBuffer"
#include "QtWidgets/QApplication"
#include "QtCore/QCommandLineOption"
#include "QtCore/QCommandLineParser"
#include "QtWidgets/QGraphicsView"
#include "QtWidgets/QGraphicsRectItem"
#include "QtWidgets/QOpenGLWidget"
#include "QtOpenGL/QGLWidget"
#include "QtOpenGL/QGLFramebufferObject"
#include "QtOpenGL/QGLPixelBuffer"
#include "QtOpenGL/QGLFunctions"
#include "QtOpenGL/QGLFramebufferObject"
#include "QtSvg/QGraphicsSvgItem"
#include "QtSvg/QSvgRenderer"
#include "QtSvg/QSvgWidget"
#include "QtGui/QOpenGLContext"
#include "QtGui/QOpenGLPaintDevice"
#include "QtGui/QFont"


class MyGLWidget : public QGLWidget, protected QGLFunctions
{
public:
	MyGLWidget(QWidget *parent)
		: QGLWidget(parent) {}

public:
	QSize sizeHint() const;

protected:

	void initializeGL();
	void resizeGL(int w, int h);
	void paintGL();

private:
	QGLFramebufferObject *fbo;
	QFont font;
	quint32 vbo_id[2], texture_id;
};