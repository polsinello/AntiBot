#ifndef RpnParser_H
#define RpnParser_H

#include <QFile>
#include "Public.h"

class RpnParser
{
public:
    RpnParser(QString path);
    QList<int> parseFile();
    int getDecryptKeyPos(int decryptInt);

private:
    void readFile();

    QString m_path;
    QByteArray m_byteCode;
};

#endif // RpnParser_H
