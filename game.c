#include <stdbool.h>
#include <stdio.h>
#include "assets2banks.h"
#include "libs/SMSlib.h"
#include "libs/GSLib.h"

unsigned char deltax = 0;
unsigned char deltay = 0;
unsigned int frame_cnt = 0;

void init_console() {
    SMS_init();
    SMS_setSpriteMode(SPRITEMODE_NORMAL);
    SMS_useFirstHalfTilesforSprites(false);
    SMS_VDPturnOnFeature(VDPFEATURE_LEFTCOLBLANK);
}


void main() {
	init_console();
    SMS_loadBGPalette(level1_palette_bin);    
    SMS_loadTiles(&level1_tiles_bin, 0, level1_tiles_bin_size);
    GSL_initializeMap(&level1_scrolltable_bin, &level1_metatiles_bin);
	GSL_positionWindow(0,0);
	GSL_refreshVDP();
    SMS_displayOn();
    deltax = 1;
	while (1) {
        GSL_scroll(deltax,deltay);
        if(frame_cnt == 100) {
            deltax = 1;
        }
        if((GSL_getCurrentX() + 256) == GSL_getMapWidthInPixels()) {
            deltax = 0;
        }
        frame_cnt++;
        SMS_waitForVBlank();
        GSL_VBlank(); 
    }
}
SMS_EMBED_SEGA_ROM_HEADER(9999, 0); // code 9999 hopefully free, here this means 'homebrew'
SMS_EMBED_SDSC_HEADER_AUTO_DATE(0, 0, "1985Alternativo", "Shooter Tutorial",
	"Tutorial for elotrolado.net");