#include "MyGLWidget.hpp"


#ifdef __linux__
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

QSize MyGLWidget::sizeHint() const
{
	return QSize(500, 300);
}

void MyGLWidget::initializeGL()
{
	initializeGLFunctions();
	qglClearColor(Qt::white);

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

	fbo = new QGLFramebufferObject(1920, 1080, GL_TEXTURE_2D);
	fbo->bind();
	texture_id = fbo->texture();

	QPainter painter(fbo);
	painter.setPen(Qt::red);
	font.setPointSize(80);
	painter.setFont(font);
	painter.drawText(0, 60, "Hello Word!");
	painter.end();

	fbo->toImage().save("QGLFramebufferObject.png", "PNG");

	fbo->release();
}

void MyGLWidget::resizeGL(int w, int h)
{
	glViewport(0, 0, w, h);
}

void MyGLWidget::paintGL()
{
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
}
