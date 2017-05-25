#ifndef SHOWDETAIL_H
#define SHOWDETAIL_H


#include <QWidget>
#include <QDockWidget>
#include <QDialog>
#include "klinegrid.h"

//class ShowDetail : public QDockWidget
class ShowDetail : public QDialog
{

    Q_OBJECT

public:
    explicit ShowDetail(QWidget* parent);
    void virtual paintEvent(QPaintEvent* event);
    void virtual drawBK();
    void drawStr();


private:

    QString time = "";
    double currentPrice = 0;
    double openingPrice = 0;
    double highestBid = 0;
    double lowestBid =0;
    double closeingPrice =0;
    double amountOfIncrease=0;
    double amountOfAmplitude =0;
    QString totalVolume = "";
    QString totalAmount = "";
    double turnoverRate = 0;



    QColor timeColor ;
    QColor currentPriceColor ;
    QColor openingPriceColor ;
    QColor highestBidColor ;
    QColor lowestBidColor ;
    QColor closeingPriceColor ;
    QColor amountOfIncreaseColor;
    QColor amountOfAmplitudeColor ;
    QColor totalVolumeColor ;
    QColor totalAmountColor ;
    QColor turnoverRateColor ;

public :

  void receiveParams(QString time,QColor timeColor,
                     double currentPrice,QColor currentPriceColor,
                     double openingPrice,QColor openingPriceColor,
                     double highestBid,QColor highestBidColor,
                     double lowestBid,QColor lowestBidColor,
                     double closeingPrice,QColor closeingPriceColor,
                     double amountOfIncrease,QColor amountOfIncreaseColor,
                     double amountOfAmplitude,QColor amountOfAmplitudeColor,
                     QString totalVolume,QColor totalVolumeColor,
                     QString totalAmount,QColor totalAmountColor,
                     double turnoverRate,QColor turnoverRateColor);
};

#endif // SHOWDETAIL_H
