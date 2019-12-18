
#include "MyGLWidget.hpp"


#ifdef __linux__
#include <sys/time.h>
struct vrtx {
	GLint   x;
	GLint   y;
	GLubyte r;
	GLubyte g;
	GLubyte b;
}__attribute__((packed)) line_geo[] = {
	//   x, y,   r, g, b
	{ 1, 1, 255, 0, 0 },
	{ 1, 2, 0, 255, 0 },
	{ 1, 2, 0, 255, 0 },
	{ 2, 2, 255, 0, 0 },
	{ 2, 2, 255, 0, 0 },
	{ 2, 1, 0, 255, 0 },
	{ 2, 1, 0, 255, 0 },
	{ 1, 1, 255, 0, 0 },
};

struct txtr_vrtx {
	GLint   x;
	GLint   y;
	GLint   tx;
	GLint   ty;
}__attribute__((packed)) txtr_geo[] = {
	//   x, y, tx,ty
	{ 3, 1, 0, 0 },
	{ 3, 2, 0, 1 },
	{ 4, 2, 1, 1 },
	{ 4, 1, 1, 0 },
};

#endif




bool MyGLWidget::loadSvg(const QByteArray &contents)
{
	printf("load() begin. %s\r\n", print_time());

	if (!svgRender.load(contents))
	{
		printf("load svg stream error.\r\n");
		return false;
	}
	else
	{
		printf("load() end. %s\r\n", print_time());
	}

	//用svg文件的尺寸更新widget大小
	resize(svgRender.defaultSize());

	return true;
}

QSize MyGLWidget::sizeHint() const
{
	return QSize(500, 300);
}

char* MyGLWidget::print_time()
{
	static  char tmp_buf[128] = { 0, };

#ifndef WIN32
	struct  timeval    tv = { 0, };


	gettimeofday(&tv, NULL);

	memset(tmp_buf, 0, sizeof(tmp_buf));
	sprintf(tmp_buf, "time:%d     %d\n", tv.tv_sec, tv.tv_usec);

#endif

	return tmp_buf;
}

void MyGLWidget::initializeGLFormat()
{
#ifdef WIN32
	// 设置 OpenGL 版本信息
	// 注意: format 必须在 show() 调用前设置
	format.setRenderableType(QSurfaceFormat::OpenGL);
	format.setProfile(QSurfaceFormat::CoreProfile);
	//format.setProfile(QGLFormat::CoreProfile);
	//format.setProfile(QSurfaceFormat::CompatibilityProfile);
	format.setVersion(1, 1);
#else
	// 设置 OpenGL 版本信息
	// 注意: format 必须在 show() 调用前设置
	format.setRenderableType(QSurfaceFormat::OpenGLES);
	//format.setProfile(QSurfaceFormat::CoreProfile);
	//format.setProfile(QGLFormat::CoreProfile);
	//format.setProfile(QGLFormat::CompatibilityProfile);
	format.setProfile(QSurfaceFormat::CompatibilityProfile);
	format.setVersion(3, 1);
#endif

	setFormat(format);
	//setFixedSize(QSize(3840, 2160));
}

void MyGLWidget::initializeGL()
{
	initializeGLFunctions();

	printContextInformation();

	//初始opengl版本相关信息
	//initializeGLFormat();

	printf("qglClearColor begin! %s\r\n", print_time());

	glClearColor(0, 0, 0, 1);
	//glClear(GL_COLOR_BUFFER_BIT);
	//qglClearColor(Qt::transparent);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
	//qglColor(Qt::transparent);

	printf("qglClearColor end! %s\r\n", print_time());

#if 0

	glGenBuffers(2, vbo_id);
	glBindBuffer(GL_ARRAY_BUFFER, vbo_id[0]);

#ifdef __linux__
	glBufferData(GL_ARRAY_BUFFER, sizeof(line_geo), line_geo, GL_STATIC_DRAW);
#endif

	glBindBuffer(GL_ARRAY_BUFFER, vbo_id[1]);
#ifdef __linux__
	glBufferData(GL_ARRAY_BUFFER, sizeof(txtr_geo), txtr_geo, GL_STATIC_DRAW);
#endif

	glBindBuffer(GL_ARRAY_BUFFER, 0);       // must unbind for QPainter

	QGLFramebufferObject	*fbo;

	fbo = new QGLFramebufferObject(3840, 2160, GL_TEXTURE_2D);
	fbo->bind();
	// Construct an OpenGL pixel buffer.

	//QGLPixelBuffer	*fbo;
	//fbo = new QGLPixelBuffer(3840, 2160);
	// Make the QGLContext object bound to pixel buffer the current context
	//fbo->makeCurrent();
	QPainter painter(fbo);

#if 0
	texture_id = fbo->texture();

	QPainter painter(fbo);
	painter.setPen(Qt::red);
	font.setPointSize(80);
	painter.setFont(font);
	painter.drawText(0, 60, "Hello Word!");
	painter.end();
#endif

	printf("render begin! %s\r\n", print_time());

	svgRender.render(&painter);

	printf("render end! %s\r\n", print_time());

	fbo->toImage().save("QGLFramebufferObject.png", "PNG");

	//fbo->release();

#endif

}

void MyGLWidget::resizeGL(int w, int h)
{
	glViewport(0, 0, w, h);
}

void MyGLWidget::paintGL()
{
	glClearColor(0, 0, 0, 1);
	//glClear(GL_COLOR_BUFFER_BIT);
	//qglClearColor(Qt::transparent);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
	//glClear(GL_COLOR_BUFFER_BIT);

#if 0


#ifdef WIN32
	glClear(GL_COLOR_BUFFER_BIT);

	glLoadIdentity();
	glOrtho(0, 5, 0, 3, -1, 1);

	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_COLOR_ARRAY);

	glBindBuffer(GL_ARRAY_BUFFER, vbo_id[0]);

#ifdef __linux__
	glVertexPointer(2, GL_INT, sizeof(struct vrtx), 0);
	glColorPointer(3, GL_UNSIGNED_BYTE, sizeof(struct vrtx), ((char*)NULL + 8));
	glDrawArrays(GL_LINES, 0, sizeof(line_geo) / sizeof(struct vrtx));
#endif

	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_BLEND);
	glEnable(GL_TEXTURE_2D);

	glDisableClientState(GL_COLOR_ARRAY);
	glEnableClientState(GL_TEXTURE_COORD_ARRAY);

	glBindBuffer(GL_ARRAY_BUFFER, vbo_id[1]);
	glBindTexture(GL_TEXTURE_2D, texture_id);

#ifdef __linux__
	glVertexPointer(2, GL_INT, sizeof(struct txtr_vrtx), 0);
	glTexCoordPointer(2, GL_INT, sizeof(struct txtr_vrtx), ((char*)NULL + 8));
#endif

	glDrawArrays(GL_QUADS, 0, 4);

	glDisableClientState(GL_TEXTURE_COORD_ARRAY);
	glDisableClientState(GL_VERTEX_ARRAY);
	glDisableClientState(GL_COLOR_ARRAY);

	glDisable(GL_TEXTURE_2D);
	glDisable(GL_BLEND);

	glFlush();
#endif

#endif

}

// 打印相关信息，调试用
void MyGLWidget::printContextInformation()
{
	QString glType;
	QString glVersion;
	QString glProfile;

	// 获取版本信息
	glType = (context()->isOpenGLES()) ? "OpenGL ES" : "OpenGL";
	glVersion = reinterpret_cast<const char*>(glGetString(GL_VERSION));

	// 获取 Profile 信息
#define CASE(c) case QSurfaceFormat::c: glProfile = #c; break
	switch (format.profile())
	{
		CASE(NoProfile);
		CASE(CoreProfile);
		CASE(CompatibilityProfile);
	}
#undef CASE

	qDebug() << qPrintable(glType) << qPrintable(glVersion) << "(" << qPrintable(glProfile) << ")";
}

