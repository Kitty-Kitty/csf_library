#include "QtWidgets/QApplication"
#include "QtCore/QCommandLineOption"
#include "QtCore/QCommandLineParser"
#include "MyView.h"


int
main(int argc, char *argv[])
{

  QApplication app(argc, argv);
  MyView myView(0);
  myView.repaint();
  myView.show();
  return app.exec();

}