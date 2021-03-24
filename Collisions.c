#include "Collisions.h"


unsigned char isColiding(unsigned char x1,unsigned char y1 ,unsigned char x2, unsigned char y2){
  unsigned char dist1 = y2-y1;
  unsigned char dist2 = x2-x1;

  return(dist2 > dist1 ?  dist2 : dist1);
  
}

