#include"loadgame.h"
typedef struct {
	int  scoure;
	char name[20];
}playerRank;
playerRank* top10arr;
int end = 0;
SDL_Texture** namestexture, ** ranktexture, ** scouretexture;

void setupranks() {
	int size;
	FILE* datapickup = fopen("ranks.txt", "r");
	fscanf(datapickup, "%d ", &size);
	top10arr = calloc(size, sizeof(playerRank));
	for (int i = 0; i < size; i++) {
		fscanf(datapickup, "%s %d", &top10arr[i].name, &top10arr[i].scoure);
	}
	fclose(datapickup);
	end = size >= 10 ? 10 : size;
	for (int i = 0; i < end; i++) {
		for (int j = 0; j < size - 1; j++) {
			if (top10arr[j].scoure < top10arr[j + 1].scoure) {
				playerRank tem = top10arr[j];
				top10arr[j] = top10arr[j + 1];
				top10arr[j + 1] = tem;
			}
		}
	}
	namestexture = calloc(end, sizeof(SDL_Texture*));
	ranktexture = calloc(end, sizeof(SDL_Texture*));
	scouretexture = calloc(end, sizeof(SDL_Texture*));
	for (int i = 0; i < end; i++) {
		text1 = TTF_RenderText_Solid(font, top10arr[i].name, i != 0 ? white : gold);
		namestexture[i] = SDL_CreateTextureFromSurface(renderer, text1);
	}
	for (int i = 0; i < end; i++) {
		char temp[4];
		sprintf(temp, "%d", i + 1);
		text1 = TTF_RenderText_Solid(font, temp, i != 0 ? white : gold);
		ranktexture[i] = SDL_CreateTextureFromSurface(renderer, text1);
	}
	for (int i = 0; i < end; i++) {
		char temp[4];
		sprintf(temp, "%d", top10arr[i].scoure);
		text1 = TTF_RenderText_Solid(font, temp, i != 0 ? white : gold);
		scouretexture[i] = SDL_CreateTextureFromSurface(renderer, text1);
	}

	text1 = TTF_RenderText_Solid(font, "top 10", top10color);
	texture_1 = SDL_CreateTextureFromSurface(renderer, text1);

}
void removeDATA() {
	remove("ranks.txt");
	FILE* delete = fopen("ranks.txt","w");
	fprintf(delete, "0\n");
	fclose(delete);
}
void rendererRanks() {
	SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
	SDL_RenderClear(renderer);

	SDL_Rect table = {
		WINDOW_WIDTH / 2 - 500,
		WINDOW_LENGHT / 2 - 450,
		1000,
		900
	};
	SDL_SetRenderDrawColor(renderer, 43, 45, 66, 255);
	SDL_RenderFillRect(renderer, &table);
	for (int i = 0; i < end; i++) {
		int w = strlen(top10arr[i].name) * 50;
		SDL_Rect names = {
			WINDOW_WIDTH / 2 - w / 2,
			WINDOW_LENGHT / 2 - 400 + i * 80,
			w ,
			40
		};
		SDL_RenderCopy(renderer, namestexture[i], NULL, &names);
	}
	for (int i = 0; i < end; i++) {
		SDL_Rect ranks = {
			WINDOW_WIDTH / 2 - 400,
			WINDOW_LENGHT / 2 - 400 + i * 80,
			30,
			40
		};
		SDL_RenderCopy(renderer, ranktexture[i], NULL, &ranks);
	}
	for (int i = 0; i < end; i++) {
		SDL_Rect names = {
			WINDOW_WIDTH / 2 + 300,
			WINDOW_LENGHT / 2 - 400 + i * 80,
			50,
			40
		};
		SDL_RenderCopy(renderer, scouretexture[i], NULL, &names);
	}
	SDL_Rect top10 = {
			WINDOW_WIDTH / 2 - 200,
			WINDOW_LENGHT / 2 - 550 ,
			400,
			100
	};
	SDL_RenderCopy(renderer, texture_1, NULL, &top10);
	SDL_QueryTexture(theexit, NULL, NULL, &width1, &height1);
	SDL_Rect exit = {
		Exit.x,
		Exit.y,
		width1 / 3,
		height1 / 3
	};

	SDL_RenderCopy(renderer, theexit, NULL, &exit);
	SDL_QueryTexture(thedelete, NULL, NULL, &width1, &height1);
	SDL_Rect deletebox = {
		Exit.x,
		Exit.y+1250,
		width1 / 10,
		height1 /10
	};
	SDL_RenderCopy(renderer,thedelete,NULL,&deletebox); 
	SDL_QueryTexture(thehome, NULL, NULL, &width2, &height2); 
	SDL_Rect homebox = { 
		Exit.x - 100, 
		Exit.y,
		width1 / 8, 
		height1 /8 
	}; 
	SDL_RenderCopy(renderer, thehome, NULL, &homebox); 
	SDL_RenderPresent(renderer);

}
void inputRank() {
	SDL_Event rank;
	SDL_PollEvent(&rank);
	switch (rank.type)
	{
	case SDL_QUIT:
		test = false;
		break;
	case SDL_MOUSEBUTTONDOWN:
		if (rank.button.button == SDL_BUTTON_LEFT
			&& rank.button.x > Exit.x
			&& rank.button.x < Exit.x + 50
			&& rank.button.y > Exit.y
			&& rank.button.y < Exit.y + 50) {
			out = 1;

		}
		if (rank.button.button == SDL_BUTTON_LEFT
			&& rank.button.x > Exit.x-100
			&& rank.button.x < Exit.x - 50
			&& rank.button.y > Exit.y
			&& rank.button.y < Exit.y + 50) {
			out = 1;
			homecheck = 1;
		}
		if (rank.button.button == SDL_BUTTON_LEFT 
			&& rank.button.x > Exit.x 
			&& rank.button.x < Exit.x + 50 
			&& rank.button.y > Exit.y +1250
			&& rank.button.y < Exit.y + 1300) {
			out = 1;
			homecheck = 1;
			removeDATA();
		}
		break;
	}

}
void rankmode() {
	setupranks();
	while (test && !out) {
		rendererRanks();
		inputRank();
	}
	free(top10arr);
}
