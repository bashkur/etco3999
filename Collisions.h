#ifndef _COLLISIONS_H
#define _COLLISIONS_H

unsigned char isColliding(unsigned char x,unsigned char y);

unsigned char canPlayerMove(unsigned char x,unsigned char y);

void pickupSprite(unsigned char x,unsigned char y);
  
unsigned char overDoor(unsigned char x,unsigned char y);

unsigned char overTile(unsigned char x,unsigned char y,unsigned char tile);

struct GameState{
  const unsigned char* CurMap;
  struct pickup** Currentitems;
  char MapPickupNum;
  
};

struct pickup{
  unsigned char x;
  unsigned char y;
  char status;
  char sprite;
};
#endif