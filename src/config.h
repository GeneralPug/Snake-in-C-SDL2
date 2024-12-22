#include "lib.h"
#ifndef CONFIG_H
#define CONFIG_H

#define WINDOW_WIDTH 1000
#define WINDOW_HEIGHT 1000
#define AMOUNT_TILES 12//Tiles per axis (e.g. 10 tiles will be a 10x10 board)
#define WINDOW_TITLE "SNAKE GAME"

#define FPS 60
#define SPEED_MULTIPLIER 1.25f

const float FRAME_TARGET_TIME = (float)1000/(float)FPS;
const float BLOCK_WIDTH = (float)WINDOW_WIDTH / (float) AMOUNT_TILES;
const float BLOCK_HEIGHT = (float)WINDOW_HEIGHT / (float)AMOUNT_TILES;

struct RGBA Background_Color1 	= {NULL, 0  , 115, 11 , 0};
struct RGBA Background_Color2 	= {NULL, 38 , 153, 49 , 0};
struct RGBA Head_Color			= {NULL, 2  , 72 , 125, 0};
struct RGBA Body_Color			= {NULL, 27 , 160, 196, 0};
struct RGBA Fruit_Color			= {NULL, 255, 0  , 0  , 0};
struct RGBA Outline_Color		= {NULL, 31 , 81 , 64 , 0};
struct RGBA Empty_Color			= {NULL, 33 , 54 , 36 , 0};

bool fill_board_boxes = true;
bool draw_outline = true;

#endif
