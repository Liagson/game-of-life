#include <stdio.h>
#include <ncurses.h>

#define VIDA 'X'
#define MUERTE 'O'

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
	int tamaño = 20;
	int turno = 0;
	int i, j;

	matriz1 = malloc(tamaño * sizeof(char*));
	for(i = 0; i < tamaño; i++) matriz1[i] = malloc(tamaño);
	matriz2 = malloc(tamaño * sizeof(char*));
	for(i = 0; i < tamaño; i++) matriz2[i] = malloc(tamaño);

	for(i = 0; i < tamaño; i++)
		for(j = 0; j < tamaño; j++){
			matriz1[i][j] = MUERTE;
			matriz2[i][j] = MUERTE;
		}

}