/*********************************************************************
	transient v2 library

	Author : Jean-Marc Chiappa
	Date   : 11.01.2022
	Rev : 1
	
	*******************************************************************/

#ifndef TRANSIENT2_h
#define TRANSIENT2_h

#include "Arduino.h"


class transient2
{
	public:
		transient2(void);
		void begin(uint8_t Pin, uint8_t Input_type=INPUT, uint64_t DebouncerDelay=50);
		uint8_t isChanged();
		// uint8_t getState();
		void changeDebouncerDelay(uint64_t delay);

		enum EDGE {
			NO_CHANGE,
			RISING_EDGE,
			FALLING_EDGE
		};

	private:
		uint8_t PinNumber;
		uint8_t Last_input_state;
		uint64_t t0;
		uint64_t delay=50; //ms
    bool Update=false;
		
};

#endif // TRANSIENT2_h