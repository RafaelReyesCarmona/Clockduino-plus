/* Copyrigth (c), 2021, Francisco Rafael Reyes Carmona.
 * Reservados todos los derechos.
 *  
 *     Queda totalmente prohibida la distribución, reproducción, copia, almacenamiento o
 * transcripción total o parcial de ésta obra en cualquier soporte físico o electrónico sin el
 * consentimiento expreso del propietario del copyrigth.
 *
 *     Este código se distribuye “tal cual” sin garantía implícita, incluso mercantil, o
 * de uso, así como la adecuación para un propósito concreto.
 *
 *     El autor no se hace responsable de cualquier tipo de daño derivado del uso, así como
 * pérdidas económicas o de información.
 */

// Date and time functions using a DS3231 RTC connected via I2C and Wire lib
#include "RTClib.h"
#include <elapsedMillis.h>
#include <U8x8lib.h>
#include <U8g2lib.h>
#include <SPI.h>
#include "graphics.h"

RTC_DS3231 rtc;
elapsedMillis timeElapsed; //declare global if you don't want it reset every time loop runs
elapsedSeconds timeBackLight;

#define PIN_BL  2
#define LCD_DIN 11
#define LCD_CLK 13
#define LCD_RST 5
#define LCD_CS  12
#define LCD_BL  6
#define SCREEN_WIDTH 96 // OLED display width, in pixels
#define SCREEN_HEIGHT 68 // OLED display height, in pixels
#define display_offset 93
U8G2_HX1230_96X68_1_3W_SW_SPI u8g2(U8G2_R0, /* clock=*/ LCD_CLK, /* data=*/ LCD_DIN, /* cs=*/ LCD_CS, /* reset=*/ LCD_RST);

//char daysOfTheWeek[7][12] = {"Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday"};
char daysOfTheWeekShort[7][4] = {"Sun","Mon","Tue","Wed","Thu","Fri","Sat"};

#define TIME_FONT u8g2_font_logisoso28_tn
#define SECS_FONT u8g2_font_t0_13b_mf

#define BAT_MIN        2950
#define BAT_MAX        4150

// delay in milliseconds to refresh time.
unsigned int interval = 1000;
// Time in seconds to turn of light.
unsigned int time_fade = 6;

enum states {
  CLOCK,
  SETUP,
  ALARM,
  REMEMBER
} state_clockduino;

enum alarms_type {
  ALARM_DEFAULT,
  BEEP,
  LONG_BEEP,
  VIBRATE
};

alarms_type alarm = ALARM_DEFAULT;
alarms_type remember = BEEP;

void setup () {
  Serial.begin(57600);

  u8g2.begin();
  pinMode(LCD_BL, OUTPUT);
  digitalWrite(LCD_BL, HIGH);
  u8g2.setContrast(150);

  while (!Serial); // wait for serial port to connect. Needed for native USB

  if (! rtc.begin()) {
//    Serial.println("Couldn't find RTC");
//    Serial.flush();
    abort();
  }

  if (rtc.lostPower()) {
  //  Serial.println("RTC lost power, let's set the time!");
    // When time needs to be set on a new device, or after a power loss, the
    // following line sets the RTC to the date & time this sketch was compiled
    rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
    // This line sets the RTC with an explicit date & time, for example to set
    // January 21, 2014 at 3am you would call:
    // rtc.adjust(DateTime(2014, 1, 21, 3, 0, 0));
  }

  // When time needs to be re-set on a previously configured device, the
  // following line sets the RTC to the date & time this sketch was compiled
  // rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
  // This line sets the RTC with an explicit date & time, for example to set
  // January 21, 2014 at 3am you would call:
  // rtc.adjust(DateTime(2014, 1, 21, 3, 0, 0));

  u8g2.setFontRefHeightExtendedText();
  u8g2.setDrawColor(1);
  u8g2.setFontPosTop();

  pinMode(PIN_BL, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(PIN_BL), backlight, CHANGE);

  state_clockduino = CLOCK;
}

void loop () {
  switch(state_clockduino){
    case CLOCK:
      show_clock();
      break;
    case SETUP:
      show_setup();
      break;
    case ALARM:
      show_alarm(alarm);
      break;
    case REMEMBER:
      show_remember(remember);
      break;
    default:
      mesg("Error!!!");
      break;
  }
  
}

void mesg(const char* text) {
  uint8_t i, h;
  u8g2_uint_t c, d, l;
  u8g2.firstPage();
  do  {
    u8g2.setFont(SECS_FONT);    
    
    h = u8g2.getMaxCharHeight();
    l = u8g2.getStrWidth(text);
    d = ((SCREEN_WIDTH - l) / 2) - 1;
    c = ((SCREEN_HEIGHT - h) / 2) - 1;

    u8g2.setCursor(d, c);
    u8g2.print(text);
    u8g2.drawFrame(d - 5, c - 5, l + 8, h + 8);
  } while( u8g2.nextPage() );
}

void backlight(){
  digitalWrite(LCD_BL, HIGH);
  timeBackLight = 0;
}

void show_clock(){
  u8g2_uint_t h, c, d, l;
  u8g2_uint_t h2, c2, d2, l2;
  byte percent;
  long v;

  char date_str[16];
  char time_str[6];
  char hour_str[3];
  char min_str[3];
  char secs_str[3];
  char day_str[3];
  char mounth_str[3];

  DateTime now = rtc.now();
  float tempC = rtc.getTemperature();
  
  strcpy(hour_str, u8x8_u8toa(now.hour(), 2));    /* convert hour to a string with two digit */
  strcpy(min_str, u8x8_u8toa(now.minute(), 2));    /* convert mimute to a string with two digits */
  strcpy(time_str, hour_str);
  strcat(time_str, ":");
  strcat(time_str, min_str);
  strcpy(secs_str, u8x8_u8toa(now.second(), 2));    /* convert seconds to a string with two digits */
  strcpy(day_str, u8x8_u8toa(now.day(), 2));
  strcpy(mounth_str, u8x8_u8toa(now.month(), 2));


    u8g2.setFont(TIME_FONT);
    h = u8g2.getMaxCharHeight();
    l = u8g2.getStrWidth(time_str);
    u8g2.setFont(SECS_FONT);
    h2 = u8g2.getMaxCharHeight();
    l2 = u8g2.getStrWidth(secs_str);
    d = ((SCREEN_WIDTH - l) / 2) - 1 - l2/2;
    c = ((SCREEN_HEIGHT - h) / 2) + 3;
    d2 = SCREEN_WIDTH - l2 -1;
    c2 = c + h - h2 - 3;

  v = readVcc();
  percent = map(constrain(v,BAT_MIN,BAT_MAX),BAT_MIN,BAT_MAX,0,100);  
    
  u8g2.firstPage();
  do  {
    u8g2.setFont(TIME_FONT);
    u8g2.setCursor(d,c);
    u8g2.print(hour_str);
    u8g2.print(":");
    u8g2.setCursor(45,c);
    u8g2.print(min_str);
    u8g2.setFont(SECS_FONT);
    u8g2.setCursor(45,2);
    u8g2.print(tempC);
    u8g2.print("\260C");
    u8g2.drawStr(d2,c2,secs_str);
    u8g2.setCursor(0,SCREEN_HEIGHT-h2-1);
    u8g2.print(daysOfTheWeekShort[now.dayOfTheWeek()]);
    u8g2.setCursor(25,SCREEN_HEIGHT-h2-1);
    u8g2.print(day_str);
    u8g2.print("/");
    u8g2.print(mounth_str);
    u8g2.print("/");
    u8g2.print(now.year());
    drawiconbat(percent);
  } while( u8g2.nextPage() );
  /*
    Serial.print(now.year(), DEC);
    Serial.print('/');
    Serial.print(now.month(), DEC);
    Serial.print('/');
    Serial.print(now.day(), DEC);
    Serial.print(" (");
    Serial.print(daysOfTheWeekShort[now.dayOfTheWeek()]);
    Serial.print(") ");
    Serial.print(now.hour(), DEC);
    Serial.print(':');
    Serial.print(now.minute(), DEC);
    Serial.print(':');
    Serial.print(now.second(), DEC);
    Serial.println();
    
    Serial.print(" since midnight 1/1/1970 = ");
    Serial.print(now.unixtime());
    Serial.print("s = ");
    Serial.print(now.unixtime() / 86400L);
    Serial.println("d");

    // calculate a date which is 7 days and 30 seconds into the future
    DateTime future (now + TimeSpan(7,12,30,6));

    Serial.print(" now + 7d + 30s: ");
    Serial.print(future.year(), DEC);
    Serial.print('/');
    Serial.print(future.month(), DEC);
    Serial.print('/');
    Serial.print(future.day(), DEC);
    Serial.print(' ');
    Serial.print(future.hour(), DEC);
    Serial.print(':');
    Serial.print(future.minute(), DEC);
    Serial.print(':');
    Serial.print(future.second(), DEC);
    Serial.println();
   
    Serial.print("Temperature: ");
    Serial.print(rtc.getTemperature());
    Serial.println(" C");

    Serial.println();
    Serial.flush();

    */
  if (Serial.available()){
      
  }
  
  while (timeElapsed < interval/2);


  u8g2.firstPage();
  do  {
    u8g2.setFont(TIME_FONT);
    u8g2.setCursor(d,c);
    u8g2.print(hour_str);
    u8g2.setCursor(45,c);
    u8g2.print(min_str);
    u8g2.setFont(SECS_FONT);
    u8g2.setCursor(45,2);
    u8g2.print(tempC);
    u8g2.print("\260C");
    u8g2.drawStr(d2,c2,secs_str);
    u8g2.setCursor(0,SCREEN_HEIGHT-h2-1);
    u8g2.print(daysOfTheWeekShort[now.dayOfTheWeek()]);
    u8g2.setCursor(25,SCREEN_HEIGHT-h2-1);
    u8g2.print(day_str);
    u8g2.print("/");
    u8g2.print(mounth_str);
    u8g2.print("/");
    u8g2.print(now.year());
    drawiconbat(percent);
  } while( u8g2.nextPage() );

  if (timeBackLight >= time_fade) {
    for (int brightness=255; brightness <= 0; brightness-=17){
      digitalWrite(LCD_BL, brightness);
      delay(30);
    }
    timeBackLight = 0;
  }
    
  while (timeElapsed < interval);

  timeElapsed = 0; // reset the counter to 0 so the counting starts over...  
}

void show_setup(){
  
}

void show_alarm(alarms_type alarm){
  
}

void show_remember(alarms_type alarm){
  
}

void drawiconbat(byte percent) {
  char percent_str[3] = "ff";

  if (percent < 100) sprintf(percent_str, "%02d", percent);
  
  u8g2.drawLine(93-display_offset, 0, 124-display_offset, 0);
  u8g2.drawLine(93-display_offset, 15, 124-display_offset, 15);
  u8g2.drawLine(93-display_offset, 1, 93-display_offset, 14);
  u8g2.drawLine(126-display_offset, 2, 126-display_offset, 13);
  u8g2.drawLine(127-display_offset, 6, 127-display_offset, 9);
  u8g2.drawPixel(125-display_offset, 1);
  u8g2.drawPixel(125-display_offset, 14);

  word w = percent * 3 / 10;
  
  u8g2.drawHLine(95-display_offset, 2, w);
  u8g2.drawHLine(95-display_offset, 13, w);
  if (w > 28) u8g2.drawVLine(123-display_offset, 2, 12);
  if (w > 27) u8g2.drawVLine(122-display_offset, 2, 12);
  if (w > 2) u8g2.drawVLine(97-display_offset, 2, 12);
  if (w > 1) u8g2.drawVLine(96-display_offset, 2, 12);
  if (w > 0) u8g2.drawVLine(95-display_offset, 2, 12);

  switch(percent_str[0]) {
    case '0':
      //u8g.drawXBMP(99, 4, 6, 8, BAT_0);
      break;
    case '1':
      u8g2.drawXBMP(99-display_offset, 4, 6, 8, BAT_1);
      break;
    case '2':
      u8g2.drawXBMP(99-display_offset, 4, 6, 8, BAT_2);
      break;
    case '3':
      u8g2.drawXBMP(99-display_offset, 4, 6, 8, BAT_3);
      break;
    case '4':
      u8g2.drawXBMP(99-display_offset, 4, 6, 8, BAT_4);
      break;
    case '5':
      u8g2.drawXBMP(99-display_offset, 4, 6, 8, BAT_5);
      break;
    case '6':
      u8g2.drawXBMP(99-display_offset, 4, 6, 8, BAT_6);
      break;
    case '7':
      u8g2.drawXBMP(99-display_offset, 4, 6, 8, BAT_7);
      break;
    case '8':
      u8g2.drawXBMP(99-display_offset, 4, 6, 8, BAT_8);
      break;
    case '9':
      u8g2.drawXBMP(99-display_offset, 4, 6, 8, BAT_9);
      break;
  }

  switch(percent_str[1]) {
    case '0':
      u8g2.drawXBMP(107-display_offset, 4, 6, 8, BAT_0);
      break;
    case '1':
      u8g2.drawXBMP(107-display_offset, 4, 6, 8, BAT_1);
      break;
    case '2':
      u8g2.drawXBMP(107-display_offset, 4, 6, 8, BAT_2);
      break;
    case '3':
      u8g2.drawXBMP(107-display_offset, 4, 6, 8, BAT_3);
      break;
    case '4':
      u8g2.drawXBMP(107-display_offset, 4, 6, 8, BAT_4);
      break;
    case '5':
      u8g2.drawXBMP(107-display_offset, 4, 6, 8, BAT_5);
      break;
    case '6':
      u8g2.drawXBMP(107-display_offset, 4, 6, 8, BAT_6);
      break;
    case '7':
      u8g2.drawXBMP(107-display_offset, 4, 6, 8, BAT_7);
      break;
    case '8':
      u8g2.drawXBMP(107-display_offset, 4, 6, 8, BAT_8);
      break;
    case '9':
      u8g2.drawXBMP(107-display_offset, 4, 6, 8, BAT_9);
      break;
  }

  if (percent < 100) {
        u8g2.drawXBMP(115-display_offset, 4, 6, 8, PER);
      }
      else {
        u8g2.drawXBMP(98-display_offset, 4, 24, 8, FULL_BAT);
        u8g2.drawLine(98-display_offset, 3, 121-display_offset, 3);
        u8g2.drawLine(98-display_offset,12, 121-display_offset,12);
        u8g2.drawLine(121-display_offset,4, 121-display_offset,11);
        u8g2.drawLine(124-display_offset,3, 124-display_offset,12);
      }
}
long readVcc() 
{
  long result;
  // Read 1.1V reference against AVcc
  ADMUX = _BV(REFS0) | _BV(MUX3) | _BV(MUX2) | _BV(MUX1);
  delay(2); // Wait for Vref to settle
  ADCSRA |= _BV(ADSC); // Convert
  while (bit_is_set(ADCSRA,ADSC));
  result = ADCL;
  result |= ADCH<<8;
  result = 1125300L / result; // Back-calculate AVcc in mV
  return result;
}
// ------------------------------------------------
