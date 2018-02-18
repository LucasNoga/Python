#include "theme.h"

/*- Etats -*/
#define LIRE_BLANC 0
#define LIRE_MOT 1
#define LIRE_COM 2
#define LIRE_BYE 3

/*- Classe -*/
#define BLANC 0
#define LETTRE 1
#define DIESE 2
#define CRETURN 3

void 
theme_valeurs_par_defaut (void)
{

  TAILLE_CARRE = 16;
  TAILLE_PETIT_CARRE = 4;

  OFFSET_X = 61;
  OFFSET_Y = 30;

  PSUIVANTEX = 230;
  PSUIVANTEY = 20;

  SCOREX = 12;
  SCOREY = 20;
  TIMEX = 70;
  TIMEY = 20;
  LIGNEX = 12;
  LIGNEY = 40;
  MESSAGEX = 70;
  MESSAGEY = 390;

  FEN_W = 450;
  FEN_H = 400;

  TAILLE_TAB_X = MAX_TAB_X;
  TAILLE_TAB_Y = MAX_TAB_Y;

/*- Position des fenetres espionnes -*/
  SPYX[0] = SPYX[3] = SPYX[6] = SPYNX[0] = SPYNX[3] = SPYNX[6] = 300;
  SPYX[1] = SPYX[4] = SPYX[7] = SPYNX[1] = SPYNX[4] = SPYNX[7] = 350;
  SPYX[2] = SPYX[5] = SPYNX[2] = SPYNX[5] = 400;

/*- Elle forment un tableau a droite de l'ecran de jeu. -*/
  SPYY[1] = SPYY[0] = SPYY[2] =  20;
  SPYY[3] = SPYY[4] = SPYY[5] = 120;
  SPYY[6] = SPYY[7] = 220;
  
/*- Les noms ont les meme positions, mais sont un peu en dessous des spys. -*/
  SPYNY[0] = SPYNY[1] = SPYNY[2] = 115;
  SPYNY[3] = SPYNY[4] = SPYNY[5] = 215; 
  SPYNY[6] = SPYNY[7] = 315;

  MAXPLAYERS = NOMBRE;
  MAXPIECES  = PIECES_CLASSIC;
  TOURNOI = 3 ;
  HANDICAP = 0 ;


/*- Ca peut eviter des problemes -*/
}

int 
theme_classe (char c)
{
  if ((c == ' ') || (c == '\t'))
    return BLANC;
  if ((c == '#') || (c == '%'))
    return DIESE;
  if (c == '\n')
    return CRETURN;
  return LETTRE;
}

void 
theme_nouvel_etat (int classe, int *etat)
{
  int nouvel_etat;
  int tableau_etats[4][4] =
  {
/*-  BLANC         MOT          COM        BYE            -*/
    {LIRE_BLANC, LIRE_BLANC, LIRE_COM, LIRE_BYE},
/*- Si je lis un blanc -*/
    {LIRE_MOT, LIRE_MOT, LIRE_COM, LIRE_BYE},
/*- une lettre -*/
    {LIRE_COM, LIRE_COM, LIRE_BLANC, LIRE_BYE},
/*- un diese   -*/
    {LIRE_BYE, LIRE_BYE, LIRE_BYE, LIRE_BYE}
/*- un return -*/
  };

  nouvel_etat = tableau_etats[classe][(*etat)];

  (*etat) = nouvel_etat;

}

void 
theme_lire_commande (FILE * entree, int *argc, char ***argv)
{
  char c;
  char t[1024], *p;
  int i, etat, c_classe;

  i = 0;
  (*argc) = 0;
  etat = LIRE_BLANC;

  do
    {
      c = fgetc (entree);
      c_classe = theme_classe (c);

      switch (etat)
	{
	case LIRE_BLANC:
	  if (feof (entree))
	    t[i++] = 0;
	  else
	    {
	      if (c_classe == LETTRE)
		{
		  t[i++] = c;
		  (*argc)++;
		}
	    }
	  break;
	case LIRE_MOT:
	  if (feof (entree))
	    t[i++] = 0;
	  else
	    {
	      if (c_classe == LETTRE)
		t[i++] = c;
	      if (c_classe == BLANC)
		t[i++] = 0;
	    }
	  break;
	case LIRE_COM:
	  if (feof (entree))
	    t[i++] = 0;
	  else
	    {
	      if (c_classe == DIESE);
	    }
	  break;
	}
      theme_nouvel_etat (c_classe, &etat);
    }
  while (!feof (entree) && (c != '\n'));

/*- Allocation de la memoire pour le tableau -*/
  t[i++] = 0;
  (*argv) = (char **) calloc (sizeof (char *), *argc);
  i = 0;
  p = t;

/*- Recuperation -*/
  while (i < *argc)
    {

/*- Copie du mot dans la place reservee pour la chaine-*/
      (*argv)[i] = (char *) calloc (sizeof (char), strlen (p) + 1);
      strcpy ((*argv)[i], p);

/*- Passage au mot suivant -*/
      while (*p != 0)
	p++;
      p++;
      i++;
    }
}

void 
theme_executer_commande (int argc, char **argv)
{
  int i;

  if (argc > 0)
    {
      if ((strcmp (argv[0], "Winsize") == 0) && (argc == 3))
	{
	  FEN_W = atoi (argv[1]);
	  FEN_H = atoi (argv[2]);
	}
      if ((strcmp (argv[0], "Offset") == 0) && (argc == 3))
	{
	  OFFSET_X = atoi (argv[1]);
	  OFFSET_Y = atoi (argv[2]);
	}
      if ((strcmp (argv[0], "Next") == 0) && (argc == 3))
	{
	  PSUIVANTEX = atoi (argv[1]);
	  PSUIVANTEY = atoi (argv[2]);
	}
      if ((strcmp (argv[0], "Time") == 0) && (argc == 3))
	{
	  TIMEX = atoi (argv[1]);
	  TIMEY = atoi (argv[2]);
	}
      if ((strcmp (argv[0], "Score") == 0) && (argc == 3))
	{
	  SCOREX = atoi (argv[1]);
	  SCOREY = atoi (argv[2]);
	}
      if ((strcmp (argv[0], "Lines") == 0) && (argc == 3))
	{
	  LIGNEX = atoi (argv[1]);
	  LIGNEY = atoi (argv[2]);
	}
      if ((strcmp (argv[0], "Message") == 0) && (argc == 3))
	{
	  MESSAGEX = atoi (argv[1]);
	  MESSAGEY = atoi (argv[2]);
	}
      if ((strcmp (argv[0], "Table") == 0) && (argc == 3))
	{
	  TAILLE_TAB_X = atoi (argv[1]);
	  TAILLE_TAB_Y = atoi (argv[2]);
	  if ((TAILLE_TAB_Y < 8) || (TAILLE_TAB_Y > MAX_TAB_Y))
	    TAILLE_TAB_Y = MAX_TAB_Y;
	  if ((TAILLE_TAB_X < 3) || (TAILLE_TAB_X > MAX_TAB_X))
	    TAILLE_TAB_X = MAX_TAB_X;

	}
      if ((strcmp (argv[0], "Box") == 0) && (argc == 3))
	{
	  TAILLE_CARRE = atoi (argv[1]);
	  TAILLE_PETIT_CARRE = atoi (argv[2]);
	}
      if ((strcmp (argv[0], "Fgcolor") == 0) && (argc == 4))
	{
/*- Choisir la couleur des textes, allouer la couleur, et la foutre dans gc[i] en foreground. -*/
/*-	    Il suffit de faire un XSetForeground(canal,gc) avec la valeur la plus proche -*/
	}
      if ((strcmp (argv[0], "Spy") == 0) && (argc == 4))
	{
	  i = atoi (argv[1]);
	  if (i >= 0 && i < NOMBRE)
	    {
	      SPYX[i] = atoi (argv[2]);
	      SPYY[i] = atoi (argv[3]);
	    }
	}
      if ((strcmp (argv[0], "Spyname") == 0) && (argc == 4))
	{
	  i = atoi (argv[1]);
	  if (i >= 0 && i < NOMBRE)
	    {
	      SPYNX[i] = atoi (argv[2]);
	      SPYNY[i] = atoi (argv[3]);
	    }
	}
      if ((strcmp (argv[0], "SpyMode") == 0) && (argc == 2))
	{
	  if (!strcmp (argv[1], "Yes"))
	    SPY = YES;
	  if (!strcmp (argv[1], "No"))
	    SPY = NO;
	}
      if ((strcmp (argv[0], "Extendpieces") == 0) && (argc == 2))
	{
	  if (!strcmp (argv[1], "Yes"))
	    MAXPIECES = PIECES_EXTENDED;
	  if (!strcmp (argv[1], "No"))
	    MAXPIECES = PIECES_CLASSIC;
	}
      if ((strcmp (argv[0], "Language") == 0) && (argc == 2))
	{
	  if (!strcmp (argv[1], "English"))
	    LANG = GB;
	  else
	    LANG = FR;
	}
      if ((strcmp (argv[0], "PlayersMax") == 0) && (argc == 2))
	{
	  MAXPLAYERS = atoi (argv[1]);
	  if ((MAXPLAYERS < 1) || (MAXPLAYERS > NOMBRE))
	    MAXPLAYERS = 8;
	}
    }
}

/*- Liberation de la memoire allouee par l'automate. -*/
void 
theme_liberer_commande (int argc, char **argv)
{
  int i;
  for (i = 0; i < argc; i++)
    {
      if (argv[i] != NULL)
	free (argv[i]);
    }
  if (argv != NULL)
    free (argv);
}

/*- Analyse du fichier de theme -*/
void 
theme_set (char *theme_file)
{
  FILE *entree;
  int argc;
  char **argv;

  theme_valeurs_par_defaut ();

#ifdef DEBUG
	printf("Default values set\n");
#endif

/*- On essaye le repertoire par defaut -*/
  entree = fopen ("theme", "rt");



/*- Si ca marche pas, on choisit le dossier standard -*/
  if (entree == NULL) {
    chdir (DIR);
#ifdef DEBUG
	printf("Dir set to pixart\n");
#endif
        entree = fopen ("theme", "rt");
  }


#ifdef DEBUG
	printf("OPened the file\n");
#endif

  if (entree != NULL)
    {

      while (!feof (entree))
	{

	  theme_lire_commande (entree, &argc, &argv);

#ifdef DEBUG
	printf(" Commande readed \n");
#endif
	  theme_executer_commande (argc, argv);

#ifdef DEBUG
	printf(" Executee\n");
#endif
	  theme_liberer_commande (argc, argv);

#ifdef DEBUG
	printf("Freeded\n");
#endif
	}

	  fclose (entree);

    }
  else
    {

#ifdef DEBUG
      printf ("Couldn't load theme file:%s\n", theme_file);
#endif

    }



/*- Centrage de la fenetre de jeu -*/
  OFFSET_X += (MAX_TAB_X - TAILLE_TAB_X) * TAILLE_CARRE / 2;

}
