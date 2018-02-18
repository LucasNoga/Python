/*- Module espion -*/
#include "spy.h"

Pixart petit_carre_noir[NOMBRE],petit_carre_blanc[NOMBRE];

Pixart dead[NOMBRE],win[NOMBRE];


void 
spy_creation_pixmaps (int i)
{
  XpmAttributes attributs;
  int status;

#ifdef DEBUG
  printf ("Loading pixmaps for player %d\n", i);
#endif

/*- Mise en place des donnees -*/
  attributs.closeness = 65535;
  attributs.colormap = DefaultColormap (canal_aff[i], DefaultScreen (canal_aff[i]));
  attributs.valuemask = XpmColormap | XpmCloseness;

/*- create a pixmap from the XPM file -*/
  status = XpmReadFileToPixmap (canal_aff[i], fenetre[i],
				"small_white.xpm",
				&(petit_carre_blanc[i].data),
				&(petit_carre_blanc[i].mask),
				&attributs);

  if (status != XpmSuccess)
    {
      fprintf (stderr, "XpmError: %s,status:%d.\n", XpmGetErrorString (status), status);
      exit (1);
    }

/*- create a pixmap from the XPM file,           too! -*/
  status = XpmReadFileToPixmap (canal_aff[i], fenetre[i],
				"spy_dead.xpm",
				&(dead[i].data),
				&(dead[i].mask),
				&attributs);

  if (status != XpmSuccess)
    {
      fprintf (stderr, "XpmError: %s,status:%d.\n", XpmGetErrorString (status), status);
      exit (1);
    }


/*- create a pixmap from the XPM file,           too! -*/
  status = XpmReadFileToPixmap (canal_aff[i], fenetre[i],
				"spy_win.xpm",
				&(win[i].data),
				&(win[i].mask),
				&attributs);

  if (status != XpmSuccess)
    {
      fprintf (stderr, "XpmError: %s,status:%d.\n", XpmGetErrorString (status), status);
      exit (1);
    }


/*- create a pixmap from the XPM file,           too! -*/
  status = XpmReadFileToPixmap (canal_aff[i], fenetre[i],
				"small_black.xpm",
				&(petit_carre_noir[i].data),
				&(petit_carre_noir[i].mask),
				&attributs);

  if (status != XpmSuccess)
    {
      fprintf (stderr, "XpmError: %s,status:%d.\n", XpmGetErrorString (status), status);
      exit (1);
    }
#ifdef DEBUG
  printf ("Loaded\n");
#endif
}

void
spy_afficher_sprite (int player, int x, int y, Pixart moi)
{
  XCopyArea (canal_aff[player], moi.data, fenetre[player], gc[player],
	     0, 0,
	     TAILLE_PETIT_CARRE, TAILLE_PETIT_CARRE,
	     x, y);
}

void 
spy_effacer_sprite (int player, int x, int y)
{
  XClearArea (canal_aff[player], fenetre[player],
	     x, y,
	     TAILLE_PETIT_CARRE, TAILLE_PETIT_CARRE,
	     0);
}

/*- Affiche la croix sur le display player, dans la case de opponent -*/
void
spy_afficher_croix (int player,int opponent, Pixart moi[NOMBRE])
{
    /*- Un clip Mask pour la transparence -*/
    XSetClipOrigin(canal_aff[player],gc[player],SPYX[opponent],SPYY[opponent]);
    XSetClipMask(canal_aff[player],gc[player],moi[player].mask);

    /*- Affichage effectif -*/
    XCopyArea(canal_aff[player],moi[player].data,fenetre[player],gc[player],
	      0,0,
	      TAILLE_PETIT_CARRE*MAX_TAB_X,TAILLE_PETIT_CARRE*MAX_TAB_Y,
	      SPYX[opponent],SPYY[opponent]);

    /*- On retire ce masque pour eviter un gros bug d'affichage -*/
    XSetClipMask(canal_aff[player],gc[player],None);

}

void 
spy_afficher_petit_tableau (int player, int opponent)
{

  int x, y;

#ifdef DEBUG
  printf ("Affichage du tableau %d,%d\n", player, opponent);
#endif




  /*- L'affichage se fait dans fenetre[player], a offset_x et y
    Les donnees sont dans tableau[opponent] -*/
  
  for (x = 0; x < TAILLE_TAB_X; x++)
      for (y = 0; y < TAILLE_TAB_Y; y++)
	  
	  if (tableau[opponent][x][y])
	      spy_afficher_sprite (player, SPYX[opponent] + x * TAILLE_PETIT_CARRE, SPYY[opponent] + y * TAILLE_PETIT_CARRE,
				   petit_carre_blanc[player]);
	  else
	      spy_effacer_sprite(player, SPYX[opponent] + x * TAILLE_PETIT_CARRE, SPYY[opponent] + y * TAILLE_PETIT_CARRE);

  if (etat[opponent]==PERDU)
      spy_afficher_croix(player,opponent,dead);


  /*- Je force le vidage du canal d'affichage -*/
  XFlush (canal_aff[player]);
#ifdef DEBUG
  printf("Affiche\n");
#endif
}

/*- Ca veut dire ce que ca veut dire... -*/
void
spy_afficher_noms (int player,int opponent)
{
      XDrawString(canal_aff[player],fenetre[player],gc[player],
		  SPYNX[opponent],SPYNY[opponent],
		  names[opponent],strlen(names[opponent]));
}

/*- Affichage de la totalite des spy_windows pour un gars -*/
void 
spy_affichage (int i)
{
  int j;

  for (j = 0; j < MAXIMUM; j++) {
/*- Affichage d'un des tableaux -*/
	  spy_afficher_petit_tableau (i, j);
	  spy_afficher_noms (i,j);
  }
}

void 
spy_init (void)
{

  int i;
  if (SPY == YES)
    for (i = 0; i < MAXIMUM; i++)
/*- Creer les spy_windows de jeu -*/
	spy_creation_pixmaps (i);
}

void 
spy_update (int player)
/*- player est le joueur dont la piece est tombee -*/
{

  int i;

  if (SPY ==YES )
      for (i = 0; i < MAXIMUM; i++) {
/*- Mettre a jour -*/
	spy_afficher_petit_tableau (i,player);
	spy_afficher_noms (i,player);
      }
}

void 
spy_expose (int player)
{
  if (SPY == YES)
    spy_affichage (player);
}

void spy_win( int i )
{
    int un_vainqueur,j;
    un_vainqueur=0;

    /*- recherche d'un vainqueur -*/
    if (SPY==YES) {
        for ( j=0 ; j<MAXIMUM ; j++ )

	    if (etat[j]==ENCORE_EN_COURSE) un_vainqueur=j;

        for ( j=0 ; j<MAXIMUM ; j++ ) {

	    spy_afficher_noms (i,j);

	    if ( team[j] == team[un_vainqueur] )

	        spy_afficher_croix(i,j,win);

    	    else

	        spy_afficher_croix(i,j,dead);
	}
    }
}

void 
spy_free (void)
{

  int i;

  if (SPY == YES)
    for (i = 0; i < MAXIMUM; i++)
      {

#ifdef DEBUG
	  printf("Liberation des pixmaps du module SPY\n");
#endif

/*- D'abord les sprites -*/
	XFreePixmap (canal_aff[i], petit_carre_noir[i].data);
	XFreePixmap (canal_aff[i], petit_carre_blanc[i].data);
	XFreePixmap (canal_aff[i], petit_carre_blanc[i].mask);
	XFreePixmap (canal_aff[i], petit_carre_noir[i].mask);
	XFreePixmap (canal_aff[i], dead[i].mask);
	XFreePixmap (canal_aff[i], dead[i].data);
	XFreePixmap (canal_aff[i], win[i].mask);
	XFreePixmap (canal_aff[i], win[i].data);

      }
}
