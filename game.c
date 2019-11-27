#include <stdbool.h>
#include <stdio.h>
#include "libs/SMSlib.h"

unsigned int frame_cnt = 0;

void init_console() {
    SMS_init();
    SMS_setSpriteMode(SPRITEMODE_NORMAL);
    SMS_useFirstHalfTilesforSprites(false);
    SMS_VDPturnOnFeature(VDPFEATURE_LEFTCOLBLANK);
}


void main() {
	init_console();
    SMS_displayOn();

	while (1) {
        frame_cnt++;
        SMS_waitForVBlank(); 
    }
}
SMS_EMBED_SEGA_ROM_HEADER(9999, 0); // code 9999 hopefully free, here this means 'homebrew'
SMS_EMBED_SDSC_HEADER_AUTO_DATE(0, 0, "1985Alternativo", "Shooter Tutorial",
	"Tutorial for elotrolado.net");