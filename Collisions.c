#include "Collisions.h"


unsigned char isColliding(unsigned char x,unsigned char y){
  x + y;
 return 1; 
}

unsigned char canPlayerMove(unsigned char x,unsigned char y,const unsigned char* CurMap){
  if(x >= 240 || x <= 20)
    return 0;
  if(y >= 185 || y <= 20)
    return 0;
  x = x/8;
  y = y/8;
  
  if(CurMap[y*16 + x] & 0x06){
    return 0;
    
  }
  return 1;
}