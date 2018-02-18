/*
   Initialisation des fenetres...
   Ce module est charge d'ouvrir les fenetres et de creer les sprites...
 */
#include "init.h"

int status;

int BGMODE;
int LANG_FR;

char *pixpath[] =
{
/*- Avec un bg -*/
  "bckgnd.xpm",
  "block_bckgnd.xpm",
  "spy_bckgnd.xpm",
  "block_blue.xpm",
  "block_light.xpm",
  "block_red.xpm",
  "block_purple.xpm",
  "block_green.xpm",
  "block_yellow.xpm",
  "block_pink.xpm",
  "block_sea.xpm",
  "block_dark_brown.xpm",
  "block_orange.xpm",
/*- Mode sans background -*/
  "black_pixel.xpm",
  "block_bckgnd.xpm",
  "spy_bckgnd.xpm",
  "block_blue.xpm",
  "block_light.xpm",
  "block_purple.xpm",
  "block_red.xpm",
  "block_green.xpm",
  "block_yellow.xpm",
  "block_pink.xpm",
  "block_sea.xpm",
  "block_dark_brown.xpm",
  "block_orange.xpm"
};


/*- ajouter une gestion d'erreurs -*/
/*- Ligne de commande, --bg --nobg, --fr --gb -*/
void 
process_command_line (int argc, char **argv)
{
  int i;
  BGMODE = YES;
/*- Mode par defaut -*/
  LANG = FR;
  SPY = YES;

  for (i = 1; i < argc; i++)
    {
      if (strcmp (argv[i], "--nobg") == 0)
	BGMODE = NO;
      else if (strcmp (argv[i], "--bg") == 0)
	BGMODE = YES;
      else if (strcmp (argv[i], "--fr") == 0)
	LANG = FR;
      else if (strcmp (argv[i], "--gb") == 0)
	LANG = GB;
      else if (strcmp (argv[i], "--spy") == 0)
	SPY = YES;
      else if (strcmp (argv[i], "--nospy") == 0)
	SPY = NO;
      else if (strcmp (argv[i], "--dir") == 0)
	{
	  if (i + 1 >= argc)
	    {
	      printf ("--dir with illegal path! Killed.\n");
	      exit (1);
	    }
	  else
	    {
	      if (chdir (argv[i + 1]) != 0)
		{
		  printf ("Warning: directory not existing: %s", argv[i + 1]);
		  chdir (DIR);
		}
	      else
		{
		  printf ("OK for dir %s\n", argv[i + 1]);
		}
	    }
	}
    }
}

/*- Ouverture des fenetres des joueurs -*/
void 
init_all_windows ()
{
  int courant, i;
  int bgm;
/*- Offset pour le background et les themes... -*/
  XpmAttributes attribut_xpm;

  /* Ouverture des canaux */
  for (courant = 0; courant < MAXIMUM; courant++)
    {

      /* creation du canal d'affichage */
      canal_aff[courant] = GOpenDisplay (machines[courant]);

      /* Fenetre mere de chaque poste */
      racine[courant] = DefaultRootWindow (canal_aff[courant]);

      /* Dimensions de la fenetre de jeu */
      infos_fen[courant].x = FEN_X;
      infos_fen[courant].y = FEN_Y;
      infos_fen[courant].width = FEN_W;
      infos_fen[courant].height = FEN_H;
      infos_fen[courant].max_width = infos_fen[courant].min_width = FEN_W;
      infos_fen[courant].max_height = infos_fen[courant].min_height = FEN_H;
      infos_fen[courant].flags = PSize | PMinSize | PMaxSize;
      manager[courant].flags = InputHint;
      manager[courant].input = True;

      /* L'ecran */
      ecran[courant] = DefaultScreen (canal_aff[courant]);
      blanc[courant] = WhitePixel (canal_aff[courant], ecran[courant]);
      noir[courant] = BlackPixel (canal_aff[courant], ecran[courant]);

      /*- Chargement des pixmaps dont on aura besoin pour le fond de fenetre -*/

      if (BGMODE == YES)
	  bgm = 0;
      else
	  bgm = PIXMAX;
#ifdef DEBUG
      if (BGMODE == YES)
	  printf ("mode bg\n");
      if (BGMODE == NO)
	  printf ("mode nobg\n");
#endif
      
      attribut_xpm.closeness = 65535;
      attribut_xpm.valuemask = XpmCloseness;
      for (i = 0; i < PIXMAX; i++)
	  {
	      /*- create a pixmap from the XPM file -*/
#ifdef DEBUG
	  printf ("Loading:%s\n", pixpath[i]);
#endif
	  status = XpmReadFileToPixmap (canal_aff[courant],
					racine[courant],
					pixpath[i + bgm],
					&(sprite_img[courant][i].data),
					&(sprite_img[courant][i].mask),
					&attribut_xpm);
	  if (status != XpmSuccess)
	      {
		  fprintf (stderr, "XpmError: %s,\ndisplay: %d,file: %s\n,status:%d.\n", XpmGetErrorString (status), i, pixpath[i], status);
		  exit (1);
	    }
	  }

      xswa[courant].background_pixmap=sprite_img[courant][BACK_PIX].data;
      xswa[courant].event_mask=ExposureMask | KeyPressMask | ButtonPressMask;

      /*- creation de la fenetre -*/
      fenetre[courant]= XCreateWindow (canal_aff[courant], racine[courant],
				       infos_fen[courant].x,infos_fen[courant].y,
				       infos_fen[courant].width,infos_fen[courant].height,
				       3,DefaultDepth(canal_aff[courant],ecran[courant]),
				       InputOutput,
				       DefaultVisual(canal_aff[courant],ecran[courant]),
				       CWEventMask | CWBackPixmap,
				       &xswa[courant]);

      if ((fenetre[courant] == BadMatch) ||
	  (fenetre[courant] == BadAlloc) ||
	  (fenetre[courant] == BadValue) ||
	  (fenetre[courant] == BadWindow))	/* Cherchez l'erreur */
	{
	  fprintf (stderr, "Can't open display\n");
	  exit (1);
	}

      XSetWMHints (canal_aff[courant], fenetre[courant],
		   &manager[courant]);
      XSetStandardProperties (canal_aff[courant], fenetre[courant],
	   names[courant], names[courant], None, 0, 0, &infos_fen[courant]);

      /* Le contexte graphique */
      gc[courant] = XCreateGC (canal_aff[courant], fenetre[courant], 0, 0);
      XSetForeground (canal_aff[courant], gc[courant], blanc[courant]);
      XSetBackground (canal_aff[courant], gc[courant], noir[courant]);

      XMapRaised (canal_aff[courant], fenetre[courant]);
    }
}

