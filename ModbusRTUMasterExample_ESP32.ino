/*
  ModbusRTUMasterExample_ESP32
  
  This example demonstrates how to setup and use the ModbusRTUMaster library on an Arduino Nano ESP32.
  It is intended to be used with a second board running ModbusRTUSlaveExample from the ModbusRTUSlave library.  
  
  Circuit:
  - A pushbutton switch from pin 2 to GND
  - A pushbutton switch from pin 3 to GND
  - A LED from pin 5 to GND with a 330 ohm series resistor
  - A LED from pin 6 to GND with a 330 ohm series resistor
  - A LED from pin 7 to GND with a 330 ohm series resistor
  - A LED from pin 8 to GND with a 330 ohm series resistor
  - The center pin of a potentiometer to pin A0, and the outside pins of the potentiometer to 3.3V and GND
  - The center pin of a potentiometer to pin A1, and the outside pins of the potentiometer to 3.3V and GND 
  - pin 10 to pin 11 of the slave/server board
  - pin 11 to pin 10 of the slave/server board
  - GND to GND of the slave/server board
  - Pin 13 is set up as the driver enable pin. This pin will be HIGH whenever the board is transmitting.
  
  Created: 2023-11-11
  By: C. M. Bulliner
  
*/

#include <ModbusRTUMaster.h>


const uint8_t rxPin = 16;
const uint8_t txPin = 17;

ModbusRTUMaster modbus(Serial2); // serial port, driver enable pin for rs-485 (optional)

bool coils[4] = {1,1,1,1};
bool discreteInputs[4];
uint16_t holdingRegisters[2];
uint16_t inputRegisters[2];


void setup() {
    Serial.begin(115200);
  modbus.begin(38400, SERIAL_8N1, rxPin, txPin);
}

void loop() {
    modbus.readDiscreteInputs(1, 0, discreteInputs, 4);              // slave id, starting data address, bool array to place discrete 
  
    for (int a = 0; a < 4; a++){
        Serial.println(discreteInputs[a]);
        delay(10);
    }


    modbus.readHoldingRegisters(1, 0, holdingRegisters, 2);
    for (int a = 0; a < 2; a++){
        Serial.println(holdingRegisters[a]);
        delay(10);
    }

    delay(200);
      coils[0] = true;
  coils[1] = true;
  coils[2] = true;
  coils[3] = true;
    modbus.writeMultipleCoils(1, 0, coils, 4);
    delay(1000);
  coils[0] = false;
  coils[1] = false;
  coils[2] = false;
  coils[3] = false;
    // coils[4] = {false, false, false, false};
    modbus.writeMultipleCoils(1, 0, coils, 4);
}