
#include <Wire.h>
#include <EEPROM_I2C.h>


// it's only 1Kbit!!!
#define EE24LC01MAXBYTES 1024/8

// the address of your EEPROM
#define DEVICEADDRESS (0x50)

#define TEST_ADDR 16

// this must start on a page boundary!
#define TEST_PAGE_ADDR 0
#define BUFFER_LEN 4

#define SERIAL_DEBUG SerialUSB

EEPROM_I2C eeprom;

void readAndWriteVar() { 
    SERIAL_DEBUG.println("----------------------------------------------");     
    SERIAL_DEBUG.print("SINGLE BYTE: writing and retreiving EEPROM on I2C at address ");
    SERIAL_DEBUG.println(DEVICEADDRESS);
    SERIAL_DEBUG.println("----------------------------------------------");  

    byte curval = eeprom.readByte(TEST_ADDR);

    SERIAL_DEBUG.print("last value: ");
    SERIAL_DEBUG.println(curval);


    curval += 1;
    eeprom.writeByte(TEST_ADDR, curval);

    SERIAL_DEBUG.print("updating to: ");
    SERIAL_DEBUG.println(curval);
    delay(10);

    curval = eeprom.readByte(TEST_ADDR);
    SERIAL_DEBUG.print("new value: ");
    SERIAL_DEBUG.println(curval);    

}

void readAndWritePage() { 
    SERIAL_DEBUG.println("----------------------------------------------");     
    SERIAL_DEBUG.print("PAGE: writing and retreiving EEPROM Page on I2C at address ");
    SERIAL_DEBUG.println(DEVICEADDRESS);
    SERIAL_DEBUG.println("----------------------------------------------");  


    byte testBuffer[BUFFER_LEN + 1];

    // null-terminate for printing!
    testBuffer[BUFFER_LEN] = NULL;

    eeprom.readBuffer(TEST_PAGE_ADDR, testBuffer, BUFFER_LEN);


    SERIAL_DEBUG.print("last value: ");
    SERIAL_DEBUG.println((char*)testBuffer);

    for (int i = 0; i < BUFFER_LEN; i++) {
      // use max to init to all AAAA's on first run.
      testBuffer[i] = max('A', testBuffer[i] + i + 1);
    }

    eeprom.writePage(TEST_PAGE_ADDR, testBuffer, BUFFER_LEN);

    SERIAL_DEBUG.print("updating to: ");
    SERIAL_DEBUG.println((char*)testBuffer);
    delay(10);

    eeprom.readBuffer(TEST_PAGE_ADDR, testBuffer, BUFFER_LEN);
    SERIAL_DEBUG.print("new value: ");
    SERIAL_DEBUG.println((char*)testBuffer);    

}
     
void setup()
{
  SERIAL_DEBUG.begin(57600); 
  while (!SERIAL_DEBUG) {
    ; // wait for SERIAL_DEBUG port to connect. Needed for Leonardo only
  }

  SERIAL_DEBUG.println("IT IS BEGINNING"); 
  delay(2000);
  SERIAL_DEBUG.println("WAIT FOR IT");  
  
  eeprom.begin(DEVICEADDRESS, EE24LC01MAXBYTES);
  
  readAndWriteVar();
  readAndWritePage();
}

void loop()
{
  // Nothing to do during loop
}