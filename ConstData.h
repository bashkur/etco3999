#ifndef Consts
#define Consts

/// METASPRITES
// define a 2x2 metasprite
#define DEF_METASPRITE_2x2(name,code,pal)\
const unsigned char name[]={\
        0,      0,      (code)+0,   pal, \
        0,      8,      (code)+1,   pal, \
        8,      0,      (code)+2,   pal, \
        8,      8,      (code)+3,   pal, \
        128};

// define a 2x2 metasprite, flipped horizontally
#define DEF_METASPRITE_2x2_FLIP(name,code,pal)\
const unsigned char name[]={\
        8,      0,      (code)+0,   (pal)|OAM_FLIP_H, \
        8,      8,      (code)+1,   (pal)|OAM_FLIP_H, \
        0,      0,      (code)+2,   (pal)|OAM_FLIP_H, \
        0,      8,      (code)+3,   (pal)|OAM_FLIP_H, \
        128};

// right facing
DEF_METASPRITE_2x2(playerRStand, 0x80, 0);
DEF_METASPRITE_2x2(playerRRun1, 0x84, 0);
DEF_METASPRITE_2x2(playerRRun2, 0x88, 0);
DEF_METASPRITE_2x2(playerRRun3, 0x8c, 0);
DEF_METASPRITE_2x2(playerRJump, 0x90, 0);

// left facing
DEF_METASPRITE_2x2_FLIP(playerLStand, 0x80, 0);
DEF_METASPRITE_2x2_FLIP(playerLRun1, 0x84, 0);
DEF_METASPRITE_2x2_FLIP(playerLRun2, 0x88, 0);
DEF_METASPRITE_2x2_FLIP(playerLRun3, 0x8c, 0);
DEF_METASPRITE_2x2_FLIP(playerLJump, 0x90, 0);

// player run sequence
const unsigned char* const playerRunSeq[16] = {
  playerLRun1, playerLRun2, playerLRun3, 
  playerLRun1, playerLRun2, playerLRun3, 
  playerLRun1, playerLRun2,
  playerRRun1, playerRRun2, playerRRun3, 
  playerRRun1, playerRRun2, playerRRun3, 
  playerRRun1, playerRRun2,
};


/*{pal:"nes",layout:"nes"}*/
const char PALETTE[32] = { 
  0x0E,			// screen color

  0x00,0x0C,0x3D,0x00,	// background palette 0
  0x1C,0x20,0x2C,0x00,	// background palette 1
  0x00,0x10,0x20,0x00,	// background palette 2
  0x06,0x16,0x26,0x00,   // background palette 3

  0x16,0x35,0x24,0x00,	// sprite palette 0
  0x00,0x37,0x25,0x00,	// sprite palette 1
  0x0D,0x2D,0x3A,0x00,	// sprite palette 2
  0x0D,0x27,0x2A	// sprite palette 3
};

const unsigned char map1[250]={
0x02,0x01,0x02,0x9d,0x41,0x01,0x02,0x3a,0x04,0x05,0x06,0x01,0x02,0x1c,0x14,0x15,
0x16,0x01,0x02,0x05,0x04,0x05,0x06,0x01,0x02,0x04,0x00,0x02,0x11,0x01,0x02,0x05,
0x14,0x15,0x16,0x01,0x02,0x04,0x00,0x02,0x11,0x01,0x02,0x05,0x00,0x02,0x02,0x01,
0x02,0x04,0x2d,0x00,0x02,0x10,0x01,0x02,0x05,0x00,0x02,0x02,0x01,0x02,0x04,0x00,
0x02,0x11,0x01,0x02,0x05,0x00,0x00,0x1f,0x01,0x02,0x04,0x00,0x02,0x11,0x3a,0x3b,
0x01,0x02,0x03,0x00,0x02,0x02,0x01,0x02,0x04,0x00,0x02,0x11,0x4a,0x4b,0x01,0x01,
0x6a,0x6b,0x00,0x02,0x02,0x01,0x02,0x04,0x00,0x02,0x11,0x5a,0x5b,0x01,0x01,0x7a,
0x7b,0x00,0x02,0x02,0x01,0x02,0x04,0x2d,0x00,0x02,0x04,0x01,0x02,0x05,0x86,0x87,
0x01,0x02,0x09,0x00,0x02,0x02,0x01,0x02,0x04,0x00,0x02,0x05,0x01,0x02,0x05,0x96,
0x97,0x04,0x05,0x06,0x01,0x02,0x06,0x00,0x02,0x02,0x01,0x02,0x04,0x00,0x02,0x05,
0x01,0x02,0x05,0xa6,0xa7,0x14,0x15,0x16,0x01,0x02,0x06,0x00,0x02,0x02,0x01,0x02,
0x04,0x00,0x02,0x05,0x01,0x01,0x00,0x02,0x08,0x1f,0x01,0x02,0x05,0x00,0x02,0x0d,
0x01,0x01,0x22,0x23,0x00,0x02,0x07,0x01,0x02,0x05,0x00,0x02,0x0d,0x01,0x01,0x32,
0x33,0x00,0x02,0x07,0x01,0x02,0x05,0x00,0x02,0x0d,0x01,0x01,0x42,0x43,0x00,0x02,
0x04,0xd1,0xd2,0xd3,0x01,0x02,0x05,0x00,0x02,0x0d,0x01,0x01,0x52,0x53,0x00,0x02,
0x04,0xf1,0xf2,0xf3,0x01,0x02,0x21,0x01,0x02,0x00
};

const unsigned char map2[213]={
0x01,0x51,0x01,0x6a,0x00,0x01,0x10,0x51,0x01,0x0e,0x00,0x01,0x10,0x51,0x01,0x0e,
0x00,0x01,0x10,0x51,0x01,0x0e,0x00,0x01,0x02,0x51,0x01,0x09,0x00,0x01,0x03,0x51,
0x01,0x0e,0x00,0x01,0x02,0x51,0x01,0x09,0x4c,0x00,0x00,0x4c,0x51,0x01,0x0e,0x00,
0x01,0x02,0x51,0x01,0x09,0x2e,0x00,0x00,0x1e,0x51,0x01,0x05,0x00,0x01,0x0f,0x51,
0x01,0x05,0x00,0x01,0x03,0x51,0x01,0x05,0x00,0x01,0x0f,0x51,0x01,0x05,0x00,0x01,
0x03,0x51,0x01,0x05,0x00,0x01,0x0f,0x51,0x01,0x05,0x00,0x01,0x03,0x51,0x01,0x05,
0x6a,0x6b,0x00,0x01,0x0d,0x51,0x01,0x05,0x00,0x01,0x03,0x51,0x01,0x05,0x7a,0x7b,
0x00,0x01,0x0d,0x51,0x01,0x05,0x00,0x01,0x03,0x51,0x01,0x05,0x00,0x01,0x0f,0x51,
0x01,0x05,0x4c,0x00,0x00,0x4c,0x51,0x01,0x05,0x00,0x01,0x0f,0x51,0x01,0x05,0x2e,
0x00,0x00,0x1e,0x51,0x01,0x05,0x00,0x01,0x0f,0x51,0x01,0x05,0x00,0x01,0x03,0x51,
0x01,0x05,0x00,0x01,0x0f,0x51,0x01,0x05,0x00,0x01,0x03,0x51,0x01,0x1b,0x00,0x01,
0x03,0x51,0x01,0x1b,0x00,0x01,0x03,0x51,0x01,0x05,0x3a,0x3b,0x00,0x01,0x17,0x51,
0x01,0x05,0x4a,0x4b,0x00,0x01,0x17,0x51,0x01,0x05,0x5a,0x5b,0x00,0x01,0x17,0x51,
0x01,0x22,0x51,0x01,0x00
};




#endif