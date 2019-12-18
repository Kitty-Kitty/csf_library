#include "SvgWidget.h"
#include "QtGui/QPainter"
#include "QtWidgets/QLayout"

SvgWidget::SvgWidget(QWidget * parent) :
    QWidget(parent),background_(this)
{
}

SvgWidget::~SvgWidget()
{
}

void
SvgWidget::setUpBackgroundSvg(QString backgroundPath)
{
  background_.load(backgroundPath);

  this->resize(background_.defaultSize());
  repaint();
}

void
SvgWidget::paintEvent(QPaintEvent *pe)
{
  if (background_.isValid())
    {
      QPainter painter(this);
      background_.render(&painter);
    }
}