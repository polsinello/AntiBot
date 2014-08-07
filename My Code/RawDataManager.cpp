#include "RawDataManager.h"

RawDataManager::RawDataManager(QString ticket, QString swf) :
    m_ticket(ticket),
    m_swf(swf)
{
}

void RawDataManager::processKey()
{
    QString path = getRessourcesPath();
    QString cmd = "java -jar " +path + "/RDM/ffdec.jar -format script:pcode -export script,binaryData " + path + "/RDM/Assets " + m_swf.fileName();
    system(cmd.toStdString().c_str());

    StringReader sr;
    sr.init();
    m_binariesStrings = sr.getResult();
    int decryptInt = sr.getDecryptInt();

    RpnParser p(path + "/RDM/Assets/HumanCheck.as");
    QList<int> result = p.parseFile();
    m_decryptKey = m_binariesStrings[p.getDecryptKeyPos(decryptInt)];
    qDebug() << m_decryptKey.toBase64();

    Writer w1;
    foreach (int i, result)
        w1.writeByte(i);

    QByteArray data1 = w1.getBuffer();    
    for (int i = 0; i < data1.size(); i++)
        m_key[i] = (data1[i] ^ (m_decryptKey[i % m_decryptKey.size()] * 2));

}

QByteArray RawDataManager::encrypt()
{
    using namespace CryptoPP;

    byte key[ CryptoPP::AES::DEFAULT_KEYLENGTH ];
    byte iv[ CryptoPP::AES::BLOCKSIZE ];

    memset( key, 0x00, CryptoPP::AES::DEFAULT_KEYLENGTH );
    memset( iv, 0x00, CryptoPP::AES::BLOCKSIZE );

    AutoSeededRandomPool asrp;
    asrp.GenerateBlock(iv, sizeof(iv));

    const char* tmp_key = m_key.data();
    for (int i = 0; i < AES::DEFAULT_KEYLENGTH; i++)
        key[i] = (byte)tmp_key[i];

    QByteArray m_iv;
    m_iv.append((const char*) iv);
    m_iv = m_iv.mid(0, 16);

    std::string plaintext = m_ticket.toStdString();
    std::string ciphertext;

    CryptoPP::AES::Encryption aesEncryption(key, CryptoPP::AES::DEFAULT_KEYLENGTH);
    CryptoPP::CBC_Mode_ExternalCipher::Encryption cbcEncryption( aesEncryption, iv );

    CryptoPP::StreamTransformationFilter stfEncryptor(cbcEncryption, new CryptoPP::StringSink( ciphertext ) );
    stfEncryptor.Put( reinterpret_cast<const unsigned char*>( plaintext.c_str() ), plaintext.length() + 1 );
    stfEncryptor.MessageEnd();

    QByteArray result(ciphertext.c_str());
    QString part1(result.toHex());
    QString part2(m_iv.toHex());
    result.clear();
    part1.prepend(part2);

    result.append(QByteArray::fromHex(part1.toLatin1()));
    qDebug() << result.toHex() << m_key.toHex();

    return result;
}
