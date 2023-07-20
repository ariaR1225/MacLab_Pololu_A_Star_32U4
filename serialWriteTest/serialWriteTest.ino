void setup() {
  Serial.begin(9600); // Set the baud rate to match your UART device
}

void loop() {
  Serial.write("a\r\n");
  // if (Serial.available()) { // Check if data is available to read
  //   char receivedChar = Serial.read(); // Read a single character from UART

  //   // Do something with the received character
  //   // For example, you can print it to the serial monitor
  //   Serial.print("Received character: ");
  //   Serial.println(receivedChar);
  // }
  // else{
  //   Serial.write("none\r\n");
  // }
}
