#include "graph.h"
#include <QPainter>
#include <QPen>
#include <QFont>
#include <cmath>

Graph::Graph(QWidget *parent) : QWidget(parent)
{
    context = nullptr;
    shouldDraw = false;
    columnInput = 0;
    fromYear = 1900;
    toYear = 2100;
    setMinimumSize(400, 250);
}

Graph::~Graph()
{
}

void Graph::setData(AppContext* context, int columnInput)
{
    this->context = context;
    this->columnInput = columnInput;
    shouldDraw = true;
}

void Graph::setFilter(const QVector<QString>& regions, int fromYear, int toYear)
{
    this->regions = regions;
    this->fromYear = fromYear;
    this->toYear = toYear;
}

void Graph::drawGraph()
{
    update();
}

double Graph::findCoefX(int width)
{
    if (toYear - fromYear == 0)
        return 1;
    return (double)(width - LEFT_BOTTOM_GRAPH_X) / (toYear - fromYear);
}

double Graph::findCoefY(int height)
{
    double range = context->tableMetrics.max - context->tableMetrics.min;
    if (range < EPS)
        return 1;
    return (height - STANDARD_COEF * 2) / range;
}

void Graph::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);

    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);
    painter.fillRect(rect(), Qt::white);

    if (!shouldDraw || !context || context->tableLogic.correctRows == 0)
        return;

    int currentWidth = width();
    int currentHeight = height();

    // Draw axes
    QPen axisPen(Qt::black, 2);
    painter.setPen(axisPen);

    // X-axis
    painter.drawLine(LEFT_BOTTOM_GRAPH_X, currentHeight - STANDARD_COEF,
                     currentWidth, currentHeight - STANDARD_COEF);

    // Y-axis
    painter.drawLine(LEFT_BOTTOM_GRAPH_X, STANDARD_COEF,
                     LEFT_BOTTOM_GRAPH_X, currentHeight - STANDARD_COEF);

    // Calculate coefficients for scaling
    double coefX = findCoefX(currentWidth);
    double coefY = findCoefY(currentHeight);

    // Draw axis labels
    QFont font = painter.font();
    font.setPointSize(8);
    painter.setFont(font);

    // X-axis labels (years)
    int stepX = (toYear - fromYear) / 10;
    if (stepX < 1) stepX = 1;

    for (int year = fromYear; year <= toYear; year += stepX)
    {
        int x = LEFT_BOTTOM_GRAPH_X + (year - fromYear) * coefX;
        painter.drawText(x - 15, currentHeight - 5, QString::number(year));
        painter.drawLine(x, currentHeight - STANDARD_COEF, x, currentHeight - STANDARD_COEF + 5);
    }

    // Y-axis labels (metrics)
    double stepY = (context->tableMetrics.max - context->tableMetrics.min) / 5;
    if (stepY < EPS) stepY = 1;

    for (double metric = context->tableMetrics.min; metric <= context->tableMetrics.max; metric += stepY)
    {
        int y = currentHeight - STANDARD_COEF - (metric - context->tableMetrics.min) * coefY;
        painter.drawText(5, y + 5, QString::number(metric, 'f', 2));
        painter.drawLine(LEFT_BOTTOM_GRAPH_X - 5, y, LEFT_BOTTOM_GRAPH_X, y);
    }

    // Prepare points for each region
    QMap<QString, QVector<QPoint>> regionPoints;
    RowData* current = context->tableLogic.head;
    while (current != NULL)
    {
        char* endptr;
        double value = strtod((char*)current->data[columnInput-1], &endptr);
        int year = strtod((char*)current->data[0], &endptr);
        QString region = QString::fromUtf8((char*)current->data[REGION_INDEX]);

        bool regionMatch = regions.isEmpty() || regions.contains(region);
        bool yearMatch = year >= fromYear && year <= toYear;
        bool validValue = endptr != current->data[columnInput-1];

        if (regionMatch && yearMatch && validValue)
        {
            int x = LEFT_BOTTOM_GRAPH_X + (year - fromYear) * coefX;
            int y = currentHeight - STANDARD_COEF - (value - context->tableMetrics.min) * coefY;
            regionPoints[region].append(QPoint(x, y));
        }
        current = current->next;
    }

    // Define colors for different regions
    QVector<QColor> regionColors = {
        Qt::blue, Qt::red, Qt::green, Qt::magenta, Qt::cyan, Qt::darkYellow
    };

    // Draw lines and points for each region
    int colorIndex = 0;
    for (auto it = regionPoints.begin(); it != regionPoints.end(); ++it)
    {
        const QVector<QPoint>& points = it.value();
        if (points.isEmpty()) continue;

        QColor regionColor = regionColors[colorIndex % regionColors.size()];
        colorIndex++;

        // Draw connecting lines
        if (points.size() > 1)
        {
            QPen linePen(regionColor, 1.5);
            painter.setPen(linePen);
            for (int i = 0; i < points.size() - 1; ++i) {
                painter.drawLine(points[i], points[i+1]);
            }
        }

        // Draw points
        QPen dataPen(regionColor, 4);
        painter.setPen(dataPen);
        for (const QPoint& point : points) {
            painter.drawEllipse(point, 3, 3);
        }

        // Add region label
        painter.drawText(points.last().x() + 5, points.last().y() - 5, it.key());
    }

    // Draw metric lines (min, max, median)
    QPen metricPen(Qt::black, 1, Qt::DashLine);
    painter.setPen(metricPen);

    // Min line
    int yMin = currentHeight - STANDARD_COEF;
    painter.drawLine(LEFT_BOTTOM_GRAPH_X, yMin, currentWidth, yMin);
    painter.drawText(currentWidth - 50, yMin - 5, "Min");

    // Max line
    int yMax = currentHeight - STANDARD_COEF - (context->tableMetrics.max - context->tableMetrics.min) * coefY;
    painter.drawLine(LEFT_BOTTOM_GRAPH_X, yMax, currentWidth, yMax);
    painter.drawText(currentWidth - 50, yMax - 5, "Max");

    // Median line
    int yMedian = currentHeight - STANDARD_COEF - (context->tableMetrics.median - context->tableMetrics.min) * coefY;
    painter.drawLine(LEFT_BOTTOM_GRAPH_X, yMedian, currentWidth, yMedian);
    painter.drawText(currentWidth - 50, yMedian - 5, "Median");

    // Draw trend line if we have enough points
    if (context->tableLogic.correctRows > 1)
    {
        QColor trendColor = (context->tableMetrics.coefB0 > 0) ? Qt::green : Qt::red;
        QPen trendPen(trendColor, 1.5, Qt::DashLine);
        painter.setPen(trendPen);

        double y1 = context->tableMetrics.coefB0 * fromYear + context->tableMetrics.coefB1;
        double y2 = context->tableMetrics.coefB0 * toYear + context->tableMetrics.coefB1;

        int x1 = LEFT_BOTTOM_GRAPH_X;
        int x2 = currentWidth;
        int yy1 = currentHeight - STANDARD_COEF - (y1 - context->tableMetrics.min) * coefY;
        int yy2 = currentHeight - STANDARD_COEF - (y2 - context->tableMetrics.min) * coefY;

        painter.drawLine(x1, yy1, x2, yy2);

        // Add trend label
        painter.drawText((x1 + x2) / 2, (yy1 + yy2) / 2,
                         QString("Trend (%1)").arg(context->tableMetrics.coefB0 > 0 ? "↑" : "↓"));
    }

    // Draw title
    font.setPointSize(10);
    painter.setFont(font);
    painter.drawText(rect(), Qt::AlignTop | Qt::AlignHCenter,
                     QString("Graph for column: %1").arg(context->tableLogic.columnName[columnInput-1]));
}

/*void Graph::clearMask()
{
    shouldDraw = false;
    update();
}*/
