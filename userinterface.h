#include "conts.h"

SDL_Window* window = NULL; 
SDL_Renderer* renderer = NULL;
SDL_Texture* theexit = NULL;
SDL_Texture* thelogo = NULL;
SDL_Texture* thehome = NULL;
SDL_Texture* thedelete = NULL;
TTF_Font* font;
SDL_Surface* text1 = NULL;
SDL_Surface* text2 = NULL;
SDL_Surface* text3 = NULL;
SDL_Surface* text4 = NULL;
SDL_Surface* surface_1 = NULL;
SDL_Texture* texture_1 = NULL;
SDL_Texture* texture_2 = NULL;
SDL_Texture* texture_3 = NULL;
SDL_Texture* texture_4 = NULL;
SDL_Color white = { 255,255,255 };
Mix_Music* music;

const char* path_image1;
const char* logo,*redo,*undo,*home,*delete_path,*song_path;
int path = NOPATHCHOSEN;
int test = 1 , out = 0,checkload;
int homecheck = 0;



typedef struct button {
	float x, y, wigth, length;
}button;
button HtoH, HtoC, Lgame, Rank, Exit;



int open_window(void) {
	if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
	{
		fprintf(stderr, "samething went wrong!");
		return false;
	}
	window = SDL_CreateWindow(
		"dots and boxes",
		SDL_WINDOWPOS_CENTERED,
		SDL_WINDOWPOS_CENTERED,
		WINDOW_WIDTH,
		WINDOW_LENGHT,
		SDL_WINDOW_BORDERLESS
	);
	if (!window)
	{
		fprintf(stderr, "error");
		return false;
	}
	if (!(IMG_Init(IMG_INIT_PNG))) {
		fprintf(stderr, "error");
		return false;
	}
	if (TTF_Init() != 0)
	{
		fprintf(stderr, "samething went worng!in ttf");
		return false;
	}

	renderer = SDL_CreateRenderer(window, -1, 0);
	if (!renderer) {
		fprintf(stderr, "error");
		return false;
	}
	
	return true;
}
void input_ueser_interface() {
	SDL_Event event;
	SDL_PollEvent(&event);

	switch (event.type)
	{
	case SDL_QUIT:
		test = false;
		break;

	case SDL_MOUSEBUTTONDOWN:
		if (event.button.button == SDL_BUTTON_LEFT
			&& event.button.x > WINDOW_WIDTH / 2 - 200
			&& event.button.x < WINDOW_WIDTH / 2 + 200
			&& event.button.y > 500
			&& event.button.y < 600) {
			path = PLAYERTOPLAYER;
		}

		if (event.button.button == SDL_BUTTON_LEFT
			&& event.button.x > WINDOW_WIDTH / 2 - 200
			&& event.button.x < WINDOW_WIDTH / 2 + 200
			&& event.button.y > 700
			&& event.button.y < 800) {
			path = PLAYERTOCOMPUTER;
		}

		if (event.button.button == SDL_BUTTON_LEFT
			&& event.button.x > WINDOW_WIDTH / 2 - 200
			&& event.button.x < WINDOW_WIDTH / 2 + 200
			&& event.button.y > 900
			&& event.button.y < 1000 && checkload) {
			path = LOADGAME;
		}

		if (event.button.button == SDL_BUTTON_LEFT
			&& event.button.x > WINDOW_WIDTH / 2 - 200
			&& event.button.x < WINDOW_WIDTH / 2 + 200
			&& event.button.y > 1100
			&& event.button.y < 1200) {
			path = RANK;
		}

		if (event.button.button == SDL_BUTTON_LEFT
			&& event.button.x > Exit.x
			&& event.button.x < Exit.x + 50
			&& event.button.y > Exit.y
			&& event.button.y < Exit.y + 50) {
			path = ExitB;
		}
		break;

	}


}
void renderer_ueser_interface(void) {

	SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
	SDL_RenderClear(renderer);


	SDL_Rect htoh = {
		HtoH.x,
		HtoH.y,
		HtoH.wigth,
		HtoH.length
	};
	SDL_Rect htoc = {
		HtoC.x,
		HtoC.y,
		HtoC.wigth,
		HtoC.length
	};
	SDL_Rect lgame = {
		Lgame.x,
		Lgame.y,
		Lgame.wigth,
		Lgame.length
	};
	SDL_Rect rank = {
		Rank.x,
		Rank.y,
		Rank.wigth,
		Rank.length
	};



	int width1, height1, width2, height2;
	SDL_QueryTexture(theexit, NULL, NULL, &width1, &height1);
	SDL_Rect exit = {
		Exit.x,
		Exit.y,
		width1 / 3,
		height1 / 3
	};

	SDL_RenderCopy(renderer, theexit, NULL, &exit);

	SDL_QueryTexture(thelogo, NULL, NULL, &width2, &height2);
	SDL_Rect Logo = {
		WINDOW_WIDTH / 2 - width2 / 2,
		200,
		width2 ,
		height2
	};

	SDL_RenderCopy(renderer, thelogo, NULL, &Logo);

	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
	SDL_RenderFillRect(renderer, &htoh);
	SDL_RenderFillRect(renderer, &htoc);
	SDL_RenderFillRect(renderer, &lgame);
	SDL_RenderFillRect(renderer, &rank);


	SDL_Rect s_1 = {
		s_1.x = HtoH.x + 5,
		s_1.y = HtoH.y,
		s_1.w = HtoH.wigth - 10,
		s_1.h = HtoH.length - 10
	};
	SDL_RenderCopy(renderer, texture_1, NULL, &s_1);

	SDL_Rect s_2 = {
		s_2.x = HtoC.x + 5,
		s_2.y = HtoC.y,
		s_2.w = HtoC.wigth - 10,
		s_2.h = HtoC.length - 10
	};
	SDL_RenderCopy(renderer, texture_2, NULL, &s_2);

	SDL_Rect s_3 = {
		s_3.x = Lgame.x + 5,
		s_3.y = Lgame.y,
		s_3.w = Lgame.wigth - 10,
		s_3.h = Lgame.length - 10
	};
	SDL_RenderCopy(renderer, texture_3, NULL, &s_3);

	SDL_Rect s_4 = {
		s_4.x = Rank.x + 100,
		s_4.y = Rank.y + 20,
		s_4.w = Rank.wigth - 200,
		s_4.h = Rank.length - 50
	};
	SDL_RenderCopy(renderer, texture_4, NULL, &s_4);

	SDL_RenderPresent(renderer);
} 
void setup() {

	HtoH.x = WINDOW_WIDTH / 2 - 200;
	HtoH.y = 500;
	HtoH.wigth = 400;
	HtoH.length = 100;

	HtoC.x = WINDOW_WIDTH / 2 - 200;
	HtoC.y = 700;
	HtoC.wigth = 400;
	HtoC.length = 100;

	Lgame.x = WINDOW_WIDTH / 2 - 200;
	Lgame.y = 900;
	Lgame.wigth = 400;
	Lgame.length = 100;

	Rank.x = WINDOW_WIDTH / 2 - 200;
	Rank.y = 1100;
	Rank.wigth = 400;
	Rank.length = 100;

	Exit.x = 1400;
	Exit.y = 50;
	Exit.wigth = 50;
	Exit.length = 50;
	path_image1 = "RedX.bmp";
	logo = "logo2.png";
	home = "home.png";
	delete_path = "delete.png";
	theexit = IMG_LoadTexture(renderer, path_image1);
	if (theexit == NULL) {
		printf("error loading image: %s\n", IMG_GetError());
		return;
	}
	thelogo = IMG_LoadTexture(renderer, logo);
	if (thelogo == NULL) {
		printf("error loading image: %s\n", IMG_GetError());
		return;
	}
	thehome = IMG_LoadTexture(renderer, home);
	if (thehome == NULL) {
		printf("error loading image: %s\n", IMG_GetError());
		return;
	} 
	thedelete = IMG_LoadTexture(renderer, delete_path);
	if (thedelete == NULL) {
		printf("error loading image: %s\n", IMG_GetError());
		return;
	}
	font = TTF_OpenFont("Open 24 Display St.ttf", 32);
	if (font == NULL) {
		printf("Font loadind failed :%s\n", TTF_GetError());
		return;
	}

	text1 = TTF_RenderText_Solid(font, "Human vs Human", white, 500);
	if (text1 == NULL) {
		printf("Font1 loadind failed :%s\n", TTF_GetError());
		return;
	}
	texture_1 = SDL_CreateTextureFromSurface(renderer, text1);
	if (texture_1 == NULL) {
		printf("Font2 loadind failed :%s\n", TTF_GetError());
		return;
	}
	text2 = TTF_RenderText_Solid(font, "Human vs AI", white, 500);
	texture_2 = SDL_CreateTextureFromSurface(renderer, text2);

	text3 = TTF_RenderText_Solid(font, "Load Game", white, 500);
	texture_3 = SDL_CreateTextureFromSurface(renderer, text3);

	text4 = TTF_RenderText_Solid(font, "Rank", white, 500);
	texture_4 = SDL_CreateTextureFromSurface(renderer, text4);

	homecheck = 0;
	out = 0;
	path = NOPATHCHOSEN;  
	FILE* ifloadgame = fopen("games.txt", "r"); 
	fscanf(ifloadgame, "%d", &checkload); 
	fclose(ifloadgame); 
} 

void ueserinterface() { 
	setup(); 
	while (test && !path) { 
		input_ueser_interface(); 
		renderer_ueser_interface(); 
	}
}