#include <avrm/delay.h>
#include <max7221.h>

int main(void)
{
  // Initialize the max7221.
  max7221_init(MAX7221_INIT_BCD);

  // Test setting the digits.
  max7221_display_bcd_digit(0, 1);
  max7221_display_bcd_digit(1, 2);
  max7221_display_bcd_digit(2, 3);
  max7221_display_bcd_digit(3, 4);
  delay_ms(1000);
  max7221_display_bcd_digit(0, MAX7221_BCD_E);
  max7221_display_bcd_digit(1, MAX7221_BCD_H);
  max7221_display_bcd_digit(2, MAX7221_BCD_L);
  max7221_display_bcd_digit(3, MAX7221_BCD_P);
  delay_ms(1000);

  // Test setting an int.
  delay_ms(1000);
  for (int i = 0; i < 100; i++)
  {
    max7221_display_bcd_int(i, 4);
    delay_ms(10);
  }
  max7221_display_bcd_int(-123, 4);
  delay_ms(1000);
  max7221_display_bcd_int(4321, 4);
  delay_ms(1000);

  // Test setting a float.
  max7221_display_bcd_float(123.4, 1, 4, 0);
  delay_ms(1000);

  // Test setting the power.
  max7221_set_power(TRUE);
  delay_ms(1000);
  max7221_set_power(FALSE);
  delay_ms(1000);
  max7221_set_power(TRUE);
  delay_ms(1000);

  // Test setting the intensity.
  max7221_set_intensity(0x03);
  delay_ms(1000);
  max7221_set_intensity(0x0F);
  delay_ms(1000);

  // Test setting the scan limit.
  for (byte i = 0; i < 4; i++)
  {
    max7221_set_scan_limit(i);
    delay_ms(1000);
  }

  // Test setting the decode mode.
  max7221_set_decode_mode(0x00);
  delay_ms(1000);
  max7221_set_decode_mode(0xFF);
  delay_ms(1000);

  // Test the display test.
  max7221_set_display_test(TRUE);
  delay_ms(1000);
  max7221_set_display_test(FALSE);
  delay_ms(1000);

  return 0;
}
