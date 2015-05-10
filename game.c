#include <locale.h> //Necesario para trabajar con los mismos carácteres que la consola
#include <ncursesw/ncurses.h> //Necesario para la interfaz
#include <stdio.h>
#include <stdlib.h> //Necesario para el malloc y el exit
#include <unistd.h> //Necesario para el usleep (deprecated, por lo visto)

#include "game.h"

char matriz1[TAMANO][TAMANO];
char matriz2[TAMANO][TAMANO];

int contador_vecinos(int x, int y, char matriz[TAMANO][TAMANO]){
	/* Devuelve el número de vecinos vivos */
	int contador = 0;
	if (matriz[x - 1][y - 1] == VIDA) contador++;
	if (matriz[x][y - 1] == VIDA) contador++;
	if (matriz[x + 1][y - 1] == VIDA) contador++;

	if (matriz[x - 1][y + 1] == VIDA) contador++;
	if (matriz[x][y + 1] == VIDA) contador++;
	if (matriz[x + 1][y + 1] == VIDA) contador++;

	if (matriz[x - 1][y] == VIDA) contador++;
	if (matriz[x + 1][y] == VIDA) contador++;

	return contador;
}

void print_matriz(int turno, char matriz[TAMANO][TAMANO], int starty, int startx){
	int i, j;
	for(i = 1; i < TAMANO - 1; i++){
		mvprintw(starty + i, startx, "%c", ' ');	
		for(j = 1; j < TAMANO - 1; j++)
			if (matriz[i][j]) {
				attron(COLOR_PAIR(2));
				printw("%s", CHAR_VIDA);
				attroff(COLOR_PAIR(2));
			}else printw("%s", CHAR_MUERTE);
	}
	mvprintw(starty + i, startx +1,"turno: %d\n", turno);
	usleep(FRAME_RATE);
	refresh();
}

void actualizo_matriz(char matriz_i[TAMANO][TAMANO], char matriz_o[TAMANO][TAMANO],  int turno, int starty, int startx){
	/*No solo actualiza sino que además imprime la matriz actual*/
	int vecinos;
	int i, j;

	for(i = 1; i < TAMANO - 1; i++){
		mvprintw(starty + i, startx, "%s", CHAR_MUERTE);				
		for(j = 1; j < TAMANO - 1; j++){
			vecinos = contador_vecinos(i, j, matriz_i);
			if (matriz_i[i][j]){		// posicion = VIDA
				if (vecinos > 3 || vecinos < 2) matriz_o[i][j] = MUERTE;
				else matriz_o[i][j] = VIDA;
			}
			else{
				if (vecinos == 3) matriz_o[i][j] = VIDA;
				else matriz_o[i][j] = MUERTE;
			}					
		}
	}
	print_matriz(turno, matriz_i, starty, startx);
}

main(){

  	setlocale(LC_ALL,"");
	int turno = 0;
	int turno_limite = 100;	
	int starty, startx;	
	int i, j;
	if (has_colors()){
		printf("Error: la terminal no funciona con colores");
		exit(-1);
	}
/*
	matriz1 = malloc(TAMANO * sizeof(char*));
	for(i = 0; i < TAMANO; i++) matriz1[i] = malloc(TAMANO);
	matriz2 = malloc(TAMANO * sizeof(char*));
	for(i = 0; i < TAMANO; i++) matriz2[i] = malloc(TAMANO);
		*/
	/*
	for(i = 0; i < TAMANO; i++)
		for(j = 0; j < TAMANO; j++){
			matriz1[i][j] = MUERTE;
			matriz2[i][j] = MUERTE;
		}
	*/
	matriz1[1][3] = VIDA; // Glider
	matriz1[2][3] = VIDA;
	matriz1[3][3] = VIDA;
	matriz1[1][1] = VIDA;
	matriz1[3][2] = VIDA;

	initscr();
	starty = (LINES - TAMANO) / 2;
	startx = (COLS - TAMANO) / 2;
	start_color();
	init_pair(1, BLANCO, NEGRO); //Color celda MUERTE y estandar
	init_pair(2, ROJO, NEGRO); //Color celda VIDA	
	while(turno < turno_limite){
		
		if(turno % 2) actualizo_matriz(matriz2, matriz1, turno, starty, startx);
		else actualizo_matriz(matriz1, matriz2, turno, starty, startx);
		turno++;	
	}	
	endwin();
}