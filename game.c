#include <locale.h> //Necesario para trabajar con los mismos carácteres que la consola
#include <ncursesw/ncurses.h> //Necesario para la interfaz
#include <stdio.h> 
#include <stdlib.h> //Necesario para el exit
#include <unistd.h> //Necesario para el usleep (deprecated, por lo visto)

#include "game.h"

void print_matriz();
void pantalla_inicio();
void actualizo_matriz();

char matriz1[TAMANO_Y][TAMANO_X];
char matriz2[TAMANO_Y][TAMANO_X];

int startx; //Posicion desde donde se imprime la matriz. La posición se calcula una vez se ejecuta 'initscr()'
int starty; 

int turno = 0;
int salida = 0;

void pantalla_inicio(){
	int tecla = 0;
	int tecla_anterior;

	int limite_izq = startx + 1; // Los numeros sumados vienen del marco de la matriz (que nunca se visualiza)
	int limite_sup = starty + 1;
	int limite_inf = starty +  TAMANO_Y - 2; 
	int limite_der = startx + TAMANO_X - 2;

	int x = limite_izq;
	int y = limite_sup;
	int x_matriz = 1;
	int y_matriz = 1;

	while(tecla_anterior != K_SPACE){

		/* Cabecera - Pantalla inicio */
		mvprintw(limite_sup - 3, startx - 1, "Usa las flechas del numberpad para navegar\n");
		mvprintw(limite_sup - 2, startx - 8, "El '5' del numberpad sirve para crear/destruir celulas\n");
		mvprintw(limite_sup - 1, startx, "Para continuar pulsa la barra de espacio");

		print_matriz(matriz1);
		move (y, x); 

		tecla_anterior = 0;		
		while((tecla = getch()) != ERR) tecla_anterior = tecla;  //Elimina el buffer de stdin
		
		switch(tecla_anterior){
				case K_UP: 
					if (y > limite_sup){
						y--;
						y_matriz--;
					}
					break;
				case K_DOWN: 
					if (y < limite_inf){
						y++;
						y_matriz++;
					}
					break;
				case K_RIGHT: 
					if(x < limite_der) {
						x++;
						x_matriz++;
					}
					break;
				case K_LEFT: 
					if(x > limite_izq) {
						x--;
						x_matriz--;						
					}
					break;					
				case K_INTRO:
					matriz1[y_matriz][x_matriz] = (matriz1[y_matriz][x_matriz]) ? MUERTE : VIDA;
					break;
				default:
					break;
		}		
		usleep(10000); //Evita que haya problemas al darle muy rapido al teclado
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
	/* El refresh() no se hace dentro! */
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

	/* Cabecera - Partida */
	move(starty - 2, 0);
	clrtoeol();

	move(starty - 1, 0);
	clrtoeol();

	mvprintw(starty - 1, startx + 2, "Para salir pulsa la barra de espacio\n\n");
	move(starty - 1, startx + 1); //Dejo el cursor en un sitio discreto
	refresh();
}

main(int argc, char* argv[]){

  	setlocale(LC_ALL,""); //Ajuste de caracteres de terminal
	int turno_limite = (argc > 1) ? atoi(argv[1]) : -1; //Si no hay input el bucle es inifinito	
	int i, j;

	if (has_colors()){
		fprintf(stderr, "Error: la terminal no funciona con colores\n");
		exit(1);
	}
	
	/* Inicialización de las matrices */
	for(i = 0; i < TAMANO_Y; i++)
		for(j = 0; j < TAMANO_X; j++){
			matriz1[i][j] = MUERTE;
			matriz2[i][j] = MUERTE;
		}

	
	/* Inicio del juego */	
	WINDOW *w = initscr();
	starty = (LINES - TAMANO_Y) / 2;
	startx = (COLS - TAMANO_X) / 2;

	start_color();
	init_pair(1, BLANCO, NEGRO); //Color celda MUERTE y estandar
	init_pair(2, ROJO, NEGRO); //Color celda VIDA	
	
	noecho(); //Evita que aparezca la tecla pulsada en pantalla

	cbreak(); // Consigue que getch() no pare el programa
	nodelay(w, TRUE);

	pantalla_inicio();


	while(((turno_limite < 0)||(turno < turno_limite)) && (salida != K_SPACE)){
		salida = getch();
		turno++;	
		if(turno % 2) actualizo_matriz(matriz1, matriz2);
		else actualizo_matriz(matriz2, matriz1);
		
	}
	salida = 0;
	while(salida != K_SPACE) salida = getch();
	endwin();
	exit(0);
}
