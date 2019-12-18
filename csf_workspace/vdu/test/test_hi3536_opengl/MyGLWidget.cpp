
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
	//format.setRenderableType(QSurfaceFormat::OpenGL);
	//format.setProfile(QSurfaceFormat::CoreProfile);
	format.setProfile(QGLFormat::CoreProfile);
	//format.setProfile(QSurfaceFormat::CompatibilityProfile);
	format.setVersion(1, 1);
#else
	// 设置 OpenGL 版本信息
	// 注意: format 必须在 show() 调用前设置
	//format.setRenderableType(QSurfaceFormat::OpenGLES);
	//format.setProfile(QSurfaceFormat::CoreProfile);
	//format.setProfile(QGLFormat::CoreProfile);
	format.setProfile(QGLFormat::CompatibilityProfile);
	//format.setProfile(QSurfaceFormat::CompatibilityProfile);
	format.setVersion(3, 1);
#endif

	setFormat(format);
	//setFixedSize(QSize(3840, 2160));
}

void MyGLWidget::initializeGL()
{
	initializeGLFunctions();

	//初始opengl版本相关信息
	//initializeGLFormat();

	printf("qglClearColor begin! %s\r\n", print_time());

	qglClearColor(Qt::transparent);
	//qglColor(Qt::transparent);

	printf("qglClearColor end! %s\r\n", print_time());


	//qglClearColor(Qt::black);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	//glShadeModel(GL_SMOOTH);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	//glMatrixMode(GL_MODELVIEW);
	//glLoadIdentity();
	//glTranslatef(0, 0, -10);

	this->makeCurrent();

	// Initializing frame buffer object
	// Here we create a framebuffer object with the smallest necessary precision, i.e. GL_LUMINANCE in order to make
	// the subsequent calls to glReadPixels MUCH faster because the internal format is simpler and no casts are needed
	QGLFramebufferObjectFormat fboFormat;
	fboFormat.setMipmap(false);
	fboFormat.setSamples(0);
	fboFormat.setInternalTextureFormat(GL_LUMINANCE);
	// Create the framebuffer object

	QGLFramebufferObject	*fbo;

	//fbo = new QGLFramebufferObject(3840, 2160, GL_TEXTURE_2D);
	fbo = new QGLFramebufferObject(QSize(this->width(), this->height()), fboFormat);

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
}

void MyGLWidget::resizeGL(int w, int h)
{
	glViewport(0, 0, w, h);
}

void MyGLWidget::paintGL()
{
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
}
