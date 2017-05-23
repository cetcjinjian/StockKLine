#include "autogrid.h"
#include <QPainter>
#include <QPen>

AutoGrid::AutoGrid(QWidget *parent) : QWidget(parent)
{

    initial();

}


void AutoGrid::drawBK()
{
    this->setAutoFillBackground(true);
    QPalette palette;
    palette.setColor(QPalette::Window,QColor("#000000"));
    this->setPalette(palette);
}

void AutoGrid::resizeEvent(QResizeEvent *event)
{
    widgetWidth = this->width();
    widgetHeight  = this->height();
    gridHeight = widgetHeight - marginTop - marginBottom;
    gridWidth = widgetWidth - marginLeft - marginRight;
    calAtomGridHeight();
    calAtomGridWidth();

}



void AutoGrid::initial()
{
    atomGridHeight = 60;
    atomGridHeightMin = 60;
    atomGridWidth = 640;
    atomGridWidthMin = 640;
    drawBK();
}


void AutoGrid::calAtomGridHeight()
{
    hGridNum = 0;
    int height = gridHeight;
    while( height - atomGridHeightMin > atomGridHeightMin)
    {
        ++hGridNum;
        height -= atomGridHeightMin;
    }
    atomGridHeight = gridHeight / hGridNum;
}

void AutoGrid::calAtomGridWidth()
{
    wGridNum = 0;
    int width = gridWidth;
    while( width - atomGridWidthMin >atomGridWidthMin)
    {
        ++wGridNum;
        width -= atomGridWidthMin;
    }
    atomGridWidth = gridWidth / wGridNum;

}

void AutoGrid::paintEvent(QPaintEvent* event)
{
    drawGrid();
}

void AutoGrid::drawHorLine()
{
    QPainter painter(this);
    QPen     pen;
    pen.setColor(QColor("#FF0000"));
    painter.setPen(pen);


    int xstart = marginLeft;
    int ystart = marginTop;
    int xend =  widgetWidth - marginRight;
    int yend = marginTop;

    for(int i=0;i<hGridNum+1;++i)
    {
        if( i == 0 || i == hGridNum)
        {
            pen.setStyle(Qt::SolidLine);
            painter.setPen(pen);
        }
        else
        {
            pen.setStyle(Qt::DashDotLine);
            painter.setPen(pen);
        }
        painter.drawLine(xstart,ystart+i*atomGridHeight,
                         xend,yend+i*atomGridHeight);
    }

    if( 0 == hGridNum)
    {
        painter.drawLine(marginLeft,marginTop,
                         widgetWidth - marginRight,marginTop);
        painter.drawLine(marginLeft,marginTop+gridHeight,
                         widgetWidth - marginRight,marginTop+gridHeight);
    }

}


void AutoGrid::drawVerLine()
{

    QPainter painter(this);
    QPen     pen;
    pen.setColor(QColor("#FF0000"));
    painter.setPen(pen);


    int xstart = marginLeft;
    int ystart = marginTop;
    int xend =  marginLeft;
    int yend = widgetHeight - marginBottom;

    for(int i=0;i<wGridNum+1;++i)
    {
        if( i == 0 || i == wGridNum)
        {
            pen.setStyle(Qt::SolidLine);
            painter.setPen(pen);
        }
        else
        {
            pen.setStyle(Qt::DashDotLine);
            painter.setPen(pen);
        }
        painter.drawLine(xstart+i*atomGridWidth,ystart,
                         xend+i*atomGridWidth,yend);

    }

    if( 0 == wGridNum)
    {
        painter.drawLine(marginLeft,marginTop,
                         marginLeft,widgetHeight - marginBottom);
        painter.drawLine(marginLeft+gridWidth,marginTop,
                         marginLeft+gridWidth,marginTop+gridHeight);
    }

}

void AutoGrid::drawGrid()
{
    drawHorLine();
    drawVerLine();
}

int AutoGrid::getMarginLeft() const
{
    return marginLeft;
}

void AutoGrid::setMarginLeft(int value)
{
    marginLeft = value;
}

int AutoGrid::getMarginRight() const
{
    return marginRight;
}

void AutoGrid::setMarginRight(int value)
{
    marginRight = value;
}

int AutoGrid::getMarginTop() const
{
    return marginTop;
}

void AutoGrid::setMarginTop(int value)
{
    marginTop = value;
}

int AutoGrid::getMarginBottom() const
{
    return marginBottom;
}

void AutoGrid::setMarginBottom(int value)
{
    marginBottom = value;
}

int AutoGrid::getWidgetHeight() const
{
    return widgetHeight;
}

int AutoGrid::getWidgetWidth() const
{
    return widgetWidth;
}

double AutoGrid::getGridHeight() const
{
    return gridHeight;
}

double AutoGrid::getGridWidth() const
{
    return gridWidth;
}

int AutoGrid::getHGridNum() const
{
    return hGridNum;
}

void AutoGrid::setHGridNum(int value)
{
    hGridNum = value;
}

int AutoGrid::getWGridNum() const
{
    return wGridNum;
}

void AutoGrid::setWGridNum(int value)
{
    wGridNum = value;
}

double AutoGrid::getAtomGridHeightMin() const
{
    return atomGridHeightMin;
}

void AutoGrid::setAtomGridHeightMin(double value)
{
    atomGridHeightMin = value;
}

double AutoGrid::getAtomGridWidthMin() const
{
    return atomGridWidthMin;
}

void AutoGrid::setAtomGridWidthMin(double value)
{
    atomGridWidthMin = value;
}

double AutoGrid::getAtomGridHeight() const
{
    return atomGridHeight;
}

double AutoGrid::getAtomGridWidth() const
{
    return atomGridWidth;
}
