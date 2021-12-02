//---WS2812B RGB LED CONTROL---//
#include <FastLED.h>
#define LED_PIN 5
#define NUM_LEDS 8
CRGB leds[NUM_LEDS];

//-------AUX PIN CONTROL-------//
const byte switch_pin = 3;

//----------FADELOOP-----------//             
bool fadeLoop_gate = false;
bool fadeLoop_init = false;

//----------SWAPMEET-----------//
volatile byte switch_state = false;
bool flop_switch = false;
bool instant = false;

//--------PROGRAM START--------//
/*
 1) Turns on/off WS2812B (can be repurposed for any type) strip RGB LEDs via a button.
 2) LEDs are orange color.
 3) LEDs fade up to max brightness then back off to a lower brightness.
 4) LEDs then slow fade orange to red-orange and back in a loop.
 5) Optional photocell influence brightness during fade loop so that LEDs get 
    brighter in the dark and dimmer in bright light.
*/
    
void setup()
{
  FastLED.addLeds<WS2812, LED_PIN, GRB>(leds, NUM_LEDS);
  pinMode(switch_pin, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(switch_pin), swapMeet, FALLING);
  Serial.begin(9600);
}

// main loop
void loop() 
{  
  TerminatorEyes();
}


// turns off LEDs when the off button is pressed
void killSwitch()
{
  switch (instant)
  {
    case true:
    leds[0] = CRGB::Black;
    leds[1] = CRGB::Black;
    leds[2] = CRGB::Black;
    leds[3] = CRGB::Black;
    leds[4] = CRGB::Black;
    leds[5] = CRGB::Black;
    leds[6] = CRGB::Black;
    leds[7] = CRGB::Black;
    // can also be CRGB(0, 0, 0); instead of :Black
    FastLED.show();
    instant = false;
    flop_switch = false;
    fadeLoop_gate = false;
    fadeLoop_init = false;
    break;
  }  
}

// handles bool variable changes for gatekeeping in all functions
void swapMeet()
{
  switch_state = !switch_state;
  
  if (switch_state == true)
  {
    flop_switch = true;
    instant = false;
    fadeLoop_gate = false;
    fadeLoop_init = false;
  }
  
  if (switch_state == false)
  {
    instant = true;
  }
}

// power on effect
void TerminatorEyes()
{
  if (flop_switch == true && instant == false)
  {
    leds[0] = CRGB::Black;
    leds[1] = CRGB::Black;
    leds[2] = CRGB::Black;
    leds[3] = CRGB::Black;
    leds[4] = CRGB::Black;
    leds[5] = CRGB::Black;
    leds[6] = CRGB::Black;
    leds[7] = CRGB::Black;
    int redValue = leds[0].r = leds[1].r = leds[2].r = leds[3].r = leds[4].r = leds[5].r = leds[6].r = leds[7].r;
    int greenValue = leds[0].g = leds[1].g = leds[2].g = leds[3].g = leds[4].g = leds[5].g = leds[6].g = leds[7].g;
  
    for(int fadeValue = redValue; fadeValue < 255; fadeValue +=5)
    { 
      if(instant == true)
      {
        killSwitch();
      }
      if(flop_switch == true)
      {
        redValue += 5;
        greenValue = (redValue * .14);
        leds[0].r = leds[1].r = leds[2].r = leds[3].r = leds[4].r = leds[5].r = leds[6].r = leds[7].r = redValue;
        leds[0].g = leds[1].g = leds[2].g = leds[3].g = leds[4].g = leds[5].g = leds[6].g = leds[7].g = greenValue;
        FastLED.show();
        // number inside of brackets sets brightness relative to full (256)
        delay(18);
      }
    }
    for(int fadeValue = redValue; fadeValue > 120; fadeValue -=5)
    {
      if(instant == true)
      {
        killSwitch();
      }
      if(flop_switch == true)
      {
        redValue -= 5;
        greenValue = (redValue * .14);
        leds[0].r = leds[1].r = leds[2].r = leds[3].r = leds[4].r = leds[5].r = leds[6].r = leds[7].r = redValue;
        leds[0].g = leds[1].g = leds[2].g = leds[3].g = leds[4].g = leds[5].g = leds[6].g = leds[7].g = greenValue;
        FastLED.show();
        delay(20);
      }
    }   
    if (instant == true)
    {
      fadeLoop_gate = false;
      fadeLoop_init = false;
    }
    if (flop_switch == true && instant == false)
    {
      fadeLoop_gate = true;
      fadeLoop_init = true;   
    }
  }
  fadeLoop(); 
}    

// forever fade loop
void fadeLoop()
{
  if (fadeLoop_gate == true)
  { 
    flop_switch = false;
    leds[0].r = 120;
    leds[0].g = 17;
    leds[0].b = 0;
    leds[1].r = 120;
    leds[1].g = 17;
    leds[1].b = 0;
    leds[2].r = 120;
    leds[2].g = 17;
    leds[2].b = 0;
    leds[3].r = 120;
    leds[3].g = 17;
    leds[3].b = 0;
    leds[4].r = 120;
    leds[4].g = 17;
    leds[4].b = 0;
    leds[5].r = 120;
    leds[5].g = 17;
    leds[5].b = 0;
    leds[6].r = 120;
    leds[6].g = 17;
    leds[6].b = 0;
    leds[7].r = 120;
    leds[7].g = 17;
    leds[7].b = 0;
    int redValue = leds[0].r = leds[1].r = leds[2].r = leds[3].r = leds[4].r = leds[5].r = leds[6].r = leds[7].r;
    int greenValue = leds[0].g = leds[1].g = leds[2].g = leds[3].g = leds[4].g = leds[5].g = leds[6].g = leds[7].g;
    FastLED.show();      
    for(int fadeValue = redValue; fadeValue > 20; fadeValue -=5)
    {   
      if(instant == true) 
      {
        killSwitch();
      }
      if (fadeLoop_init == true)
      {
        redValue -= 5;
        greenValue = (redValue * .14);
        leds[0].g = leds[1].g = leds[2].g = leds[3].g = leds[4].g = leds[5].g = leds[6].g = leds[7].g = greenValue;
        FastLED.show();
        delay(200);  
      }
    } 
    for (int  fadeValue = redValue; fadeValue < 120; fadeValue += 5)
    {
      if(instant == true) 
      {
        killSwitch();
      }
      if (fadeLoop_init == true)
      {
        redValue += 5;
        greenValue = (redValue * .14);
        leds[0].r = leds[1].r = leds[2].r = leds[3].r = leds[4].r = leds[5].r = leds[6].r = leds[7].r = 120;
        leds[0].g = leds[1].g = leds[2].g = leds[3].g = leds[4].g = leds[5].g = leds[6].g = leds[7].g = greenValue;
        FastLED.show();
        delay(200);
      }
    }
    delay(0);
  }
}