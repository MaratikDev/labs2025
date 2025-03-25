#include "graph.h"

Graph::Graph(QWidget *parent) : QWidget(parent),context(NULL), shouldDraw(false), columnInput(0) {}

Graph::~Graph() {}

void Graph::setData(AppContext* context, int columnInput) {
    this->context = context;
    this->columnInput = columnInput;

}
void Graph::drawGraph(){
    shouldDraw = true;
    update();
}

void Graph::paintEvent(QPaintEvent *event) {
    Q_UNUSED(event);

    if(!shouldDraw)
        return;
    QPainter painter(this);

    // График (если что, я сам эти комменты пишу что б читать код легче было)
    int width = this->width();
    int height = this->height(); //250
    int leftBottomX = 45;
    int leftBottomY = height;
    painter.setPen(QPen(Qt::black, 2, Qt::SolidLine));
    painter.drawLine(leftBottomX,height/2, width-leftBottomX,height/2);  //  X
    painter.drawLine(leftBottomX,leftBottomY, leftBottomX,0);  //  Y


    // Подписи
    painter.setPen(QPen(Qt::black, 2, Qt::SolidLine));
    painter.drawText(leftBottomX + width/2 - 50, height/2+25, QString("%1").arg(context->tableLogic.columnName[0]));
    painter.rotate(-90);
    painter.drawText(-130, 10, QString("%1").arg(context->tableLogic.columnName[columnInput-1]));
    painter.rotate(90);
    for(int i = leftBottomY;i>=0;i-=25){
        painter.drawText(   20,i,  QString("%1").arg( int( (height/2-i)/findCoef() ) )  ); //можно убрать int и тогда цена деления будет психо
    }


    char* endptr;
    RowData* current = context->tableLogic.head;
    int year;
    double metric;
    int lastYear;
    double lastMetric;
    bool isStart = false;
    bool hasBeen = false;
    double b0 = context->tableMetrics.coefB0;
    double b1 = context->tableMetrics.coefB1;

    //это типо если тренд восходящий то зелененькое а если нет то красное
    if(context->tableMetrics.coefB0>=0){
        painter.setPen(QPen(Qt::green, 3, Qt::SolidLine));
    }
    else{
        painter.setPen(QPen(Qt::red, 3, Qt::SolidLine));
    }

    //линия тренда (это тип доп задание)
    painter.drawLine(leftBottomX+(context->tableMetrics.minYear-context->tableMetrics.minYear)*25,height/2-(context->tableMetrics.minYear*b0+b1)*findCoef(),
                     leftBottomX+(context->tableMetrics.maxYear-context->tableMetrics.minYear)*25,height/2-(context->tableMetrics.maxYear*b0+b1)*findCoef());

    painter.setPen(QPen(Qt::blue, 3, Qt::SolidLine));
    while(current->next!=NULL){
        if(strlen(context->filterRegion) == 0 || strcmp(context->filterRegion,(char*)current->data[REGION_INDEX])== 0 ){
            year = (int)strtod((char*)current->data[0],&endptr);
            metric = strtod((char*)current->data[columnInput-1],&endptr);
            if (isStart && strlen(context->filterRegion)!=0){
                painter.drawLine(leftBottomX+(year-context->tableMetrics.minYear)*25,height/2-metric*findCoef(),
                                 leftBottomX+(lastYear-context->tableMetrics.minYear)*25,height/2-lastMetric*findCoef());
            }
            lastYear = year;
            lastMetric = metric;
            painter.drawPoint(leftBottomX+(year-context->tableMetrics.minYear)*25,height/2-metric*findCoef());

            isStart = true;
        }
        //алгортим что б год писался только в определенном интервале и тольео один раз
        if(year % 5 == 0){
            if(!hasBeen){
                painter.setPen(QPen(Qt::black, 2, Qt::SolidLine));
                painter.drawText(leftBottomX+(year-context->tableMetrics.minYear-0.5)*25,height/2+10,QString((char*)current->data[0]));
                painter.setPen(QPen(Qt::blue, 2, Qt::SolidLine));
                hasBeen = true;
            }
        }
        else{
            hasBeen = false;
        }
        current = current->next;
    }


}
//это стандартный коэфицент,что б из значений метрик переводить в пиксели
double Graph::findCoef(){
    double result = 1;
    while(context->tableMetrics.max*result - context->tableMetrics.min*result < 80){
        result*=1.1;
    }
    while(context->tableMetrics.max*result > 100){
        result/=1.1;
    }
    return result;
}
//это для цены деления на графике
double Graph::findCoefMetric(){
    int result = 1;
    while(abs(context->tableMetrics.avgMetric)/result != 0){
        result*=5;
    }
    return result;

}


