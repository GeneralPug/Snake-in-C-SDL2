# Snake in C / SDL2

## A very simple classic snake game made using only C and the SDL2 library.
This is my first game in C/SDL. I really wanted to try making a game that was customizable (to some extent) and simple just to dip my toes into making games without a game engine.

## Controls
	-WASD to move
	-ESC to quit the game and close window

## Dependencies
	-The SDL2 library for C/C++
	-A C compiler (gcc, clang, etc)

## Running the game
To run the game with no modifications, simply execute the **__run__** file (that was compiled on linux, don't be surprised if it doesn't compile/run on Windows)

## Configuration
As mentioned, the game is easily customizable. Simply modify the **__./src/config.h__** file to adjust the colors/scale of the game to your liking. Once the file modified, you will need to re-compile the program in order for the modifications to apply.

## Compiling
To compile the program normally, just use `make`.
If you want the game to open as soon as the game is done compiling, use `make exec`

## Bugs
This happens very rarely but sometimes, after eating a fruit, the new "block" or "body" part is offset by 1, which creates a weird gap in the body of the snake. I have no clue why it happens, how it happens, or how to fix it :(

### Thank you :)
