
#include "qcustomplot.h"
#include <QApplication>
#include <QTimer>

#include "DataSet.h"
#include "DataNode.h"

#ifndef _USE_MATH_DEFINES
#define _USE_MATH_DEFINES
#endif

#include <cmath>
#include <memory>
#include <chrono>
#include <thread>

#ifndef M_PI
#define M_PI = 3.1415926535897932384626433832795028841971693993751
#endif

#include <iostream>
#include <memory>

using std::cout;
using std::cerr;
using std::endl;
using std::sin;
using std::fabs;

using namespace jono;
using std::shared_ptr;
using DataPoint = DataSet::DataPoint;

using jono::DataSet;
using dvec = jono::DataSet::dvec;

const double g_pi = M_PI;

//using namespace jono;
using namespace std;

int main(int argc, char* argv[])
{
    DataSet data;

    int data_size = 100;

    double x_begin = 0.0;
    double x_end = 2*g_pi;

    auto& points = data.getPoints();

    // set up dataset with data sampled from sine curve
    for (int i = 0; i < data_size; ++i) {
        auto p = shared_ptr<DataPoint>(new DataPoint);
        p->x.resize(1);
        p->y.resize(1);

        p->x[0] = x_begin + i * (x_end-x_begin) / data_size;
        p->y[0] = sin(p->x[0]);

        points.push_back(p);
    }

    // create root node of tree


    // error callback
    using ErrorCallback = std::function<double(const DataSet&, const dvec&)>;

    auto error_callback = [](DataSet& dset, const dvec& y) -> double
    {
        double error = 0.0;
        for (auto& point: dset.getPoints())
            error += fabs(point->y[0]-y[0]);
        return error;
    };

    // loop over depth for error comparison
    int depth = 10;

    DataNode root(data);

    root.partition(0, error_callback, depth);
    root.computeError(error_callback);

    // check that the returned error is what we expected
    if ( root.totalError() > 0.06) {
        cerr << "Test failed: 1d tree reports an error which is too large" << endl;
        return 1;
    }


    QApplication app(argc, argv);
    QCustomPlot* customPlot = new QCustomPlot();
    QTimer* timer = new QTimer();

    auto plot_ptr = shared_ptr<QCustomPlot>(customPlot);
    auto timer_ptr = shared_ptr<QTimer>(timer);

    points = data.getPoints();

    // generate some data:
    QVector<double> x(points.size()), y(points.size()); // initialize with entries 0..100
    for (int i=0; i<points.size(); ++i)
    {
      x[i] = points[i]->x[0];
      y[i] = root.predict(points[i]->x)[0]; // let's plot a quadratic function
    }
    // create graph and assign data to it:
    customPlot->addGraph();
    customPlot->graph(0)->setData(x, y);
    // give the axes some labels:
    customPlot->xAxis->setLabel("x");
    customPlot->yAxis->setLabel("y");
    // set axes ranges, so we see all data:
    customPlot->xAxis->setRange(0, 2*g_pi);
    customPlot->yAxis->setRange(-1, 1);
    customPlot->replot();

    //customPlot->show();
    customPlot->resize(500, 500);

    timer->connect(timer, SIGNAL(timeout()), customPlot, SLOT(close()));
    timer->setInterval(50);
    timer->start();


    return app.exec();
}
