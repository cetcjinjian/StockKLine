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
    QString totalVolume;             //总手
    QString totalAmount;             //金额
    double turnoverRate;            //换手率
    double volumeAmount;            //成交次数
    double averageLine5;            //5日均线
    double averageLine10;           //10日均线
    double averageLine20;           //20日均线
    double averageLine30;           //30日均线
    double averageLine60;           //60日均线
    double ftotalVolume;
    double ftotalAmount;
    double volumeAverage5;          //成交量5日均值
    double volumeAverage10;         //成交量10日均值
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


    void calvolumeAverage5();
    void calvolumeAverage10();

    void Corvert();


};

#endif // DATAFILE_H
