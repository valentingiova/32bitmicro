/**
 * This file should be burned to the target.
 * For testing and fun purposes.
 */

#include <lpc2000/io.h>
#include <lpc2000/interrupt.h>


/**
 * Start with flashing led 12 three times,
 * then flash leds 7 to 14 one after the other.
 */
int main(void) {
  IODIR0 |= 0x0000FF00;
  IOPIN0 |= 0x0000FF00;

  int kaha = 0;
  volatile dummy = 1;

  for (int i = 0; i < 5; i++) {
	  while (dummy++ < 50000) {}
	  dummy = 1;

	  if (kaha) {
		  IOPIN0 |= BIT12;
	  } else {
		  IOPIN0 &= ~BIT12;
	  }

	  kaha = !kaha;
  }

  while (1) {
	  kaha = 1;
	  uint32_t current_led = BIT7;
	  for (int i = 0; i < 15; i++) {

		  while (dummy++ < 5000) {}
		  dummy = 1;

		  if (kaha) {
			  IOPIN0 |= current_led;
			  current_led <<= 1;
		  } else {
			  IOPIN0 &= ~current_led;
		  }
		  kaha = !kaha;
	  }
  }
}
