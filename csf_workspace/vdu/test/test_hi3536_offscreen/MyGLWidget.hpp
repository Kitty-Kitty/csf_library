#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <iostream>

#include "QtCore/QBuffer"
#include "QtCore/QDebug"
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


class MyGLWidget : public QOpenGLWidget, protected QGLFunctions
{
public:
	MyGLWidget(QWidget *parent)
		: QOpenGLWidget(parent)
	{
		
	}

public:
	QSize sizeHint() const;
	bool loadSvg(const QByteArray &contents);

protected:
	char* print_time();
	void initializeGLFormat();
	void initializeGL();
	void resizeGL(int w, int h);
	void paintGL();
	// 打印相关信息，调试用
	void printContextInformation();
private:
	QSvgRenderer			svgRender;
	QSurfaceFormat			format;
	QFont					font;
	quint32 vbo_id[2], texture_id;
};