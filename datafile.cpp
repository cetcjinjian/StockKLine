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
            temp.totalVolume = atof(token);

        token = strtok( NULL, "'\t'" );
        if( token != NULL )
            temp.totalAmount = atof(token);

        token = strtok( NULL, "'\t'" );
        if( token != NULL )
            temp.turnoverRate = atof(token);

        token = strtok( NULL, "'\t'" );
        if( token != NULL )
            temp.volumeAmount = atof(token);

        kline.push_back(temp);
        }
    return true;
}

