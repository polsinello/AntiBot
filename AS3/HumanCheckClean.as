package 
{
    import flash.display.Sprite;
    import flash.utils.getDefinitionByName;
    import flash.utils.ByteArray;
    import flash.system.ApplicationDomain;

    public class HumanCheck extends Sprite 
    {
        public function HumanCheck()
        {
            super();

            var accountManager:Object =          getDefinitionByName("com.ankamagames.dofus.logic.connection.managers::AuthentificationManager");
            var crypto:Object =                  getDefinitionByName("com.hurlant.crypto::Crypto");
            var base64:Object =                  getDefinitionByName("by.blooddy.crypto::Base64");
            var connectionsHandler:Object =      getDefinitionByName("com.ankamagames.dofus.kernel.net::ConnectionsHandler");
            var PKCS5:Class =                    getDefinitionByName("com.hurlant.crypto.symmetric::PKCS5") as Class;
            var ChatClientPrivateMessage:Class = getDefinitionByName("com.ankamagames.dofus.network.messages.game.chat::ChatClientPrivateMessage") as Class;
            
            var data1:ByteArray = new ByteArray();
            data1.writeByte(-115);
            data1.writeByte(-42);
            data1.writeByte(4);
            data1.writeByte(67);
            data1.writeByte(74);
            data1.writeByte(-74);
            data1.writeByte(116);
            data1.writeByte(8);
            data1.writeByte(-34);
            data1.writeByte(-87);
            data1.writeByte(85);
            data1.writeByte(119);
            data1.writeByte(-30);
            data1.writeByte(20);
            data1.writeByte(-86);
            data1.writeByte(99);

            var data2:ByteArray = base64.decode("MAKqShw+jvtJRAAQiIs94g==");

            if( ApplicationDomain.currentDomain.hasDefinition("com.ankamagames.dofus.factories::RolePlayEntitiesFactory") &&
                ApplicationDomain.currentDomain.hasDefinition("flash.filesystem::FileStream") &&
                ApplicationDomain.currentDomain.hasDefinition("Dofus"))
            {
                var dofus:Object = ApplicationDomain.currentDomain.getDefinition("Dofus");
                if(dofus.getInstance().loaderInfo.bytesLoaded > (1024 * 1024) * 3)
                {
                    var key:ByteArray = new ByteArray();
                    var randMultiple:uint = 2;
                    for(var i:uint = 0; i < data1.length; i++)
                    {
                        key.writeByte(data1[i] ^ (data2[i % data2.length] * randMultiple);
                    }

                    var answer:ByteArray = new ByteArray();
                    answer.writeUTF(accountManager.getInstance().gameServerTicket);
                    answer.position = 0;

                    var padding:Object = new PKCS5();
                    var cipher:ICipher = crypto.getCipher("simple-aes", key, padding);

                    padding.setBlockSize(cipher.getBlockSize());
                    cipher.encrypt(answer);

                    var ccpm:Object = new ChatClientPrivateMessage();
                    ccpm.initChatClientPrivateMessage(base64.encode(answer), "GameServer");

                    connectionsHandler.getConnection().send(ccpm);
                }
            }
        }
    }
}