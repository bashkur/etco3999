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

#define PICKUPSMAP1 2
#define PICKUPSMAP2 0
struct Entity{
  unsigned char x;
  unsigned char y;
  unsigned char dir;		// facing direction (0=right, 1=left)
  byte state;			// EntityState
  unsigned char health;
  const unsigned char* CurSprite;
  unsigned char is_player;
};
struct hud{
  unsigned char hx;
  unsigned char hy;
  unsigned char ex;
  unsigned char ey;
  bool pickup;
  unsigned char numpickups;
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
struct pickup temp={120,160,1,0x14};
struct pickup temp2={120,180,1,0x14};
struct pickup* Map1items[PICKUPSMAP1] = {&temp,&temp2};


struct GameState GS = {
    map1,Map1items,PICKUPSMAP1
  };
void main(void)
{
  char i;
  struct Entity P = {
    25, 125, 1, STANDING, 8, playerRStand, 1
  };
   struct hud H = {
    10,10,10,20,true,0
  };
  
  char oam_id;    // sprite ID
  char state = 0;
  char pad;	  // controller flags
  
  setup_graphics();
   
  bank_bg(1);
  vram_adr(NTADR_A(0,4));
  vram_unrle(GS.CurMap);
  for(i = 0;i < GS.MapPickupNum ;++i){
      vram_adr(NTADR_A((*GS.Currentitems[i]).x/8,(*GS.Currentitems[i]).y/8));
      vram_put(0xA4);
      }
  
  
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
      ppu_wait_nmi();
      //ppu_wait_frame();
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
      
      for(i = 0;i < GS.MapPickupNum ;++i){
        if((*GS.Currentitems[i]).status)
        oam_id = oam_spr((*GS.Currentitems[i]).x,(*GS.Currentitems[i]).y,
                          (*GS.Currentitems[i]).sprite,0,oam_id);
        
      }
      for(i=0; i < P.health+2; i++){
        if(i==0)
        oam_id = oam_spr(H.hx+i*7,H.hy,0x48,0,oam_id);
        else if(i==1)
          oam_id = oam_spr(H.hx+i*7,H.hy,0x50,0,oam_id);
        else oam_id = oam_spr(H.hx+i*9+9,H.hy,0x15,0,oam_id);
      }
          for(i=0; i < P.health+3; i++){
        if(i==0)
        oam_id = oam_spr(H.ex+i*7,H.ey,0x45,0,oam_id);
        else if(i==1)
          oam_id = oam_spr(H.ex+i*7,H.ey,0x48,0,oam_id);
        else if(i==2)
          oam_id = oam_spr(H.ex+i*7,H.ey,0x50,0,oam_id);
        else oam_id = oam_spr(H.ex+i*9,H.ey,0x15,0,oam_id);
      }
      if(H.pickup)
        oam_id = oam_spr(130,20,0x14,0,oam_id);
        oam_id = oam_spr(140,20,0x30+H.numpickups,0,oam_id);
      
      
      
      oam_id = oam_meta_spr(P.x, P.y, oam_id, P.CurSprite);
      oam_hide_rest(oam_id);
      
      vrambuf_flush();
    }
}
