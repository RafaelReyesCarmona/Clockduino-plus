/* Copyrigth (c), 2020, Francisco Rafael Reyes Carmona.
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
