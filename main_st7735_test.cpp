/**
 *  Demo code for ILI9341 320x240 screen with touch capability
 * 
 
 * 
 */
#include "lnArduino.h"
#include "ili_lnSpi.h"
#include "simpler9341_priv.h"
#include "st7735_priv.h"
#include "opensans20.h"
lnSpi9341          *ili;
hwlnSPIClass *spi;


const uint8_t no_data[1]={0};

// screen is rotated by 90 degrees
#define SCREEN_WIDTH    WW
#define SCREEN_HEIGHT   HH

/**
 * 
 */
void setup()
{
    Logger("Setuping up DSO...\n");
    
     // arbitrer must be created with screen already set up
    // ili must be first
    //
#define FAST 1
    spi=new hwlnSPIClass(0,-1);    
    lnSPISettings transaction(FAST*36*1000*1000+(1-FAST)*500, SPI_MSBFIRST, SPI_MODE0,-1);
    spi->begin();
    
    
    ili=new lnSpi9341( SCREEN_HEIGHT, SCREEN_WIDTH,
                                    spi,        
                                    PB11,       // DC/RS
                                    PB8,       // CS 
                                    PB9);  // Reset
    spi->beginTransaction(transaction);    
    
    ili->init(st7735_data,NULL);  
    ili->forceChipId(CHIPID_ST7735);
  //  ili->setRotation(1);
    ili->fillScreen(GREEN);   
#define FONT OpenSans_Regular28pt7b    
    ili->setFontFamily(&FONT,&FONT,&FONT) ;
    ili->setFontSize(ili9341::SmallFont);
    lnPinMode(LN_SYSTEM_LED,lnOUTPUT);
   }

void once()
{
   ili->fillScreen(BLACK);
   ili->setFontSize(ili9341::SmallFont);
   ili->setTextColor(ILI_WHITE, ILI_BLACK);
   ili->square(ILI_RED,0,0,SCREEN_WIDTH/2,SCREEN_HEIGHT);
   ili->square(ILI_BLUE,SCREEN_WIDTH/2,0,SCREEN_WIDTH/2,SCREEN_HEIGHT);
   ili->print(0,SCREEN_HEIGHT/2,"RED");
   ili->print(SCREEN_WIDTH/2,SCREEN_HEIGHT/2,"BLUE");
}

/**
 * @brief 
 * 
 */
void loop()
{
    once();
    while(1)
    {
        lnDigitalToggle(LN_SYSTEM_LED);
        //foo();
        lnDelayMs(1000);
    }
}
//
