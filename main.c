#include <stdlib.h>
#include <string.h>
#include "bcd.h"
#include "neslib.h"
#include <nes.h>
#include "Collisions.h"
#include "vrambuf.h"
#include "ConstData.h"

// link the pattern table into CHR ROM
//#link "chr_generic.s"
// BCD arithmetic support
//#link "bcd.c"
//#link "Collisions.c"
// VRAM update buffer
//#link "vrambuf.c"

// enable horizontal scrolling
//#define NES_MIRRORING 1




// setup PPU and tables
void setup_graphics() {
  // clear sprites
  oam_clear();
  // set palette colors
  pal_all(PALETTE);
}



void main(void)
{
  const unsigned char* runanimright[] = {run1,run2,run3,run4};
  struct Entity P = {
    8,100,100,run3,1
  };
  struct GameState GS = {
    map1
  };
  char i = 3;
  char state = 0;
  setup_graphics();
   
  bank_bg(1);
  vram_adr(NTADR_A(0,4));
  vram_unrle(GS.CurMap);
  bank_bg(1);
  
  vrambuf_clear();
  set_vram_update(updbuf);
  
  // enable rendering
  ppu_on_all();
  //vrambuf_put(NTADR_A(1,1), "hey", 3);
  
  
  // infinite loop
    while(1) {

      // do this at the start of each frame
      char oam_id = 0;
      // Do this when "drawing" each sprite
      P.CurSprite = runanimright[i];
      oam_id = oam_meta_spr(P.x, P.y, oam_id, P.CurSprite);
      // Do this to "hide" any remaining sprites
      oam_hide_rest(oam_id);

      state?--P.x:++P.x;
      if(!(P.x %15)){
        --i;
        if(i== 0){
          i = 3;
        }
      }
      if( P.x > 240  || P.x < 8){
        state = !state;

      }
      vrambuf_flush();
    }
  
}
