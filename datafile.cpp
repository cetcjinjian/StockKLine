#include "datafile.h"

DataFile::DataFile()
{

}


DataFile::~DataFile()
{
    delete pfile;
    pfile = nullptr;
}

bool DataFile::readData(QString filestr)
{
    pfile = new QFile(filestr);
    if( !pfile->open(QFile::ReadOnly) )
        return false;

    char    line[1024];
    char    *token;
    KLine temp;

    while( pfile->readLine(line,1024)  > 0 )
    {
        token = strtok( line, "'\t'" );
        if( token != NULL )
            temp.time = token;

        token = strtok( NULL, "'\t'" );
        if( token != NULL )
            temp.openingPrice = atof(token);

        token = strtok( NULL, "'\t'" );
        if( token != NULL )
            temp.highestBid = atof(token);

        token = strtok( NULL, "'\t'" );
        if( token != NULL )
            temp.lowestBid = atof(token);

        token = strtok( NULL, "'\t'" );
        if( token != NULL )
            temp.closeingPrice = atof(token);

        token = strtok( NULL, "'\t'" );
        if( token != NULL )
            temp.amountOfIncrease = atof(token);

        token = strtok( NULL, "'\t'" );
        if( token != NULL )
            temp.amountOfAmplitude = atof(token);

        token = strtok( NULL, "'\t'" );
        if( token != NULL )
            temp.totalVolume = (token);

        token = strtok( NULL, "'\t'" );
        if( token != NULL )
            temp.totalAmount = (token);

        token = strtok( NULL, "'\t'" );
        if( token != NULL )
            temp.turnoverRate = atof(token);

        token = strtok( NULL, "'\t'" );
        if( token != NULL )
            temp.volumeAmount = atof(token);

        kline.push_back(temp);


        }


    calAverageLine();
    return true;
}


void DataFile::calAverageLine()
{

    // 初始化各均线的值
    for(int i=0;i<4;i++)
        kline[i].averageLine5 = 0;

    for(int i=0;i<9;i++)
        kline[i].averageLine10 = 0;

    for(int i=0;i<19;i++)
        kline[i].averageLine20 = 0;

    for(int i=0;i<29;i++)
        kline[i].averageLine30 = 0;

    for(int i=0;i<59;i++)
        kline[i].averageLine60 = 0;


    calAverageLine5();
    calAverageLine10();
    calAverageLine20();
    calAverageLine30();
    calAverageLine60();

}


void DataFile::calAverageLine5()
{
    for( int i=4;i<kline.size();++i)
    {
        double sum = 0;
        for(int j=i-4;j<=i;++j)
        {
            sum += kline[j].closeingPrice;
        }
        kline[i].averageLine5 = sum /5;
    }
}


void DataFile::calAverageLine10()
{
    for( int i=9;i<kline.size();++i)
    {
        double sum = 0;
        for(int j=i-9;j<=i;++j)
        {
            sum += kline[j].closeingPrice;
        }
        kline[i].averageLine10 = sum /10;
    }
}




void DataFile::calAverageLine20()
{
    for( int i=19;i<kline.size();++i)
    {
        double sum = 0;
        for(int j=i-19;j<=i;++j)
        {
            sum += kline[j].closeingPrice;
        }
        kline[i].averageLine20 = sum /20;
    }
}


void DataFile::calAverageLine30()
{
    for( int i=29;i<kline.size();++i)
    {
        double sum = 0;
        for(int j=i-29;j<=i;++j)
        {
            sum += kline[j].closeingPrice;
        }
        kline[i].averageLine30 = sum /30;
    }
}



void DataFile::calAverageLine60()
{
    for( int i=59;i<kline.size();++i)
    {
        double sum = 0;
        for(int j=i-59;j<=i;++j)
        {
            sum += kline[j].closeingPrice;
        }
        kline[i].averageLine60 = sum /60;
    }
}

