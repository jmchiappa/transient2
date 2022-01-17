#include "transient2.h"

#define DEFAULT			HIGH
transient2 Button;

void setup(){
	pinMode(LED_BLUE,OUTPUT);
	pinMode(LED_RED,OUTPUT);
	Button.begin(SW1_BTN, INPUT_PULLUP);	// Bouton bleue de la NUCLEO
  Button.changeDebouncerDelay(10);
}

void loop()
{
	if( Button.isChanged() ) {
		uint8_t event = Button.getEdge();
		if( event == transient2::RISING_EDGE ) {
			digitalWrite(LED_BLUE,HIGH);
			delay(15);
			digitalWrite(LED_BLUE,LOW);
		}
		if( event == transient2::FALLING_EDGE ) {
			digitalWrite(LED_RED,HIGH);
			delay(15);
			digitalWrite(LED_RED,LOW);
		}
	}
}
