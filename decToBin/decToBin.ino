void convert(int16_t val) {

    // Extract the last 7 bits (LSB) and the sign bit + first 4 bits (MSB)
    uint16_t num = abs(val);
    unsigned char byteL = num & 0b1111111;
    unsigned char byteH = (num >> 7) & 0b1111;
    unsigned char signBit;

    if(val<0){
      signBit = 0b0000;
    }
    else{
      signBit = 0b1000;
    }

    uint8_t A = signBit | byteH;
    uint8_t B = 0b10000000 | byteL;
    Serial.print("First: ");
    Serial.println(A);
    Serial.print("Last: ");
    Serial.println(B);
    Serial.println(signBit);
}

void setup(){
}

void loop(){
  for(int i = -2000; i< 2000;i++){
    convert(i);
    Serial.println(i);
  }
}
