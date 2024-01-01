#include"rank.h"

void destroy_window(void)
{
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_DestroyTexture(theexit);
	SDL_DestroyTexture(thelogo);
	SDL_DestroyTexture(thedelete);
	SDL_FreeSurface(text1);
	SDL_FreeSurface(text2);
	SDL_FreeSurface(text3);
	SDL_FreeSurface(text4);
	SDL_FreeSurface(beginner); 
	SDL_FreeSurface(play1); 
	SDL_FreeSurface(remaingSurface);
	SDL_FreeSurface(numremaingsurface);
	SDL_FreeSurface(play2); 
	SDL_FreeSurface(Start);
	SDL_FreeSurface(surface_1);
	SDL_FreeSurface(winnersurface);
	SDL_FreeSurface(winnersurfacename);
	TTF_CloseFont(font);
	SDL_DestroyTexture(texture_1);
	SDL_DestroyTexture(thehome);
	SDL_DestroyTexture(texture_2);
	SDL_DestroyTexture(texture_3);
	SDL_DestroyTexture(texture_4);
	SDL_DestroyTexture(expe);
	SDL_DestroyTexture(begin);
	SDL_DestroyTexture(remaingtexture);
	SDL_DestroyTexture(numremaingtexture);
	SDL_DestroyTexture(p1);
	SDL_DestroyTexture(p2);
	SDL_DestroyTexture(s);
	SDL_DestroyTexture(playertexture1);
	SDL_DestroyTexture(playertexture2);
	for (int i = 0; i < end; i++) {
		SDL_DestroyTexture(namestexture[i]); 
	}
	for (int i = 0; i < end; i++) {
		SDL_DestroyTexture(ranktexture[i]);
	}
	for (int i = 0; i < end; i++) {
		SDL_DestroyTexture(scouretexture[i]);
	}
	SDL_DestroyTexture(winner);
	SDL_DestroyTexture(winnername);
	SDL_DestroyTexture(theundo);
	SDL_DestroyTexture(theredo);
	SDL_StopTextInput();
	Mix_CloseAudio();
	TTF_Quit();
	SDL_Quit();
	free(name1);
	free(name2);
	for (int i = 0; i < hardness - 1; i++) {
		free(game[i]);
	}
	free(game);
	for (int i = 0; i < (hardness - 1) * (hardness) * 2; i++) {
		for (int j = 0; j < hardness - 1; j++) {
			free(undostack[i][j]);
		}
		free(undostack[i]);
	}
	free(undostack);
	for (int i = 0; i < (hardness - 1) * (hardness) * 2; i++) {
		for (int j = 0; j < hardness - 1; j++) {
			free(redostack[i][j]);
		}
		free(redostack[i]);
	}
	free(redostack);
	free(H);
	free(V);
}
void game_loop() {
	ueserinterface();   
	switch (path) { 
		case PLAYERTOPLAYER: 
			playertoplayermode();  
			break;
		case PLAYERTOCOMPUTER:
			playertocomputermode();    
			break;
		case LOADGAME :
			Loadgamemode(); 
			break;
		case RANK:
			rankmode();  
			break;
	}
	if (homecheck) 
		game_loop();  
} 
void* backgraund(void* p) {
	while (out) {
		if (Mix_PlayMusic(music, 0) == -1) {
			printf("Failed to play music! SDL_mixer Error: %s\n", Mix_GetError());
			break;
		}
		
		while (Mix_PlayingMusic()) {
			SDL_Delay(2400); 
		}
	}
}
int main(int argc, char* argv[])
{
	pthread_t sounds_thread;

	test = open_window(); 
	//pthread_create(&sounds_thread,NULL,backgraund,NULL);
	game_loop();
	destroy_window(); 
	 
	return 0;
}

