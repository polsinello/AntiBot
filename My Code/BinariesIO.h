#ifndef BINARIESIO_H
#define BINARIESIO_H

#include "Public.h"
#include "System/Tools/IO/Reader.h"
#include "System/Tools/IO/Writer.h"

class StringReader
{
public:
    StringReader();
    QList<QByteArray> getResult() const;
    int getDecryptInt() const;
    void init();

private:
    QByteArray getKey(Reader &r);
    void decode(Reader &r, QByteArray key, QList<QString> &result);

    QList<QByteArray> m_binaries;
    QString filePath;
    int m_decryptInt;
};

class StringParser
{
public:
    StringParser(QByteArray initKey);
    QByteArray parseString(QByteArray param1);
    void init(QByteArray param1);
    void getString(QByteArray &param1);
    uint parseKey();

private:
    QByteArray m_key;
    uint m_const;
    int decryptInt1;
    int decryptInt2;
};

#endif // BINARIESIO_H
