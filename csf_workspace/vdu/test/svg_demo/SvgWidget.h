#ifndef SVGWIDGET_H_
#define SVGWIDGET_H_
 
#include "QtWidgets/QWidget"
#include "QtSvg/QSvgRenderer"
 
/*!
 * @brief This class represents a little extension of the QWidget to display a svg as a backgroundimage.
 */
class SvgWidget : public QWidget
{
public:
  /*!
   *Constructor with given parent Widget
   * @param parent is the parent widget
   */
  SvgWidget(QWidget * parent);
  ~SvgWidget();
 
  /*!
   * Sets the background to be displayed and resizes the widget to the
   * background's size.
   * repaints the widget if background is changed
   * @param backgroundPath the path to the svg for the background
   */
  void
  setUpBackgroundSvg(QString backgroundPath);
 
protected:
  /*!
   * Paints the background of the widget.
   * @param pe
   */
  void
  paintEvent(QPaintEvent *pe);
 
private:
  /*!
   * Renderer for the background
   */
  QSvgRenderer background_;
};
 
#endif /* SVGWIDGET_H_ */