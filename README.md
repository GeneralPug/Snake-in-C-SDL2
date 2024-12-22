# Snake-in-C-SDL2
A very simple snake game made in C and SDL2 that is customizable

I have no idea how to do .md files and I don't feel like learning it (for now), sorry.

This is my first game without a game engine. This was made entirely in C using the SDL2 library.

The game is very customizable via the **./src/config.h** file. In it, you can customize all the colors, some graphic settings and the scale of the game.

#*Controls*:

  -WASD to move

  -ESC to leave the game

#*Dependencies*:

  -SDL2 library

  -A C compiler

#*Running the game*

If you want to run the game without modifying it, simply execute the run file (this was compiled on linux 64-bit, don't be surprised if it doesn't run on Windows).

#*Configuration*

To configure all the different settings, simply modify some values in the ./src/config.h file.

After making modifications, you will need to re-compile for the modifications to apply. To compile the program, use "make" or "make exec" to run the game once it's done compiling.

#*Bugs*

This happens very rarely but sometimes a block will just be offset by 1 leaving a gap in the snake. I have no idea what causes this or how to fix it.

Thank you :)

