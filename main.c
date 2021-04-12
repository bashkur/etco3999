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

struct Entity{
  unsigned char x;
  unsigned char y;
  unsigned char dir;		// facing direction (0=right, 1=left)
  byte state;			// EntityState
  unsigned char health;
  const unsigned char* CurSprite;
  unsigned char is_player;
};

struct GameState{
  const unsigned char* CurMap;
};

typedef enum EntityState {
  STANDING, WALKING_H, WALKING_V
};


// setup PPU and tables
void setup_graphics() {
  // clear sprites
  oam_clear();
  // set palette colors
  pal_all(PALETTE);
}


char debug1;

void main(void)
{
  struct Entity P = {
    25, 125, 1, STANDING, 100, playerRStand, 1
  };
  struct GameState GS = {
    map1
  };
  
  char oam_id;    // sprite ID
  char state = 0;
  char pad;	  // controller flags
  
  setup_graphics();
   
  bank_bg(1);
  vram_adr(NTADR_A(0,4));
  vram_unrle(GS.CurMap);
  
  vrambuf_clear();
  set_vram_update(updbuf);
  
  // enable rendering
  ppu_on_all();  
	
  // infinite loop
    while(1) {
      
      oam_id = 0;
      
      // poll controller
      pad = pad_poll(0);
      // move left/right
      //ppu_wait_nmi();
      if(pad & PAD_LEFT )
      {
        if(canPlayerMove(P.x,P.y+8)){
        P.x--;
        P.dir=1;
        P.state = WALKING_H;
        }
      }
      else if(pad & PAD_RIGHT )
      {
        if(canPlayerMove(P.x +14,P.y+8)){
        P.x++;
        P.dir=0;
        P.state = WALKING_H;
        }
      }
      else P.state = STANDING;
      // move up/down
      if(pad & PAD_DOWN )
      {
        if(canPlayerMove(P.x+8 ,P.y+16)){
        P.y++;
        P.state = WALKING_V;
        }
      }
      else if(pad & PAD_UP )
      {
        
        if(canPlayerMove(P.x+8 ,P.y+5)){
        P.y--;
        P.state = WALKING_V;
        }
      }
      //vram_adr(NTADR_A(0,0));
      // draw and move player
      switch (P.state){
        case STANDING:
          P.CurSprite = P.dir ? playerLStand : playerRStand;
          break;
        case WALKING_H:
          P.CurSprite = playerRunSeq[(P.x%7) + (P.dir?0:8)];
          break;
        case WALKING_V:
          P.CurSprite = playerRunSeq[(P.y%7) + (P.dir?0:8)];
          break;
      }
      oam_id = oam_meta_spr(P.x, P.y, oam_id, P.CurSprite);
      oam_hide_rest(oam_id);
      
      vrambuf_flush();
    }
}
