#include "gbuffer.h"
#include "gbufferconnector.h"
#include "uart_def.h"
#include "uart.h"

extern GBufferConnector conn;

struct data_t {
    uint8_t values[2];
} data;

int C[10] = {-2000,-1000,-100,-50,-1,1,50,100,1000,2000};
void DtoB(int16_t val) {

    // Extract the last 7 bits (LSB) and the sign bit + first 4 bits (MSB)
    uint16_t num = abs(val);
    unsigned char byteL = num & 0b1111111;
    unsigned char byteH = (num >> 7) & 0b1111;
    unsigned char signBit;

    if(val<0){
      signBit = 0b00000;
    }
    else{
      signBit = 0b10000;
    }

    uint8_t A = signBit | byteH;
    uint8_t B = 0b10000000 | byteL;

    UART_IO_BYTE = A;
    Serial.print("H: ");
    Serial.println(byteH);
    UART_IO_BYTE = B;
    Serial.print("L: ");
    Serial.println(byteL);
}

void setup() {
  Uart_begin(9600);
}

void loop() {
  for(int16_t i = 0; i < 10; i++ ){
    DtoB(C[i]);
    delay(10);
  }

}

