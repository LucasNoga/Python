#include "graphics.h"
#include "my_string.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <X11/xpm.h>


/*- Indice du pix de la piece dans le tableau des sprites -*/
int sprite_num[13] = { 0,1,2,3,4,5,6,7,8,9,10,11,12 } ;


/* Demande la saisie d'une chaine */
char *
GInputString (FILE * entree)
{
  char c, t[100], *p;
  int i = 0;

  do
    {
      c = fgetc (entree);
      t[i++] = (c == '\n') ? 0 : c;
    }
  while ((c != '\n') && !(feof (entree)));
  p = (char *) calloc (sizeof (char), strlen (t) + 1);
  strcpy (p, t);
  return (p);
}

char *
GInputStringForTerm (FILE * entree, int courant)
{
  printf ("Terminal %d:", courant);
  return (GInputString (entree));
}
/*- Ouvre un ecran (necessite xhost+ sur un autre ecran) -*/
Display *
GOpenDisplay (char *terminal)
{
  Display *canal;
#ifdef DEBUG
  if (strcmp (terminal, "") == 0)
    fprintf (stderr, "Demande de canal a localhost:");
  else
    fprintf (stderr, "Demande de canal a %s:", terminal);
#endif
  canal = XOpenDisplay (terminal);
  if (!canal)
    {
      fprintf (stderr, "Couldn't open display %s\n",terminal);
      exit (1);
    }
#ifdef DEBUG
  fprintf (stderr, " Acceptee.\n");
#endif
  return canal;
}

/* Vide un canal d'affichage de tout evenement */
void 
GFlush (int i)
{
  XEvent evenem;
  while (XEventsQueued (canal_aff[i], QueuedAfterReading))
    XNextEvent (canal_aff[i], &evenem);
}

/* Dessine la boite de base avec un sprite sinon efface */
void 
GDrawBox (int i, unsigned int x, unsigned int y, int mode, Pixart sprite, int OFFSET_X, int OFFSET_Y)
{
  if (mode == ERASE_MODE) {

      /*- Mode effacement -*/
      XClearArea(canal_aff[i],fenetre[i],
		 OFFSET_X + TAILLE_CARRE * x, OFFSET_Y + TAILLE_CARRE * y,
		 TAILLE_CARRE, TAILLE_CARRE,0);

/*-
      XSetClipOrigin(canal_aff[i],gc[i],OFFSET_X + TAILLE_CARRE * x, OFFSET_Y + TAILLE_CARRE * y);
      XSetClipMask(canal_aff[i],gc[i],sprite_img[i][BL_BCK].mask);
      XCopyArea (canal_aff[i], sprite_img[i][BL_BCK].data, fenetre[i], gc[i],
		 0, 0, TAILLE_CARRE, TAILLE_CARRE,
		 OFFSET_X + TAILLE_CARRE * x, OFFSET_Y + TAILLE_CARRE * y);
      XSetClipMask(canal_aff[i],gc[i],None);
-*/
  }  else  {

      /*- Clipping -*/
      XSetClipOrigin(canal_aff[i],gc[i],OFFSET_X + TAILLE_CARRE * x, OFFSET_Y + TAILLE_CARRE * y);
      XSetClipMask(canal_aff[i],gc[i],sprite.mask);

      /*- Mode dessin -*/
      XCopyArea (canal_aff[i], sprite.data, fenetre[i], gc[i],
		 0, 0, TAILLE_CARRE, TAILLE_CARRE,
		 OFFSET_X + TAILLE_CARRE * x, OFFSET_Y + TAILLE_CARRE * y);

      /*- Free -*/
      XSetClipMask(canal_aff[i],gc[i],None);
  }
}

void 
GAffBackground (int i)
{
    XClearWindow(canal_aff[i],fenetre[i]);
    XFlush (canal_aff[i]);
}


/* Dessine une piece */
void 
GDrawPiece (int i, unsigned int x, unsigned int y, int mode, twintris moi[NOMBRE], int OFFSET_X, int OFFSET_Y)
{
    int j;

#ifdef DEBUG
    printf("GDrawBox\n");
    printf("blocs:%d\n",moi[i].nb_blocks);
#endif
    for ( j=0 ; j<moi[i].nb_blocks ; j++)
    /*- Dessin effectif -*/
	GDrawBox (i,
		  x + (moi[i].positions)[j][XPIECE], y + (moi[i].positions)[j][YPIECE],
		  mode,
		  sprite_img[i][sprite_num[moi[i].couleur+2]], OFFSET_X, OFFSET_Y);
    /*-
    GDrawBox (i,
	      x + (moi[i].positions)[1][XPIECE], y + (moi[i].positions)[1][YPIECE],
	      mode,
	      sprite_img[i][moi[i].couleur-1], OFFSET_X, OFFSET_Y);

    GDrawBox (i,
	      x + (moi[i].positions)[2][XPIECE], y + (moi[i].positions)[2][YPIECE],
	      mode,
	      sprite_img[i][moi[i].couleur-1], OFFSET_X, OFFSET_Y);

    GDrawBox (i,
	      x + (moi[i].positions)[3][XPIECE], y + (moi[i].positions)[3][YPIECE],
	      mode,
	      sprite_img[i][moi[i].couleur-1], OFFSET_X, OFFSET_Y);
-*/
    XFlush(canal_aff[i]);
#ifdef DEBUG
    printf("End GDrawBox\n");
#endif
}

/* Afficher une valeur numerique */
void 
GAfficheChiffre (int fen, int offsetx, int offsety, int moi)
{
  int ecartx, i;
  int reste;
  char chiffres[10] =
  {"0123456789"};
  char c;
  i = moi;
  ecartx = 24;
  if (i <= 0)
    XDrawString (canal_aff[fen], fenetre[fen], gc[fen],
		 offsetx, offsety,
		 "    0",
		 5);
  while (i > 0)
    {
      reste = i % 10;
      i = i / 10;		/* Choix du reste */
      c = chiffres[reste];
      XDrawString (canal_aff[fen], fenetre[fen], gc[fen],
		   offsetx + ecartx, offsety,
		   &chiffres[reste],
		   1);		/* J'affiche le chiffre */
      ecartx = ecartx - 6;
    }				/* Je decale */
}

void 
GAfficherScore (int i)
{
  XClearArea (canal_aff[i], fenetre[i],
	     SCOREX, SCOREY - 10,
	     50, 10, 0);
  XClearArea (canal_aff[i], fenetre[i],
	     LIGNEX, LIGNEY - 10,
	     50, 10, 0);

  GAfficheChiffre (i, SCOREX, SCOREY, score[i]);
  GAfficheChiffre (i, LIGNEX, LIGNEY, lignes[i]);

}

void GAfficherTemps ( int i ) {

  XClearArea (canal_aff[i], fenetre[i],
	     TIMEX, TIMEY - 10,
	     50, 10, 0);
  GAfficheChiffre ( i , TIMEX , TIMEY , time_temps_restant ( ) ) ;
}


void 
GAfficheGameOver (int i)
{

  GAfficheMessage (i, say (SAY_PERDU) /*-"You lose!"-*/ );

}

void 
GAfficheVictoire (int i)
{

  GAfficheMessage (i, say (SAY_GAGNE) /*-"You win!"-*/ );

}

void 
GAfficheVainqueur (int i, int winner)
{
  char *temp_str;

  temp_str = concat_chaine (say (SAY_VAINQUEUR) /*-"The winner is "-*/ , names[winner]);

  GAfficheMessage (i, temp_str);

  free (temp_str);
}

void 
GClearMessageZone (int i)
{
/*- Ceci permet d'effacer la zone de messages -*/
  XClearArea (canal_aff[i], fenetre[i],
	     MESSAGEX, MESSAGEY - 10,
	     150, 12,0);
}

void 
GAfficheTableau (int i)
{
  int j, k;

  if (etat[i] == ENCORE_EN_COURSE)
    for (j = 0; j < TAILLE_TAB_Y; j++)

      for (k = 0; k < TAILLE_TAB_X; k++)
	{

	  GDrawBox (i, k, j, ERASE_MODE, sprite_img[i][sprite_num[tableau[i][k][j] + 2]], OFFSET_X, OFFSET_Y);

	  if (tableau[i][k][j])

	    GDrawBox (i, k, j, DRAW_MODE, sprite_img[i][sprite_num[tableau[i][k][j] + 2]], OFFSET_X, OFFSET_Y);
	}
  else
    GAfficheGameOver (i);

  XFlush (canal_aff[i]);
}

void 
GAfficheFin (int i)
{
  GAfficheTout(i);
  if ( MAXIMUM != 1 ) spy_win (i);
  XFlush (canal_aff[i]);
}

void
GAfficheTout (int i)
{
    GAffBackground(i);
    GAfficherScore(i);
    GAfficherTemps(i);
    XFlush(canal_aff[i]);
}

/* Cette procedure sera destinee a l'affichage des messages */
void 
GAfficheMessage (int i, char *message)
{

  GClearMessageZone (i);

  XDrawString (canal_aff[i], fenetre[i], gc[i],
	       MESSAGEX, MESSAGEY,
	       message, strlen (message));
}
