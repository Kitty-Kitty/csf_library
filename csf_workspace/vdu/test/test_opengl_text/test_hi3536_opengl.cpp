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
#define		DEFAULT_BUFFER_LENGTH							50 * 1024 * 1024
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
	QApplication				*tmp_app = NULL;
	QGraphicsView				*tmp_view = NULL;
	QGraphicsScene				*tmp_scene = NULL;
	MyGLWidget					*tmp_qgl_widget = NULL;
	QGLFramebufferObject		*tmp_fb = NULL;
	QGLPixelBuffer				*tmp_pb = NULL;
	QGLFormat					tmp_format;
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

	printf("program start. %s", print_time());	

	//创建application
	try
	{
		tmp_app = new QApplication(tmp_argc, NULL);
		if (tmp_app) {
			printf(
				"create QApplication[0x%x] succeed.\r\n",
				tmp_app);
		}

#ifdef WIN32
		// 设置 OpenGL 版本信息
		// 注意: format 必须在 show() 调用前设置
		//tmp_format.setRenderableType(QSurfaceFormat::OpenGL);
		//tmp_format.setProfile(QSurfaceFormat::CoreProfile);
		tmp_format.setProfile(QGLFormat::CoreProfile);
		//tmp_format.setProfile(QSurfaceFormat::CompatibilityProfile);
		tmp_format.setVersion(1, 1);
#else
		// 设置 OpenGL 版本信息
		// 注意: format 必须在 show() 调用前设置
		//tmp_format.setRenderableType(QSurfaceFormat::OpenGLES);
		//tmp_format.setProfile(QSurfaceFormat::CoreProfile);
		//tmp_format.setProfile(QGLFormat::CoreProfile);
		tmp_format.setProfile(QGLFormat::CompatibilityProfile);
		//tmp_format.setProfile(QSurfaceFormat::CompatibilityProfile);
		tmp_format.setVersion(3, 1);
#endif

		//QCommandLineParser parser;
		//parser.addPositionalArgument("graphicssystem", "opengl", "opengl", "opengl");
		//parser.process(*(tmp_app));
	}
	catch (std::exception& e)
	{
		printf(
			"create QApplication() error. exception[%s]", e.what());
		return -2;
	}

	//创建和初始化view视图对象
	try
	{
		tmp_view = new QGraphicsView();
		if (tmp_view) {
			printf(
				"create QGraphicsView[0x%x] succeed.\r\n",
				tmp_view);

			//QOpenGLPaintDevice *qopenglpaintdevice = new QOpenGLPaintDevice();
			//QGLContext *qgl_context = new QGLContext(QGLFormat(QGL::Rgba | QGL::SampleBuffers | QGL::DirectRendering), new QOpenGLPaintDevice());
			//QGLWidget *tmp_qgl_widget = new QGLWidget(qgl_context);
			//QGLWidget *tmp_qgl_widget = new QGLWidget(QGLFormat(QGL::Rgba | QGL::SampleBuffers | QGL::DirectRendering));

			
			tmp_qgl_widget = new MyGLWidget(Q_NULLPTR);
			//tmp_qgl_widget = new QGLWidget(QGLFormat(QGL::DoubleBuffer));
			tmp_qgl_widget->setFormat(tmp_format);
			tmp_qgl_widget->setFixedSize(QSize(3840, 2160));
		}
	}
	catch (std::exception& e)
	{
		printf(
			"create QGraphicsView() error. exception[%s]\r\n", e.what());
		return -2;
	}

	//创建和初始化scene场景对象
	try
	{
		tmp_scene = new QGraphicsScene(tmp_view);

		if (tmp_scene) {
			printf(
				"create QGraphicsScene[0x%x] succeed.\r\n",
				tmp_scene);
			tmp_scene->addWidget(tmp_qgl_widget);
		}
	}
	catch (std::exception& e)
	{
		printf(
			"create QGraphicsScene() error. exception[%s]\r\n", e.what());
		return -2;
	}

	QGraphicsSvgItem			*tmp_svg_item = NULL;

	//创建和初始化svg item
	try
	{
		tmp_svg_item = new QGraphicsSvgItem();
		if (tmp_svg_item)
		{
			printf(
				"create QGraphicsSvgItem[0x%x] success.\r\n"
				, tmp_svg_item);
		}
	}
	catch (std::exception& e)
	{
		printf(
			"create QGraphicsSvgItem() error. exception[%s]\r\n"
			, e.what());
		return -2;
	}

	QSvgRenderer				*tmp_svg_renderer = NULL;

	//创建和初始化render
	try	{
		tmp_svg_renderer = new QSvgRenderer();
		if (tmp_svg_renderer) {
			printf(
				"create QSvgRenderer[0x%x] success.\r\n",
				tmp_svg_renderer);

			//设置SvgItem内容信息
  			//tmp_svg_item->setSharedRenderer(tmp_svg_renderer);
  			tmp_svg_item->setFlags(QGraphicsItem::ItemClipsToShape);
  			//tmp_svg_item->setCacheMode(QGraphicsItem::NoCache);
  			tmp_svg_item->setCacheMode(QGraphicsItem::DeviceCoordinateCache);
  			tmp_svg_item->setZValue(0);

  			tmp_scene->addItem(tmp_svg_item);
		}
	}
	catch (std::exception& e)
	{
		printf(
			"create QSvgRenderer() error. exception[%s]\r\n",
			e.what());
		return -2;
	}

	//QImage image(rect.right - rect.left, rect.bottom - rect.top, QImage::Format_ARGB32);
	//QImage tmp_image(tmp_rect.right - tmp_rect.left, tmp_rect.bottom - tmp_rect.top, tmp_fmt);
	//QImage tmp_image((uchar *)tmp_buf, 1920, 1080, QImage::Format_RGBA8888);
	//QImage tmp_image(tmp_rect.right - tmp_rect.left, tmp_rect.bottom - tmp_rect.top, tmp_fmt);
	//image.fill(0xaaA08080);  // partly transparent red-ish background
	//tmp_image.fill(Qt::transparent);

	//QOpenGLPaintDevice *qopenglpaintdevice = new QOpenGLPaintDevice(1920, 1080);

	//创建painter
	//QPainter tmp_painter(&tmp_image);
	//qopenglpaintdevice->setSize(QSize(1920, 1080));
	//QPainter tmp_painter(qopenglpaintdevice);
	QPainter tmp_painter(tmp_qgl_widget);
	//QPainter tmp_painter(tmp_fb);
	//QPainter tmp_painter(tmp_pb);

	tmp_painter.setRenderHints(QPainter::Antialiasing | QPainter::TextAntialiasing | QPainter::SmoothPixmapTransform);
	//QSvgWidget *svg_widget = new QSvgWidget();
	//QPainter tmp_painter(svg_widget);


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

	//加载svg文件流数据
	if (!tmp_svg_renderer->load(QByteArray((const char*)tmp_buf, strlen(tmp_buf)))) {
		printf("load svg stream error.\r\n");
		return -3;
	}
	else {
		printf("load() succeed. %s\r\n", print_time());

		//tmp_svg_item->setSharedRenderer(tmp_svg_renderer);
		tmp_qgl_widget->resize(tmp_svg_renderer->defaultSize());

//		tmp_svg_item->setSharedRenderer(tmp_svg_renderer);
// 		tmp_svg_item->setFlags(QGraphicsItem::ItemClipsToShape);
// 		//tmp_svg_item->setCacheMode(QGraphicsItem::NoCache);
// 		tmp_svg_item->setCacheMode(QGraphicsItem::DeviceCoordinateCache);
// 		tmp_svg_item->setZValue(0);
// 		tmp_svg_item->setCachingEnabled(true);
// 		tmp_svg_item->setMaximumCacheSize(QSize(3840, 2160));
// 
// 		tmp_scene->addItem(tmp_svg_item);
	}

	printf("render begin! %s\r\n", print_time());

	//tmp_scene->render(&tmp_painter);
	tmp_svg_renderer->render(&tmp_painter);
	//tmp_svg_renderer->render(&tmp_painter, QRectF(0, 0, 1920, 1080));


	printf("render end! %s\r\n", print_time());

	//QImage tmp_image = tmp_qgl_widget->grabFrameBuffer(true);

#if 0
	if (!tmp_image.save("out.png", "PNG")) {
		printf("save file[%s] failed!\r\n", output_file);
		return -4;
	}
	else {
		printf("save file[%s] succeed!\r\n", output_file);
	}
#endif

#if 0
	//释放资源
	delete tmp_svg_renderer;
	delete tmp_svg_item;
	delete tmp_scene;
	delete tmp_view;
	delete tmp_qgl_widget;
	delete tmp_app;
#endif
	free(tmp_buf);

	printf("\r\n\r\nprogram stop!!!\r\n");

	return 0;
}