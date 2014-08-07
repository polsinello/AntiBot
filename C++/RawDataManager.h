#ifndef RAWDATAMANAGER_H
#define RAWDATAMANAGER_H

#include "Public.h"
#include "RpnParser.h"
#include "BinariesIO.h"
#include "System/Tools/IO/Writer.h"
#include "System/Tools/IO/Reader.h"

#include "osrng.h"
#include <cstdlib>
#include "cryptlib.h"
#include "filters.h"
#include "hex.h"
#include "aes.h"
#include "ccm.h"

class RawDataManager
{
public:
    RawDataManager(QString ticket, QString swf);
    void processKey();
    QByteArray encrypt();

private:
    QFile m_swf;
    QString m_ticket;
    QByteArray m_key;
    QByteArray m_decryptKey;
    QList<QByteArray> m_binariesStrings;
};

#endif // RAWDATAMANAGER_H
