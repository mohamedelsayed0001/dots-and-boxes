#include"playertoplayer.h"
int call = 0;

void input_introptc() {
	SDL_Event intro;
	SDL_PollEvent(&intro);
	switch (intro.type)
	{
	case SDL_QUIT:
		test = false;
		break;
	case SDL_MOUSEBUTTONDOWN:
		buttonsevents(intro);
		break;
	case SDL_TEXTINPUT:
		textinputevents(&name1, &playerSurface1, &playertexture1, intro);
		scale1++;
		break;
	}
}
void renderer_introptc() {
	SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
	SDL_RenderClear(renderer);

	buttonsRender();

	SDL_Rect textInputRectp1 = {
		WINDOW_WIDTH / 2 - 150,
		WINDOW_LENGHT / 2 + 100,
		300,
		100
	};
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
	SDL_RenderDrawRect(renderer, &textInputRectp1);

	textboutonsRender();

	SDL_Rect player1text = {
		player1.x,
		player1.y,
		player1.wigth,
		player1.length
	};
	SDL_RenderCopy(renderer, p1, NULL, &player1text);

	SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255);
	SDL_RenderFillRect(renderer, &textInputRectp1);

	SDL_Rect textInputerenderer1 = {
		WINDOW_WIDTH / 2 - 150 + 10,
		WINDOW_LENGHT / 2 + 100 + 30,
		50 + 20 * scale1,
		50
	};


	SDL_RenderCopy(renderer, playertexture1, NULL, &textInputerenderer1);
	SDL_RenderPresent(renderer);
}
void setup_introptc() {
	hardness = NOPATHCHOSEN;
	start = 0;
	scale1 = 0;
	scale2 = 0;
	fwinner = 0;
	SDL_DestroyTexture(playertexture1);
	intro_buttons();

	play1 = TTF_RenderText_Solid(font, "Player 1", blue, 500);
	p1 = SDL_CreateTextureFromSurface(renderer, play1);

	play2 = TTF_RenderText_Solid(font, "Computer", red, 500);
	p2 = SDL_CreateTextureFromSurface(renderer, play2);

	player1.x = WINDOW_WIDTH / 2 - 200;
	player1.y = WINDOW_LENGHT / 2 - 100;
	player1.wigth = 400;
	player1.length = 100;

	player2.x = WINDOW_WIDTH / 2 + 100;
	player2.y = WINDOW_LENGHT / 2 - 100;
	player2.wigth = 400;
	player2.length = 100;

	text_input_name(playerSurface1, playertexture1, &name1);
}
void introptc() {
	setup_introptc();
	while (test && !start && !out) {
		input_introptc();
		renderer_introptc();
	}
}
void setup_ptc() {
	Hl = 0;
	Vl = 0;
	redocount = 0;
	undocount = 0;
	sc1 = 0;
	sc2 = 0;
	turn = BLUEturn;
	score_setup();
	image_including();
	data_setup();
	starttime = time(NULL); 
	timer_set(); 
	srand(time(NULL)); 
}
void input_ptc() {
	SDL_Event play;
	SDL_PollEvent(&play);
	switch (play.type) {
	case SDL_QUIT:
		test = false;
		break;
	case SDL_MOUSEBUTTONDOWN:
		if (!computerturn)
			lines_inputckeck(play);
		buttons_inputckeck(play);
		break;
	}

}
int points(int x, int y) {
	call++;
	if (x >= hardness - 1 || x == -1 || y >= hardness - 1 || y == -1||game[x][y].sum ==4 || game[x][y].sum <2) {
		return 0;
	}
	if (game[x][y].sum == 3 && call == 1) {
		return 3 + points(x+1, y) + points(x-1, y) + points(x, y+1) + points(x, y-1);
	}
	if (game[x][y].sum == 2 && call == 1) {
			return -3;
	}
	return game[x][y].sum;
}
void  play(int* x ,int* y,int* type,int max , int xmax ,int ymax) {
	call++;
	if (game[xmax][ymax].sum == 3) {
		if (game[xmax][ymax].hn != 2) {
			*type = 1;
			*x = game[xmax][ymax].hl[0].x;
			*y = game[xmax][ymax].vl[0].y == game[xmax][ymax].hl[0].y ? game[xmax][ymax].hl[0].y + 170 : game[xmax][ymax].hl[0].y - 170;
		}
		else {
			*type = 0;
			*x = game[xmax][ymax].vl[0].x == game[xmax][ymax].hl[0].x ? game[xmax][ymax].vl[0].x + 185 : game[xmax][ymax].vl[0].x - 185;
			*y = game[xmax][ymax].vl[0].y;
		}
		return;
	}
	
	*type = rand() % 2;
	if (*type) {
		int random_index1 = rand() % (hardness-1);
		int random_index2 = rand() % (hardness);
		*x = WINDOW_WIDTH / 2 - width2 / 2 + 60 + 185 * random_index1; 
		*y = startYh = WINDOW_LENGHT / 2 - height2 / 2 + 150 + 170 * random_index2;
		if (found(H, *x, *y, Hl))
			play(x, y, type, max, xmax, ymax);
	}
	else {
		int random_index1 = rand() % (hardness);
		int random_index2 = rand() % (hardness - 1);
		*x = WINDOW_WIDTH / 2 - width2 / 2 + 60 + 185 * random_index1;
		*y = startYh = WINDOW_LENGHT / 2 - height2 / 2 + 150 + 170 * random_index2;
		if (found(V, *x, *y, Vl))
			play(x, y, type, max, xmax, ymax);
	}
	int ytest = findy(*x); 
	int xtest = findx(*y); 
	if (game[xtest][ytest].sum == 2 && call <16) {
		play(x, y, type, max, xmax, ymax);
	}
}
void computerchose(int* x, int* y, int* type) { 
	int max = INT_MIN ,xmax ,ymax,evalation;
	for (int i = 0; i < hardness-1; i++) {  
		for (int j = 0; j < hardness - 1; j++) {
			evalation = points(i,j);
			call = 0;
			if (evalation > max) {
				max =evalation; 
				xmax = i;
				ymax = j;
			}
		}
	}
	printf("max = %d (%d ,%d)\n",max,xmax,ymax); 
	play(x,y,type,max,xmax,ymax); 
	call = 0;
}
void updata_ptc() {
	if (Hl + Vl == (hardness) * (hardness - 1) * 2 && !fwinner) {
		if (sc1 > sc2) {
			winnersurface = TTF_RenderText_Solid(font, "you WINNER!", blue, 500);
			winner = SDL_CreateTextureFromSurface(renderer, winnersurface);

		}
		else if (sc2 > sc1) {
			winnersurface = TTF_RenderText_Solid(font, "you lost :(", red, 500);
			winner = SDL_CreateTextureFromSurface(renderer, winnersurface);
		}
		else {
			winnersurface = TTF_RenderText_Solid(font, "DROW!", black, 500);  
			winner = SDL_CreateTextureFromSurface(renderer, winnersurface);
		}
		fwinner = 1;
	}
	else {
		timer_set(); 
	}
	if (computerturn && !fwinner) {
		int xp, yp,type;   
		scoer = 0;
		computerchose(&xp,&yp,&type); 
		if (type) {
			H[Hl].x = xp;
			H[Hl].y = yp;
			H[Hl++].color = REDturn;
			int y = findy(xp);
			int x = findx(yp);
			game[x][y].sum++; 
			game[x][y].color = REDturn; 
			game[x][y].hl[game[x][y].hn].x = xp; 
			game[x][y].hl[game[x][y].hn].y = yp; 
			game[x][y].hl[game[x][y].hn++].color = turn;
			game[0][0].h = H;
			game[0][0].ht = Hl;
		
			numberp2++;
			if (x - 1 >= 0 && !edgey) {
				game[x - 1][y].sum++;
				game[x - 1][y].color = REDturn; 
				game[x - 1][y].hl[game[x - 1][y].hn].x = xp;
				game[x - 1][y].hl[game[x - 1][y].hn].y = yp; 
				game[x - 1][y].hl[game[x - 1][y].hn++].color = REDturn;
				check(x - 1, y); 
			}
			check(x, y);
		}else {
			V[Vl].x = xp;
			V[Vl].y = yp;
			V[Vl++].color = REDturn; 
			int y = findy(xp);
			int x = findx(yp);
			game[x][y].sum++; 
			game[x][y].color =REDturn; 
			game[x][y].vl[game[x][y].vn].x = xp; 
			game[x][y].vl[game[x][y].vn].y = yp;  
			game[x][y].vl[game[x][y].vn++].color = REDturn; 
			game[0][0].v = V; 
			game[0][0].vt = Vl;
			numberp2++; 
			if (y - 1 >= 0 && !edgex) {
				game[x][y - 1].sum++; 
				game[x][y - 1].color = REDturn; 
				game[x][y - 1].vl[game[x][y - 1].vn].x = xp; 
				game[x][y - 1].vl[game[x][y - 1].vn].y = yp; 
				game[x][y - 1].vl[game[x][y - 1].vn++].color = REDturn;   
				check(x, y - 1); 
			}
			check(x, y);
		}
		sprintf(linesrem, "%d", -(Hl + Vl) + (hardness) * (hardness - 1) * 2);
		numremaingsurface = TTF_RenderText_Solid(font, linesrem, top10color, 500);
		numremaingtexture = SDL_CreateTextureFromSurface(renderer, numremaingsurface);
		if (!scoer) {  
			computerturn = 0; 
		}
	}

}
void renderer_ptc() {
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
	}
	SDL_Rect timerboxes = { 
		WINDOW_WIDTH / 2 - 700,
		WINDOW_LENGHT / 2 - 200 ,
		200,
		200
	};
	SDL_RenderCopy(renderer, timertexture, NULL, &timerboxes); 
	SDL_FreeSurface(timersurface); 
	SDL_DestroyTexture(timertexture); 

	redoAndundoRender();
	SDL_RenderPresent(renderer);
}
void playertocomputermode() {
	introptc();
	setup_ptc();
	while (test && !out) {
		input_ptc();
		updata_ptc();
		renderer_ptc();
	}
}
