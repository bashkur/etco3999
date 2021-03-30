#include "Collisions.h"


unsigned char isColliding(unsigned char x,unsigned char y){
  x + y;
 return 1; 
}

unsigned char canPlayerMove(unsigned char x,unsigned char y){
  if(x >= 240)
    return 0;
  if(y >= 185)
    return 0;
  x = x/8;
  y = y/8;
  
  return 1;
}