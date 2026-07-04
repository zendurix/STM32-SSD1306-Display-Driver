 SSD1306 128x32 OLED example usage:  
 Board used - Nucleo STM32U031R8T6.    
   
 Connections:   
 OLED VCC -> Board 3V3  
 OLED GND -> Board GND  
 OLED SDA -> Board D14 (PB9 on processor)  
 OLED SCL -> Board D15 (PB8 on processor)  
   
 This programs shows 3 modes of my own SSD1306 128x32 driver:    
 0 - Clock Mode - Display shows current time in HH:MM format. start time for now is hard coded 00::00,  
 .	but can be later setup with additional buttons.  
  
 1 - Text Mode - Display shows text in 8x8 font. Screen is divided into 16x4 tiles for letters (spacing == 0)  
 .	text can be written on screen as single characters with xy pos (where xy is letter tile pos x:0-15, y:0-3)  
 .	or as strings with starting pos xy, strings are written char by char into next tiles, and wrap to next line  
  
 2 - Images Mode - Display shows 128x32 black and white images, that are stored on device flash memory. Images are stored  
 .	as uint8_t[512] bitmaps representing whole buffer of oled screen.  
 .	Images can be converted to this format with "\python_scripts\image_converter.py"  
  
 Pressing USER button (on board):  
 - short press (<1s) - toggle display ON/OFF, switch to next image in images mode  
 - long press (>1s) - switch to next Mode (0 -> 1 -> 2 -> 0 -> 1 ...)  
 
 Uses 8x8 bitmap font from: https://github.com/dhepper/font8x8/blob/master/font8x8_basic.h  
 
