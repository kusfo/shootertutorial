#include <stdbool.h>
#include <stdio.h>
#include "assets2banks.h"
#include "libs/SMSlib.h"
#include "libs/GSLib.h"

unsigned char deltax = 0;
unsigned char deltay = 0;
unsigned int frame_cnt = 0;

struct {
    unsigned char x;
    unsigned char y;
    signed char deltax;
    signed char deltay;
} player;

void init_console() {
    SMS_init();
    SMS_setSpriteMode(SPRITEMODE_NORMAL);
    SMS_useFirstHalfTilesforSprites(false);
    SMS_VDPturnOnFeature(VDPFEATURE_LEFTCOLBLANK);
}

void manage_input() {
    unsigned int keys = SMS_getKeysHeld();
    if(keys & PORT_A_KEY_LEFT) {
        player.deltax = -1;
    } else if(keys & PORT_A_KEY_RIGHT) {
        player.deltax = 1;
    } else {
        player.deltax = 0;
    }
    if(keys & PORT_A_KEY_UP) {
        player.deltay = -1;
    } else if(keys & PORT_A_KEY_DOWN) {
        player.deltay = 1;
    } else {
        player.deltay = 0;
    }
}

void draw_player() {
    player.x += player.deltax;
    player.y += player.deltay;
    SMS_addSprite(player.x+8,player.y,257);
    if((frame_cnt&15) < 7) {
        SMS_addSprite(player.x,player.y+8,258);
        SMS_addSprite(player.x,player.y+16,258);
    } else {
        SMS_addSprite(player.x,player.y+8,262);
        SMS_addSprite(player.x,player.y+16,262);
    }
    SMS_addSprite(player.x+8,player.y+8,259);
    SMS_addSprite(player.x+16,player.y+8,260);
    SMS_addSprite(player.x+24,player.y+8,261);
    
    SMS_addSprite(player.x+8,player.y+16,263);
    SMS_addSprite(player.x+16,player.y+16,264);
    SMS_addSprite(player.x+24,player.y+16,265);
    SMS_addSprite(player.x+8,player.y+24,266);
}

void main() {
	init_console();
    SMS_loadBGPalette(level1_palette_bin);  
    SMS_loadSpritePalette(navepalette_bin);  
    SMS_loadTiles(&level1_tiles_bin, 0, level1_tiles_bin_size);
    SMS_loadTiles(&navetiles_bin, 256, navetiles_bin_size);
    GSL_initializeMap(&level1_scrolltable_bin, &level1_metatiles_bin);
	GSL_positionWindow(0,0);
	GSL_refreshVDP();
    SMS_displayOn();
    deltax = 1;
    player.x = 20;
    player.y = 30;
    player.deltax = 0;
    player.deltay = 0;
	while (1) {
        GSL_scroll(deltax,deltay);
        if(frame_cnt == 100) {
            deltax = 1;
        }
        if((GSL_getCurrentX() + 256) == GSL_getMapWidthInPixels()) {
            deltax = 0;
        }
        frame_cnt++;
        manage_input();
        SMS_initSprites();
        draw_player();
        SMS_waitForVBlank();
        GSL_VBlank(); 
        SMS_copySpritestoSAT();
    }
}
SMS_EMBED_SEGA_ROM_HEADER(9999, 0); // code 9999 hopefully free, here this means 'homebrew'
SMS_EMBED_SDSC_HEADER_AUTO_DATE(0, 0, "1985Alternativo", "Shooter Tutorial",
	"Tutorial for elotrolado.net");