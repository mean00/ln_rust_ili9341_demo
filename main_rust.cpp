/**
 *  Demo code for ILI9341 320x240 screen with touch capability
 *

 *
 */
#include "../private_include/lnSPI_priv.h"
#include "ili_lnSpi.h"
#include "lnArduino.h"
#include "opensans20.h"
#include "simpler9341_priv.h"
#include "st7735_priv.h"

extern "C" void rnInit();
extern "C" void rnLoop();

/**
 *
 */
void setup()
{
    Logger("Setuping up ST7735 demo...\n");
    rnInit();
}

/**
 * @brief
 *
 */
// extern LN_SPI_Registers *aspi0 ;
void loop()
{
    bool one = true;
    while (true)
    {
        rnLoop();
        one = !one;
        lnDigitalToggle(LN_SYSTEM_LED);
        // foo();
        lnDelayMs(1000);
    }
}
//
