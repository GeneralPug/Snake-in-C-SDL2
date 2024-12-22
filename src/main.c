#include "lib.h"
#include "render.c"

bool game_over;

int main(){
	if(initialize_window()){
		game_over = false;
		SDL_Event e;
		start_game();
		while(!game_over){
			render();
			input(e);
			update();
		}
	}

	return 0;
}
