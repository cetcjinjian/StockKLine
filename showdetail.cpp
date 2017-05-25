#include "showdetail.h"
#include "mainwindow.h"
#include <QDockWidget>
#include <QPainter>
#include <QFont>
#include <klinegrid.h>

ShowDetail::ShowDetail(QWidget* parent) : QDialog(parent)
{

    QFont ft;
    ft.setPointSize(14);
    this->setFont(ft);
}


void ShowDetail::drawBK()
{
    this->setAutoFillBackground(true);
    QPalette palette;
    palette.setColor(QPalette::Window,QColor("#000000"));
    this->setPalette(palette);
}

void ShowDetail::paintEvent(QPaintEvent *event)
{
    drawBK();
    drawStr();


}

void ShowDetail::drawStr()
{
    QPainter painter(this);
    QPen pen;
    pen.setColor(QColor("#FFFFFF"));
    painter.setPen(pen);

    QRect rectTime( 20,20,100,30);
    painter.drawText(rectTime,tr("time"));


    pen.setColor(timeColor);
    painter.setPen(pen);
    QRect rectTime2( 20,50,100,30);
    QString str = time.mid(1,10);
    painter.drawText(rectTime2,str);



    pen.setColor(QColor("#FFFFFF"));
    painter.setPen(pen);
    QRect rectTime3(20,80,100,30);
    painter.drawText(rectTime3,tr("currentValue"));


    pen.setColor(currentPriceColor);
    painter.setPen(pen);
    QRect rectTime4(20,110,100,30);
    painter.drawText(rectTime4,str.sprintf("%.2f",currentPrice));




    pen.setColor(QColor("#FFFFFF"));
    painter.setPen(pen);
    QRect rectTime5(20,140,100,30);
    painter.drawText(rectTime5,tr("opening"));


    pen.setColor(openingPriceColor);
    painter.setPen(pen);
    QRect rectTime6(20,170,100,30);
    painter.drawText(rectTime6,str.sprintf("%.2f",openingPrice));



    pen.setColor(QColor("#FFFFFF"));
    painter.setPen(pen);
    QRect rectTime7(20,200,100,30);
    painter.drawText(rectTime7,tr("highestBid"));


    pen.setColor(highestBidColor);
    painter.setPen(pen);
    QRect rectTime8(20,230,100,30);
    painter.drawText(rectTime8,str.sprintf("%.2f",highestBid));



    pen.setColor(QColor("#FFFFFF"));
    painter.setPen(pen);
    QRect rectTime9(20,260,100,30);
    painter.drawText(rectTime9,tr("lowestBid"));


    pen.setColor(lowestBidColor);
    painter.setPen(pen);
    QRect rectTime10(20,290,100,30);
    painter.drawText(rectTime10,str.sprintf("%.2f",lowestBid));



    pen.setColor(QColor("#FFFFFF"));
    painter.setPen(pen);
    QRect rectTime11(20,320,100,30);
    painter.drawText(rectTime11,tr("closeingPrice"));



    pen.setColor(closeingPriceColor);
    painter.setPen(pen);
    QRect rectTime12(20,350,100,30);
    painter.drawText(rectTime12,str.sprintf("%.2f",closeingPrice));


    pen.setColor(QColor("#FFFFFF"));
    painter.setPen(pen);
    QRect rectTime13(20,380,100,30);
    painter.drawText(rectTime13,tr("amountOfIncrease"));



    pen.setColor(amountOfIncreaseColor);
    painter.setPen(pen);
    QRect rectTime14(20,410,100,30);
    painter.drawText(rectTime14,str.sprintf("%.2f%",amountOfIncrease));




    pen.setColor(QColor("#FFFFFF"));
    painter.setPen(pen);
    QRect rectTime15(20,440,100,30);
    painter.drawText(rectTime15,tr("amountOfAmplitude"));


    pen.setColor(amountOfAmplitudeColor);
    painter.setPen(pen);
    QRect rectTime16(20,470,100,30);
    painter.drawText(rectTime16,str.sprintf("%.2f%",amountOfAmplitude));





    pen.setColor(QColor("#FFFFFF"));
    painter.setPen(pen);
    QRect rectTime17(20,500,100,30);
    painter.drawText(rectTime17,tr("totalVolume"));




    pen.setColor(totalVolumeColor);
    painter.setPen(pen);
    QRect rectTime18(20,530,100,30);
    str = totalVolume;
    str = str.mid(1,str.length());
    str = str.mid(0,str.length()-1);
    painter.drawText(rectTime18,str);




    pen.setColor(QColor("#FFFFFF"));
    painter.setPen(pen);
    QRect rectTime19(20,560,100,30);
    painter.drawText(rectTime19,tr("totalAmount"));



    pen.setColor(totalAmountColor);
    painter.setPen(pen);
    QRect rectTime20(20,590,100,30);

    str = totalAmount;
    str = str.mid(1,str.length());
    str = str.mid(0,str.length()-1);
    painter.drawText(rectTime20,str);




    pen.setColor(QColor("#FFFFFF"));
    painter.setPen(pen);
    QRect rectTime21(20,620,100,30);
    painter.drawText(rectTime21,tr("turnoverRate"));



    pen.setColor(turnoverRateColor);
    painter.setPen(pen);
    QRect rectTime22(20,650,100,30);
    painter.drawText(rectTime22,str.sprintf("%.2f",turnoverRate));



//    QRect rectTime4( 20,50,100,30);
//    painter.drawText(rectTime4,str.sprintf("%.2f",currentPrice));

}

void ShowDetail::receiveParams(QString time,QColor timeColor,
                               double currentPrice,QColor currentPriceColor,
                               double openingPrice,QColor openingPriceColor,
                               double highestBid,QColor highestBidColor,
                               double lowestBid,QColor lowestBidColor,
                               double closeingPrice,QColor closeingPriceColor,
                               double amountOfIncrease,QColor amountOfIncreaseColor,
                               double amountOfAmplitude,QColor amountOfAmplitudeColor,
                               QString totalVolume,QColor totalVolumeColor,
                               QString totalAmount,QColor totalAmountColor,
                               double turnoverRate,QColor turnoverRateColor)
{
    this->time = time;
    this->currentPrice = currentPrice;
    this->openingPrice = openingPrice;
    this->highestBid = highestBid;
    this->lowestBid = lowestBid;
    this->closeingPrice = closeingPrice;
    this->amountOfIncrease = amountOfIncrease;
    this->amountOfAmplitude = amountOfAmplitude;
    this->totalVolume = totalVolume;
    this->totalAmount = totalAmount;
    this->turnoverRate = turnoverRate;


    this->timeColor = timeColor;
    this->currentPriceColor = currentPriceColor;
    this->openingPriceColor = openingPriceColor;
    this->highestBidColor = highestBidColor;
    this->lowestBidColor = lowestBidColor;
    this->closeingPriceColor = closeingPriceColor;
    this->amountOfIncreaseColor = amountOfIncreaseColor;
    this->amountOfAmplitudeColor = amountOfAmplitudeColor;
    this->totalVolumeColor = totalVolumeColor;
    this->totalAmountColor = totalAmountColor;
    this->turnoverRateColor = turnoverRateColor;

    update();
}
