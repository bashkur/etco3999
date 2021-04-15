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

unsigned char bright;

static const unsigned char* maps[2] = { map1, map2 };
static unsigned char cur_map_id = 0;
char debug1;
struct pickup temp={120,160,1,0x14};
struct pickup temp2={120,180,1,0x14};
struct pickup* Map1items[PICKUPSMAP1] = {&temp,&temp2};

struct Entity {
  unsigned char x;
  unsigned char y;
  unsigned char dir;		// facing direction (0=right, 1=left)
  byte state;			// EntityState
  unsigned char health;
  const unsigned char* CurSprite;
  unsigned char is_player;
};
struct hud {
  unsigned char hx;
  unsigned char hy;
  unsigned char ex;
  unsigned char ey;
  bool pickup;
  unsigned char numpickups;
};
struct GameState GS = {
    map1,Map1items,PICKUPSMAP1
  };

typedef enum EntityState {
  STANDING, WALKING_H, WALKING_V
};

struct Entity player = {
  25, 200, 0, STANDING, 8, playerRStand, 1
  };

// setup PPU and tables
void setup_graphics() {
  // clear sprites
  oam_clear();
  // set palette colors
  pal_all(PALETTE);
}

void transition_to_map(const unsigned char* map) {
  bright = 0;
  pal_bright(bright);
  ppu_off();
  
  // reset player position
  if(cur_map_id) {
    player.x = 25;
    player.y = 125;
  }
  else {
    player.x = 25;
    player.y = 200;
  }
  // load map
  vram_adr(NTADR_A(0,4));
  vram_unrle(map);
  GS.CurMap = maps[cur_map_id];
  ppu_on_all();
  // fade
  while(bright != 4){
    if(bright<4) ++bright;
    else --bright;
    pal_bright(bright);
    delay(8);
  }
}

void main(void)
{
  char i;
   struct hud H = {
    10,10,10,20,true,0
  };
  
  char oam_id;    // sprite ID
  char state = 0;
  char pad;	  // controller flags
  
  setup_graphics();
   
  bank_bg(1);
  bank_spr(0);
  transition_to_map(maps[cur_map_id]);
  
  for(i = 0; i < GS.MapPickupNum ;++i) {
    vram_adr(NTADR_A((*GS.Currentitems[i]).x/8,(*GS.Currentitems[i]).y/8));
    vram_put(0xA4);
  }
  
  
  
  vrambuf_clear();
  set_vram_update(updbuf);
  
  // infinite loop
    while(1) {
      
      oam_id = 0;
      
      // poll controller
      pad = pad_poll(0);
      
      ppu_wait_nmi();
      
      // move left/right
      if(pad & PAD_LEFT) {
        if(canPlayerMove(player.x,player.y+8)){
        player.x--;
        player.dir=1;
        player.state = WALKING_H;
        }
      }
      else if(pad & PAD_RIGHT) {
        if(canPlayerMove(player.x +14,player.y+8)){
        player.x++;
        player.dir=0;
        player.state = WALKING_H;
        }
      }
      else player.state = STANDING;
      // move up/down
      if(pad & PAD_DOWN) {
        if(canPlayerMove(player.x+8 ,player.y+16)){
        player.y++;
        player.state = WALKING_V;
        }
      }
      else if(pad & PAD_UP) {
        if(canPlayerMove(player.x+8, player.y+5)){
        player.y--;
        player.state = WALKING_V;
        }
      }
      
      // should we switch maps?
      if(overDoor(player.x, player.y)) {
        cur_map_id = cur_map_id ? 0 : 1;
        transition_to_map(maps[cur_map_id]);
      }
      
      // draw and move player
      switch (player.state){
        case STANDING:
          player.CurSprite = player.dir ? playerLStand : playerRStand;
          break;
        case WALKING_H:
          player.CurSprite = playerRunSeq[(player.x%7) + (player.dir?0:8)];
          break;
        case WALKING_V:
          player.CurSprite = playerRunSeq[(player.y%7) + (player.dir?0:8)];
          break;
      }
      
      for(i = 0;i < GS.MapPickupNum ;++i){
        if((*GS.Currentitems[i]).status)
        oam_id = oam_spr((*GS.Currentitems[i]).x,(*GS.Currentitems[i]).y,
                          (*GS.Currentitems[i]).sprite,0,oam_id);
        
      }
      for(i=0; i < player.health+2; i++){
        if(i==0)
        oam_id = oam_spr(H.hx+i*7,H.hy,0x48,0,oam_id);
        else if(i==1)
          oam_id = oam_spr(H.hx+i*7,H.hy,0x50,0,oam_id);
        else oam_id = oam_spr(H.hx+i*9+9,H.hy,0x15,0,oam_id);
      }
          for(i=0; i < player.health+3; i++){
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
      
      oam_id = oam_meta_spr(player.x, player.y, oam_id, player.CurSprite);
      oam_hide_rest(oam_id);
      
      ppu_wait_frame();
      
      vrambuf_flush();
    }
}
