#include "EEPROM_I2C.h"
#include <Wire.h>

#if ARDUINO >= 100
#include "Arduino.h"
#else
#include "WProgram.h"
#endif

void EEPROM_I2C::begin(byte deviceAddress, unsigned int deviceSize) {
  this->deviceAddress = deviceAddress;
   
  // Chips 16Kbit (2048KB) or smaller only have one-word addresses.
  // Also try to guess page size from device size (going by Microchip 24LCXX datasheets here).
  if (deviceSize > 256 * 8) {
    this->isAddressSizeTwoWords = true;
    this->pageSize = 32;
  }
  else {
    this->isAddressSizeTwoWords = false;

    if (deviceSize <= 256) {
      this->pageSize = 8;
    }
    else {
      this->pageSize = 16;
    }
  }
  
  Wire.begin();
}

void EEPROM_I2C::writeByte(unsigned int eeaddress, byte data){
  int rdata = data;
  this->_beginTransmission(eeaddress);
  Wire.write(rdata);
  this->_endTransmission();
}

byte EEPROM_I2C::readByte(unsigned int eeaddress){
  int rdata;
  this->_beginTransmission(eeaddress);
  this->_endTransmission();
  
  Wire.requestFrom((byte)this->deviceAddress, (byte)1);
  if (Wire.available()) rdata = Wire.read();
  return rdata;
}

void EEPROM_I2C::writePage(unsigned int eeaddress, byte* data, byte length ){


        
  byte c = 0;
  while (c < length) {

    this->_beginTransmission(eeaddress + c);

    while (c < length) {
      
      Wire.write(data[c++]);

      byte bytesPastPageBoundary = (c + eeaddress) % this->pageSize;
      if (bytesPastPageBoundary == 0) {
        break;
      }
    }
    
    this->_endTransmission();
    
    delay(10);                           // need some delay
  }
}

void EEPROM_I2C::readBuffer(unsigned int eeaddress, byte *buffer, int length ){
  this->_beginTransmission(eeaddress);
  this->_endTransmission();
  Wire.requestFrom((byte)this->deviceAddress, (byte)length);

  for ( int c = 0; c < length; c++ )
    if (Wire.available()) buffer[c] = Wire.read();
}



void EEPROM_I2C::_beginTransmission(unsigned int eeaddress){
  Wire.beginTransmission(this->deviceAddress);

  if (this->isAddressSizeTwoWords) {
    Wire.write((eeaddress >> 8));    // Address High Byte    
  }

  Wire.write((eeaddress & 0xFF));  // Address Low Byte (or only byte for chips 16K or smaller that only have one-word addresses)
}
void EEPROM_I2C::_endTransmission(){
  Wire.endTransmission();
}