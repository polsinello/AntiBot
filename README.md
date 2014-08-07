AntiBot
=======

RawDataMessage AntiBot bypass
This is my own C++ up-to-date version of the RawDataMessage implementation (which actually needs a fix)

The AS3 folder is the original deobfuscated code from the RawDataMessage who was taken from Sorrow (https://github.com/LuaxY/Dofus-Anti-Bot)


Explanation of my C++ classe:
  -> The BinariesIO contains two classes that are used to extract 
     the value of the two randome datas
  -> The RpnParser is used to parse the reverse polish bytecode arithmetics
     notation (used by BinariesIO)
  -> The RawDataManager uses the two data extracted from the BinariesIO class and 
     merge them to create the aes encryption key to then encrypt the gameServerTicket
