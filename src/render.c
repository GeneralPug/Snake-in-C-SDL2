#include "lib.h"
#include "config.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

SDL_Renderer *renderer = NULL;
SDL_Window *window = NULL;
bool inputted;

int initialize_window(){
	if(SDL_Init(SDL_INIT_EVERYTHING) != 0){
		fprintf(stderr, "Error initializing SDL\n");
		return false;
	}
	window = SDL_CreateWindow(WINDOW_TITLE, SDL_WINDOWPOS_CENTERED,SDL_WINDOWPOS_CENTERED, WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_BORDERLESS);
	if (!window){
		fprintf(stderr,"Error creating SDL Window\n");
		return true;
	}

	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
	if(!renderer){
		fprintf(stderr,"Error creating renderer\n");
		return false;
	}
	set_colors();
	return true;
}


void render(){

	SDL_SetRenderDrawColor(Empty_Color.renderer, Empty_Color.r, Empty_Color.g, Empty_Color.b, Empty_Color.a);
	SDL_RenderClear(renderer);

	for(int i = 0; i < AMOUNT_TILES; i++){
		for(int j = 0; j < AMOUNT_TILES; j++){
			if((i + j) % 2 == 0){
				SDL_SetRenderDrawColor(Background_Color1.renderer, Background_Color1.r, Background_Color1.g, Background_Color1.b, Background_Color1.a);
				SDL_Rect rect = {i*BLOCK_WIDTH, j*BLOCK_HEIGHT, BLOCK_WIDTH, BLOCK_HEIGHT};
				fill_board_boxes ? SDL_RenderFillRect(renderer, &rect) : SDL_RenderDrawRect(renderer, &rect);
			}
			else{
				SDL_SetRenderDrawColor(Background_Color2.renderer, Background_Color2.r, Background_Color2.g, Background_Color2.b, Background_Color2.a);
				SDL_Rect rect = {i*BLOCK_WIDTH, j*BLOCK_HEIGHT, BLOCK_WIDTH, BLOCK_HEIGHT};
				fill_board_boxes ? SDL_RenderFillRect(renderer, &rect) : SDL_RenderDrawRect(renderer, &rect);
			}
		}
	}

	Block * p = blocks;
	while(p!=NULL){
		switch(p->type){
			case FHEAD:
				SDL_SetRenderDrawColor(Head_Color.renderer, Head_Color.r, Head_Color.g, Head_Color.b, Head_Color.a);
				break;
			case FBODY:
				SDL_SetRenderDrawColor(Body_Color.renderer, Body_Color.r, Body_Color.g, Body_Color.b, Body_Color.a);
				break;
			case FFRUIT:
				SDL_SetRenderDrawColor(Fruit_Color.renderer, Fruit_Color.r, Fruit_Color.g, Fruit_Color.b, Fruit_Color.a);
				break;
			default:
				break;
		}
		SDL_Rect rect;
		rect.w = BLOCK_WIDTH;
		rect.h = BLOCK_HEIGHT;
		rect.x = p->tilex * BLOCK_WIDTH;
		rect.y = p->tiley * BLOCK_HEIGHT;
		SDL_RenderFillRect(renderer, &rect);
		if(draw_outline)
			SDL_SetRenderDrawColor(Outline_Color.renderer, Outline_Color.r, Outline_Color.g, Outline_Color.b, Outline_Color.a); SDL_RenderDrawRect(renderer,&rect);
		p=p->previous;
	}

	SDL_RenderPresent(renderer);
}

int last_frame_time;

float accumulated_time = 0.0f;
void update(){
	int time_to_wait = FRAME_TARGET_TIME - (SDL_GetTicks() - last_frame_time);

	if (time_to_wait > 0 && time_to_wait <= FRAME_TARGET_TIME){
		SDL_Delay(time_to_wait);
	}
	
	float delta_time = (SDL_GetTicks() - last_frame_time)/1000.0f;
	last_frame_time = SDL_GetTicks();

	accumulated_time += delta_time * SPEED_MULTIPLIER;
	while(accumulated_time >= 0.25f){
		accumulated_time -= 0.25;
		update_pos();
		//update_direction();
		change_blocks_direction();
		check_collision();
		inputted = false;
	}

}

void kill_window(){
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
	free_list();
	exit(0);
}

void input(SDL_Event e){
	SDL_PollEvent(&e);
	if(e.type==SDL_KEYDOWN){
		switch(e.key.keysym.sym){
			case SDLK_ESCAPE:
				kill_window();
				break;
			case SDLK_w:
				change_direction(UP);
				break;
			case SDLK_s:
				change_direction(DOWN);
				break;
			case SDLK_a:
				change_direction(LEFT);
				break;
			case SDLK_d:
				change_direction(RIGHT);
				break;
			default:
				break;
		}
	}
}
