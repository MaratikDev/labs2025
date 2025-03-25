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
    double width = this->width();
    int height = this->height(); //HEIGHT
    int leftBottomX = 45*(width/WIDTH);
    int leftBottomY = height;
    painter.setPen(QPen(Qt::black, 2, Qt::SolidLine));
    painter.drawLine(leftBottomX,height/2, width,height/2);  //  X
    painter.drawLine(leftBottomX,leftBottomY, leftBottomX,0);  //  Y


    // Подписи
    painter.setPen(QPen(Qt::black, 2, Qt::SolidLine));
    painter.drawText((leftBottomX + width/2 - 50*(width/WIDTH)), height/2+STANDARD_COEF, QString("%1").arg(context->tableLogic.columnName[0]));
    painter.rotate(-90);
    painter.drawText(-130, 10*(width/WIDTH), QString("%1").arg(context->tableLogic.columnName[columnInput-1]));
    painter.rotate(90);
    //for(int i = leftBottomY;i>=0;i-=STANDARD_COEF){
    //    painter.drawText(   20,i,  QString("%1").arg( int( (height/2-i)/findCoef() ) )  ); //можно убрать int и тогда цена деления будет психо
    //}
    for(int i = leftBottomY;i>=0;i-=STANDARD_COEF){
        painter.drawText( 20*(width/WIDTH),i,  QString("%1").arg((height/2-i)*findCoefMetric()/PIXEL_TO_METRIC)    );
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

    //линия тренда (это типо доп задание)
    painter.drawLine(leftBottomX+(context->tableMetrics.minYear-context->tableMetrics.minYear)*STANDARD_COEF*(width/WIDTH),height/2-(context->tableMetrics.minYear*b0+b1)*PIXEL_TO_METRIC/findCoefMetric(),
                     leftBottomX+(context->tableMetrics.maxYear-context->tableMetrics.minYear)*STANDARD_COEF*(width/WIDTH),height/2-(context->tableMetrics.maxYear*b0+b1)*PIXEL_TO_METRIC/findCoefMetric());

    painter.setPen(QPen(Qt::blue, 3, Qt::SolidLine));
    while(current->next!=NULL){
        if(strlen(context->filterRegion) == 0 || strcmp(context->filterRegion,(char*)current->data[REGION_INDEX])== 0 ){
            year = (int)strtod((char*)current->data[0],&endptr);
            metric = strtod((char*)current->data[columnInput-1],&endptr);
            if (isStart && strlen(context->filterRegion)!=0){
                painter.drawLine(leftBottomX+(year-context->tableMetrics.minYear)*STANDARD_COEF*(width/WIDTH),height/2-metric*PIXEL_TO_METRIC/findCoefMetric(),
                                 leftBottomX+(lastYear-context->tableMetrics.minYear)*STANDARD_COEF*(width/WIDTH),height/2-lastMetric*PIXEL_TO_METRIC/findCoefMetric());
            }
            lastYear = year;
            lastMetric = metric;
            painter.drawPoint(leftBottomX+(year-context->tableMetrics.minYear)*STANDARD_COEF*(width/WIDTH),height/2-metric*PIXEL_TO_METRIC/findCoefMetric());

            isStart = true;
        }
        //алгортим что б год писался только в определенном интервале и тольео один раз
        if(year % 5 == 0){
            if(!hasBeen){
                painter.setPen(QPen(Qt::black, 2, Qt::SolidLine));
                painter.drawText(leftBottomX+(year-context->tableMetrics.minYear-0.5)*STANDARD_COEF*(width/WIDTH),height/2+10,QString((char*)current->data[0]));
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

double Graph::findCoefMetric(){
    double result = 1;
    while((HEIGHT/2-context->tableMetrics.min*PIXEL_TO_METRIC/result)-(HEIGHT/2-context->tableMetrics.max*PIXEL_TO_METRIC/result) < 40){
        result/=1.2;
    }
    while((HEIGHT/2-context->tableMetrics.max*PIXEL_TO_METRIC/result < 0 ) || (HEIGHT/2-context->tableMetrics.min*PIXEL_TO_METRIC/result > HEIGHT)){
        result*=1.2;
    }
    return ceil(result);
}


