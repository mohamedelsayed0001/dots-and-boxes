#include"playertocomputer.h" 
FILE* updataing;
void including_data() {
	for (int i = 0; i < Hl; i++) {
		fscanf(updataing, "%d %d %d \n", &H[i].x, &H[i].y, &H[i].color);
	}
	for (int i = 0; i < Vl; i++) {
		fscanf(updataing, "%d %d %d \n", &V[i].x, &V[i].y, &V[i].color);
	}
	for (int i = 0; i < hardness - 1; i++) {
		for (int j = 0; j < hardness - 1; j++) {
			fscanf(updataing, "%d %d %d %d ", &game[i][j].color
				, &game[i][j].sum
				, &game[i][j].hn
				, &game[i][j].vn);
			for (int k = 0; k < game[i][j].hn; k++) {
				fscanf(updataing, "%d %d %d ", &game[i][j].hl[k].x, &game[i][j].hl[k].y, &game[i][j].hl[k].color);
			}
			for (int k = 0; k < game[i][j].vn; k++) {
				fscanf(updataing, "%d %d %d ", &game[i][j].vl[k].x, &game[i][j].vl[k].y, &game[i][j].vl[k].color);
			}
		}
	}
	fclose(updataing);
	game[0][0].h = H;
	game[0][0].ht = Hl;
	game[0][0].v = V;
	game[0][0].s1 = sc1;
	game[0][0].s2 = sc2;
	game[0][0].ture = turn;
	game[0][0].vt = Vl;
	for (int i = 0; i < (hardness - 1); i++) {
		for (int j = 0; j < hardness - 1; j++) {
			undostack[undocount][i][j] = game[i][j];
		}
	}
}
void setup_load() {
	if (name1 == NULL) {
		name1 = calloc(MAX_NAME_LENGTH, sizeof(char));
	}
	if (name2 == NULL) {
		name2 = calloc(MAX_NAME_LENGTH, sizeof(char));
	}
	int indecator;
	updataing = fopen("games.txt", "r");
	fscanf(updataing, "%d %s %s \n %d %d %d %d %d %d %d ",&indecator,name1,name2,&path, &hardness, &turn, &sc1, &sc2, &Hl, &Vl);
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
	fwinner = 0;
	redocount = 0;
	undocount = 0;
	image_including();
	data_setup();
	including_data();
	score_setup();
	starttime = time(NULL); 
}


void Loadgamemode() {
	setup_load();
	while (test && !out) {
		input_propmode();
		update_ptpmode();
		renderer_ptpmode();
	}
	saving();
}