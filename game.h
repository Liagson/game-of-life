/* Matriz */
#define VIDA 1
#define MUERTE 0

static const char CHAR_VIDA[] = "▪";
static const char CHAR_MUERTE[] = "▫";

#define TAMANO_X 40
#define TAMANO_Y 20

/* Teclado (numberpad) */
#define K_UP 56 // Una buena mejora sería conseguir hacer que se lean las flechas del teclado sin que todo explote. 
#define K_DOWN 50
#define K_RIGHT 54
#define K_LEFT 52
#define K_SPACE 32
#define K_INTRO 53

/* Curses */
#define ROJO COLOR_RED   
#define NEGRO COLOR_BLACK // El "negro" es mas bien un verde ¿?
#define BLANCO COLOR_WHITE

#define FRAME_RATE 100000 // 10fps