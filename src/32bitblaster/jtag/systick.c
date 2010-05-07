void busywait(uint32_t microseconds) {
  T0TC = 0;                   // Zero the timer's counter.
  T0MR0 = microseconds * 6;   // Match register.
  T0MCR = BIT2;               // Stop on match.
  T0TCR = BIT0;               // Start timer0.
  while (T0TCR & BIT0);
}
