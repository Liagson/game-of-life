#include <stdio.h>
#include <ncurses.h> //Necesario para la interfaz
#include <unistd.h> //Necesario para el usleep (deprecated, por lo visto)
#include <stdlib.h> //Necesario para el malloc y el exit

#define VIDA 'X'
#define MUERTE 'O'

#define ROJO 1   //Si usara la libreria "curses.h" me ahorraría estas definiciones
#define NEGRO 0 // El "negro" es mas bien un verde ¿?
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

void actualizo_matriz(char** matriz_i, char** matriz_o, int tamano, int turno){
	/*No solo actualiza sino que además imprime la matriz actual*/
	int vecinos;
	int i, j;

	move(0,0); //Actualizo el cursor a la posicion sup-izq
	printw("%s\n", matriz_i[0]);
	for(i = 1; i < tamano - 1; i++){
		printw("%c", MUERTE);				
		for(j = 1; j < tamano - 1; j++){
			vecinos = contador_vecinos(i, j, matriz_i);
			if (matriz_i[i][j] == VIDA){						
				if (vecinos > 3 || vecinos < 2) matriz_o[i][j] = MUERTE;
				else matriz_o[i][j] = VIDA;

				attron(COLOR_PAIR(2));
				printw("%c",matriz_i[i][j]);
				attroff(COLOR_PAIR(2));
			}
			else{
				if (vecinos == 3) matriz_o[i][j] = VIDA;
				else matriz_o[i][j] = MUERTE;

				printw("%c",matriz_i[i][j]);
			}					
		}
		printw("%c\n", MUERTE);
	}
	printw("%s\n", matriz_i[tamano - 1]);	
	printw("turno: %d\n", turno);
	usleep(500000);
	refresh();
}

main(){
	int tamano = 20;
	int turno = 0;
	int turno_limite = 40;		
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
	
	matriz1[1][3] = VIDA; // Glider
	matriz1[2][3] = VIDA;
	matriz1[3][3] = VIDA;
	matriz1[1][1] = VIDA;
	matriz1[3][2] = VIDA;

	initscr();
	start_color();
	init_pair(1, BLANCO, NEGRO); //Color celda MUERTE y estandar
	init_pair(2, ROJO, NEGRO); //Color celda VIDA	
	while(turno < turno_limite){
		if(turno % 2) actualizo_matriz(matriz2, matriz1, tamano, turno);
		else actualizo_matriz(matriz1, matriz2, tamano, turno);
		turno++;	
	}	
	endwin();
}