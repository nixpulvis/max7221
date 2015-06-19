#include <avr/uart.h>
#include <max7221.h>

// Forward declarations.
void assert(const char *name, bool test);

int main(void)
{
  // Setup the UART, necessary for stdio actions.
  uart_init();

  // Initialize the max7221.
  MAX7221_init(MAX7221_INIT_NONE);

  printf("\nRunning Tests\n");

  // Configuration Tests
  //////////////////////

  assert("config_decode_mode", MAX7221_set_decode_mode(8) == 0);

  return 0;
}

//
// assert implementation.
//
void assert(const char *name, bool test)
{
  if (test)
    printf("%s PASS\n", name);
  else
    printf("%s FAIL\n", name);
}
