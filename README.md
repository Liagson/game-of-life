#Juego de la vida (ALFA)
##Compilación
1. Instalar la librería **ncurses.h**
	* `sudo apt-get install ncurses-dev`
2. Instalar la librería **ncursesw.h** (*encargada de los carácteres especiales*)
 	* `sudo apt-get install libncurses-dev`
3. `gcc game.c game.h -lncursesw -o game`

##Descripción
Versión alfa del juego de la vida de Conway.
En la versión actual hay que añadir en el codigo la configuración inicial (ahora mismo tiene un glider).
