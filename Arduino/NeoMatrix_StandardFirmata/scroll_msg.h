// Adafruit_NeoMatrix example for single NeoPixel Shield.
// Scrolls 'Howdy' across the matrix in a portrait (vertical) orientation.

#include <Adafruit_GFX.h>
#include <Adafruit_NeoMatrix.h>
#include <Adafruit_NeoPixel.h>
#ifndef PSTR
 #define PSTR // Make Arduino Due happy
#endif

#define PIN 6
#define PANELS 2
#define SPEED 80

// MATRIX DECLARATION:
// Parameter 1 = width of NeoPixel matrix
// Parameter 2 = height of matrix
// Parameter 3 = pin number (most are valid)
// Parameter 4 = matrix layout flags, add together as needed:
//   NEO_MATRIX_TOP, NEO_MATRIX_BOTTOM, NEO_MATRIX_LEFT, NEO_MATRIX_RIGHT:
//     Position of the FIRST LED in the matrix; pick two, e.g.
//     NEO_MATRIX_TOP + NEO_MATRIX_LEFT for the top-left corner.
//   NEO_MATRIX_ROWS, NEO_MATRIX_COLUMNS: LEDs are arranged in horizontal
//     rows or in vertical columns, respectively; pick one or the other.
//   NEO_MATRIX_PROGRESSIVE, NEO_MATRIX_ZIGZAG: all rows/columns proceed
//     in the same order, or alternate lines reverse direction; pick one.
//   See example below for these values in action.
// Parameter 5 = pixel type flags, add together as needed:
//   NEO_KHZ800  800 KHz bitstream (most NeoPixel products w/WS2812 LEDs)
//   NEO_KHZ400  400 KHz (classic 'v1' (not v2) FLORA pixels, WS2811 drivers)
//   NEO_GRB     Pixels are wired for GRB bitstream (most NeoPixel products)
//   NEO_RGB     Pixels are wired for RGB bitstream (v1 FLORA pixels, not v2)


// Example for NeoPixel Shield.  In this application we'd like to use it
// as a 5x8 tall matrix, with the USB port positioned at the top of the
// Arduino.  When held that way, the first pixel is at the top right, and
// lines are arranged in columns, progressive order.  The shield uses
// 800 KHz (v2) pixels that expect GRB color data.
Adafruit_NeoMatrix matrix = Adafruit_NeoMatrix(PANELS*8, 8, PIN,
  NEO_MATRIX_TOP     + NEO_MATRIX_RIGHT +
  NEO_MATRIX_COLUMNS + NEO_MATRIX_PROGRESSIVE,
  NEO_GRB            + NEO_KHZ800);

#define SPEED 50                                  //scrpll speed 50mS
static char msg[256] = {"Message in a Bottle"};  // initial message 
int16_t cursor_x;
int16_t string_dots;
unsigned char scroll_delay;
char *buff;
char rcvbuffer[256];
int8_t cr = 255;   // textcolor R value 
int8_t cg = 0;  // textcolor G value 
int8_t cb = 0;  // textcolor B value 

void stringCallback(char *CmdString)  // STRING_DATA handler is here
{
    //Serial.println("stringCallback");
    //Serial.println(CmdString);
    //strcpy(rcvbuffer,CmdString);

// /*  
  unsigned char cmd ;   // control command value
  unsigned int r ;    // command parameterr value 

  //parse command string
  cmd = atoi(strtok(CmdString, ",")); //command code 0x10,0x11,0x12,0x13
  if ( cmd < 0x28 ) {
    r = atoi(strtok(NULL, ","));      // r 0-255
  }else if( cmd  == 0x28 || cmd == 0x29 ){
    buff = strtok(NULL,"");  
  }
  //branch command
  switch (cmd) {
    case 0x20 : strcpy(msg,"");break; //clear massage
    case 0x21 : cr = r; break;             // R intencity
    case 0x22 : cg = r; break;             // G intencity
    case 0x23 : cb = r; break;             // B intencity
    case 0x24 : matrix.setBrightness(r); break;  // brightness
    case 0x25 : matrix.setRotation(r); break;   // scroll direection
    case 0x26 : scroll_delay = r; break;        // scroll speed
    case 0x27 : ; break;             //resarve for future   
    case 0x28 : strcpy(rcvbuffer,buff); break; // message recieve 1st packet
    case 0x29 : strcat(rcvbuffer,buff);        // message recieve next packet
    default:;
  }
 // */
}

void init_panel() {
  matrix.begin();
  matrix.setTextWrap(false);
  matrix.setBrightness(64);
  matrix.setTextColor(matrix.Color(cr,cg,cb));
  matrix.setRotation(0);
  matrix.fillScreen(0);
  cursor_x = matrix.width();
  string_dots = strlen(msg)*6;
  scroll_delay = SPEED;
}

void disp_panel() {
  if(cursor_x-- >= -string_dots){
    matrix.clear();
    matrix.setTextColor(matrix.Color(cr,cg,cb));     
    matrix.setCursor(cursor_x,0);
    matrix.print(msg);
    matrix.show();
    delay(scroll_delay);
  }else{
    cursor_x = matrix.width();;
    if(strlen(rcvbuffer) > 0 ){
      strcpy(msg,rcvbuffer);
      strcpy(rcvbuffer,"");
    }
    string_dots = 6*(strlen(msg)+1);
  }  
}



