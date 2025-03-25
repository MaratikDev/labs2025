#ifndef GRAPH_H
#define GRAPH_H

#include <QWidget>
#include <QPainter>
#include "appcontext.h"
#include "RowData.h"
#include <string.h>

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
