#include "qcustomplot.h"
#include <QApplication>
#include <QTimer>

#include <memory>
#include <chrono>
#include <thread>

//using namespace jono;
using namespace std;

int main(int argc, char* argv[])
{
    QApplication app(argc, argv);
    QCustomPlot* customPlot = new QCustomPlot();
    QTimer* timer = new QTimer();

    auto plot_ptr = shared_ptr<QCustomPlot>(customPlot);
    auto timer_ptr = shared_ptr<QTimer>(timer);


    // generate some data:
    QVector<double> x(101), y(101); // initialize with entries 0..100
    for (int i=0; i<101; ++i)
    {
      x[i] = i/50.0 - 1; // x goes from -1 to 1
      y[i] = x[i]*x[i]; // let's plot a quadratic function
    }
    // create graph and assign data to it:
    customPlot->addGraph();
    customPlot->graph(0)->setData(x, y);
    // give the axes some labels:
    customPlot->xAxis->setLabel("x");
    customPlot->yAxis->setLabel("y");
    // set axes ranges, so we see all data:
    customPlot->xAxis->setRange(-1, 1);
    customPlot->yAxis->setRange(0, 1);
    customPlot->replot();

    //customPlot->show();
    customPlot->resize(500, 500);

    timer->connect(timer, SIGNAL(timeout()), customPlot, SLOT(close()));
    timer->setInterval(50);
    timer->start();

    return app.exec();
}
