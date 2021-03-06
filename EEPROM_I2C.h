#ifndef EEPROM_I2C_h
#define EEPROM_I2C_h

#if ARDUINO >= 100
#include "Arduino.h"
#else
#include "WProgram.h"
#endif


class EEPROM_I2C{
	public:
		/**
		 * Begins the Wire interface to the given device.
		 *
		 * It will try to guess page size and address word size based on the size of the device.
		 * 
		 * @param deviceAddress Byte address of the device.
		 * @param deviceSize    Max size in bytes of the device (divide your device size in Kbits by 8)
		 */
		void begin(byte deviceAddress, unsigned int deviceSize);
		
		void writeByte(unsigned int eeaddresspage, byte data);
		byte readByte(unsigned int eeaddresspage);
		
		void writePage(unsigned int eeaddresspage, byte* data, byte length );
		void readBuffer(unsigned int eeaddress, byte *buffer, int length );
		
		//uint16_t readPixel(uint16_t theMemoryAddress);
		//void readImage(uint16_t theMemoryAddress, int width, int height);
			
	protected:
		void _beginTransmission(unsigned int eeaddress);
		void _endTransmission();

	private:
		byte deviceAddress;
		byte pageSize;

		bool isAddressSizeTwoWords;
};

#endif