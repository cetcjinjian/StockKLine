#ifndef DATAFILE_H
#define DATAFILE_H


#include <vector>
#include <QString>
#include <QFile>


typedef struct
{
    QString time;                   //时间
    double openingPrice;            //开盘
    double highestBid;              //最高
    double lowestBid;               //收盘
    double closeingPrice;           //涨幅
    double amountOfIncrease;        //振幅
    double totalVolume;             //总手
    double totalAmount;             //金额
    double turnoverRate;            //换手率
    double volumeAmount;            //成交次数
}KLine;


class DataFile
{
public:
    explicit DataFile();
    ~DataFile();
    bool readData(QString filestr);
    std::vector<KLine> kline;
    QFile* pfile = nullptr;

};

#endif // DATAFILE_H
