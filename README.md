This is a small demo to drive ILI9341/ST7735/ST889 from a GD32/STM32/CH32/RP2040 over SPI in rust


The different screen only differs by their init file , containing the init sequence.

The overall layout is :

demo app => ILI9341 
         => ILI9341_access (SPI) => rArduino/SPI

The build_default.cmake contains the current target (GD32/STM32/RP2040)

There is a small demo video in the web folder


<video controls>
<source src="web/ili9341e.mp4" type="video/mp4">
</video>
