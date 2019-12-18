#ifndef MYVIEW_H_
#define MYVIEW_H_

#include "QtWidgets/QGraphicsView"
#include "SvgWidget.h"

class MyView : public QGraphicsView
{
  //Q_OBJECT
  SvgWidget* widget;
  QTimer* timer_;
public:
  MyView(QWidget* parent = 0);
  virtual
  ~MyView();
};

#endif /* MYVIEW_H_ */