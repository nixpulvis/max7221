#include "max7221.h"

//
// MAX7221_init implementation.
//
int MAX7221_init(byte options)
{
  int ret = 0;
  // Setup SPI communication for the MAX7221.
  spi_init(SPI_MASTER);
  if (options == MAX7221_INIT_BCD || options == MAX7221_INIT_RAW)
  {
    // Turn on the first 4 digits.
    ret |= MAX7221_set_scan_limit(4);
    // Set to full intensity.
    ret |= MAX7221_set_intensity(0xF);
    // Turn on the display.
    ret |= MAX7221_set_power(TRUE);
    // Clear the display.
    ret |= MAX7221_clear();
    // Use BCD decoding if asked.
    if (options == MAX7221_INIT_BCD)
      ret |= MAX7221_set_decode_mode(0xF);
  }
  return ret;
}


//
// MAX7221_set_decode_mode implementation.
//
int MAX7221_set_decode_mode(byte value)
{
  MAX7221_set_register(MAX7221_REGISTER_DECODE_MODE, value);
  return 0;
}


//
// MAX7221_set_intensity implementation.
//
int MAX7221_set_intensity(byte value)
{
  MAX7221_set_register(MAX7221_REGISTER_INTENSITY, value);
  return 0;
}


//
// MAX7221_set_scan_limit implementation.
//
int MAX7221_set_scan_limit(byte value)
{
  MAX7221_set_register(MAX7221_REGISTER_SCAN_LIMIT, value);
  return 0;
}


//
// MAX7221_set_power implementation.
//
int MAX7221_set_power(bool value)
{
  MAX7221_set_register(MAX7221_REGISTER_SHUTDOWN, value ? 0xFF : 0x00);
  return 0;
}


//
// MAX7221_set_display_test implementation.
//
int MAX7221_set_display_test(bool value)
{
  MAX7221_set_register(MAX7221_REGISTER_DISPLAY_TEST, value ? 0xFF : 0x00);
  return 0;
}


//
// MAX7221_display_matrix implementation.
//
int MAX7221_display_matrix(bool matrix[MAX7221_SIZE][MAX7221_SIZE])
{
  int ret = 0;
  for (byte y = 0; y < MAX7221_SIZE; y++)
    ret |= MAX7221_display_vector(y, matrix[y]);

  return ret;
}


//
// MAX7221_display_vector implementation.
//
int MAX7221_display_vector(byte row, bool vector[MAX7221_SIZE])
{
  // Create a byte where it's bits are equivalent to the contiguous
  // values of the vector.
  byte data = 0;
  for (byte x = 0; x < MAX7221_SIZE; x++)
    data |= (vector[x] << x);

  // Display the byte.
  return MAX7221_display_byte(row, data);
}


//
// MAX7221_display_vector implementation.
//
int MAX7221_display_byte(byte row, byte value)
{
  if (0 > row || row > 7)
    return -1;

  // Display the value.
  MAX7221_set_register(row + 1, value);

  return 0;
}


//
// MAX7221_display_bcd_digit implementation.
//
int MAX7221_display_bcd_digit(byte digit, byte value)
{
  // Check the digit range.
  if (0 > digit || digit > 7)
    return -1;
  // Check the value range.
  if (0 > value || value > 0x0F)
    return -1;
  // Display the value.
  MAX7221_set_register(digit + 1, value);
  return 0;
}

//
// MAX7221_display_bcd_int implementation.
//
int MAX7221_display_bcd_int(int32_t value, byte segments)
{
  bool negative = value < 0;
  int32_t val = abs(value);
  for (byte i = 0; i < segments; i++)
  {
    MAX7221_display_bcd_digit(segments - 1 - i, val % 10);
    val /= 10;
  }
  if (negative)
    MAX7221_display_bcd_digit(0, MAX7221_BCD_MINUS);
  return 0;
}

//
// MAX7221_display_bcd_float implementation.
//
// TODO: Write MAX7221_display_bcd_float.


//
// MAX7221_clear implementation.
//
int MAX7221_clear(void)
{
  MAX7221_set_register(0x01, 0x00);
  MAX7221_set_register(0x02, 0x00);
  MAX7221_set_register(0x03, 0x00);
  MAX7221_set_register(0x04, 0x00);
  MAX7221_set_register(0x05, 0x00);
  MAX7221_set_register(0x06, 0x00);
  MAX7221_set_register(0x07, 0x00);
  MAX7221_set_register(0x08, 0x00);
  return 0;
}


//
// MAX7221_set_register implementation.
//
int MAX7221_set_register(byte address, byte value)
{
  spi_start();
  spi_transfer(address & 0xF);
  spi_transfer(value);
  spi_end();
  return 0;
}
