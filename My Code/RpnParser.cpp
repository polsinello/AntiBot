#include "RpnParser.h"

RpnParser::RpnParser(QString path) :
    m_path(path)
{
}

void RpnParser::readFile()
{
    QFile f(m_path);

    f.open(QIODevice::ReadOnly);
    m_byteCode = f.readAll();

    f.close();
}

QList<int> RpnParser::parseFile()
{
    readFile();

    QList<QByteArray> code = m_byteCode.split('\n');
    QList<int> result;

    for (int i = 0; i < code.size(); i++)
    {
        if (code[i].indexOf("writeByte") + 1)
        {
            i++;
            QList<int> calcul;
            QString j = code[i];
            while (!(j.indexOf("kill") + 1))
            {
                j = code[i];
                if (j.indexOf("push") + 1)
                {
                    calcul.append(j.split(' ').last().toInt());
                }
                else if (j.indexOf("add") + 1)
                {
                    int a = calcul[calcul.size() - 2];
                    int b = calcul.last();

                    calcul.removeLast();
                    calcul.removeLast();

                    calcul.append(b + a);
                }
                else if (j.indexOf("modulo") + 1)
                {
                    int a = calcul[calcul.size() - 2];
                    int b = calcul.last();

                    calcul.removeLast();
                    calcul.removeLast();

                    calcul.append(a % b);
                }
                else if (j.indexOf("rshift") + 1)
                {
                    int a = calcul[calcul.size() - 2];
                    int b = calcul.last();

                    calcul.removeLast();
                    calcul.removeLast();

                    calcul.append(a >> b);
                }
                else if (j.indexOf("lshift") + 1)
                {
                    int a = calcul[calcul.size() - 2];
                    int b = calcul.last();

                    calcul.removeLast();
                    calcul.removeLast();

                    calcul.append(a << b);
                }
                else if (j.indexOf("bitand") + 1)
                {
                    int a = calcul[calcul.size() - 2];
                    int b = calcul.last();

                    calcul.removeLast();
                    calcul.removeLast();

                    calcul.append(a && b);
                }
                else if (j.indexOf("bitxor") + 1)
                {
                    int a = calcul[calcul.size() - 2];
                    int b = calcul.last();

                    calcul.removeLast();
                    calcul.removeLast();

                    calcul.append(a ^ b);
                }
                else if (j.indexOf("subtract") + 1)
                {
                    int a = calcul[calcul.size() - 2];
                    int b = calcul.last();

                    calcul.removeLast();
                    calcul.removeLast();

                    calcul.append(a - b);
                }
                else if (j.indexOf("negate") + 1)
                {
                    int a = calcul.last();

                    calcul.removeLast();

                    calcul.append(-a);
                }
                else if (j.indexOf("dup") + 1)
                {
                    calcul.append(calcul.last());
                }
                else if (j.indexOf("jump") + 1)
                {
                    QString offset = j.split(' ').last();
                    offset.remove(offset.size() - 1, 1);
                    QString k = "";
                    while (!(k.indexOf(offset) + 1))
                    {
                        i++;
                        k = code[i];
                    }

                    i--;
                }

                i++;
            }

            result.append(calcul.first());
        }
    }

    return result;
}

int RpnParser::getDecryptKeyPos(int decryptInt)
{
    QList<QByteArray> code = m_byteCode.split('\n');
    QString j;

    for (int i = 0; i < code.size(); i++)
    {
        j = code[i];
        if (j.contains("decode"))
        {
            i++;
            j = code[i];
            while (!j.contains("kill"))
            {
                if (j.contains("push"))
                    return j.split(' ').last().toInt() ^ decryptInt;

                i++;
                j = code[i];
            }
        }
    }
}
