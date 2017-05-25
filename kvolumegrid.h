#ifndef KVOLUMEGRID_H
#define KVOLUMEGRID_H


#include "autogrid.h"
#include "datafile.h"

#include <QPoint>

class kVolumeGrid : public AutoGrid
{
public:
    explicit kVolumeGrid(QWidget* parent);
    bool readData(QString strFile);
    void initial();
    void drawYtick();
    void drawVolume();
    void virtual paintEvent(QPaintEvent* event);
    void getIndicator();
    void drawAverageLine(int day);

private:
    DataFile mDataFile;

    //画成交量线的起始日期和终止日期
    int beginDay;
    int endDay;
    int totalDay;
    int currentDay;



    //当前要画的成交量线中的最大成交量
    double maxVolume;


    //鼠标位置
    QPoint mousePoint;


    //线宽
    int lineWidth;


};

#endif // KVOLUMEGRID_H
