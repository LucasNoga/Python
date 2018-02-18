#ifndef __GRAPHICS__
#define __GRAPHICS__




#include <stdio.h>
#include <stdlib.h>

#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <X11/xpm.h>
#include <X11/keysym.h>

#include "constantes.h"
#include "gestion.h"
#include "language.h"
#include "spy.h"
#include "my_time.h"


#define ERASE_MODE 0
#define DRAW_MODE  1

/*- La structure de sprite pour mieux gerer la transparence -*/
struct SPixart {
    Pixmap data;
    Pixmap mask;
};
typedef struct SPixart Pixart;


/* Tableaux des fenetres et de leurs attributs en global c'est mieux */
char *machines[NOMBRE];
char *names[NOMBRE];
Display *canal_aff[NOMBRE];
int ecran[NOMBRE];
unsigned long noir[NOMBRE], blanc[NOMBRE];
XSizeHints infos_fen[NOMBRE];
Window fenetre[NOMBRE], racine[NOMBRE];
GC gc[NOMBRE];

XWMHints manager[NOMBRE];
XSetWindowAttributes xswa[NOMBRE];

XEvent evenem[NOMBRE];

/*- Tableau des sprites -*/
Pixart sprite_img[NOMBRE][PIXMAX];



char *GInputString (FILE * entree);
char *GInputStringForTerm (FILE * entree, int courant);
Display *GOpenDisplay (char *terminal);
void GFlush (int i);

void GDrawPiece (int i, unsigned int x, unsigned int y, int mode, twintris moi[NOMBRE], int OFFSET_X, int OFFSET_Y);


void GAfficheChiffre (int fen, int x, int y, int moi);
void GAffBackground (int i);
void GAfficherScore (int i);
void GAfficherTemps (int i);
void GAfficheGameOver (int i);
void GAfficheVictoire (int i);
void GAfficheVainqueur (int i, int winner);
void GAfficheTableau (int i);
void GAfficheFin (int i);
void GAfficheTout(int i);
void GAfficheMessage (int i, char *message);
void GClearMessageZone (int i);

#endif
