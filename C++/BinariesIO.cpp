#include "BinariesIO.h"

//String Reader
StringReader::StringReader()
{
}

void StringReader::init()
{
    QString path = getRessourcesPath();
    QFile f1(path + "/RDM/Assets/binaryData/1.bin");
    QFile f2(path + "/RDM/Assets/binaryData/2.bin");
    QFile f3(path + "/RDM/Assets/binaryData/3.bin");

    f1.open(QIODevice::ReadOnly);
    f2.open(QIODevice::ReadOnly);
    f3.open(QIODevice::ReadOnly);

    QByteArray tmp3(f3.readAll());
    QByteArray tmp2(f2.readAll());
    QByteArray tmp1(f1.readAll());
    Reader r1(tmp1);
    Reader r2(tmp2);
    Reader r3(tmp3);

    r3.setLitteEndian(true);
    m_decryptInt = r3.readInt();

    QList<QByteArray> key;
    for (int i = 0; i < (int)r2.readByte(); i++)
        key.append(getKey(r2));

    int size = r1.readInt();
    QList<QString> result;
    for (int i = 0; i < size; i++)
        decode(r1, key[i % key.size()], result);

    foreach (QString str, result)
        m_binaries.append(QByteArray::fromBase64(str.toLatin1()));
}

QByteArray StringReader::getKey(Reader &r)
{
    return r.readBytes(16);
}

void StringReader::decode(Reader &r, QByteArray key, QList<QString> &result)
{
    int size = r.readInt();
    QByteArray decoded(r.readBytes(size));

    StringParser parser(key);
    parser.getString(decoded);

    Reader tmp(decoded);
    result.append(tmp.readUTFBytes());
}

QList<QByteArray> StringReader::getResult() const
{
    return m_binaries;
}

int StringReader::getDecryptInt() const
{
    return m_decryptInt;
}

//String Parser
StringParser::StringParser(QByteArray initKey)
{
    m_const = 256;
    init(initKey);
}

void StringParser::init(QByteArray param1)
{
    for (int i = 0; i < m_const; i++)
        m_key[i] = i;

    int j = 0;
    int k = 0;
    for (int i = 0; i < m_const; i++)
    {
        j = j + m_key[i] + param1[i % param1.size()] & 255;
        k = m_key[i];
        m_key[i] = m_key[j];
        m_key[j] = k;
    }

    decryptInt1 = 0;
    decryptInt2 = 0;
}

uint StringParser::parseKey()
{
     int i = 0;

     decryptInt1 = decryptInt1 + 1 & 255;
     decryptInt2 = decryptInt2 + m_key[decryptInt1] & 255;
     i = m_key[decryptInt1];
     m_key[decryptInt1] = m_key[decryptInt2];
     m_key[decryptInt2] = i;

     return m_key[i + m_key[decryptInt1] & 255];
}

QByteArray StringParser::parseString(QByteArray param1)
{
    int i = 0;
    while (i < param1.size())
    {
        param1[i] = param1[i] ^ parseKey();
        i++;
    }

    return param1;
}

void StringParser::getString(QByteArray &param1)
{
    param1 = parseString(param1);
}
