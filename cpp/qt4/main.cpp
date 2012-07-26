#include <iostream>
#include <QApplication>
#include <QWidget>
#include <QTextStream>

int main(int argc, char **argv) {
  QApplication app(argc, argv);
  QWidget window;
  window.resize(250, 150);
  window.setWindowTitle("Simple example");
  window.show();
  QTextStream out(stdout);
  out << "application starting ... " << endl;
  int retVal =  app.exec();
  out << "application ended ...\n";
  return retVal;
}
