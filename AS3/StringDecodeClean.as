package 
{
   import flash.display.Sprite;
   import flash.utils.ByteArray;
   import flash.utils.Endian;
   
   public class StringDecode extends Sprite
   {
        public function StringDecode()
        {
            super();
        }

        private static var bin1:Class = binaryDaya1; // class_4
        private static var bin2:Class = binaryDaya2; // class_6
        private static var bin3:Class = binaryDaya3; // class_3
        private static var stringList:Array = new Array();
        private static var key:Array = new Array();
        private static var isInitialized:Boolean = false;
        private static var var_10:int;

        private static function init() : void // method_1
        {
            var data1:ByteArray = new bin1() as ByteArray;
            var data2:ByteArray = new bin2() as ByteArray;
            var data3:ByteArray = new bin3() as ByteArray;

            data3.endian = Endian.LITTLE_ENDIAN;
            var_10 = data3.readInt(); // 2157131618 ( BIG: 929202323 )

            var size:int = data2.readByte(); // 1
            for(var i:int = 0; i < size; i++)
            {
                getKey(data2);
            }

            size = data1.readInt(); // 9
            for(var i:int = 0; i < size; i++)
            {
                (data1, key[i % key.length]);
            }
        }

        private static function decode(data:ByteArray, key:ByteArray) : void // method_3
        {
            var size:int = data.readInt(); // 74
            var decoded:ByteArray = new ByteArray();

            data.readBytes(decoded, 0, size);

            var decoder:Decoder = new Decoder(key);
            decoder.getString(decoded);

            decoded.position = 0;
            stringList.push(decoded.readUTFBytes(decoded.length));
        }

        private static function getKey(data:ByteArray) : void // method_2
        {
            var _loc2_:ByteArray = new ByteArray();

            data.readBytes(_loc2_, 0, 16);
            _loc2_.position = 0;
            key.push(_loc2_);
        }

        public static function getString(id:int) : String // method_7
        {
            if(!isInitialized)
                init();

            return stringList[id ^ var_10];
        }
   }
}