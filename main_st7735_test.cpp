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
#include "../private_include/lnSPI_priv.h"

lnSpi9341          *ili;
lnSPI *spi;
void dummyFunc();

const uint8_t no_data[1]={0};

// screen is rotated by 90 degrees
#define SCREEN_WIDTH    WW
#define SCREEN_HEIGHT   HH

#ifdef USE_RP2040
  #define PIN_DC GPIO8
  #define PIN_CS GPIO9
  #define PIN_RST GPIO10

#else
  #define PIN_DC PB11
  #define PIN_CS PB8
  #define PIN_RST PB9
#endif

/**
 * 
 */
void setup()
{
    Logger("Setuping up DSO...\n");
    
     // arbitrer must be created with screen already set up
    // ili must be first
    //

#ifdef USE_RP2040
    lnPinMode(GPIO6, lnSPI_MODE);
    lnPinMode(GPIO7, lnSPI_MODE);
    //lnPinMode(GPIO8, lnSPI_MODE);
#endif    

#define FAST 0
    spi=lnSPI::create(0,-1);    
    lnSPISettings transaction(FAST*36*1000*1000+(1-FAST)*50*1000, SPI_MSBFIRST, SPI_MODE0,-1);    

#ifdef USE_RP2040
    lnPinMode(PIN_DC, lnOUTPUT);
    lnPinMode(PIN_CS, lnOUTPUT);
    lnPinMode(PIN_RST, lnOUTPUT);
#endif    
    
  spi->begin();

    ili=new lnSpi9341( SCREEN_HEIGHT, SCREEN_WIDTH,
                                    spi,        
                                    PIN_DC,       // DC/RS
                                    PIN_CS,       // CS 
                                    PIN_RST);  // Reset
    spi->set(transaction);    
    
    ili->init(st7735_data,NULL);  
    ili->forceChipId(CHIPID_ST7735);
  //  ili->setRotation(1);
    ili->fillScreen(RED);   
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
   ili->print(0,SCREEN_HEIGHT/2,"RD");
   ili->print(SCREEN_WIDTH/2,SCREEN_HEIGHT/2,"BU");
}
void twice()
{
   ili->fillScreen(BLACK);
   ili->setFontSize(ili9341::SmallFont);
   ili->setTextColor(ILI_WHITE, ILI_BLACK);
   ili->square(ILI_GREEN,0,0,SCREEN_WIDTH/2,SCREEN_HEIGHT);
   ili->square(ILI_BLACK,SCREEN_WIDTH/2,0,SCREEN_WIDTH/2,SCREEN_HEIGHT);
   ili->print(0,SCREEN_HEIGHT/2,"GR");
   ili->print(SCREEN_WIDTH/2,SCREEN_HEIGHT/2,"BK");
}

/**
 * @brief 
 * 
 */
//extern LN_SPI_Registers *aspi0 ;
void loop()
{
    bool one=true;
    once();
    while(1)
    {
        if(one) once();
          else twice();
        one=!one;
        lnDigitalToggle(LN_SYSTEM_LED);
        //foo();
        lnDelayMs(1000);
        dummyFunc();
    }
}
void dummyFunc()
{
  //Logger("%x\n",aspi0->DATA);
}
//
