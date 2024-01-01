#include "conts.h"
#include"save.h"

SDL_Surface* s1 = NULL;
SDL_Surface* s2 = NULL;
SDL_Surface* winnersurface = NULL;
SDL_Surface* winnersurfacename = NULL;
SDL_Surface* timersurface = NULL;
SDL_Surface* remaingSurface = NULL;
SDL_Surface* numremaingsurface = NULL;
SDL_Texture* s1texture = NULL;
SDL_Texture* s2texture = NULL;
SDL_Texture* winner = NULL;
SDL_Texture* winnername = NULL;
SDL_Texture* theundo = NULL;
SDL_Texture* theredo = NULL;
SDL_Texture* timertexture = NULL;
SDL_Texture* remaingtexture = NULL;
SDL_Texture * numremaingtexture = NULL;
time_t starttime=0, timer,endtime =0;
char linesrem[3];
void check(); 
void draw_gamebase() {
	
	for (int i = 0; i < hardness; i++) {
		for (int j = 0; j < hardness; j++) {
			SDL_Rect dots = {
			WINDOW_WIDTH / 2 - width2 / 2 + 60 + 185 * j,
			WINDOW_LENGHT / 2 - height2 / 2 + 150 + 170 * i,
			50,
			50
			};
			SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
			SDL_RenderFillRect(renderer, &dots);
		}
	}
}
int found(lines* arr, int x, int y, int size) {
	for (int i = 0; i < size; i++) {
		if (arr[i].x == x && arr[i].y == y) {
			return 1;
		}
	}
	return 0;
}
int findy(int x) {
	int  counter = 0;
	x -= WINDOW_WIDTH / 2 - width2 / 2 + 60;
	while (x && counter < hardness - 1) {
		x -= 185;
		counter++;
	}
	if (counter == hardness - 1) {
		edgex = 1;
		return counter - 1;

	}
	edgex = 0;
	return counter;
}
int findx(int y) {
	int  counter = 0;
	y -= WINDOW_LENGHT / 2 - height2 / 2 + 150;
	while (y && counter < hardness - 1) {
		y -= 170;
		counter++;
	}
	if (counter == hardness - 1) {
		edgey = 1;
		return counter - 1;

	}
	edgey = 0;

	return counter;
}
void dfs(int x, int y) { 
	if (x >= hardness - 1 || x == -1 || y >= hardness - 1 || y == -1 || game[x][y].sum != 3) {
		return;
	} 
	if (game[x][y].hn != 2) {
		H[Hl].x = game[x][y].hl[0].x;
		H[Hl].y = game[x][y].vl[0].y == game[x][y].hl[0].y ? game[x][y].hl[0].y + 170 : game[x][y].hl[0].y - 170;
		H[Hl++].color = turn;
		int yp = findy(game[x][y].hl[0].x); 
		int xp = findx(game[x][y].vl[0].y == game[x][y].hl[0].y ? game[x][y].hl[0].y + 170 : game[x][y].hl[0].y - 170);
		game[xp][yp].sum++;
		game[xp][yp].color = turn;
		game[xp][yp].hl[game[xp][yp].hn].x = game[x][y].hl[0].x;
		game[xp][yp].hl[game[xp][yp].hn].y = game[x][y].vl[0].y == game[x][y].hl[0].y ? game[x][y].hl[0].y + 170 : game[x][y].hl[0].y - 170;
		game[xp][yp].hl[game[xp][yp].hn++].color = turn; 
		
		if (xp - 1 >= 0 && !edgey) {
			game[xp - 1][yp].sum++;
			game[xp - 1][yp].color = turn; 
			game[xp - 1][yp].hl[game[xp - 1][yp].hn].x = game[x][y].hl[0].x; 
			game[xp - 1][yp].hl[game[xp - 1][yp].hn].y = game[x][y].vl[0].y == game[x][y].hl[0].y ? game[x][y].hl[0].y + 170 : game[x][y].hl[0].y - 170;
			game[xp - 1][yp].hl[game[xp - 1][yp].hn++].color = turn; 
			check(xp - 1, yp); 
		}
		check(xp, yp);
	}
	else {
		V[Vl].x = game[x][y].vl[0].x == game[x][y].hl[0].x ? game[x][y].vl[0].x + 185 : game[x][y].vl[0].x - 185;
		V[Vl].y = game[x][y].vl[0].y;
		V[Vl++].color = turn;
		int yp = findy(game[x][y].vl[0].x == game[x][y].hl[0].x ? game[x][y].vl[0].x + 185 : game[x][y].vl[0].x - 185); 
		int xp = findx(game[x][y].vl[0].y);
		game[xp][yp].sum++;
		game[xp][yp].color = turn;
		game[xp][yp].vl[game[xp][yp].vn].x = game[x][y].vl[0].x == game[x][y].hl[0].x ? game[x][y].vl[0].x + 185 : game[x][y].vl[0].x - 185;
		game[xp][yp].vl[game[xp][yp].vn].y = game[x][y].vl[0].y;
		game[xp][yp].vl[game[xp][yp].vn++].color = turn;
		if (yp - 1 >= 0 && !edgex) {
			game[xp][yp - 1].sum++;
			game[xp][yp - 1].color = turn;
			game[xp][yp - 1].vl[game[xp][yp - 1].vn].x = game[x][y].vl[0].x == game[x][y].hl[0].x ? game[x][y].vl[0].x + 185 : game[x][y].vl[0].x - 185;
			game[xp][yp - 1].vl[game[xp][yp - 1].vn].y = game[x][y].vl[0].y;
			game[xp][yp - 1].vl[game[xp][yp - 1].vn++].color = turn;
			check(xp, yp - 1);
		}
		check(xp, yp);
	}
}
void check(int x,int y) {
	if (game[x][y].sum == 4) { 
		scoer = 1;
		if (game[x][y].color == BLUEturn &&  !game[x][y].ckecked) {
			sc1++;
			sprintf(thes1, "%d", sc1);
			s1 = TTF_RenderText_Solid(font, thes1, blue, 500);
			s1texture = SDL_CreateTextureFromSurface(renderer, s1);
			game[x][y].ckecked = 1;
		}
		else if (game[x][y].color == REDturn && !game[x][y].ckecked) { 
			sc2++;
			sprintf(thes2, "%d", sc2);
			s2 = TTF_RenderText_Solid(font, thes2, red, 500);
			s2texture = SDL_CreateTextureFromSurface(renderer, s2);
			game[x][y].ckecked = 1;
		} 
		if (!computerturn) {
			dfs(x - 1, y);
			dfs(x, y - 1);
			dfs(x + 1, y);
			dfs(x, y + 1);
		}
	}
} 
void draw_H_line(lines* arr, int num) { 
	for (int i = 0; i < num; i++) { 
		SDL_Rect line = { 
			arr[i].x + 50, 
			arr[i].y + 10,
			135,
			30
		};
		if (arr[i].color) {
			SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255);
		}
		else {
			SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
		}
		SDL_RenderFillRect(renderer, &line);
	}
} 
void draw_V_line(lines* arr, int num) {
	for (int i = 0; i < num; i++) {
		SDL_Rect linee = {
			arr[i].x + 10,
			arr[i].y + 50,
			30,
			120
		};
		if (arr[i].color) {
			SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255);
		}
		else {
			SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
		}
		SDL_RenderFillRect(renderer, &linee);
	}

}
void draw_boxse() {
	for (int i = 0; i < hardness - 1; i++) {
		for (int j = 0; j < hardness - 1; j++) {
			if (game[i][j].sum >= 4) {
				SDL_Rect box = {
					WINDOW_WIDTH / 2 - width2 / 2 + 70 + 185 * j,
					WINDOW_LENGHT / 2 - height2 / 2 + 170 + 170 * i,
					185,
					170
				};
				if (game[i][j].color) {
					SDL_SetRenderDrawColor(renderer, 65, 105, 255, 255);
				}
				else {
					SDL_SetRenderDrawColor(renderer, 255, 158, 145, 255);
				}
				SDL_RenderFillRect(renderer, &box);
			}
		}
	}
}  
void draw_scoerandplayers() {
	SDL_Rect p1text = { 
		WINDOW_WIDTH / 2 - 500, 
		100,
		player1.wigth, 
		player1.length 
	};
	SDL_RenderCopy(renderer, p1, NULL, &p1text); 
	SDL_Rect p2text = { 
		WINDOW_WIDTH / 2 + 200,
		100, 
		player2.wigth,
		player2.length 
	};
	SDL_RenderCopy(renderer, p2, NULL, &p2text); 
	SDL_Rect scoer1 = { 
		WINDOW_WIDTH / 2 - 500 + 150,
		200,
		60,
		60
	};

	SDL_RenderCopy(renderer, s1texture, NULL, &scoer1);

	SDL_Rect scoer2 = {
		WINDOW_WIDTH / 2 + 200 + 150,
		200,
		60,
		60
	};

	SDL_RenderCopy(renderer, s2texture, NULL, &scoer2);
	SDL_Rect remainingBoxes = {
		WINDOW_WIDTH -270, 
		550,
		250,
		250
	};
	SDL_RenderCopy(renderer, remaingtexture, NULL, &remainingBoxes); 
	SDL_Rect numremainingBoxes = {
		WINDOW_WIDTH - 270+125,
		830,
		80,
		80
	};
	SDL_RenderCopy(renderer, numremaingtexture, NULL, &numremainingBoxes); 
} 
void redoAndundoRender() { 
	if (undocount) {
		 
		SDL_QueryTexture(theundo, NULL, NULL, &w1, &h1); 
		SDL_Rect undobox = {  
			WINDOW_WIDTH - 120,
			WINDOW_LENGHT - 250,
			w1 / 5,
			h1 / 5
		};
		SDL_RenderCopy(renderer, theundo, NULL, &undobox); 
	}
	if (redocount) { 
		SDL_QueryTexture(theredo, NULL, NULL, &w2, &h2); 
		SDL_Rect redobox = { 
			WINDOW_WIDTH - 200, 
			WINDOW_LENGHT - 245, 
			w2 / 5, 
			h2 / 5 
		};
		SDL_RenderCopy(renderer, theredo, NULL, &redobox); 
	}
}
void undofunction() {
	
	if (undocount <= 0) {
		return;
	}
	for (int i = 0; i < hardness - 1; i++) {
		for (int j = 0; j < hardness - 1; j++) {
			redostack[redocount][i][j] = undostack[undocount][i][j];
		}
	}
	undocount--;
	redocount++;
	for (int i = 0; i < hardness - 1; i++) {
		for (int j = 0; j < hardness - 1; j++) {
			game[i][j] = undostack[undocount][i][j];
		}
	}
	Hl = game[0][0].ht;
	Vl = game[0][0].vt;
	sc1 = game[0][0].s1;
	sc2 = game[0][0].s2;
	
	sprintf(thes1, "%d", sc1);
	sprintf(thes2, "%d", sc2);
	s1 = TTF_RenderText_Solid(font, thes1, blue, 500);
	s1texture = SDL_CreateTextureFromSurface(renderer, s1);

	s2 = TTF_RenderText_Solid(font, thes2, red, 500);
	s2texture = SDL_CreateTextureFromSurface(renderer, s2);
	turn = game[0][0].ture;
	for (int i = 0; i < Hl; i++) {
		H[i] = game[0][0].h[i];
	}
	for (int i = 0; i < Vl; i++) {
		V[i] = game[0][0].v[i];
	}
	sprintf(linesrem, "%d", -(Hl + Vl) + (hardness) * (hardness - 1) * 2); 
	numremaingsurface = TTF_RenderText_Solid(font, linesrem, top10color, 500); 
	numremaingtexture = SDL_CreateTextureFromSurface(renderer, numremaingsurface); 
}
void redofunction() {
	redocount--;
	undocount++;
	for (int i = 0; i < hardness - 1; i++) {
		for (int j = 0; j < hardness - 1; j++) {
			game[i][j] = redostack[redocount][i][j];
		}
	}
	for (int i = 0; i < (hardness - 1); i++) {
		for (int j = 0; j < hardness - 1; j++) {
			undostack[undocount][i][j] = game[i][j];
		}
	}
	Hl = game[0][0].ht;
	Vl = game[0][0].vt;
	sc1 = game[0][0].s1;
	sc2 = game[0][0].s2;
	turn = game[0][0].ture;
	sprintf(thes1, "%d", sc1);
	sprintf(thes2, "%d", sc2);
	s1 = TTF_RenderText_Solid(font, thes1, blue, 500);
	s1texture = SDL_CreateTextureFromSurface(renderer, s1);
	 
	s2 = TTF_RenderText_Solid(font, thes2, red, 500);
	s2texture = SDL_CreateTextureFromSurface(renderer, s2);

	for (int i = 0; i < Hl; i++) {
		H[i] = game[0][0].h[i];
	}
	for (int i = 0; i < Vl; i++) {
		V[i] = game[0][0].v[i];
	}
	sprintf(linesrem, "%d", -(Hl + Vl) + (hardness) * (hardness - 1) * 2); 
	numremaingsurface = TTF_RenderText_Solid(font, linesrem, top10color, 500); 
	numremaingtexture = SDL_CreateTextureFromSurface(renderer, numremaingsurface); 
}
void timer_set() {
	endtime = time(NULL);
	timer = difftime(endtime,starttime);
	int sec = timer % 60;
	min = timer/60;
	char timer_string[10];
	sprintf(timer_string, "%0.2d:%0.2d", min, sec);
	timersurface = TTF_RenderText_Solid(font, timer_string, top10color, 500);
	timertexture = SDL_CreateTextureFromSurface(renderer, timersurface);
} 
void renderer_ptpmode() {
	SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
	SDL_RenderClear(renderer);

	width2 = hardness == 3 ? 550 : 900; 
	height2 = hardness == 3 ? 500 : 840; 
	SDL_Rect gameSpace = { 
		WINDOW_WIDTH / 2 - width2 / 2, 
		WINDOW_LENGHT / 2 - height2 / 2 + 100, 
		width2,
		height2 
	};
	SDL_SetRenderDrawColor(renderer, 169, 169, 169, 255); 
	SDL_RenderFillRect(renderer, &gameSpace); 

	SDL_QueryTexture(theexit, NULL, NULL, &width1, &height1);
	SDL_Rect exit = {
		Exit.x,
		Exit.y,
		width1 / 3,
		height1 / 3
	};
	SDL_RenderCopy(renderer, theexit, NULL, &exit);
	
	SDL_QueryTexture(thehome, NULL, NULL, &width1, &height1);
	SDL_Rect homebox = {
		Exit.x - 100,
		Exit.y,
		width1 / 13,
		height1 / 13
	};
	SDL_RenderCopy(renderer, thehome, NULL, &homebox);

	draw_boxse(); 
	draw_gamebase();
	 
	draw_scoerandplayers();
	draw_H_line(H, Hl);
	draw_V_line(V, Vl);
	if (fwinner) {
		SDL_Rect winnerboxes = {
			WINDOW_WIDTH / 2 - 300,
			WINDOW_LENGHT / 2 - 150,
			600,
			300
		};
		SDL_Rect resalt = {
			WINDOW_WIDTH / 2 - 150 ,
			WINDOW_LENGHT / 2 - 130 ,
			300,
			100
		};
		SDL_SetRenderDrawColor(renderer, 255, 215, 115, 255);
		SDL_RenderFillRect(renderer, &winnerboxes);
		SDL_RenderCopy(renderer, winner, NULL, &resalt);
		if (sc1 != sc2) {
			SDL_Rect name = {
			WINDOW_WIDTH / 2 - 100,
			WINDOW_LENGHT / 2 - 30,
			200,
			100
			};
			SDL_RenderCopy(renderer, winnername, NULL, &name);
		}
	}else {
		SDL_Rect timerboxes = {
		WINDOW_WIDTH / 2 - 700,
		WINDOW_LENGHT / 2 - 200 ,
		200,
		200
		};
		SDL_RenderCopy(renderer, timertexture, NULL, &timerboxes);
		SDL_FreeSurface(timersurface);
		SDL_DestroyTexture(timertexture);
	}
	
	redoAndundoRender();
	SDL_RenderPresent(renderer);
}

void update_ptpmode() {
	if (Hl + Vl == (hardness) * (hardness - 1) * 2 && !fwinner) {
		if (sc1 > sc2) {
			winnersurface = TTF_RenderText_Solid(font, "WINNER!", blue, 500);
			winner = SDL_CreateTextureFromSurface(renderer, winnersurface);
			winnersurfacename = TTF_RenderText_Solid(font, name1, blue, 500);
			winnername = SDL_CreateTextureFromSurface(renderer, winnersurfacename);
		}
		else if (sc2 > sc1) {
			winnersurface = TTF_RenderText_Solid(font, "WINNER!", red, 500);
			winner = SDL_CreateTextureFromSurface(renderer, winnersurface);
			winnersurfacename = TTF_RenderText_Solid(font, name2, red, 500);
			winnername = SDL_CreateTextureFromSurface(renderer, winnersurfacename);
		}
		else {
			winnersurface = TTF_RenderText_Solid(font, "DROW!", black, 500);
			winner = SDL_CreateTextureFromSurface(renderer, winnersurface);
		}
		fwinner = 1;
	}
		timer_set();
}
void lines_inputckeck(SDL_Event play) { 
	for (int i = 0; i < hardness; i++) {
		for (int j = 0; j < hardness - 1; j++) {
			if (play.button.button == SDL_BUTTON_LEFT
				&& play.button.x > WINDOW_WIDTH / 2 - width2 / 2 + 60 + 185 * j
				&& play.button.x < WINDOW_WIDTH / 2 - width2 / 2 + 60 + 185 * j + 185 + 50
				&& play.button.y > WINDOW_LENGHT / 2 - height2 / 2 + 150 + 170 * i
				&& play.button.y < WINDOW_LENGHT / 2 - height2 / 2 + 150 + 170 * i + 50) {

				startXh = WINDOW_WIDTH / 2 - width2 / 2 + 60 + 185 * j;
				startYh = WINDOW_LENGHT / 2 - height2 / 2 + 150 + 170 * i;
				if (found(H, startXh, startYh, Hl)) {
					return 0;
				}
				H[Hl].x = startXh;
				H[Hl].y = startYh;
				H[Hl++].color = turn;
				int y = findy(startXh);
				int x = findx(startYh);
				game[x][y].sum++;
				game[x][y].color = turn;
				game[x][y].hl[game[x][y].hn].x = startXh;
				game[x][y].hl[game[x][y].hn].y = startYh;
				game[x][y].hl[game[x][y].hn++].color = turn;
				game[0][0].h = H;
				game[0][0].ht = Hl;
				game[0][0].v = V;
				game[0][0].vt = Vl;
				if (turn) { 
					numberp1++;
				}
				else {
					numberp2++;
				}
				
				if (x - 1 >= 0 && !edgey) {
					game[x - 1][y].sum++;
					game[x - 1][y].color = turn;
					game[x-1][y].hl[game[x-1][y].hn].x = startXh; 
					game[x-1][y].hl[game[x-1][y].hn].y = startYh; 
					game[x-1][y].hl[game[x-1][y].hn++].color = turn; 
					check(x - 1, y);
				} 
				check(x, y);
				if (turn == BLUEturn && !scoer && path == PLAYERTOPLAYER) { 
					turn = REDturn; 
				}
				else if (turn == REDturn && !scoer) { 
					turn = BLUEturn; 
				} 
				else if (turn == BLUEturn && !scoer && path == PLAYERTOCOMPUTER) {  
					computerturn = 1; 
				} 
				game[0][0].s1 = sc1;
				game[0][0].s2 = sc2;
				game[0][0].ture = turn;
				scoer = 0;
				undocount++;
				redocount = 0; 

				for (int i = 0; i < (hardness - 1); i++) { 
					for (int j = 0; j < hardness - 1; j++) {  
						undostack[undocount][i][j] = game[i][j]; 
					}
				}
				sprintf(linesrem, "%d", -(Hl + Vl) + (hardness) * (hardness - 1) * 2);
				numremaingsurface = TTF_RenderText_Solid(font, linesrem, top10color, 500);
				numremaingtexture = SDL_CreateTextureFromSurface(renderer, numremaingsurface);

				return;
			}
		}
	}

	for (int i = 0; i < hardness - 1; i++) {
		for (int j = 0; j < hardness; j++) {
			if (play.button.button == SDL_BUTTON_LEFT
				&& play.button.x > WINDOW_WIDTH / 2 - width2 / 2 + 60 + 185 * j
				&& play.button.x < WINDOW_WIDTH / 2 - width2 / 2 + 60 + 185 * j + 50
				&& play.button.y > WINDOW_LENGHT / 2 - height2 / 2 + 150 + 170 * i
				&& play.button.y < WINDOW_LENGHT / 2 - height2 / 2 + 150 + 170 * i + 50 + 170) {

				startXv = WINDOW_WIDTH / 2 - width2 / 2 + 60 + 185 * j;
				startYv = WINDOW_LENGHT / 2 - height2 / 2 + 150 + 170 * i;
				if (found(V, startXv, startYv, Vl)) {
					return 0;
				}
				V[Vl].x = startXv;
				V[Vl].y = startYv;
				V[Vl++].color = turn;
				int y = findy(startXv);
				int x = findx(startYv);
				game[x][y].sum++;
				game[x][y].color = turn;
				game[x][y].vl[game[x][y].vn].x = startXv; 
				game[x][y].vl[game[x][y].vn].y = startYv; 
				game[x][y].vl[game[x][y].vn++].color = turn; 
				game[0][0].v = V;
				game[0][0].vt = Vl;
				game[0][0].h = H;
				game[0][0].ht = Hl;
				 
				if (y - 1 >= 0 && !edgex ) {
					game[x][y - 1].sum++;
					game[x][y - 1].color = turn;
					game[x][y - 1].vl[game[x][y - 1].vn].x = startXv;
					game[x][y - 1].vl[game[x][y - 1].vn].y = startYv;
					game[x][y - 1].vl[game[x][y - 1].vn++].color = turn;
					check(x, y - 1);
				}
				check(x, y); 
				game[0][0].s1 = sc1;
				game[0][0].s2 = sc2;
				game[0][0].ture = turn;
				if (turn) {
					numberp1++;
				}
				else {
					numberp2++;
				}

				if (turn == BLUEturn && !scoer && path == PLAYERTOPLAYER) {
					turn = REDturn;
				}
				else if (turn == REDturn && !scoer) {

					turn = BLUEturn;
				}else if (turn == BLUEturn && !scoer && path == PLAYERTOCOMPUTER) { 
					computerturn = 1;
				}
				scoer = 0;
				undocount++;
				redocount = 0;
				
				for (int i = 0; i < (hardness - 1); i++) {
					for (int j = 0; j < hardness - 1; j++) {
						undostack[undocount][i][j] = game[i][j];
					}
				}
				sprintf(linesrem, "%d", -(Hl + Vl) + (hardness) * (hardness - 1) * 2); 
				numremaingsurface = TTF_RenderText_Solid(font, linesrem, top10color, 500); 
				numremaingtexture = SDL_CreateTextureFromSurface(renderer, numremaingsurface); 
				return;
			}
		}
	}
}
void buttons_inputckeck(SDL_Event play) {
	if (play.button.button == SDL_BUTTON_LEFT
		&& play.button.x > Exit.x
		&& play.button.x < Exit.x + 50
		&& play.button.y > Exit.y
		&& play.button.y < Exit.y + 50) {
		out = 1;
	}
	if (play.button.button == SDL_BUTTON_LEFT 
		&& play.button.x > Exit.x-100 
		&& play.button.x < Exit.x - 50 
		&& play.button.y > Exit.y 
		&& play.button.y < Exit.y + 50) { 
		out = 1;
		homecheck = 1; 
	}
	if (play.button.button == SDL_BUTTON_LEFT
		&& play.button.x > WINDOW_WIDTH - 120
		&& play.button.x < WINDOW_WIDTH - 120 + w1 / 5
		&& play.button.y > WINDOW_LENGHT - 250
		&& play.button.y < WINDOW_LENGHT - 250 + h1 / 5
		&& (Hl || Vl) && !fwinner) {
		undofunction();
	}

	if (play.button.button == SDL_BUTTON_LEFT
		&& play.button.x > WINDOW_WIDTH - 200
		&& play.button.x < WINDOW_WIDTH - 200 + w2 / 5
		&& play.button.y > WINDOW_LENGHT - 245
		&& play.button.y < WINDOW_LENGHT - 245 + h2 / 5
		&& redocount && !fwinner) {
		redofunction();
	}

}
void input_propmode() {
	SDL_Event play;
	SDL_PollEvent(&play);

	switch (play.type) {
	case SDL_QUIT:
		test = false;
		break;
	case SDL_MOUSEBUTTONDOWN:
		lines_inputckeck(play);
		buttons_inputckeck(play);
	}

}
void score_setup() {

	sprintf(thes1, "%d", sc1); 
	sprintf(thes2, "%d", sc2); 
	sprintf(linesrem, "%d", -(Hl + Vl) + (hardness) * (hardness - 1) * 2);


	s1 = TTF_RenderText_Solid(font, thes1, blue, 500); 
	s1texture = SDL_CreateTextureFromSurface(renderer, s1); 

	s2 = TTF_RenderText_Solid(font, thes2, red, 500); 
	s2texture = SDL_CreateTextureFromSurface(renderer, s2);

	remaingSurface = TTF_RenderText_Solid(font, "remaining lines", top10color, 500);
	remaingtexture = SDL_CreateTextureFromSurface(renderer, remaingSurface);

	numremaingsurface = TTF_RenderText_Solid(font, linesrem, top10color, 500);
	numremaingtexture = SDL_CreateTextureFromSurface(renderer, numremaingsurface);

} 
void image_including() {
	undo = "undo.png";
	redo = "redo.png";
	theundo = IMG_LoadTexture(renderer, undo);
	if (theundo == NULL) {
		printf("error loading image: %s\n", IMG_GetError());
		return;
	}
	theredo = IMG_LoadTexture(renderer, redo);
	if (theredo == NULL) {
		printf("error loading image: %s\n", IMG_GetError());
		return;
	}
}
void data_setup(){
	H = calloc(hardness * (hardness - 1), sizeof(lines));
	V = calloc(hardness * (hardness - 1), sizeof(lines));
	game = calloc((hardness - 1), sizeof(boxese*));
	for (int i = 0; i < hardness - 1; i++) {
		game[i] = calloc((hardness - 1), sizeof(boxese));
	}
	undostack = calloc((hardness - 1) * (hardness) * 2 + 1, sizeof(boxese**));
	for (int i = 0; i < (hardness - 1) * (hardness) * 2 + 1; i++) {
		undostack[i] = calloc(hardness - 1, sizeof(boxese*));
		for (int j = 0; j < hardness - 1; j++) {
			undostack[i][j] = calloc(hardness - 1, sizeof(boxese));
		}
	}

	redostack = calloc((hardness - 1) * (hardness) * 2 + 1, sizeof(boxese**));
	for (int i = 0; i < (hardness - 1) * (hardness) * 2 + 1; i++) {
		redostack[i] = calloc(hardness - 1, sizeof(boxese*));
		for (int j = 0; j < hardness - 1; j++) {
			redostack[i][j] = calloc(hardness - 1, sizeof(boxese));
		}
	}
}
void setup_ptpmode() {
	Hl = 0;
	Vl = 0;
	redocount = 0;
	undocount = 0;
	sc1 = 0;
	sc2 = 0;
	turn = BLUEturn;
	fwinner = 0;
	score_setup();
	image_including();
	data_setup();
	starttime = time(NULL);   
	timer_set(); 
	
}

void playertoplayermode() { 
	intro();  
	setup_ptpmode();  
	while (test &&!out) {  
		input_propmode();   
		update_ptpmode(); 
		renderer_ptpmode(); 
	}
	if (start) {
		saving();
	}
}