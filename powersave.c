#include "spin1_api.h"

#define abs(x) ((x)<0 ? -(x) : (x))
#define BOARDS1   // rename to BOARDS24 when working with the 24 board machine, BOARDS3 when using 3 board machine
#define DELAY   3 //us delay 

#ifdef BOARDS1
  #define NUMBER_OF_CHIPS 48
  #define XCHIPS 8
  #define YCHIPS 8
  #define XCHIPS_BOARD 8
  #define YCHIPS_BOARD 8
#endif

uint coreID;
uint chipID, chipIDx, chipIDy;

int c_main(void)
{
  // Get core and chip IDs
  coreID = spin1_get_core_id();
  chipID = spin1_get_chip_id();
  
  // get this chip's coordinates for core map
  // CHIP_X(id) and CHIP_Y(id) are defined in sark.h
  chipIDx = chipID>>8; 
  chipIDy = chipID&255;

  // System controller (sc)
  // External 10MHz clock for CPUA & CPUB and div by 4
  // 1111 1111 1111 1111 1111 11X1 100X 1100
  // F    F    F    F    F    F    9    C
  if (coreID==1)
    sc[SC_CLKMUX] = 0xffffff9c;

  // System controller (sc)
  // External 10MHz clock for AHB, Router, SDRAM, CPUA & CPUB and div by 4
  // 1111 1111 1100 X110 0X11 00X1 100X 1100
  // F    F    C    E    7    1    9    C
  //sc[SC_CLKMUX] = 0xffce719c;

  // System controller (sc)
  // External 10/4=2.5MHz clock for AHB, Router, SDRAM, CPUA & CPUB and div by 4 = 625kHz
  // 1111 1111 1111 X111 1X11 11X1 111X 1111
  // F    F    F    F    F    F    F    F
  //if (coreID==1)
  //  sc[SC_CLKMUX] = 0xffffffff;


  // Disable PLL1 and PLL2 (bit-18 = 0)
  // 1111 1111 1111 1X11 1111 1111 1111 1111
  //sc[SC_PLL1] &= 0xfffbffff;
  //sc[SC_PLL2] &= 0xfffbffff;

  // Disable all CPUs (0x5ECXXXXX = security code).
  // CPUs need to be reset for this to work otherwise the CPUs keep on
  // pinging the AHB bus.
  //sc[SC_CPU_DIS]    = 0x5EC3ffff;
  //sc[SC_HARD_RST_P] = 0x5EC3ffff;
  
  return 0;
}
