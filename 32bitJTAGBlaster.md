# Introduction #

32bit Blaster JTAG interface code.

Original implementation by Rony Bershadsky and Nimrod Talmon [web page link](http://www.cs.tau.ac.il/~nimrodt5/JTAG/index.html)

# Status #

Code compiles for NXP LPC2148

[SVN trunk](http://code.google.com/p/32bitmicro/source/browse/trunk/src/32bitblaster/jtag)

Features
  * Supports JTAG, ARM core, and ICE scan chains
  * UART based communication with the host
  * 4 GPIO pins used for JTAG
    1. P0.4  - clock (TCK)
    1. P0.5  - data output (TDO)
    1. P0.6  - data input (TDI)
    1. P0.28 - mode select (TMS)
    1. P0.29 - voltage reference (VREF)