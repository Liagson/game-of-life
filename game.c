#include <stdio.h>
#include <ncurses.h> //Necesario para la interfaz
#include <unistd.h> //Necesario para el usleep (deprecated, por lo visto)
#include <stdlib.h> //Necesario para el malloc y el exit

#define VIDA 'X'
#define MUERTE 'O'

#define ROJO 1   //Si usara la libreria "curses.h" me ahorraría estas definiciones
#define NEGRO 0
#define BLANCO 7

char** matriz1;
char** matriz2;

int contador_vecinos(int x, int y, char** matriz){
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

main(){
	int tamano = 20;
	int turno = 0;
	int turno_limite = 20;
	int vecinos;
	int i, j;

	if (has_colors()){
		printf("Error: la terminal no funciona con colores");
		exit(-1);
	}


	matriz1 = malloc(tamano * sizeof(char*));
	for(i = 0; i < tamano; i++) matriz1[i] = malloc(tamano);
	matriz2 = malloc(tamano * sizeof(char*));
	for(i = 0; i < tamano; i++) matriz2[i] = malloc(tamano);

	for(i = 0; i < tamano; i++)
		for(j = 0; j < tamano; j++){
			matriz1[i][j] = MUERTE;
			matriz2[i][j] = MUERTE;
		}
	
	matriz1[1][3] = VIDA;
	matriz1[2][3] = VIDA;
	matriz1[3][3] = VIDA;
	matriz1[1][1] = VIDA;
	matriz1[3][2] = VIDA;

	initscr();
	start_color();
	init_pair(1, BLANCO, NEGRO); //Color celda MUERTE y estandar
	init_pair(2, ROJO, NEGRO); //Color celda VIDA	
	while(turno < turno_limite){
		move(0,0);
		if(turno % 2){;
			printw("%s\n", matriz2[0]);
			for(i = 1; i < tamano - 1; i++){
				printw("%c", MUERTE);				
				for(j = 1; j < tamano - 1; j++){
					vecinos = contador_vecinos(i, j, matriz2);
					if (matriz2[i][j] == VIDA){						
						if (vecinos > 3 || vecinos < 2) matriz1[i][j] = MUERTE;
						else matriz1[i][j] = VIDA;
						attron(COLOR_PAIR(2));
						printw("%c",matriz2[i][j]);
						attroff(COLOR_PAIR(2));
					}
					else{
						if (vecinos == 3) matriz1[i][j] = VIDA;
						else matriz1[i][j] = MUERTE;
						printw("%c",matriz2[i][j]);
					}					
				}
				printw("%c\n", MUERTE);
			}
		printw("%s\n", matriz2[tamano - 1]);	
		printw("turno: %d\n", turno);
		usleep(500000);
		refresh();

		}else{
			printw("%s\n", matriz1[0]);
			for(i = 1; i < tamano - 1; i++){
				printw("%c", MUERTE);				
				for(j = 1; j < tamano - 1; j++){
					vecinos = contador_vecinos(i, j, matriz1);
					if (matriz1[i][j] == VIDA){						
						if (vecinos > 3 || vecinos < 2) matriz2[i][j] = MUERTE;
						else matriz2[i][j] = VIDA;
						attron(COLOR_PAIR(2));
						printw("%c",matriz1[i][j]);
						attroff(COLOR_PAIR(2));
					}
					else{
						if (vecinos == 3) matriz2[i][j] = VIDA;
						else matriz2[i][j] = MUERTE;
						printw("%c",matriz1[i][j]);
					}					
				}
				printw("%c\n", MUERTE);
			}
			printw("%s\n", matriz1[tamano - 1]);	
			printw("turno: %d\n", turno);
			usleep(500000);
			refresh();
		}
	turno++;	
	}	
	endwin();
}