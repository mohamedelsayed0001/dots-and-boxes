#include "conts.h"
#include"userinterface.h"

int hardness = NOPATHCHOSEN, start = 0, selectedrect1 = 0, selectedrect2 = 0, scale1 = 0, scale2 = 0;
SDL_Surface* beginner = NULL;
SDL_Surface* expert = NULL;
SDL_Surface* play1 = NULL; 
SDL_Surface* play2 = NULL;
SDL_Surface* Start = NULL; 
SDL_Surface* playerSurface1 = NULL; 
SDL_Surface* playerSurface2 = NULL; 
SDL_Texture* begin = NULL;
SDL_Texture* expe = NULL;
SDL_Texture* p1 = NULL;
SDL_Texture* p2 = NULL;
SDL_Texture* s = NULL;
SDL_Texture* playertexture1 = NULL;
SDL_Texture* playertexture2 = NULL;
int width1, height1, width2, height2, turn = BLUEturn, scoer = 0, edgey = 0, edgex = 0, w1, h1, w2, h2, undocount = 0, redocount = 0, min = 0;
int fwinner = 0, sc1 = 0, sc2 = 0, startXh = 2000, startYh = 2000, startXv = 2000, startYv = 2000, Hl = 0, Vl = 0, computerturn = 0, numberp1, numberp2;
button ep, be, player1, player2, thestart;
char* name1, * name2;

typedef struct {
	int x, y, color;
}lines;
lines* H, * V;
typedef struct {
	int color, sum, ht, vt, s1, s2, hn, vn, ture, ckecked;
	lines* h, * v;
	lines hl[2], vl[2];

}boxese;
boxese** game, *** undostack, *** redostack;
char thes1[3], thes2[3];


SDL_Color blue = { 0 , 0 , 255 };
SDL_Color red = { 255 , 0 , 0 };
SDL_Color black  = { 0 , 0 , 0 };
SDL_Color gold = { 255, 215,115 }; 
SDL_Color top10color = { 0x6B,0x0F,0x1A };  
void buttonsRender() {
	int width1, height1, width2, height2; 
	SDL_QueryTexture(theexit, NULL, NULL, &width1, &height1); 
	SDL_Rect exit = { 
		Exit.x,   
		Exit.y,
		width1 / 3,
		height1 / 3
	};
	SDL_RenderCopy(renderer, theexit, NULL, &exit); 
	SDL_QueryTexture(thehome, NULL, NULL, &width2, &height2); 
	SDL_Rect homebox = { 
		Exit.x-100,  
		Exit.y, 
		width1 / 3, 
		height1 / 3
	};
	SDL_RenderCopy(renderer, thehome, NULL, &homebox);  
	SDL_Rect beginnerbutton = { 
		be.x, 
		be.y,
		be.wigth,
		be.length
	};
	SDL_Rect expertbutton = { 
		ep.x,
		ep.y,
		ep.wigth,
		ep.length
	};
	SDL_Rect startbutton = { 
		thestart.x, 
		thestart.y, 
		thestart.wigth, 
		thestart.length 
	}; 
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255); 
	SDL_RenderFillRect(renderer, &beginnerbutton); 
	SDL_RenderFillRect(renderer, &expertbutton); 
	SDL_RenderFillRect(renderer, &startbutton); 
}
void textboutonsRender() {
	SDL_Rect rec1 = {
		be.x + 5,
		be.y,
		be.wigth - 10,
		be.length - 30
	};
	SDL_RenderCopy(renderer, begin, NULL, &rec1);

	SDL_Rect rec2 = {
		ep.x + 5,
		ep.y,
		ep.wigth - 10,
		ep.length - 30
	};
	SDL_RenderCopy(renderer, expe, NULL, &rec2);
	SDL_Rect rec3 = {
		thestart.x + 10,
		thestart.y,
		thestart.wigth - 30,
		thestart.length - 30
	};
	SDL_RenderCopy(renderer, s, NULL, &rec3);
}

void renderer_intro() {
	SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
	SDL_RenderClear(renderer);
	buttonsRender();

	SDL_Rect textInputRectp1 = { 
		WINDOW_WIDTH / 2 - 500,
		WINDOW_LENGHT / 2 + 100,
		300,
		100
	};
	SDL_Rect textInputRectp2 = {
		WINDOW_WIDTH / 2 + 100,
		WINDOW_LENGHT / 2 + 100,
		300,
		100
	};

	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
	
	SDL_RenderDrawRect(renderer, &textInputRectp1);
	SDL_RenderDrawRect(renderer, &textInputRectp2);

	textboutonsRender();

	SDL_Rect player1text = {
		player1.x,
		player1.y,
		player1.wigth,
		player1.length
	};
	SDL_RenderCopy(renderer, p1, NULL, &player1text);
	SDL_Rect player2text = {
		player2.x,
		player2.y,
		player2.wigth,
		player2.length
	};
	SDL_RenderCopy(renderer, p2, NULL, &player2text);

	if (selectedrect1 || strcmp("",name1)) {
		SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255);
		SDL_RenderFillRect(renderer, &textInputRectp1);
	}
	if (selectedrect2 || strcmp("", name2)) {
		SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
		SDL_RenderFillRect(renderer, &textInputRectp2);
	}
	SDL_Rect textInputerenderer1 = {
		WINDOW_WIDTH / 2 - 500 + 10,
		WINDOW_LENGHT / 2 + 100 + 30,
		50 + 20 * scale1,
		50
	};
	SDL_Rect textInputerenderer2 = {
		WINDOW_WIDTH / 2 + 100 + 10,
		WINDOW_LENGHT / 2 + 100 + 30,
		50 + 20 * scale2,
		50
	};
	SDL_RenderCopy(renderer, playertexture1, NULL, &textInputerenderer1);
	SDL_RenderCopy(renderer, playertexture2, NULL, &textInputerenderer2);

	SDL_RenderPresent(renderer);
}

void intro_buttons() {
	beginner = TTF_RenderText_Solid(font, "Beginner", white, 500);
	begin = SDL_CreateTextureFromSurface(renderer, beginner);

	expert = TTF_RenderText_Solid(font, "Expert", white, 500);
	expe = SDL_CreateTextureFromSurface(renderer, expert);

	Start = TTF_RenderText_Solid(font, "start", white, 500);
	s = SDL_CreateTextureFromSurface(renderer, Start);

	be.x = WINDOW_WIDTH / 2 - 500;
	be.y = WINDOW_LENGHT / 2 - 400;
	be.wigth = 400;
	be.length = 100;

	ep.x = WINDOW_WIDTH / 2 + 100;
	ep.y = WINDOW_LENGHT / 2 - 400;
	ep.wigth = 400;
	ep.length = 100;

	thestart.x = WINDOW_WIDTH / 2 - 200;
	thestart.y = WINDOW_LENGHT / 2 + 400;
	thestart.wigth = 400;
	thestart.length = 100;
}
void text_input_name(SDL_Surface *namesuface ,SDL_Texture *nametexture,char** name ) {
	free(*name);
	SDL_StartTextInput();  
	*name = calloc(MAX_NAME_LENGTH, sizeof(char));
	
	namesuface = TTF_RenderText_Solid(font, *name, white);
	nametexture = SDL_CreateTextureFromSurface(renderer, namesuface);  
	SDL_FreeSurface(namesuface);

}


void setup_intro() {
	hardness = NOPATHCHOSEN;
	start = 0;
	scale1 = 0;
	scale2 = 0;
	SDL_DestroyTexture(playertexture1);
	SDL_DestroyTexture(playertexture2);
	intro_buttons();
	
	play1 = TTF_RenderText_Solid(font, "Player 1", blue, 500);
	p1 = SDL_CreateTextureFromSurface(renderer, play1);

	play2 = TTF_RenderText_Solid(font, "Player 2", red, 500);
	p2 = SDL_CreateTextureFromSurface(renderer, play2);

	player1.x = WINDOW_WIDTH / 2 - 500;
	player1.y = WINDOW_LENGHT / 2 - 100;
	player1.wigth = 400;
	player1.length = 100;

	player2.x = WINDOW_WIDTH / 2 + 100;
	player2.y = WINDOW_LENGHT / 2 - 100;
	player2.wigth = 400;
	player2.length = 100;

	text_input_name(playerSurface1, playertexture1,&name1);
	text_input_name(playerSurface2, playertexture2,&name2);
}
void buttonsevents(SDL_Event intro) {
	if (intro.button.button == SDL_BUTTON_LEFT
		&& intro.button.x > WINDOW_WIDTH / 2 - 500
		&& intro.button.x < WINDOW_WIDTH / 2 - 100
		&& intro.button.y > WINDOW_LENGHT / 2 - 400
		&& intro.button.y < WINDOW_LENGHT / 2 - 300) {
		hardness = beginners;
	}
	if (intro.button.button == SDL_BUTTON_LEFT
		&& intro.button.x > WINDOW_WIDTH / 2 + 100
		&& intro.button.x < WINDOW_WIDTH / 2 + 500
		&& intro.button.y > WINDOW_LENGHT / 2 - 400
		&& intro.button.y < WINDOW_LENGHT / 2 - 300) {
		hardness = experts;

	}
	if (intro.button.button == SDL_BUTTON_LEFT
		&& intro.button.x > Exit.x - 100
		&& intro.button.x < Exit.x - 50
		&& intro.button.y > Exit.y
		&& intro.button.y < Exit.y + 50) {
		out = 1;
		homecheck = 1;
	}
	if (intro.button.button == SDL_BUTTON_LEFT
		&& intro.button.x > WINDOW_WIDTH / 2 - 200
		&& intro.button.x < WINDOW_WIDTH / 2 + 200
		&& intro.button.y > WINDOW_LENGHT / 2 + 400
		&& intro.button.y < WINDOW_LENGHT / 2 + 500
		&& hardness && strcmp(name1, "") && (path == PLAYERTOCOMPUTER|| strcmp(name2,""))) {
		start = 1;
	}
	if (intro.button.button == SDL_BUTTON_LEFT 
		&& intro.button.x > Exit.x 
		&& intro.button.x < Exit.x + 50 
		&& intro.button.y > Exit.y 
		&& intro.button.y < Exit.y + 50) { 
		out = 1; 
	}
}
void textinputevents(char** name ,SDL_Surface **playersurface ,SDL_Texture **playertexture ,SDL_Event intro ) {
	size_t remaining_space = 100 - strlen(*name) - 1; 
	strncpy_s(*name + strlen(*name), remaining_space, intro.text.text, remaining_space); 
	
	*playersurface = TTF_RenderText_Solid(font, *name, white);
	*playertexture = SDL_CreateTextureFromSurface(renderer, *playersurface);
}
void input_intro() {
	SDL_Event intro;
	SDL_PollEvent(&intro);

	switch (intro.type)
	{
	case SDL_QUIT:
		test = false;
		break;

	case SDL_MOUSEBUTTONDOWN:
		buttonsevents(intro); 

		if (intro.button.button == SDL_BUTTON_LEFT
			&& intro.button.x > WINDOW_WIDTH / 2 - 500
			&& intro.button.x < WINDOW_WIDTH / 2
			&& intro.button.y > WINDOW_LENGHT / 2 + 100
			&& intro.button.y < WINDOW_LENGHT / 2 + 200) {
			selectedrect1 = 1;
			selectedrect2 = 0;
			
		}
		if (intro.button.button == SDL_BUTTON_LEFT
			&& intro.button.x > WINDOW_WIDTH / 2 + 100
			&& intro.button.x < WINDOW_WIDTH / 2 + 500
			&& intro.button.y > WINDOW_LENGHT / 2 + 100
			&& intro.button.y < WINDOW_LENGHT / 2 + 200) {
			selectedrect2 = 1;
			selectedrect1 = 0;
			
		}
		break;
	case SDL_TEXTINPUT:
		if (selectedrect1) {
			textinputevents(&name1, &playerSurface1, &playertexture1, intro);
			scale1++;
		}
		else if (selectedrect2) {
			textinputevents(&name2, &playerSurface2, &playertexture2, intro);
			scale2++;
		}
	}
}



void intro() {
	setup_intro();
	while (test && !start && !out) {
		input_intro();
		renderer_intro();
	}
}