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
    double lowestBid;               //最低
    double closeingPrice;           //收盘
    double amountOfIncrease;        //涨幅
    double amountOfAmplitude;       //振幅
    double totalVolume;             //总手
    double totalAmount;             //金额
    double turnoverRate;            //换手率
    double volumeAmount;            //成交次数
    double averageLine5;            //5日均线
    double averageLine10;           //10日均线
    double averageLine20;           //20日均线
    double averageLine30;           //30日均线
    double averageLine60;           //60日均线
}KLine;


class DataFile
{
public:
    explicit DataFile();
    ~DataFile();
    bool readData(QString filestr);
    std::vector<KLine> kline;
    QFile* pfile = nullptr;
    void calAverageLine();
    void calAverageLine5();
    void calAverageLine10();
    void calAverageLine20();
    void calAverageLine30();
    void calAverageLine60();

};

#endif // DATAFILE_H
