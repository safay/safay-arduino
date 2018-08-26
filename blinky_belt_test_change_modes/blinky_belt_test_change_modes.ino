// Code to power a strip of Adafruit DotStar LEDs for a glowing belt project.

// Load the dotstar library
#include <Adafruit_DotStar.h>
// Because conditional #includes don't work w/Arduino sketches...
//#include <SPI.h>         // COMMENT OUT THIS LINE FOR GEMMA OR TRINKET
#include <avr/power.h> // ENABLE THIS LINE FOR GEMMA OR TRINKET

// Number of LEDs in strip
#define NUMPIXELS 60 

// Control the LEDs from these two pins:
#define DATAPIN    4
#define CLOCKPIN   5
Adafruit_DotStar strip = Adafruit_DotStar(NUMPIXELS, DATAPIN, CLOCKPIN, DOTSTAR_BRG);

// Initialize LED strip variables
// int head  = 0, tail = -20; // Index of first 'on' and 'off' pixels
int red = 0, blue = 0, green = 0;
int i = 0;

// Hard-coded Gamma correction for LED intensity
const uint8_t PROGMEM gamma8[] = {
    0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
    0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  1,  1,  1,  1,
    1,  1,  1,  1,  1,  1,  1,  1,  1,  2,  2,  2,  2,  2,  2,  2,
    2,  3,  3,  3,  3,  3,  3,  3,  4,  4,  4,  4,  4,  5,  5,  5,
    5,  6,  6,  6,  6,  7,  7,  7,  7,  8,  8,  8,  9,  9,  9, 10,
   10, 10, 11, 11, 11, 12, 12, 13, 13, 13, 14, 14, 15, 15, 16, 16,
   17, 17, 18, 18, 19, 19, 20, 20, 21, 21, 22, 22, 23, 24, 24, 25,
   25, 26, 27, 27, 28, 29, 29, 30, 31, 32, 32, 33, 34, 35, 35, 36,
   37, 38, 39, 39, 40, 41, 42, 43, 44, 45, 46, 47, 48, 49, 50, 50,
   51, 52, 54, 55, 56, 57, 58, 59, 60, 61, 62, 63, 64, 66, 67, 68,
   69, 70, 72, 73, 74, 75, 77, 78, 79, 81, 82, 83, 85, 86, 87, 89,
   90, 92, 93, 95, 96, 98, 99,101,102,104,105,107,109,110,112,114,
  115,117,119,120,122,124,126,127,129,131,133,135,137,138,140,142,
  144,146,148,150,152,154,156,158,160,162,164,167,169,171,173,175,
  177,180,182,184,186,189,191,193,196,198,200,203,205,208,210,213,
  215,218,220,223,225,228,231,233,236,239,241,244,247,249,252,255 };

// Initialize potentiometer
#define POTPINA 2    // select the input pin for the potentiometer
#define POTPINB 3
// variables to store the value coming from the sensor
int valA = 0;
int valB = 0;

// The rotary switch has eight pins; they are attached to the eight Arduino digital pins defined here  
int pinA = 3;
int pinB = 6;
int pinC = 8;
int pinD = 9;
int pinE = 10;
int pinF = 11;
int pinG = 12;
int pinH = 14;

byte leds = 0;

struct rgb
{
  int red;
  int green;
  int blue;
};

bool greenup = true;
bool redup = true;
bool blueup = true;

struct rgb rgbArray[NUMPIXELS];

void setup(){
  // if analog input pin 0 is unconnected, random analog
  // noise will cause the call to randomSeed() to generate
  // different seed numbers each time the sketch runs.
  // randomSeed() will then shuffle the random function.
  randomSeed(analogRead(0));

  // Set up the serial monitor
  Serial.begin(9600);
  Serial.println("--- Start Serial Monitor ---");

  #if defined(__AVR_ATtiny85__) && (F_CPU == 16000000L)
    clock_prescale_set(clock_div_1); // Enable 16 MHz on Trinket
  #endif
  strip.begin(); // Initialize LED strip pins for output
  strip.show();  // Turn all LEDs off ASAP

  for (int i=0; i <= NUMPIXELS; i++){
    rgbArray[i].red = 0;
    rgbArray[i].green = 0;
    rgbArray[i].blue = 0;    
  };


  // initialize builtin LED
//  pinMode(LED_BUILTIN, OUTPUT);
//  pinMode(ledPin, OUTPUT);
  
  // Initialize pins for rotary switch
  // INPUT_PULLUP results in the pin being LOW when a switch is closed, HIGH when open: 
  // https://www.arduino.cc/en/Tutorial/InputPullupSerial 
  pinMode(pinA, INPUT_PULLUP);  
  pinMode(pinB, INPUT_PULLUP);  
  pinMode(pinC, INPUT_PULLUP);  
  pinMode(pinD, INPUT_PULLUP);  
  pinMode(pinE, INPUT_PULLUP);  
  pinMode(pinF, INPUT_PULLUP);  
  pinMode(pinG, INPUT_PULLUP);  
  pinMode(pinH, INPUT_PULLUP);  
}



 
void loop() 
{
  if (digitalRead(pinA) == LOW)
  {
    valA = analogRead(POTPINA) / 5 + 0.1;    // read the value from the sensor
    Serial.println(valA);
    i = random(NUMPIXELS);
    blue = random(77) + 20;
    green = random(77) + 20;
    red = random(77) + 20;
    strip.setPixelColor(i, pgm_read_byte(&gamma8[red]), pgm_read_byte(&gamma8[green]), pgm_read_byte(&gamma8[blue])); 
    strip.show();                     // Refresh strip
    delay(valA);                        // Pause
    Serial.println("A");
  }
  
  else if (digitalRead(pinB) == LOW)
  {
    red = 0;
    green = 0;
    blue = 0;
    for (int i=0; i <= NUMPIXELS; i++){
      strip.setPixelColor(i, pgm_read_byte(&gamma8[red]), pgm_read_byte(&gamma8[green]), pgm_read_byte(&gamma8[blue]));
      strip.show();
      delay(3);
    };
    delay(20); 
    Serial.println("B");
  }
  
  else if (digitalRead(pinC) == LOW)
  {
    valA = analogRead(POTPINA) / 5 + 0.1;    // read the value from the sensor
    // set first pixel to new value based on value of pixel at index = 1
    if (rgbArray[1].red < 200)
    {
      rgbArray[0].red = rgbArray[1].red + 1;
    }
    else
    {
      rgbArray[0].red = 50;
    };

    if (rgbArray[1].blue < 199)
    {
      rgbArray[0].blue = rgbArray[1].blue + 1;
    }
    else
    {
      rgbArray[0].blue = 35;
    };

    // set pixels to rgbArray
    for (int i=0; i <= NUMPIXELS; i++){      
      strip.setPixelColor(i, pgm_read_byte(&gamma8[rgbArray[i].red]), pgm_read_byte(&gamma8[rgbArray[i].green]), pgm_read_byte(&gamma8[rgbArray[i].blue]));
    };

    // show
    strip.show();
    
    // increment rgbArray
    for (int i=NUMPIXELS; i > 0; i--){      
      rgbArray[i].red = rgbArray[i - 1].red;
      rgbArray[i].green = rgbArray[i - 1].green;
      rgbArray[i].blue = rgbArray[i - 1].blue;
    };
    delay(valA);
    Serial.println("C");
  }

  else if (digitalRead(pinD) == LOW)
  {
    valA = analogRead(POTPINA) / 5 + 0.1;    // read the value from the sensor
    // set first pixel to new value based on value of pixel at index = 1
    if (rgbArray[1].green < 200)
    {
      rgbArray[0].green = rgbArray[1].green + 1;
    }
    else
    {
      rgbArray[0].green = 20;
    };

    if (rgbArray[1].blue < 199)
    {
      rgbArray[0].blue = rgbArray[1].blue + 1;
    }
    else
    {
      rgbArray[0].blue = 35;
    };

    // set pixels to rgbArray
    for (int i=0; i <= NUMPIXELS; i++){      
      strip.setPixelColor(i, pgm_read_byte(&gamma8[rgbArray[i].red]), pgm_read_byte(&gamma8[rgbArray[i].green]), pgm_read_byte(&gamma8[rgbArray[i].blue]));
    };

    // show
    strip.show();
    
    // increment rgbArray
    for (int i=NUMPIXELS; i > 0; i--){      
      rgbArray[i].red = rgbArray[i - 1].red;
      rgbArray[i].green = rgbArray[i - 1].green;
      rgbArray[i].blue = rgbArray[i - 1].blue;
    };
    delay(valA);
    Serial.println("D");
  }
  
  else if (digitalRead(pinE) == LOW)
  {
    valA = analogRead(POTPINA) / 5 + 0.1;    // read the value from the sensor
    // set first pixel to new value based on value of pixel at index = 1
    if (rgbArray[1].green < 197 && greenup)
    {
      rgbArray[0].green = rgbArray[1].green + 1;
    }
    else if (rgbArray[1].green > 35 && !greenup)
    {
      rgbArray[0].green = rgbArray[1].green - 1;
    }
    else
    {
      greenup = !greenup;
    }

    if (rgbArray[1].blue < 201 && blueup)
    {
      rgbArray[0].blue = rgbArray[1].blue + 1;
    }
    else if (rgbArray[1].blue > 35 && !blueup)
    {
      rgbArray[0].blue = rgbArray[1].blue - 1;
    }
    else
    {
      blueup = !blueup;
    }

    // set pixels to rgbArray
    for (int i=0; i <= NUMPIXELS; i++){      
      strip.setPixelColor(i, pgm_read_byte(&gamma8[rgbArray[i].red]), pgm_read_byte(&gamma8[rgbArray[i].green]), pgm_read_byte(&gamma8[rgbArray[i].blue]));
    };

    // show
    strip.show();
    
    // increment rgbArray
    for (int i=NUMPIXELS; i > 0; i--){      
      rgbArray[i].red = rgbArray[i - 1].red;
      rgbArray[i].green = rgbArray[i - 1].green;
      rgbArray[i].blue = rgbArray[i - 1].blue;
    };
    delay(valA);
    Serial.println("E");
  }
  
  else if (digitalRead(pinF) == LOW)
  {
    valA = analogRead(POTPINA) / 5 + 1;    // read the value from the sensor
    valB = analogRead(POTPINB) / 5 + 40;    // read the value from the sensor
    // set first pixel to new value based on value of pixel at index = 1
    if (rgbArray[1].green < 197 && greenup)
    {
      rgbArray[0].green = rgbArray[1].green + 1;
    }
    else if (rgbArray[1].green > 35 && !greenup)
    {
      rgbArray[0].green = rgbArray[1].green - 1;
    }
    else
    {
      greenup = !greenup;
    }

    if (rgbArray[1].blue < 203 && blueup)
    {
      rgbArray[0].blue = rgbArray[1].blue + 1;
    }
    else if (rgbArray[1].blue > 35 && !blueup)
    {
      rgbArray[0].blue = rgbArray[1].blue - 1;
    }
    else
    {
      blueup = !blueup;
    }

    if (rgbArray[1].red < 131 && redup)
    {
      rgbArray[0].red = rgbArray[1].red + 1;
    }
    else if (rgbArray[1].red > 35 && !redup)
    {
      rgbArray[0].red = rgbArray[1].red - 1;
    }
    else
    {
      redup = !redup;
    }

    // set pixels to rgbArray
    for (int i=0; i <= NUMPIXELS; i++){      
      strip.setPixelColor(i, pgm_read_byte(&gamma8[rgbArray[i].red]), pgm_read_byte(&gamma8[rgbArray[i].green]), pgm_read_byte(&gamma8[rgbArray[i].blue]));
    };

    // show
    strip.show();
    
    // increment rgbArray
    for (int i=NUMPIXELS; i > 0; i--){      
      rgbArray[i].red = rgbArray[i - 1].red;
      rgbArray[i].green = rgbArray[i - 1].green;
      rgbArray[i].blue = rgbArray[i - 1].blue;
    };
    delay(valA);
    Serial.print("F");
    Serial.print(valA);
    Serial.print("-");
    Serial.print(valB);
    Serial.println();
  }
  
  else if (digitalRead(pinG) == LOW)
  {
    valA = analogRead(POTPINA) / 5 + 1;    // read the value from the sensor
    valB = analogRead(POTPINB) / 5 + 40;    // read the value from the sensor
    // set first pixel to new value based on value of pixel at index = 1
    if (rgbArray[1].green < valB + 21 && greenup)
    {
      rgbArray[0].green = rgbArray[1].green + 1;
    }
    else if (rgbArray[1].green > 35 && !greenup)
    {
      rgbArray[0].green = rgbArray[1].green - 1;
    }
    else
    {
      greenup = !greenup;
    }

    if (rgbArray[1].blue < valB + 1 && blueup)
    {
      rgbArray[0].blue = rgbArray[1].blue + 1;
    }
    else if (rgbArray[1].blue > 2 && !blueup)
    {
      rgbArray[0].blue = rgbArray[1].blue - 1;
    }
    else
    {
      blueup = !blueup;
    }

    if (rgbArray[1].red < valB + 17 && redup)
    {
      rgbArray[0].red = rgbArray[1].red + 1;
    }
    else if (rgbArray[1].red > 35 && !redup)
    {
      rgbArray[0].red = rgbArray[1].red - 1;
    }
    else
    {
      redup = !redup;
    }

    // set pixels to rgbArray
    for (int i=0; i <= NUMPIXELS; i++){      
      strip.setPixelColor(i, pgm_read_byte(&gamma8[rgbArray[i].red]), pgm_read_byte(&gamma8[rgbArray[i].green]), pgm_read_byte(&gamma8[rgbArray[i].blue]));
    };

    // show
    strip.show();
    
    // increment rgbArray
    for (int i=NUMPIXELS; i > 0; i--){      
      rgbArray[i].red = rgbArray[i - 1].red;
      rgbArray[i].green = rgbArray[i - 1].green;
      rgbArray[i].blue = rgbArray[i - 1].blue;
    };
    delay(valA);
    Serial.print("G");
    Serial.print(valA);
    Serial.print("-");
    Serial.print(valB);
    Serial.println();
  }
  
  else if (digitalRead(pinH) == LOW)
  {
    digitalWrite(LED_BUILTIN, HIGH);
    delay(50);
    Serial.println("H");
  }  
  
  else
  {
    digitalWrite(LED_BUILTIN, LOW);
    Serial.println("none");
    delay(50);
  }
}


