/* 
graphics.h

Copyright © 2021 Francisco Rafael Reyes Carmona. 
All rights reserved. 

rafael.reyes.carmona@gmail.com 


  This file is part of Clockduino-plus. 

  Clockduino-plus is free software: you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published by
  the Free Software Foundation, either version 3 of the License, or
  (at your option) any later version.

  Clockduino-plus is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU General Public License for more details.

  You should have received a copy of the GNU General Public License
  along with Clockduino-plus.  If not, see <https://www.gnu.org/licenses/>.

 */

static const unsigned char FULL_BAT[] PROGMEM = {
  B00110000, B10011001, B11100111,
  B00110000, B10011001, B11100111,
  B00111100, B10011001, B11100111,
  B00110000, B10011001, B11100111,
  B00110000, B10011001, B11100111,
  B00111100, B10011001, B11100111,
  B00111100, B00011000, B10000110,
  B01111100, B00011100, B10000110
};
/*
static const unsigned char BAT_CHG[] PROGMEM = {
  B00000000, B00000010, B00000000,
  B00000000, B00000110, B00000000,
  B00000000, B00011110, B00000000,
  B00000111, B01111110, B00000000,
  B00111110, B11111110, B00000001,
  B11111000, B11111111, B00000111,
  B11100000, B11111111, B00011111,
  B10000000, B01111111, B00111100,
  B00000000, B01111110, B11100000,
  B00000000, B01111000, B00000000,
  B00000000, B01100000, B00000000,
  B00000000, B01000000, B00000000
};
 */
static const unsigned char PER[] PROGMEM = {
  B00100111,
  B00110101,
  B00010111,
  B00001000,
  B00000100,
  B00111010,
  B00101011,
  B00111001,
};
static const unsigned char BAT_0[] PROGMEM = {
  B00011110,
  B00111111,
  B00110011,
  B00111011,
  B00110111,
  B00110011,
  B00111111,
  B00011110
};
static const unsigned char BAT_1[] PROGMEM = {
  B00001100,
  B00001110,
  B00001100,
  B00001100,
  B00001100,
  B00001100,
  B00001100,
  B00011110
};
static const unsigned char BAT_2[] PROGMEM = {
  B00011110,
  B00111111,
  B00110001,
  B00111100,
  B00001110,
  B00000011,
  B00111111,
  B00111111
};
static const unsigned char BAT_3[] PROGMEM = {
  B00011110,
  B00111111,
  B00110001,
  B00111100,
  B00111100,
  B00110001,
  B00111111,
  B00011110
};

static const unsigned char BAT_4[] PROGMEM = {
  B00110000,
  B00111000,
  B00111100,
  B00110110,
  B00111111,
  B00111111,
  B00110000,
  B00110000
};
static const unsigned char BAT_5[] PROGMEM = {
  B00111111,
  B00111111,
  B00000011,
  B00011111,
  B00111111,
  B00110000,
  B00111111,
  B00011111
};
static const unsigned char BAT_6[] PROGMEM = {
  B00011110,
  B00111111,
  B00000011,
  B00011111,
  B00111111,
  B00110011,
  B00111111,
  B00011110
};
static const unsigned char BAT_7[] PROGMEM = {
  B00111111,
  B00111111,
  B00110000,
  B00011000,
  B00001100,
  B00001100,
  B00001100,
  B00001100
};
static const unsigned char BAT_8[] PROGMEM = {
  B00011110,
  B00111111,
  B00110011,
  B00111111,
  B00111111,
  B00110011,
  B00111111,
  B00011110
};
static const unsigned char BAT_9[] PROGMEM = {
  B00011110,
  B00111111,
  B00110011,
  B00111111,
  B00111110,
  B00110000,
  B00111111,
  B00011110
};
