#include <locale.h> //Necesario para trabajar con los mismos carácteres que la consola
#include <ncursesw/ncurses.h> //Necesario para la interfaz
#include <stdio.h> 
#include <stdlib.h> //Necesario para el malloc y el exit
#include <unistd.h> //Necesario para el usleep (deprecated, por lo visto)

#include "game.h"

char matriz1[TAMANO_Y][TAMANO_X];
char matriz2[TAMANO_Y][TAMANO_X];

int startx; //Posicion desde donde se imprime la matriz. La posición se calcula una vez se ejecuta 'initscr()'
int starty; 

int turno = 0;

void pantalla_inicio(){
	int tecla = 0;
	int x = 0;
	int y = 0;
	while(tecla != K_SPACE)
		switch(tecla){
				case K_UP: //UP
					if (x > 0) x--;
					break;
				case K_DOWN: //DOWN
					if (x < TAMANO_X - 1) x++;
					break;
				case K_RIGHT: //RIGHT
					if(y < TAMANO_Y - 1) y++;
					break;
				case K_LEFT: //LEFT
					if(y > 0) y--;
				default:
					break;

			}
}

int contador_vecinos(int x, int y, char matriz[TAMANO_Y][TAMANO_X]){
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

void print_matriz(char matriz[TAMANO_Y][TAMANO_X]){
	int i, j;	
	
	for(i = 1; i < TAMANO_Y - 1; i++){
		mvprintw(starty + i, startx, "%c", ' ');	
		for(j = 1; j < TAMANO_X - 1; j++)
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

void actualizo_matriz(char matriz_i[TAMANO_Y][TAMANO_X], char matriz_o[TAMANO_Y][TAMANO_X]){
	int vecinos;
	int i, j;

	for(i = 1; i < TAMANO_Y - 1; i++){
		for(j = 1; j < TAMANO_X - 1; j++){
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
	print_matriz(matriz_i);
}

main(){

  	setlocale(LC_ALL,""); //Ajuste de caracteres de terminal
	int turno_limite = 100;	
	int i, j;

	if (has_colors()){
		fprintf(stderr, "Error: la terminal no funciona con colores\n");
		exit(1);
	}
	
	for(i = 0; i < TAMANO_Y; i++)
		for(j = 0; j < TAMANO_X; j++){
			matriz1[i][j] = MUERTE;
			matriz2[i][j] = MUERTE;
		}
	
	matriz1[1][3] = VIDA; // Glider
	matriz1[2][3] = VIDA;
	matriz1[3][3] = VIDA;
	matriz1[1][1] = VIDA;
	matriz1[3][2] = VIDA;

	initscr();
	starty = (LINES - TAMANO_Y) / 2;
	startx = (COLS - TAMANO_X) / 2;

	start_color();
	init_pair(1, BLANCO, NEGRO); //Color celda MUERTE y estandar
	init_pair(2, ROJO, NEGRO); //Color celda VIDA	
	
	noecho(); //Evita que aparezca la tecla pulsada en pantalla

	while(turno < turno_limite){
		
		if(turno % 2) actualizo_matriz(matriz2, matriz1);
		else actualizo_matriz(matriz1, matriz2);
		turno++;	
	}

	endwin();
	exit(0);
}