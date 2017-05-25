#include "kvolumegrid.h"

#include <QMessageBox>
#include <QPainter>
#include <QPen>
#include <QString>


kVolumeGrid::kVolumeGrid(QWidget* parent) : AutoGrid( parent)
{
    setAtomGridHeightMin(40);
    initial();

}

void kVolumeGrid::paintEvent(QPaintEvent *event)
{

    AutoGrid::paintEvent(event);
    //画y轴坐标轴
    drawYtick();
    drawVolume();
    drawAverageLine(5);
    drawAverageLine(10);

}

void kVolumeGrid::initial()
{
    //读取数据
    QString file = tr("dataKLine.txt");
    if( !mDataFile.readData(file) )
    {
        QMessageBox::about(this,tr("数据文件读取失败"),tr("确定"));
        return ;
    }

    //初始化一些成员变量值

    endDay = mDataFile.kline.size() - 1;
    totalDay = 200;
    beginDay  = endDay - totalDay;
    currentDay = beginDay + totalDay /2;
    maxVolume = 0;

}

bool kVolumeGrid::readData(QString strFile)
{
    if( mDataFile.readData(strFile) )
        return true;
    else
        return false;
}


//获得画图所需的各项指标
void kVolumeGrid::getIndicator()
{
    maxVolume = 0;
    for(int i=beginDay;i<endDay;++i)
    {
        QString strVolume = mDataFile.kline[i].totalVolume;
        strVolume = strVolume.mid(1,strVolume.length());
        strVolume = strVolume.mid(0,strVolume.length()-1);
        strVolume.replace(QString(","),QString(""));
        if( strVolume.toInt() > maxVolume)
            maxVolume = strVolume.toInt();
    }
    maxVolume = maxVolume / 100;
}

void kVolumeGrid::drawYtick()
{

    getIndicator();

    QPainter painter(this);
    QPen     pen;
    pen.setColor(Qt::red);
    painter.setPen(pen);
    double ystep = maxVolume / getHGridNum() ;
    QString str;
    for( int i=0;i<=getHGridNum();++i)
    {
        str.sprintf("%d", (int)(i*ystep) );
        painter.drawText( QPoint( getWidgetWidth() - getMarginLeft() + 10,
                                  getWidgetHeight() - getMarginBottom() - i*getAtomGridHeight()),
                          str);
    }
}
void kVolumeGrid::drawVolume()
{
    QPainter painter(this);
    QPen     pen;


    double xstep = getGridWidth() / totalDay;
    double yscale = getGridHeight() / maxVolume;

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


        //画线连接的两个点
        QPoint p1;
        QPoint p2;

        QPoint p3;
        QPoint p4;



        QString strtemp = mDataFile.kline[i].totalVolume;
        strtemp = strtemp.mid(1,strtemp.length());
        strtemp = strtemp.mid(0,strtemp.length()-1);
        strtemp.replace(QString(","),QString(""));
        int temp = strtemp.toInt()/100;


        //阴线

        if( mDataFile.kline[i].openingPrice > mDataFile.kline[i].closeingPrice )
        {
            pen.setWidth(lineWidth);
            painter.setPen(pen);
            p1.setX( getMarginLeft() + xstep *(i - beginDay) + 0.5*lineWidth);
            p1.setY( getWidgetHeight() - (temp ) *yscale - getMarginBottom());
            p2.setX( getMarginLeft() + xstep *(i - beginDay) + 0.5*lineWidth);
            p2.setY( getWidgetHeight()  - getMarginBottom() - 0.5*lineWidth);
            painter.drawLine(p1,p2);

        }


        //阳线
        else
        {
            pen.setWidth(1);
            painter.setPen(pen);

            p1.setX( getMarginLeft() + xstep *(i - beginDay) );
            p1.setY( getWidgetHeight() - (temp ) *yscale - getMarginBottom());
            p2.setX(getMarginLeft() + xstep *(i - beginDay) + lineWidth);
            p2.setY( getWidgetHeight() - (temp ) *yscale - getMarginBottom());
            p3.setX( getMarginLeft() + xstep *(i - beginDay) );
            p3.setY( getWidgetHeight()  - getMarginBottom() );
            p4.setX( getMarginLeft() + xstep *(i - beginDay) + lineWidth);
            p4.setY( getWidgetHeight()  - getMarginBottom() );

            painter.drawLine(p1,p2);
            painter.drawLine(p1,p3);
            painter.drawLine(p2,p4);
            painter.drawLine(p3,p4);

        }
    }
}

void kVolumeGrid::drawAverageLine(int day){



    //画线要连接的点
    QVector<QPoint> point;

    //临时点
    QPoint temp;

    //x轴步进
    double xstep = getGridWidth() / totalDay;
    double yscale = getGridHeight() / maxVolume;




    switch(day)
    {
    case 5:
        for( int i= beginDay;i<endDay;++i)
        {
            if( mDataFile.kline[i].volumeAverage5 == 0)
                continue;
            temp.setX(getMarginLeft() + xstep *(i - beginDay) + 0.5*lineWidth);
            temp.setY(getWidgetHeight() - mDataFile.kline[i].volumeAverage5 /100 *yscale - getMarginBottom());
            point.push_back(temp);
        }
        break;
    case 10:
        for( int i= beginDay;i<endDay;++i)
        {
            if( mDataFile.kline[i].volumeAverage10 == 0)
                continue;
            temp.setX(getMarginLeft() + xstep *(i - beginDay) + 0.5*lineWidth);
            temp.setY(getWidgetHeight() - mDataFile.kline[i].volumeAverage10 /100 *yscale - getMarginBottom());
            point.push_back(temp);
        }
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
    }


    painter.setPen(pen);
    QPolygon polykline(point);
    painter.drawPolyline(polykline);

}

