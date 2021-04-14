#include "Collisions.h"

#include <neslib.h>

unsigned char isColliding(unsigned char x,unsigned char y){
  x + y;
 return 1; 
}
extern char debug1;
unsigned char canPlayerMove(unsigned char x,unsigned char y){
  unsigned char tile;

  if(x >= 255 || x <= 8)
    return 0;
  if(y >= 255 || y <= 8)
    return 0;
  x = x/8;
  y = y/8;
 
  vram_adr(NTADR_A(x,y));
  vram_read(&tile,1);
  vram_adr(0);
  if((char) tile == 0xA4)
    pickupSprite(x,y);
  if((char)(tile>>4) < 0x6  && (char)(tile<<4) < 0x70 && tile != 0x00){
    return 0;
    
  }
  return 1;

}
extern struct GameState GS;
void pickupSprite(unsigned char x,unsigned char y){
  char i;
  for( i = 0; i < GS.MapPickupNum; ++i){
    if((*GS.Currentitems[i]).x/8 == x && (*GS.Currentitems[i]).y/8 == y){
      (*GS.Currentitems[i]).status = 0;
    }
  }
}
unsigned char overDoor(unsigned char x,unsigned char y){
  unsigned char tile;
  x = x/8;
  y = y/8;
 
  vram_adr(NTADR_A(x,y));
  vram_read(&tile,1);
  vram_adr(0);	

  if(tile != 0x4A){
     return 0;
    
  }
  return 1;

}

unsigned char overTile(unsigned char x,unsigned char y,unsigned char tile){
  unsigned char check;
  x = x/8;
  y = y/8;
 
  vram_adr(NTADR_A(x,y));
  vram_read(&check,1);
  vram_adr(0);	

  if(check != tile){
    return 0;
    
  }
  return 1;

}
