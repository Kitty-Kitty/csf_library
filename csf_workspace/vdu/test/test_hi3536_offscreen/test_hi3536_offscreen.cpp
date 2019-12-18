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
#include "QtSvg/QGraphicsSvgItem"
#include "QtSvg/QSvgRenderer"
#include "QtSvg/QSvgWidget"
#include "QtGui/QOpenGLContext"
#include "QtGui/QOpenGLPaintDevice"
#include "MyGLWidget.hpp"


QT_BEGIN_NAMESPACE
class QGraphicsSvgItem;
class QSvgRenderer;
QT_END_NAMESPACE


//默认的缓存大小
//#define		DEFAULT_BUFFER_LENGTH							50 * 1024 * 1024
#define		DEFAULT_BUFFER_LENGTH							3840 * 2160 * 4
#define		TEST_VER										"1.0"

char		svg_file[1024] = { 0, };
char		*output_file = "out.png";

//通道中处理svg xml格式数据
int read_file(char *file_name, char *buf, int buf_length)
{
	FILE					*tmp_fd;
	int						tmp_read_length = 0;



	tmp_fd = fopen(file_name, "rb");
	if (!tmp_fd) {
		printf("open file[%s] error. errno[%d] \r\n",
			file_name,
			errno);
		return -2;
	}

	tmp_read_length = fread(buf, 1, buf_length, tmp_fd);
	if (tmp_read_length <= 0) {
		printf("read file[%s] error. errno[%d] \r\n",
			file_name,
			errno);
		return -2;
	}

	if (tmp_fd) {
		fclose(tmp_fd);
	}

	return tmp_read_length;
}

int write_file(char *file_name, const char *buf, int buf_length)
{
	FILE					*tmp_fd;
	int						tmp_write_length = 0;



	tmp_fd = fopen(file_name, "wb");
	if (!tmp_fd) {
		printf("open file[%s] error. errno[%d] \r\n",
			file_name,
			errno);
		return -2;
	}

	tmp_write_length = fwrite(buf, 1, buf_length, tmp_fd);
	if (tmp_write_length != buf_length) {
		printf("write file[%s] error. write lenght[%d] errno[%d] \r\n",
			file_name,
			tmp_write_length,
			errno);
		return -2;
	}

	if (tmp_fd) {
		fclose(tmp_fd);
	}

	return 0;
}


#ifndef WIN32

#include <sys/select.h>
#include <sys/time.h>
#include <sys/types.h>
#include <unistd.h>
#include <getopt.h>

//操作提示
void usage()
{
	fprintf(stderr, "Usage:	  test_hi3536_vdu [OPTION]\n\n"
		"\t-h, --help                   print this help\n "
		"\t-v, --version                print version\n "
		"\t-f, --file [path]			svg file\n"

	);

	exit(0);
}

//设置输入配置项处理
int setopt(int argc, char *argv[])
{
	int		tmp_ret = 0;
	int		tmp_index = 0;

	const char *opt_string = "hvp:";
	struct option tmp_longopts[] = {
		{ "help", no_argument, 0, 'h' },
		{ "version", no_argument, 0, 'v' },
		{ "file", required_argument, 0, 'f' },
		{ 0, 0, 0, 0 }
	};

	while ((tmp_ret = getopt_long_only(argc, argv, opt_string, tmp_longopts, &tmp_index)) != -1) {

		switch (tmp_ret) {

		case 'h':
			usage();
			return -1;
			break;
		case 'v':
			fprintf(stderr, "%s\r\n", TEST_VER);
			exit(0);
			break;
		case 'f':
			memset(svg_file, 0, sizeof(svg_file));
			strcpy(svg_file, optarg);
			printf("get svg file[%s]\r\n", svg_file);
			break;
		default:
			usage();
			return -1;
			break;
		}
	}

	return 0;
}

#endif


char*  print_time()
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

int main(int argc, char *argv[])
{
	int							tmp_argc = 0;
	int							tmp_read_length = 0;
	char						*tmp_argv = NULL;
	char						*tmp_buf = NULL;
	QApplication				tmp_app(tmp_argc, NULL);
	//QGLWidget					*tmp_qgl_widget = NULL;
	MyGLWidget					*tmp_qgl_widget = NULL;
	//QGLFormat					tmp_format;
	QSurfaceFormat				tmp_format;
	QString						tmp_gl_type;
	QString						tmp_gl_version;



	if (argc < 2) {
		fprintf(stderr, "unknow argument error.\r\n");
		fprintf(stderr, "Usage: test_hi3536_vdu svg_file.\r\n");
		return 1;
	}

#ifdef WIN32
	strcpy(svg_file, argv[1]);
	printf("get svg file[%s]\r\n", svg_file);
#else
	if (setopt(argc, argv)) {
		fprintf(stderr, "unknow argument error.\r\n");
		usage();
		return 1;
	}
#endif

	char *tmp_buf2 = (char*)malloc(DEFAULT_BUFFER_LENGTH);
	tmp_buf = (char*)malloc(DEFAULT_BUFFER_LENGTH);
	if (!tmp_buf) {
		printf("malloc() memory[%d] error. errno:[%d]\r\n",
			DEFAULT_BUFFER_LENGTH,
			errno);
		return -1;
	}
	else {
		memset(tmp_buf, 0, DEFAULT_BUFFER_LENGTH);
	}

	printf("memcpy begin. %s", print_time());
	printf("get time. %s", print_time());

	memcpy(tmp_buf2, tmp_buf, DEFAULT_BUFFER_LENGTH);

	printf("memcpy end. %s", print_time());


	printf("program start. %s", print_time());


	tmp_read_length = read_file(svg_file, tmp_buf, DEFAULT_BUFFER_LENGTH);
	if (tmp_read_length <= 0) {
		printf("read_file[%s] error.\r\n",
			svg_file);
		return -1;
	}
	else {
		printf("read_file[%s] succeed. %s\r\n"
			, svg_file
			, print_time());
	}


#ifdef WIN32
	// 设置 OpenGL 版本信息
	// 注意: format 必须在 show() 调用前设置
	tmp_format.setRenderableType(QSurfaceFormat::OpenGL);
	tmp_format.setProfile(QSurfaceFormat::CoreProfile);
	//tmp_format.setProfile(QGLFormat::CoreProfile);
	//tmp_format.setProfile(QSurfaceFormat::CompatibilityProfile);
	tmp_format.setSwapBehavior(QSurfaceFormat::DoubleBuffer);
	tmp_format.setVersion(1, 1);
#else
	// 设置 OpenGL 版本信息
	// 注意: format 必须在 show() 调用前设置
	tmp_format.setRenderableType(QSurfaceFormat::OpenGLES);
	tmp_format.setProfile(QSurfaceFormat::CoreProfile);
	tmp_format.setDepthBufferSize(32);
	tmp_format.setStencilBufferSize(8);
	//tmp_format.setProfile(QGLFormat::CoreProfile);
	//tmp_format.setProfile(QGLFormat::CompatibilityProfile);
	//tmp_format.setProfile(QSurfaceFormat::CompatibilityProfile);
	tmp_format.setSwapBehavior(QSurfaceFormat::DoubleBuffer);
	tmp_format.setVersion(3, 1);
#endif

	//tmp_qgl_widget = new QGLWidget(QGLFormat(QGL::Rgba | QGL::AlphaChannel | QGL::DepthBuffer | QGL::DoubleBuffer | QGL::AccumBuffer | QGL::DirectRendering));
	tmp_qgl_widget = new MyGLWidget(NULL);
	//tmp_qgl_widget->swapBuffers();
	tmp_qgl_widget->setFormat(tmp_format);
	tmp_qgl_widget->setFixedSize(QSize(3840, 2160));
	//tmp_qgl_widget->setFixedSize(QSize(0, 0));
	//tmp_qgl_widget->makeCurrent();
	//tmp_qgl_widget->makeOverlayCurrent();

	//if (!tmp_qgl_widget->loadSvg(QByteArray((const char*)tmp_buf, strlen(tmp_buf)))) {
	//	printf("load svg stream error.\r\n");
	//	return -3;
	//}
	//tmp_qgl_widget->update();

	
	QGraphicsView		tmp_view;
	QGraphicsScene		tmp_scene(&tmp_view);

	tmp_view.setRenderHint(QPainter::HighQualityAntialiasing);
	tmp_scene.addWidget(tmp_qgl_widget);

	QSvgRenderer				tmp_svg_renderer;
	QPainter					tmp_painter(tmp_qgl_widget);


	tmp_painter.setRenderHints(QPainter::HighQualityAntialiasing);

	printf("load() begin! %s\r\n", print_time());

	//加载svg文件流数据
	if (!tmp_svg_renderer.load(QByteArray((const char*)tmp_buf, strlen(tmp_buf)))) {
		printf("load svg stream error.\r\n");
		return -3;
	}
	else {
		printf("load() end! %s\r\n", print_time());

		//tmp_qgl_widget->resize(tmp_svg_renderer.defaultSize());
		QSize		tmp_size = tmp_svg_renderer.defaultSize();
		tmp_qgl_widget->resize(tmp_size);
	}

	printf("render begin! %s\r\n", print_time());

	//tmp_scene->render(&tmp_painter);
	tmp_svg_renderer.render(&tmp_painter);
	//tmp_svg_renderer->render(&tmp_painter, QRectF(0, 0, 1920, 1080));

	printf("render end! %s\r\n", print_time());


	tmp_qgl_widget->grabFramebuffer().save("out.png", "PNG");

#if 0
	QImage tmp_image = tmp_qgl_widget->grabFrameBuffer(true);

	if (!tmp_image.save("out.png", "PNG")) {
		printf("save file[%s] failed!\r\n", output_file);
		return -4;
	}
	else {
		printf("save file[%s] succeed!\r\n", output_file);
	}
#endif

	free(tmp_buf);

	printf("\r\n\r\nprogram stop!!!\r\n");

	return 0;
}