#ifndef KLINEGRID_H
#define KLINEGRID_H

#include "autogrid.h"
#include "datafile.h"

#include <QPoint>


class KLineGrid : public AutoGrid
{
public:
    explicit KLineGrid(QWidget *parent = 0);
    void virtual paintEvent(QPaintEvent* event);
    void virtual keyPressEvent(QKeyEvent* event);
    void virtual mouseMoveEvent(QMouseEvent* event);
    void virtual mousePressEvent(QMouseEvent* event);
    void virtual resizeEvent(QResizeEvent* event);


    bool readData(QString strFile);
    void initial();
    void drawLine();
    void getIndicator();
    void drawYtick();
    void drawKline();


    //键盘按下后画的十字线
    void drawCross();
    void drawCrossVerLine();
    void drawCrossHorLine();
    void drawTips();

    //键盘没按下画的十字线
    void drawCross2();
    void drawMouseMoveCrossVerLine();
    void drawMouseMoveCrossHorLine();
    void drawTips2();



private:
    DataFile mDataFile;



    //画k线的起始日期和终止日期
    int beginDay;
    int endDay;
    int totalDay;
    int currentDay;


    //当前要画的k线日期中的最高价，最低价，最大成交量
    double highestBid;
    double lowestBid;
    double maxVolume;

    //x轴和y轴的缩放比
    double xscale;
    double yscale;

    //是否显示十字线
    bool bCross = false;


    //鼠标位置
    QPoint mousePoint;

    //画笔的线宽
    int lineWidth;


    //键盘是否按下
    bool isKeyDown = false;
};

#endif // KLINEGRID_H
