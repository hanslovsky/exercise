#include <iostream>
#include <QApplication>
#include <QWidget>
#include <QTextStream>
#include <QImage>
#include <QtGui>
#include <QCursor>
#include <QPushButton>
#include <QFile>

#include <own/mandelbrot.hxx>



int main(int argc, char **argv) {
  /*
  // create basic app
  QApplication app(argc, argv);
  // QWidget window;
  // window.resize(250, 150);
  // window.setWindowTitle("Simple example");
  // window.show();
  QTextStream out(stdout);
  QCursor cursor;
  

  Complex offset(0, 0);
  Mandelbrot brot(-0.72, -0.7, 0.24, 0.26, 100, 100, 1000, offset, 4);
  try {
    brot.fillGrid();
  }
  catch(...) {
    std::cout << "enhance < 1\n";
  }
  brot.writeImage("test.png");

  // add image to app
  int WIDTH = 400;
  int HEIGHT = 300;
  QWidget* main = new QWidget();
  main->setGeometry(200, 200, WIDTH, HEIGHT);
  main->show();
  QWidget *test1 = new QWidget(main);
  test1->show();
  QImage Mandel;
  Mandel.load("test.png");
  QGraphicsPixmapItem item(QPixmap::fromImage(Mandel));
  QGraphicsScene* scene = new QGraphicsScene(main);
  scene->addItem(&item);  
  QGraphicsView *view = new QGraphicsView(scene);

  view->show();
  // scene->show();
  

  // start app
  out << "starting application ... " << endl;
  out << cursor.pos().x() << " " << cursor.pos().y() << endl;
  int retVal =  app.exec();
  out << "application ended ...\n";
  return retVal;*/
  QFile data("bla");
  if (data.open(QFile::WriteOnly)) {
    QTextStream out(&data);
    out << "bla" << endl;
  }
  return 0;
}
