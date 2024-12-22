#ifndef STDLIBS_H
#define STDLIBS_H
#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <string.h>
#include "funcs.c"
#endif

#ifndef STRUCTURES_H
#define STRUCTURES_H

typedef int bool;
#define true 1
#define false 0

typedef enum{
	FHEAD,
	FBODY,
	FFRUIT
}Flags;

typedef enum{
	RIGHT,
	LEFT,
	UP,
	DOWN,
	STATIC,
}Directions;

typedef struct Block{
	int tilex;
	int tiley;
	Flags type;
	Directions direction;
	struct Block * next;
	struct Block * previous;
}Block;

#include <SDL2/SDL.h>

struct RGBA{
	SDL_Renderer * renderer;
	uint8_t r;
	uint8_t g;
	uint8_t b;
	uint8_t a;
};

#include <stdint.h>
typedef uint8_t 	byte;
typedef int8_t 		sbyte;
typedef uint16_t	uint16;
typedef int16_t		int16;
typedef uint32_t	uint32;
typedef int32_t		int32;
typedef uint64_t	uint64;
typedef int64_t		int64;

extern Block * blocks;
extern bool game_over;
extern bool inputted;
extern SDL_Renderer * renderer;
extern void kill_window();

#endif

#ifndef CONSTS_H
#define CONSTS_H

#define NAMEBUFF 50
#define BUFF 255

#define HEAD 1
#define BODY 2
#define FRUIT 3

#endif
