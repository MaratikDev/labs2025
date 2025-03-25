#ifndef GRAPH_H
#define GRAPH_H

#include <QWidget>
#include <QPainter>
#include "appcontext.h"
#include "RowData.h"
#include <string.h>

#define LEFT_BOTTOM_GRAPH_X 45
#define STANDARD_COEF 25
#define PIXEL_TO_METRIC 100
#define HEIGHT 250
#define WIDTH 782
#define NULL_GRAPH 125

class Graph : public QWidget
{
    Q_OBJECT

public:
    explicit Graph(QWidget *parent = 0);
    ~Graph();

    void setData(AppContext* context, int columnInput);
    void drawGraph();
    double findCoef();
    double findCoefMetric();
protected:
    void paintEvent(QPaintEvent *event) override;

private:
    AppContext* context;
    bool shouldDraw;
    int columnInput;
};

#endif // GRAPH_H
