#[Juego de la vida](http://en.wikipedia.org/wiki/Conway%27s_Game_of_Life) (ALFA) ![Glider](http://upload.wikimedia.org/wikipedia/commons/f/f2/Game_of_life_animated_glider.gif)
##Compilación
1. Instalar la librería **ncurses.h**
	* `sudo apt-get install ncurses-dev`
2. Instalar la librería **ncursesw.h** (*encargada de los carácteres especiales*)
 	* `sudo apt-get install libncursesw5-dev`
3. Instalar **cmake**
	* `sudo apt-get install cmake`
4. Generar Makefile
	* Asegúrate que tienes el build-essential instalado
		* `sudo apt-get install build-essential`
	* Ejecuta `cmake .`
5. Compilar
	* Ejecuta `make`


##Descripción
Versión alfa del juego de la vida de [Conway](http://en.wikipedia.org/wiki/John_Horton_Conway).
En la versión actual hay que añadir en el código de game.c la configuración inicial (ahora mismo tiene un glider).
* [Video de numberphile](https://www.youtube.com/watch?v=E8kUJL04ELA) sobre el juego.
