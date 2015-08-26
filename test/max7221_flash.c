#include <max7221.h>

int main(void)
{
  // Initialize the max7221.
  max7221_init(MAX7221_INIT_BCD);

  for (int i = 0; i < 100000; i++)
  {
    max7221_display_bcd_int(i, 4);
    delay_ms(1);
  }

  return 0;
}
