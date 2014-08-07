package
{
   import flash.utils.ByteArray;

   public class Decoder extends Object
   {

      {
         var bool1:* = false;
         var bool2:* = true;
      }

      public function Decoder(param1:ByteArray = null) {
         var bool1:* = false;
         var bool2:* = true;
         super();
         this.key = new ByteArray();
         if(param1)
         {
            this.init(param1);
         }
      }

      private var decryptInt1:int = 0;

      private var decryptInt2:int = 0;

      private var key:ByteArray;

      private const const:uint = 256;

      public function method_11() : uint { //USELESS
         var bool1:* = true;
         var bool2:* = false;
         return this.const;
      }

      public function init(param1:ByteArray) : void { //method_4
         var bool1:* = false;
         var bool2:* = true;
         var j:int = 0;
         var k:int = 0;

         for (var i:int = 0; i < 256; i++)
            this.key[i] = i;

         for (var i:int = 0; i < 256; i++)
         {
            j = j + this.key[i] + param1[i % param1.length] & 255;
            k = this.key[_loc2_];
            this.key[i] = this.key[j];
            this.key[j] = k;
         }

         this.decryptInt1 = 0;
         this.decryptInt2 = 0;
      }

      private function parseKey() : uint { //method_8
         var bool1:* = true;
         var bool2:* = false;
         var i:int = 0;

         this.decryptInt1 = this.decryptInt1 + 1 & 255;
         this.decryptInt2 = this.decryptInt2 + this.key[this.decryptInt1] & 255;
         i = this.key[this.decryptInt1];
         this.key[this.decryptInt1] = this.key[this.decryptInt2];
         this.key[this.decryptInt2] = i;
         return this.key[i + this.key[this.decryptInt1] & 255];
      }

      public function method_9() : uint { //USELESS
         var bool1:* = true;
         var bool2:* = false;
         return 1;
      }

      public function parseString(param1:ByteArray) : void { //method_5
         var bool1:* = false;
         var bool2:* = true;
         for (var i:int = 0; i < param1.length; i++)
            param1[i] = param1[i] ^ this.method_8();
      }

      public function getString(param1:ByteArray) : void { //method_6
         var bool1:* = false;
         var bool2:* = true;
         this.parseString(param1);
      }

      public function method_10() : void { //USELESS
         var bool1:* = false;
         var bool2:* = true;

         if(this.key != null)
         {
            for (var i:int = 0; i < this.key.length; i++)
               this.key[i] = Math.random() * 256;

            this.key.length = 0;
            this.key = null;
         }

         this.decryptInt1 = 0;
         this.decryptInt2 = 0;
      }
   }
}
