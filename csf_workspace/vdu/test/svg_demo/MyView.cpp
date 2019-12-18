#include "MyView.h"
#include "QtOpenGL/QGLWidget"
#include "QtCore/QTimer"


MyView::MyView(QWidget* parent) :
    QGraphicsView(parent)
{
  setScene(new QGraphicsScene(this));

  widget = new SvgWidget(0);
  //widget->setUpBackgroundSvg(":/images/tiger.svg");
  widget->setUpBackgroundSvg("tiger.svg");
  //some more layers will be set up here
  scene()->addWidget(widget);       //from here
  setViewport(
      new QGLWidget(QGLFormat(QGL::SampleBuffers | QGL::DirectRendering)));
  setViewportUpdateMode(QGraphicsView::FullViewportUpdate);
  update();                                      //to here 
  // if the code above is disabled, it looks better but is not rendered on the cpu right?
  timer_ = new QTimer(this);
  timer_->setInterval(20);
  connect(timer_, SIGNAL(timeout()), this, SLOT(repaint()));
  timer_->start();
}

MyView::~MyView()
{
}
