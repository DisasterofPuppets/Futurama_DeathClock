// Use the Parola library to scroll text on the display
//
// Demonstrates the use of the scrolling function to display text received
// from the serial interface
//
// User can enter text on the serial monitor and this will display as a
// scrolling message on the display.
// Speed for the display is controlled by a pot on SPEED_IN analog in.
// Scrolling direction is controlled by a switch on DIRECTION_SET digital in.
// Invert ON/OFF is set by a switch on INVERT_SET digital in.
//
// UISwitch library can be found at https://github.com/MajicDesigns/MD_UISwitch
// MD_MAX72XX library can be found at https://github.com/MajicDesigns/MD_MAX72XX
//



#include <MD_Parola.h>
#include <MD_MAX72xx.h>
#include <SPI.h>

// set to 1 if we are implementing the user interface pot, switch, etc
#define USE_UI_CONTROL 0

#if USE_UI_CONTROL
#include <MD_UISwitch.h>
#endif

// Turn on debug statements to the serial output
#define DEBUG 0

#if DEBUG
#define PRINT(s, x) { Serial.print(F(s)); Serial.print(x); }
#define PRINTS(x) Serial.print(F(x))
#define PRINTX(x) Serial.println(x, HEX)
#else
#define PRINT(s, x)
#define PRINTS(x)
#define PRINTX(x)
#endif

// Connections for ESP8266 hardware SPI are:
// Vcc       3v3     LED matrixes seem to work at 3.3V
// GND       GND     GND
// DIN        D7     HSPID or HMOSI
// CS or LD   D8     HSPICS or HCS
// CLK        D5     CLK or HCLK
//
#define HARDWARE_TYPE MD_MAX72XX::FC16_HW 
#define MAX_DEVICES 4
#define CLK_PIN   14 //D5
#define DATA_PIN  13 //D7
#define CS_PIN    15 //D8
#define S_PIN     12 //D6

// Assinging a variable to the Parola instance
MD_Parola LCD = MD_Parola(HARDWARE_TYPE, DATA_PIN, CLK_PIN, CS_PIN, MAX_DEVICES);

/* Scrolling parameters
#if USE_UI_CONTROL
const uint8_t SPEED_IN = A5;
const uint8_t DIRECTION_SET = 8;  // change the effect
const uint8_t INVERT_SET = 9;     // change the invert

const uint8_t SPEED_DEADBAND = 5;
#endif // USE_UI_CONTROL
*/

uint8_t scrollSpeed = 25;    // default frame delay value
textEffect_t scrollEffect = PA_SCROLL_LEFT;
textPosition_t scrollAlign = PA_LEFT;
uint16_t scrollPause = 2000; // in milliseconds

// Global message buffers shared by Serial and Scrolling functions
#define	BUF_SIZE	120
char COD1[BUF_SIZE] = { " " };
char deathMessage[BUF_SIZE] = { " " };
char curMessage[BUF_SIZE] = { " " };
char newMessage[BUF_SIZE] = {"DeathClock"};
char Default[BUF_SIZE] = {"DeathClock"};
bool dateshown = false;



char* COD[]={"Ants!! So many ants",
"Radioactive apes",
"Hit by a camel",
"Sucked out an airlock",
"Unable to retrieve carrot",
"Trip over own pants",
"Noxious gasses",
"Venomous rabbit",
"Junk caught in vacuum",
"You get mauled by a bear",
"Surfed to long",
"Planet-wide extinction event",
"Space herpes",
"Ask again later, I'm trying to score with the toaster",
"Reverse enema",
"Get an owwieeee",
"Suffocated by puppets"
};

char* mon[]={
"JAN",
"FEB",
"MAR",
"APR",
"MAY",
"JUN",
"JUL",
"AUG",
"SEP",
"OCT",
"NOV",
"DEC",
};

int day;



void GetDeath()
{


  int MMM = random(0, 12);

  char* month = (mon[MMM]);

  int year = random(2024,2101);

   if (month == "FEB")
     {
     day = random (1,29);
     }
     
   else if(month == "SEP" or month == "APR" or month == "JUN" or month == "NOV")
     {
      day = random (1,31);
     }
     
   else 
     {
      day = random (1,32);
     }

   if (day < 10)
      {
      //add the leading 0 to <10
      }

 

// assign your new message here

     String space = " ";
     String date = day + space + month + space + year;
     //formatting to DD MMM YYYY

     date.toCharArray(curMessage, BUF_SIZE);

}



void setup()
{
  // initiates and displays message to the Serial monitor
  Serial.begin(57600);
  //Serial.print("\n[Parola Scrolling Display]\nType a message for the scrolling display\nEnd message line with a newline");

pinMode(S_PIN,INPUT_PULLUP);

// Initialize the object data. 'LCD' This needs to be called during setup() to initialize new data for the class 
// that cannot be done during the object creation. This form of the method is for backward compatibility 
// and creates one zone for the entire display. 

  LCD.begin();

// Easy start for a non-scrolling text display. This method is a convenient way to set up a 
// static text display. All the data necessary for setup is passed through as parameters and the 
// display animation is started. Assumes one zone only (zone 0).
  
  LCD.displayText(newMessage, scrollAlign, scrollSpeed, scrollPause, scrollEffect, scrollEffect);

}




void loop()
{

 // Animate all the zones in the display using the currently specified text and animation parameters
// bool true if at least one zone animation has completed, false otherwise. 
int var = digitalRead(S_PIN);

  if (LCD.displayAnimate())
    {
      GetDeath();
    if (var == 0 or dateshown == true) //Pushed
    {
      if (dateshown == true){
          int picker = random(0,17);
          strcpy(newMessage,COD[picker]);
   
              LCD.displayReset();
              LCD.displayAnimate();
              dateshown = false;
                            }
      else{
              // Date
              strcpy(newMessage,curMessage);
              LCD.displayReset();
              LCD.displayAnimate();
              dateshown = true;
          }
    
    }
    else{
              strcpy(newMessage,Default);
              LCD.displayReset();
              LCD.displayAnimate();
    }

       
  }

}
