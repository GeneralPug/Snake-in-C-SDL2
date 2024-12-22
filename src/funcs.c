#include "lib.h"
#include "config.h"
#include <time.h>


byte board[AMOUNT_TILES][AMOUNT_TILES];
Block * blocks = NULL;
bool game_over;
bool inputted;

void free_list();

byte * get_fruit_pos(){
	int seed = time(NULL) * time(NULL);
	srand(seed);
	bool is_valid = false;

	byte * pos = (byte *) malloc(sizeof(byte) * 2);
	while(!is_valid){
		*pos = rand()%AMOUNT_TILES;
		pos++;
		*pos = rand()%AMOUNT_TILES;
		pos--;

		is_valid = true;

		Block * p = blocks;
		while(p!=NULL){
			if(p->tilex == pos[0] && p->tiley == pos[1]){
				is_valid = false;
				break;
			}
			p=p->previous;
		}
	}
	return pos;
}

byte list_count();

void update_board(){
	byte ** positions = (byte **)malloc(sizeof(byte) * list_count() * 3);
	byte count = 0;
	Block * p = blocks;
	byte flag;
	while(p!=NULL){
		if(p->type == FHEAD)
			flag = 1;
		else if(p->type == FBODY)
			flag = 2;
		else if(p->type == FFRUIT)
			flag = 3;
		positions[count][0] = p->tilex;
		positions[count][1] = p->tiley;
		positions[count][2] = flag;
		p=p->previous;
		count++;
	}
	for(int i = 0; i < AMOUNT_TILES;i++){
		for(int j = 0; j < AMOUNT_TILES; j++){
			for(int k = 0; k < list_count(); k++){
				if(i == positions[k][0] && j == positions[k][1]){
					board[i][j] = positions[k][2];
				}
			}
		}
	}
}

void add_block_to_list(byte pos[2], Flags f){
	Block * temp = (Block *) malloc(sizeof(Block));
	temp->tilex = pos[0];
	temp->tiley = pos[1];
	temp-> type=f;
	temp->previous = NULL;
	if(f == FHEAD){
		temp->direction = RIGHT;
	}
	if(blocks == NULL){
		temp->next = NULL;
		temp->previous=NULL;
		blocks = temp;
	}
	else{
		Block * p = blocks;
		while(p->previous != NULL){
			p=p->previous;
		}
		temp->next = p;
		p->previous = temp;
		if(f == FBODY){
			if(temp->next->type == FHEAD){
				temp->direction = RIGHT;
			}
			else{
				if(temp->next->type == FFRUIT)
					temp->direction = temp->next->next->direction;
				else
					temp->direction = temp->next->direction;
			}
		}
		if(f == FFRUIT){
			temp->direction = STATIC;
		}
	}
}

void add_block_to_snake(){
	Block * p = blocks;
	while(p->previous!= NULL){
		p=p->previous;
	}

	byte pos[2] = {0};
	Directions d;

	while (p->type == FFRUIT){
		p=p->next;
	}

	d = p->direction;
	if(d == RIGHT){
		pos[0] = p->tilex - 1;
		pos[1] = p->tiley;
		add_block_to_list(pos, FBODY);
	}
	if(d == LEFT){
		pos[0] = p->tilex +1;
		pos[1] = p->tiley;
		add_block_to_list(pos, FBODY);
	}
	if(d == UP){
		pos[0] = p->tilex;
		pos[1] = p->tiley + 1;
		add_block_to_list(pos, FBODY);
	}
	if(d == DOWN){
		pos[0] = p->tilex;
		pos[1] = p->tiley - 1;
		add_block_to_list(pos, FBODY);
	}
	else if(d==STATIC){printf("ERROR: tried to add fruit to snake\n");}
}

void update_direction(){
	Block * p = blocks;
	p=p->previous;
	while(p->previous!=NULL){
		if(p->next->type != FFRUIT){
			p->direction = p->next->direction;
		}
		p=p->previous;
	}
}

byte list_count(){
	Block * p = blocks;
	byte count = 0;
	while(p!=NULL){
		count++;
		p=p->previous;
	}
	return count;
}

void lose(){
	game_over = true;
	kill_window();
}

void new_fuit(){
	Block * p = blocks;
	while(p->previous != NULL){
		if(p->type == FFRUIT){
			p->previous->next = p->next;
			p->next->previous = p->previous;
			free(p);
		}
		p=p->previous;
	}
	byte * pos = get_fruit_pos();
	byte vector[2] = {pos[0],pos[1]};
	free(pos);
	add_block_to_list(vector, FFRUIT);
}

void check_collision(){
	Block * p = blocks;
	Block * head = blocks;
	if(head->tilex >= AMOUNT_TILES ||
					head->tilex < 0 ||
					head->tiley >= AMOUNT_TILES ||
					head->tiley < 0){
		lose();
	}
	while(p!=NULL){
		if(p->tilex == head->tilex && p->tiley == head->tiley){
			if(p->type == FBODY){
				lose();
			}
			else if(p->type == FFRUIT){
				add_block_to_snake();
				new_fuit();
			}
		}
		p=p->previous;
	}
}

void start_game(){
	if(AMOUNT_TILES < 5){
		fprintf(stderr, "AMOUNT_TILES in config.h needs to be 8 or bigger");
		exit(1);
	}
	byte startx = (AMOUNT_TILES / 2) - 3;
	byte starty = (AMOUNT_TILES / 2);
	byte * fruitpos = get_fruit_pos();

	for(byte j = 0; j < AMOUNT_TILES; j++){
		for(byte i = 0; i < AMOUNT_TILES; i++){
			if(i+1 == startx && j == starty){
				board[i+1][j] = HEAD;
				byte pos[2]={i+1, j};
				add_block_to_list(pos, FHEAD);

				board[i][j] = BODY;
				byte pos2[2] = {i,j};
				add_block_to_list(pos2, FBODY);
			}
			else if(board[i][j] != HEAD && board[i][j] != BODY){
				board[i][j] = 0;
			}
		}
	}

	for(byte j = 0; j < AMOUNT_TILES; j++){
		for(byte i = 0; i < AMOUNT_TILES; i++){
			if(i == fruitpos[0] && j == fruitpos[1]){
				board[i][j] = FRUIT;
				byte pos[2] = {i,j};
				add_block_to_list(pos, FFRUIT);
			}
		}
	}
}

void update_pos(){
	Block * p = blocks;
	while(p!=NULL){
		switch(p->direction){
			case RIGHT:
				p->tilex++;
				break;
			case LEFT:
				p->tilex--;
				break;
			case UP:
				p->tiley--;
					break;
			case DOWN:
					p->tiley++;
					break;
			case STATIC:
			default:
					break;
		}
		p=p->previous;
	}
}

void change_blocks_direction(){
	Block * p = blocks;
	while(p->previous != NULL){
		p=p->previous;
	}
	while(p->next != NULL){
		if(p->type != FFRUIT){
			if(p->next->type != FFRUIT){
				p->direction = p->next->direction;
			}
			else{
				p->direction = p->next->next->direction;
			}
		}
		p=p->next;
	}
}
void change_direction(Directions d){
	Directions curr = blocks->direction;
	if(d == RIGHT && curr == LEFT)
		return;
	if(d == LEFT && curr == RIGHT)
		return;
	if(d == UP && curr == DOWN)
		return;
	if(d == DOWN && curr == UP)
		return;
	if(!inputted)
		blocks->direction = d;
	inputted = true;
}

void set_colors(){
	Background_Color1.renderer = renderer;
	Background_Color2.renderer = renderer;
	Head_Color.renderer = renderer;
	Body_Color.renderer = renderer;
	Fruit_Color.renderer = renderer;
	Outline_Color.renderer = renderer;
	Empty_Color.renderer = renderer;
}

void free_list(){
	Block * p = blocks;
	while(p!=NULL){
		blocks = p;
		p=p->previous;
		free(blocks);
	}
}
