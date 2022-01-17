#include "transient2.h"


transient2::transient2() {}

void transient2::begin(uint8_t Pin, uint8_t Input_type, uint64_t DebouncerDelay)
{
	this->PinNumber=Pin;
	this->delay=DebouncerDelay;
	if((Input_type==INPUT)||(Input_type==INPUT_PULLUP))
	{
		pinMode(Pin, Input_type);
	}
	else
		pinMode(Pin, INPUT);

	Last_input_state = digitalRead(this->PinNumber);
	t0=0;
	Update=false;
//	Serial.begin(115200);
}

/* Return true if an expected transition occurs
*/
bool transient2::isChanged(void)
{
	bool ret = false;

	uint8_t state = digitalRead(this->PinNumber);
//	Serial.print("1 "+String(Last_input_state)+" "+String(state)+" "+String(Active_Edge));
	if(t0==0) {
		if(state!=Last_input_state) { // transition occurs
			t0=millis();
		}
	}
	else if((millis()-t0)>delay) {
		if(state!=Last_input_state) { // transition occurs
//			Serial.print("-> 4");
			// Current_state=state;	// XOR Current_state
			detected_edge = state==LOW ? FALLING_EDGE : RISING_EDGE ;
			Update=true;
			ret = true;
		}
//		Serial.print("-> 5");
		t0=0;
		Last_input_state = state;
	}

	//Last_input_state = state;
//	Serial.println();
	// Update=true;

	return ret; // no change
}

/* Return current state of bistable variable
*/
uint8_t transient2::getEdge(void)
{	
	if(!Update) isChanged();
	Update=false;
	return detected_edge;
}

void transient2::changeDebouncerDelay(uint64_t delay)
{
	this->delay = delay;
}
