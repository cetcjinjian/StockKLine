#include "klinegrid.h"
#include <QMessageBox>


#include <QPainter>
#include <QPen>
#include <QKeyEvent>
#include <QMouseEvent>
#include <QVector>
#include <QDockWidget>
#include <QWidget>
#include "mainwindow.h"

KLineGrid::KLineGrid(QWidget *parent) : AutoGrid(parent)
{
    //开启鼠标追踪
    setMouseTracking(true);

    initial();
}
bool KLineGrid::readData(QString strFile)
{
    if( mDataFile.readData(strFile) )
        return true;
    else
        return false;
}


KLineGrid::~KLineGrid()
{
    delete mShowDrtail;
    mShowDrtail = nullptr;
}

void KLineGrid::initial()
{

    //读取数据
    QString file = tr("dataKLine.txt");
    if( !mDataFile.readData(file) )
    {
        QMessageBox::about(this,tr("数据文件读取失败"),tr("确定"));
        return ;
    }
    //开启鼠标追踪
    setMouseTracking(true);
    //初始化一些成员变量

    endDay = mDataFile.kline.size() - 1;
    totalDay = 200;
    beginDay  = endDay - totalDay;
    currentDay = beginDay + totalDay /2;
    if( beginDay < 0)
    {
        beginDay = 0;
        totalDay = mDataFile.kline.size();
    }
    highestBid = 0;
    lowestBid = 1000;
    maxVolume = 0;


    //构造详情展示页面

    /*
        mShowDrtail = new ShowDetail(this);
        //mShowDrtail->setFeatures(QDockWidget::DockWidgetFloatable | QDockWidget::DockWidgetClosable);
        mShowDrtail->setFeatures(QDockWidget::QDockWidget::DockWidgetVerticalTitleBar);
        QWidget* main = this->parentWidget() ;
        static_cast<MainWindow*>(main)->addDockWidget(Qt::AllDockWidgetAreas,mShowDrtail);
        QWidget* titleWidget = new QWidget(this);
        //mShowDrtail->setTitleBarWidget( titleWidget );
        mShowDrtail->resize(50,100);
        //mShowDrtail->setGeometry(20,20,100,300);
        //mShowDrtail->move(20,20);
    */


    //构造详细数据展示页面
    mShowDrtail = new ShowDetail(this);
    mShowDrtail->setModal(false);
    mShowDrtail->setFixedSize(140,700);
    mShowDrtail->show();

    //mShowDrtail->setFeatures(QDockWidget::DockWidgetFloatable | QDockWidget::DockWidgetMovable);
    QWidget* main = this->parentWidget() ;
    //static_cast<MainWindow*>(main)->addDockWidget(Qt::LeftDockWidgetArea,mShowDrtail);
    //delete main;

}


void KLineGrid::paintEvent(QPaintEvent *event)
{
    AutoGrid::paintEvent(event);

    //画k线
    drawLine();
}


void KLineGrid::drawLine()
{
    //获取y轴指标
    getIndicator();

    //显示y轴价格
    drawYtick();

    //画k线
    drawKline();


    //画十字线
    if( !isKeyDown && bCross)
    {
        drawCross2();
    }

    if(isKeyDown && bCross)
    {
        drawCross();
    }


    //画5日均线
    drawAverageLine(5);
    //画5日均线
    drawAverageLine(10);
    //画5日均线
    drawAverageLine(20);
    //画5日均线
    drawAverageLine(30);
    //画5日均线
    drawAverageLine(60);

}


void KLineGrid::getIndicator()
{

    highestBid = 0;
    lowestBid = 1000;
    maxVolume = 0;

    for( int i= beginDay;i<endDay;++i)
    {
        if( mDataFile.kline[i].highestBid > highestBid )
            highestBid = mDataFile.kline[i].highestBid;
        if( mDataFile.kline[i].lowestBid < lowestBid )
            lowestBid = mDataFile.kline[i].lowestBid;
//        if( mDataFile.kline[i].totalVolume.toFloat() > maxVolume )
//            maxVolume = mDataFile.kline[i].totalVolume.toFloat();
    }
}

void KLineGrid::drawYtick()
{
    QPainter painter(this);
    QPen     pen;
    pen.setColor(Qt::red);
    painter.setPen(pen);

    double ystep = (highestBid - lowestBid)/ getHGridNum();
    QString str;


    if( 0 == getHGridNum() )
    {
        str.sprintf("%.2f",lowestBid);
        painter.drawText( QPoint( getWidgetWidth() - getMarginLeft() + 10,
                                  getWidgetHeight() - getMarginBottom() ),
                          str);
        str.sprintf("%.2f",highestBid);
        painter.drawText( QPoint( getWidgetWidth() - getMarginLeft() + 10,
                                  getMarginTop() ),
                          str);
        return;
    }

    for( int i=0;i<=getHGridNum();++i)
    {
        str.sprintf("%.2f",lowestBid+ i*ystep);
        painter.drawText( QPoint( getWidgetWidth() - getMarginLeft() + 10,
                                  getWidgetHeight() - getMarginBottom() - i*getAtomGridHeight()),
                          str);
    }
}

void KLineGrid::drawKline()
{
    QPainter painter(this);
    QPen     pen;
    pen.setColor(Qt::red);
    painter.setPen(pen);


    if (beginDay <0)
        return;

    //y轴缩放
    yscale = getGridHeight() / (highestBid -lowestBid ) ;

    //画笔的线宽
    lineWidth;

    //画线连接的两个点
    QPoint p1;
    QPoint p2;

    QPoint p3;
    QPoint p4;

    double xstep = getGridWidth() / totalDay;

    for( int i= beginDay;i<endDay;++i)
    {
        if( mDataFile.kline[i].openingPrice > mDataFile.kline[i].closeingPrice )
            pen.setColor(QColor(85,252,252));
        else
            pen.setColor(Qt::red);


        lineWidth = getGridWidth() / totalDay;

        //为了各个k线之间不贴在一起，设置一个间隔
        lineWidth = lineWidth - 0.2*lineWidth;

        //最小线宽为3
        if( lineWidth < 3)
            lineWidth = 3;



        //阴线

        if( mDataFile.kline[i].openingPrice > mDataFile.kline[i].closeingPrice )
        {
            //画开盘与收盘之间的粗实线
            pen.setWidth(lineWidth);
            painter.setPen(pen);
            p1.setX( getMarginLeft() + xstep *(i - beginDay) + 0.5*lineWidth);
            p1.setY( getWidgetHeight() - (mDataFile.kline[i].openingPrice - lowestBid) *yscale - getMarginBottom());
            p2.setX( getMarginLeft() + xstep *(i - beginDay) + 0.5*lineWidth);
            p2.setY( getWidgetHeight() - (mDataFile.kline[i].closeingPrice - lowestBid) *yscale - getMarginBottom() - 0.5*lineWidth);
            painter.drawLine(p1,p2);


            //画最高价与最低价之间的细线
            pen.setWidth(1);
            painter.setPen(pen);
            p1.setX( getMarginLeft() + xstep *(i - beginDay) + 0.5*lineWidth);
            p1.setY( getWidgetHeight() - (mDataFile.kline[i].highestBid - lowestBid) *yscale - getMarginBottom());
            p2.setX( getMarginLeft() + xstep *(i - beginDay) + 0.5*lineWidth);
            p2.setY( getWidgetHeight() - (mDataFile.kline[i].lowestBid - lowestBid) *yscale - getMarginBottom());
            painter.drawLine(p1,p2);


        }
        else
        {
            //像同花顺一样阳线画成空心的

            pen.setWidth(1);
            painter.setPen(pen);


            p1.setX( getMarginLeft() + xstep *(i - beginDay) );
            p1.setY( getWidgetHeight() - (mDataFile.kline[i].openingPrice - lowestBid) *yscale - getMarginBottom());

            p2.setX( getMarginLeft() + xstep *(i - beginDay) + lineWidth);
            p2.setY( getWidgetHeight() - (mDataFile.kline[i].openingPrice - lowestBid) *yscale - getMarginBottom());


            p3.setX( getMarginLeft() + xstep *(i - beginDay) );
            p3.setY( getWidgetHeight() - (mDataFile.kline[i].closeingPrice - lowestBid) *yscale - getMarginBottom());

            p4.setX( getMarginLeft() + xstep *(i - beginDay) + lineWidth);
            p4.setY( getWidgetHeight() - (mDataFile.kline[i].closeingPrice - lowestBid) *yscale - getMarginBottom());

            painter.drawLine(p1,p2);
            painter.drawLine(p1,p3);
            painter.drawLine(p2,p4);
            painter.drawLine(p3,p4);


            //画最高价与最低价之间的细线
            pen.setWidth(1);
            painter.setPen(pen);
            p1.setX( getMarginLeft() + xstep *(i - beginDay) + 0.5*lineWidth);
            p1.setY( getWidgetHeight() - (mDataFile.kline[i].highestBid - lowestBid) *yscale - getMarginBottom());


            double y1,y2;
            if( mDataFile.kline[i].openingPrice > mDataFile.kline[i].closeingPrice )
            {
                y1 = mDataFile.kline[i].openingPrice;
                y2 = mDataFile.kline[i].closeingPrice;
            }
            else
            {
                y1 = mDataFile.kline[i].closeingPrice;
                y2 = mDataFile.kline[i].openingPrice;
            }

            p2.setX( getMarginLeft() + xstep *(i - beginDay) + 0.5*lineWidth);
            p2.setY( getWidgetHeight() - (y1 - lowestBid) *yscale - getMarginBottom());
            p3.setX(getMarginLeft() + xstep *(i - beginDay) + 0.5*lineWidth);
            p3.setY( getWidgetHeight() - (y2 - lowestBid) *yscale - getMarginBottom());
            p4.setX(getMarginLeft() + xstep *(i - beginDay) + 0.5*lineWidth);
            p4.setY(getWidgetHeight() - (mDataFile.kline[i].lowestBid - lowestBid) *yscale - getMarginBottom());

            painter.drawLine(p1,p2);
            painter.drawLine(p3,p4);
        }


    }
}

void KLineGrid::keyPressEvent(QKeyEvent *event)
{
    currentDay = (double)( mousePoint.x() - getMarginLeft() ) / (getGridWidth()) * totalDay + beginDay;

    isKeyDown = true;
    switch(event->key())
    {
    case Qt::Key_Left:
    {
        double xstep = getGridWidth() / totalDay ;

        if( mousePoint.x() - xstep < getMarginLeft())
        {
            if( beginDay -1 < 0)
                return;
            endDay -= 1;
            beginDay -= 1;
        }
        else
            mousePoint.setX(mousePoint.x() - xstep);

        update();
        break;
    }

    case Qt::Key_Right:
    {
        double xstep = getGridWidth() / totalDay ;

        if( mousePoint.x() + xstep > getWidgetWidth() - getMarginRight())
        {
            if( endDay +1 > mDataFile.kline.size() -1)
                return;
            endDay += 1;
            beginDay += 1;
        }
        else
            mousePoint.setX(mousePoint.x() + xstep);


        update();
        break;
    }

    case Qt::Key_Up:
    {
        totalDay = totalDay /2;

        //最少显示10个
        if( totalDay < 10)
        {
            totalDay *= 2;
            return;
        }


        endDay = currentDay + totalDay/2;
        beginDay = currentDay - totalDay/2;

        if( endDay > mDataFile.kline.size() -10)
        {
            endDay = mDataFile.kline.size() -10;
            beginDay = endDay - totalDay;
        }

        if(beginDay < 0 )
        {
            beginDay = 0;
            endDay = beginDay + totalDay;
        }

        update();


        break;
    }

    case Qt::Key_Down:
    {
        if(totalDay == mDataFile.kline.size() -1 )
            return;

        totalDay = totalDay * 2;
        if( totalDay > mDataFile.kline.size() -1)
        {
            totalDay = mDataFile.kline.size() -1;
        }


        endDay = currentDay + totalDay/2;
        if( endDay > mDataFile.kline.size() -10)
        {
            endDay = mDataFile.kline.size() -10;
        }



        beginDay = currentDay - totalDay/2;
        if( beginDay < 0)
            beginDay = 0;



        totalDay = endDay - beginDay;

        update();

    }
    default:
        break;
    }
}

void KLineGrid::mouseMoveEvent(QMouseEvent *event)
{
    mousePoint = event->pos();
    isKeyDown = false;
    update();
}


void KLineGrid::mousePressEvent(QMouseEvent *event)
{
    if(event->button() == Qt::LeftButton)
    {
        bCross = !bCross;
        update();
    }
}


void KLineGrid::resizeEvent(QResizeEvent* event)
{

    AutoGrid::resizeEvent(event);
    bCross = false;

}

void KLineGrid::drawCross()
{

    drawCrossVerLine();
    drawCrossHorLine();
    drawTips();
}

void KLineGrid::drawCrossVerLine()
{
    QPainter painter(this);
    QPen     pen;
    pen.setColor(QColor("#FFFFFF"));
    pen.setWidth(1);
    painter.setPen(pen);


    double xstep = getGridWidth() / totalDay ;
    double xPos = getMarginLeft() ;
    while( mousePoint.x() - xPos > xstep )
    {
        xPos += xstep;
    }
    xPos += 0.5*lineWidth;
    QLine horline(xPos,getMarginTop(),xPos,getWidgetHeight() - getMarginBottom());
    painter.drawLine(horline);

}

void KLineGrid::drawCrossHorLine()
{
    QPainter painter(this);
    QPen     pen;
    pen.setColor(QColor("#FFFFFF"));
    pen.setWidth(1);
    painter.setPen(pen);


    double yPos;
    currentDay = ( mousePoint.x() - getMarginLeft() ) * totalDay / getGridWidth() + beginDay;


    if( mDataFile.kline[currentDay].openingPrice < mDataFile.kline[currentDay].closeingPrice )
        yPos =  ( mDataFile.kline[currentDay].closeingPrice - lowestBid ) * yscale ;
    else
        yPos =  ( mDataFile.kline[currentDay].closeingPrice - lowestBid ) * yscale ;

    QLine verline ( getMarginLeft(),getWidgetHeight()-getMarginBottom()-yPos,
                    getWidgetWidth()-getMarginRight(),getWidgetHeight()-getMarginBottom()-yPos);
    painter.drawLine(verline);

}




void KLineGrid::drawTips()
{
    QPainter painter(this);
    QPen     pen;
    QBrush brush(QColor(64,0,128));
    painter.setBrush(brush);
    pen.setColor(QColor("#FFFFFF"));
    pen.setWidth(1);
    painter.setPen(pen);


    int currentDay = ( mousePoint.x() - getMarginLeft() ) * totalDay / getGridWidth() + beginDay;
    double yval = mDataFile.kline[currentDay].closeingPrice;


    double yPos;
    if( mDataFile.kline[currentDay].openingPrice < mDataFile.kline[currentDay].closeingPrice )
        yPos =  ( mDataFile.kline[currentDay].closeingPrice - lowestBid ) * yscale ;
    else
        yPos =  ( mDataFile.kline[currentDay].closeingPrice - lowestBid ) * yscale ;


    yPos = getWidgetHeight()-getMarginBottom()-yPos;

    int iTipsWidth = 60;
    int iTipsHeight = 30;

    QString str;

    QRect rect( getWidgetWidth() - getMarginRight(),
                yPos - iTipsHeight/2,iTipsWidth,iTipsHeight);
    painter.drawRect(rect);


    QRect rectText( getWidgetWidth() - getMarginRight() + iTipsWidth/4,
                yPos - iTipsHeight/4,iTipsWidth,iTipsHeight);
    painter.drawText(rectText, str.sprintf("%.2f",yval));



    if( currentDay ==0)
        return;


    QColor openingColor = mDataFile.kline[currentDay].openingPrice > mDataFile.kline[currentDay -1].openingPrice ?
                          QColor("#FF0000"):QColor("#00FF00");

    QColor highestColor = mDataFile.kline[currentDay].highestBid > mDataFile.kline[currentDay -1].closeingPrice ?
                QColor("#FF0000"):QColor("#00FF00");

    QColor lowestColor = mDataFile.kline[currentDay].lowestBid > mDataFile.kline[currentDay -1].closeingPrice ?
                QColor("#FF0000"):QColor("#00FF00");


    QColor closeingColor = mDataFile.kline[currentDay].closeingPrice > mDataFile.kline[currentDay ].openingPrice ?
                QColor("#FF0000"):QColor("#00FF00");


    QColor amountOfIncreaseColor = mDataFile.kline[currentDay].amountOfIncrease > 0 ?
                QColor("#FF0000"):QColor("#00FF00");

    mShowDrtail->receiveParams(      mDataFile.kline[currentDay].time,QColor("#FFFFFF"),
                                     mDataFile.kline[currentDay].closeingPrice,QColor("#FF0000"),
                                     mDataFile.kline[currentDay].openingPrice,openingColor,
                                     mDataFile.kline[currentDay].highestBid,highestColor,
                                     mDataFile.kline[currentDay].lowestBid,lowestColor,
                                     mDataFile.kline[currentDay].closeingPrice,closeingColor,
                                     mDataFile.kline[currentDay].amountOfIncrease,amountOfIncreaseColor,
                                     mDataFile.kline[currentDay].amountOfAmplitude,QColor("#02E2F4"),
                                     mDataFile.kline[currentDay].totalVolume,QColor("#02E2F4"),
                                     mDataFile.kline[currentDay].totalAmount,QColor("#02E2F4"),
                                     mDataFile.kline[currentDay].turnoverRate,QColor("#02E2F4")
                                     );
}


void KLineGrid::drawMouseMoveCrossVerLine()
{

    if(mousePoint.x() < getMarginLeft() || mousePoint.x() > getWidgetWidth() - getMarginRight())
        return;

    if(mousePoint.y() < getMarginTop() || mousePoint.y() > getWidgetHeight() - getMarginBottom())
        return;

    QPainter painter(this);
    QPen     pen;
    pen.setColor(QColor("#FFFFFF"));
    pen.setWidth(1);
    painter.setPen(pen);
    painter.drawLine(mousePoint.x(),getMarginTop(),
                     mousePoint.x(),getWidgetHeight() - getMarginBottom());

}


void KLineGrid::drawMouseMoveCrossHorLine()
{

    if(mousePoint.x() < getMarginLeft() || mousePoint.x() > getWidgetWidth() - getMarginRight())
        return;

    if(mousePoint.y() < getMarginTop() || mousePoint.y() > getWidgetHeight() - getMarginBottom())
        return;

    QPainter painter(this);
    QPen     pen;
    pen.setColor(QColor("#FFFFFF"));
    pen.setWidth(1);
    painter.setPen(pen);

    painter.drawLine(getMarginLeft(),mousePoint.y(),
                     getWidgetWidth()-getMarginRight(),mousePoint.y());

}



void KLineGrid::drawCross2()
{

    drawMouseMoveCrossHorLine();
    drawMouseMoveCrossVerLine();
    drawTips2();
}




void KLineGrid::drawTips2()
{

    if(mousePoint.x() < getMarginLeft() || mousePoint.x() > getWidgetWidth() - getMarginRight())
        return;

    if(mousePoint.y() < getMarginTop() || mousePoint.y() > getWidgetHeight() - getMarginBottom())
        return;

    QPainter painter(this);
    QPen     pen;
    QBrush brush(QColor(64,0,128));
    painter.setBrush(brush);
    pen.setColor(QColor("#FFFFFF"));
    pen.setWidth(1);
    painter.setPen(pen);

    double yval =  highestBid - ( mousePoint.y() - getMarginTop() ) / yscale;
    double yPos = mousePoint.y();

    int iTipsWidth = 60;
    int iTipsHeight = 30;

    QString str;

    QRect rect( getWidgetWidth() - getMarginRight(),
                yPos - iTipsHeight/2,iTipsWidth,iTipsHeight);
    painter.drawRect(rect);


    QRect rectText( getWidgetWidth() - getMarginRight() + iTipsWidth/4,
                yPos - iTipsHeight/4,iTipsWidth,iTipsHeight);
    painter.drawText(rectText, str.sprintf("%.2f",yval));
}



void KLineGrid::drawAverageLine(int day)
{

    //y轴缩放
    yscale = getGridHeight() / (highestBid -lowestBid ) ;
    //画笔的线宽
    lineWidth;
    //画线要连接的点
    QVector<QPoint> point;

    //临时点
    QPoint temp;

    //x轴步进
    double xstep = getGridWidth() / totalDay;



    if( beginDay < 0)
        return;


    switch(day)
    {
    case 5:
        for( int i= beginDay;i<endDay;++i)
        {
            if( mDataFile.kline[i].averageLine5 == 0)
                continue;
            temp.setX(getMarginLeft() + xstep *(i - beginDay) + 0.5*lineWidth);
            temp.setY(getWidgetHeight() - (mDataFile.kline[i].averageLine5 - lowestBid) *yscale - getMarginBottom());
            point.push_back(temp);
        }
        break;
    case 10:
        for( int i= beginDay;i<endDay;++i)
        {
            if( mDataFile.kline[i].averageLine10 == 0)
                continue;
            temp.setX(getMarginLeft() + xstep *(i - beginDay) + 0.5*lineWidth);
            temp.setY(getWidgetHeight() - (mDataFile.kline[i].averageLine10 - lowestBid) *yscale - getMarginBottom());
            point.push_back(temp);
        }
        break;
    case 20:
        for( int i= beginDay;i<endDay;++i)
        {
            if( mDataFile.kline[i].averageLine20 == 0)
                continue;
            temp.setX(getMarginLeft() + xstep *(i - beginDay) + 0.5*lineWidth);
            temp.setY(getWidgetHeight() - (mDataFile.kline[i].averageLine20 - lowestBid) *yscale - getMarginBottom());
            point.push_back(temp);
        }
        break;
    case 30:
        for( int i= beginDay;i<endDay;++i)
        {
            if( mDataFile.kline[i].averageLine30 == 0)
                continue;
            temp.setX(getMarginLeft() + xstep *(i - beginDay) + 0.5*lineWidth);
            temp.setY(getWidgetHeight() - (mDataFile.kline[i].averageLine30 - lowestBid) *yscale - getMarginBottom());
            point.push_back(temp);
        }
        break;
    case 60:
        for( int i= beginDay;i<endDay;++i)
        {
            if( mDataFile.kline[i].averageLine60 == 0)
                continue;
            temp.setX(getMarginLeft() + xstep *(i - beginDay) + 0.5*lineWidth);
            temp.setY(getWidgetHeight() - (mDataFile.kline[i].averageLine60 - lowestBid) *yscale - getMarginBottom());
            point.push_back(temp);
        }
        break;
    default:
        break;
    }


    QPainter painter(this);
    QPen     pen;

    switch(day)
    {
    case 5:
        pen.setColor(Qt::white);
        break;
    case 10:
        pen.setColor(Qt::yellow);
        break;
    case 20:
        pen.setColor(Qt::magenta);
        break;
    case 30:
        pen.setColor(Qt::green);
        break;
    case 60:
        pen.setColor(Qt::cyan);
        break;
    default:
        pen.setColor(Qt::white);
        break;
    }
    painter.setPen(pen);
    QPolygon polykline(point);
    painter.drawPolyline(polykline);
}



