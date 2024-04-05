// Simple project using Arduino UNO with Pimoroni 7x11px LED Matrix Display to display smooth animation
// however, since the Pimoroni display is not supported on WOKWI, I´m simulating this display with NeoPixel canvas

// created by upir, 2024
// youtube channel: https://www.youtube.com/upir_upir

// YouTube video: https://youtu.be/sZZFgSmYJjc
// Source files: https://github.com/upiir/arduino_pimoroni_7x11px_display
// Wokwi simulation: https://wokwi.com/projects/394323585291513857

// Links from the video:
// Previous video (gear indicator): https://youtu.be/QixtxaAda18
// Pimoroni 7x11px LED Matrix Display: https://shop.pimoroni.com/products/11x7-led-matrix-breakout?variant=21791690752083
// Adafruit IS31FL3731 board: https://www.adafruit.com/product/2946
// Adafruit documentation: https://learn.adafruit.com/i31fl3731-16x9-charliplexed-pwm-led-driver/pinouts
// Smoothstep function: https://stackoverflow.com/questions/28889210/smoothstep-function
// Adafruit library: https://github.com/adafruit/Adafruit_IS31FL3731
// Neopixel canvas: https://wokwi.com/projects/379096458121466881
// Online Image Converter: https://lvgl.io/tools/imageconverter
// Breadboard wires: https://s.click.aliexpress.com/e/_Dkbngin
// Arduino UNO R3: https://s.click.aliexpress.com/e/_AXDw1h
// Arduino breadboard prototyping shield: https://s.click.aliexpress.com/e/_DlxEfPX
// NeoPixel starting project: https://wokwi.com/projects/392984672413834241
// Photopea (online graphics editor like Photoshop): https://www.photopea.com/


// Related videos with LED Matrix Displays:
// LED ring light for potentiometer - https://youtu.be/Bot865qmdsM
// Robot eyes display: https://youtu.be/If-hiuwsQh0
// Arduino Wood Clock: https://youtu.be/50bVXHYW_9Q
// Arduino UNO R4 display: https://youtu.be/Qpi0Y5bcvlQ
// LED matrix badges: https://youtu.be/MRTxTx8bgYg
// Why are pixels square?: https://youtu.be/oLgUtjyKO6Q
// Three knob controller: https://youtu.be/e2UNsZPjHkk
// Really old display: https://youtu.be/PBaL9w5w-2c



#include <Wire.h> // wire library is required for IIC/I2C communication
#include <Adafruit_GFX.h> // adafruit GFX is required for the IS31FL3731 chip
#include <Adafruit_IS31FL3731.h> // library for Pimoroni 11x7px LED matrix display (and Adafruit 16x9 LED matrix display)
#include <Adafruit_NeoPixel.h> // library for NeoPixels - only used for testing on WOKWI 

Adafruit_IS31FL3731 ledmatrix = Adafruit_IS31FL3731(); // initialization of the Pimoroni 11x7px display

#define PIN_NEO_PIXEL 6  // Arduino pin that connects to NeoPixel
#define NUM_PIXELS 77 // The number of LEDs (pixels) on NeoPixel

Adafruit_NeoPixel NeoPixel(NUM_PIXELS, PIN_NEO_PIXEL, NEO_GRB + NEO_KHZ800); // set the NeoPixel (canvas) initialization, only used for WOKWI simulation

// our canvas for pimoroni 11x7px LED matrix display
byte canvas_7x11px[] = { // preinitialize with checkerboard pattern, but will be overwritten later on
  0, 60, 0, 60, 0, 60, 0,
  60, 0, 60, 0, 60, 0, 60,
  0, 60, 0, 60, 0, 60, 0,
  60, 0, 60, 0, 60, 0, 60,
  0, 60, 0, 60, 0, 60, 0,
  60, 0, 60, 0, 60, 0, 60,
  0, 60, 0, 60, 0, 60, 0,
  60, 0, 60, 0, 60, 0, 60,
  0, 60, 0, 60, 0, 60, 0,
  60, 0, 60, 0, 60, 0, 60,
  0, 60, 0, 60, 0, 60, 0
};

// digit 3
byte bitmap_digit_3[] = {
  0x33, 0xc7, 0xff, 0xff, 0xff, 0xc7, 0x33,
  0x9b, 0x5c, 0x00, 0x00, 0x00, 0x5c, 0xc7,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x33, 0xff,
  0x00, 0x00, 0x00, 0x00, 0x33, 0xff, 0x33,
  0x00, 0x00, 0x00, 0x33, 0xff, 0x33, 0x00,
  0x00, 0x00, 0x00, 0xff, 0xff, 0xff, 0xc7,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xff,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xff,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xff,
  0x9b, 0x5c, 0x00, 0x00, 0x00, 0x5c, 0xc7,
  0x33, 0xc7, 0xff, 0xff, 0xff, 0xc7, 0x33
};

// circle, 255 in the middle, 0 around the edges
byte bitmap_circle[] = {
  0x02, 0x0d, 0x17, 0x1b, 0x17, 0x0d, 0x02,
  0x1b, 0x30, 0x41, 0x47, 0x41, 0x30, 0x1b,
  0x3b, 0x5b, 0x74, 0x7d, 0x74, 0x5b, 0x3b,
  0x5b, 0x86, 0xa7, 0xb3, 0xa7, 0x86, 0x5b,
  0x74, 0xa7, 0xcf, 0xe0, 0xcf, 0xa7, 0x74,
  0x7d, 0xb3, 0xe0, 0xff, 0xe0, 0xb3, 0x7d,
  0x74, 0xa7, 0xcf, 0xe0, 0xcf, 0xa7, 0x74,
  0x5b, 0x86, 0xa7, 0xb3, 0xa7, 0x86, 0x5b,
  0x3b, 0x5b, 0x74, 0x7d, 0x74, 0x5b, 0x3b,
  0x1b, 0x30, 0x41, 0x47, 0x41, 0x30, 0x1b,
  0x02, 0x0d, 0x17, 0x1b, 0x17, 0x0d, 0x02,
};

// smoothstep function, will return value between 0-1
// based on - https://stackoverflow.com/questions/28889210/smoothstep-function
float smoothstep(float edge0, float edge1, float x)
{
  // Scale, bias and saturate x to 0..1 range
  x = constrain((x - edge0) / (edge1 - edge0), 0.0, 1.0);
  // Evaluate polynomial
  return x * x * (3 - 2 * x);
}


int offset = 128; // offset variable for animation
int offset_inc = 10; // offset increment for setting the speed of the animation

void setup() {

  NeoPixel.begin();  // initialize the NeoPixel object

  //Serial.begin(9600);
  //Serial.println("ISSI swirl test");

  if (! ledmatrix.begin(0x75)) {
    //Serial.println("IS31 not found");
    //while (1); // commented out for the WOKWI simulation, since the Pimoroni display is not connected/supported on WOKWI
  }
  //Serial.println("IS31 found!");
}

void loop() { // main loop

  // offset variable is used in the animation
  // change the offset_inc (increment) above to play the animation faster or slower
  offset = offset + offset_inc;
  if ((offset > 400) && (offset_inc > 0)) {
    offset_inc = offset_inc * -1;
  }
  if ((offset < -200) && (offset_inc < 0)) {
    offset_inc = offset_inc * -1;
  }


  // draw on our canvas
  for (uint8_t pixel = 0; pixel < 77; pixel++) {
    // draw digit 3
    //canvas_7x11px[pixel] = bitmap_digit_3[pixel];

    // draw the circle
    //canvas_7x11px[pixel] = bitmap_circle[pixel];

    // step function
    /*if (bitmap_circle[pixel] < offset) {
      canvas_7x11px[pixel] = 0;
      }
      else {
      canvas_7x11px[pixel] = 255;
      }*/

    // smoothstep function(s)
    float smoothstep_inner = smoothstep(offset - 100, offset - 5, bitmap_circle[pixel]); // inner circle for smoothstep
    float smoothstep_outer = smoothstep(offset + 100, offset + 5, bitmap_circle[pixel]); // outer circle for smoothstep

    float reveal_image = smoothstep_inner * bitmap_digit_3[pixel]; // revealing the "bitmap_digit_3" image
    //canvas_7x11px[pixel] = round(smoothstep_inner * 255.0); // just the inner smoothstep
    //canvas_7x11px[pixel] = round(smoothstep_inner * smoothstep_outer * 255.0); // just the outline
    // final version = revealing the image + outline circle
    canvas_7x11px[pixel] = constrain(reveal_image + (smoothstep_inner * smoothstep_outer * 255.0), 0, 255);
  }


  // Transfer the content of the 11x7 canvas to the 11x7 display
  // Since the Adafruit library is made for 16x9 display, we need to do this in two steps
  //
  // This is the placement of Pimoroni 11x7px content on Adafruit 16x9px canvas
  //
  // A => first half of the 11x7 content  - 7x6px
  // B => second half of the 11x7 content - 7x5px
  // empty => pixel not used
  //
  //
  //     0 0 0 0 0 0 0 0 0 0 1 1 1 1 1 1
  //     0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5
  //    ┌─┬─┬─┬─┬─┬─┬─┬─┬─┬─┬─┬─┬─┬─┬─┬─┐
  //   0│A│A│A│A│A│A│A│ │B│B│B│B│B│B│B│ │        Pimoroni 11x7px (7x11px)
  //    ├─┼─┼─┼─┼─┼─┼─┼─┼─┼─┼─┼─┼─┼─┼─┼─┤
  //   1│A│A│A│A│A│A│A│ │B│B│B│B│B│B│B│ │            ┌──┬───────────────┐
  //    ├─┼─┼─┼─┼─┼─┼─┼─┼─┼─┼─┼─┼─┼─┼─┼─┤            │O │ A A A A A A A │
  //   2│A│A│A│A│A│A│A│ │B│B│B│B│B│B│B│ │            │  │ A A A A A A A │
  //    ├─┼─┼─┼─┼─┼─┼─┼─┼─┼─┼─┼─┼─┼─┼─┼─┤      ┌─────┘  │ A A A A A A A │
  //   3│A│A│A│A│A│A│A│ │B│B│B│B│B│B│B│ │      │o 3-5V  │ A A A A A A A │
  //    ├─┼─┼─┼─┼─┼─┼─┼─┼─┼─┼─┼─┼─┼─┼─┼─┤      │o SDA   │ A A A A A A A │
  //   4│A│A│A│A│A│A│A│ │B│B│B│B│B│B│B│ │      │o SCL   │ A A A A A A A │
  //    ├─┼─┼─┼─┼─┼─┼─┼─┼─┼─┼─┼─┼─┼─┼─┼─┤      │o -     │ B B B B B B B │
  //   5│A│A│A│A│A│A│A│ │ │ │ │ │ │ │ │ │      │o GND   │ B B B B B B B │
  //    ├─┼─┼─┼─┼─┼─┼─┼─┼─┼─┼─┼─┼─┼─┼─┼─┤      └─────┐  │ B B B B B B B │
  //   6│ │ │ │ │ │ │ │ │ │ │ │ │ │ │ │ │            │  │ B B B B B B B │
  //    ├─┼─┼─┼─┼─┼─┼─┼─┼─┼─┼─┼─┼─┼─┼─┼─┤            │O │ B B B B B B B │
  //   7│ │ │ │ │ │ │ │ │ │ │ │ │ │ │ │ │            └──┴───────────────┘
  //    ├─┼─┼─┼─┼─┼─┼─┼─┼─┼─┼─┼─┼─┼─┼─┼─┤
  //   8│ │ │ │ │ │ │ │ │ │ │ │ │ │ │ │ │
  //    └─┴─┴─┴─┴─┴─┴─┴─┴─┴─┴─┴─┴─┴─┴─┴─┘
  //

  // this is step 1...
  for (uint8_t x = 0; x < 7; x++) {
    for (uint8_t y = 0; y < 6; y++) {
      ledmatrix.drawPixel(x, y, canvas_7x11px[y * 7 + x] / 8); // transfer first half of the picture
    }
  }
  // and this is step 2
  for (uint8_t x = 8; x < 15; x++) {
    for (uint8_t y = 0; y < 5; y++) {
      ledmatrix.drawPixel(x, y, canvas_7x11px[ (7 * 6) + y * 7 + (x - 8)] / 8); // transfer second half of the picture
    }
  }


  // Neopixel code below
  // neopixels are only used to simulate the content of the Pimoroni 11x7px display inside WOKWI emulator

  // clear neopixels
  NeoPixel.clear();  // set all pixel colors to 'off'. It only takes effect if pixels.show() is called
  // transfer the content of the 11x7 canvas to neopixels
  for (uint8_t pixel = 0; pixel < 77; pixel++) {
    NeoPixel.setPixelColor(pixel, NeoPixel.Color(canvas_7x11px[pixel], canvas_7x11px[pixel], canvas_7x11px[pixel]));
  }
  NeoPixel.show(); // show all the set pixels on neopixel canvas
}



