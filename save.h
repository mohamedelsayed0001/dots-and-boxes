#include "intro.h"

void save_game() {
	remove("games.txt");
	FILE* saveing = fopen("games.txt", "w");
	printf("%s\n", name1);
	fprintf(saveing, "1 %s %s \n%d %d %d %d %d %d %d \n", name1, name2, path, hardness, turn, sc1, sc2, Hl, Vl);
	for (int i = 0; i < Hl; i++) {
		fprintf(saveing, "%d %d %d \n", H[i].x, H[i].y, H[i].color);
	}
	for (int i = 0; i < Vl; i++) {
		fprintf(saveing, "%d %d %d \n", V[i].x, V[i].y, V[i].color);
	}
	for (int i = 0; i < hardness - 1; i++) {
		for (int j = 0; j < hardness - 1; j++) {
			fprintf(saveing, "%d %d %d %d ", game[i][j].color
				, game[i][j].sum
				, game[i][j].hn
				, game[i][j].vn);
			for (int k = 0; k < game[i][j].hn; k++) {
				fprintf(saveing, "%d %d %d ", game[i][j].hl[k].x, game[i][j].hl[k].y, game[i][j].hl[k].color);
			}
			for (int k = 0; k < game[i][j].vn; k++) {
				fprintf(saveing, "%d %d %d ", game[i][j].vl[k].x, game[i][j].vl[k].y, game[i][j].vl[k].color);
			}
			fprintf(saveing, "\n");
		}
	}
	fclose(saveing);
}
int numofdigits(int n) {
	int num = 0;
	while (n) {
		num++;
		n /= 10;
	}
	return num;
}
int searchplayer(FILE** file, char* name, int theadd) {
	*file = fopen("ranks.txt", "r+");
	char temp[30];
	int size, carry;
	fscanf(*file, "%d", &size);
	for (int i = 0; i < size; i++) {
		fscanf(*file, "%s  %d", temp, &carry);
		if (!strcmp(name, temp)) {
			int offset = ftell(*file) - numofdigits(carry + theadd);
			fseek(*file, offset, SEEK_SET);
			fprintf(*file, "%d", carry + theadd);
			fclose(*file);
			return 0;
		}
	}
	fclose(*file);
	return 1;
} 
void add_new(FILE** file, char* name, int s) {
	*file = fopen("ranks.txt", "r+");
	int first_number;
	fscanf(*file, "%d", &first_number);
	fseek(*file, 0, SEEK_SET);
	fprintf(*file, "%d", first_number + 1);

	fclose(*file);
	*file = fopen("ranks.txt", "a");
	fprintf(*file, "%s  %d  \n", name, s);
	fclose(*file);
} 
void save_winners() {
	FILE* add_scores;
	if (searchplayer(&add_scores, name1, sc1)) {
		add_new(&add_scores, name1, sc1);
	}
	if (searchplayer(&add_scores, name2, sc2)) {
		add_new(&add_scores, name2, sc2);
	}
}  
void saving() { 
	
		if (!fwinner) {
			save_game();
		}
		else {
			remove("games.txt"); 
			FILE*updataing = fopen("games.txt", "w"); 
			fprintf(updataing, "0"); 
			fclose(updataing);  
			save_winners(); 
		}
}