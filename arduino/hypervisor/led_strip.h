//LED-Class to easy access the 8-LED-Strip
//COLOR-INDEX:
//0: White
//1: Red
//2: Green
//3: Blue
//4: Yellow
//5: Purple
//6: Orange
#include <Adafruit_NeoPixel.h>
#include "Arduino.h"
class LED_Strip {
  private:
    static const int __LED_COUNT = 8;
    static const int __LED_PIN = 30;
    int R;
    int G;
    int B;
    Adafruit_NeoPixel *strip;
  public:
    LED_Strip() {}

    void setupLED() {
      strip = new Adafruit_NeoPixel(__LED_COUNT, __LED_PIN, NEO_GRB + NEO_KHZ800);
      strip->begin();
      strip->show();
      strip->setBrightness(50);
    };

    void setColor(int colorIndex) {
      getColor(colorIndex);
      for (int i = 0; i < __LED_COUNT; i++) {
        strip->setPixelColor(i, strip->Color(R, G, B));
      };
      strip->show();
    };
    
    void getColor(int colorIndex) {
      switch (colorIndex) {
        case 6: //Orange
          R = 210;
          G = 55;
          B = 0;
          break;
        case 5: //Purple
          R = 82;
          G = 0;
          B = 144;
          break;
        case 4: //Yellow
          R = 215;
          G = 199;
          B = 0;
          break;
        case 3: //Blue
          R = 0;
          G = 61;
          B = 155;
          break;
        case 2: //Green
          R = 0;
          G = 255;
          B = 84;
          break;
        case 1: //Red
          R = 215;
          G = 17;
          B = 17;
          break;
        case 0: //White
          R = 255;
          G = 255;
          B = 255;
          break;
        default: //White
          R = 255;
          G = 255;
          B = 255;
          break;
      };
    };
};
