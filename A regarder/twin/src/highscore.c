#include "highscore.h"

char *high =
{"highscore"};

char *hs_nom;
int hs_score;

void 
hs_reset_victory (void)
{
  int i;
  for (i = 0; i < MAXPLAYERS; i++)
    victory[i] = 0;
}

void 
hs_load_maximum (void)
{
  FILE *entree;
  char *ascore;

/*- Le meilleur score -*/
  if ((entree = fopen (high, "rt")) != NULL)
    {
      hs_nom = GInputString (entree);
      ascore = GInputString (entree);

      hs_score = atoi (ascore);
      free (ascore);
#ifdef DEBUG
      printf ("loaded highscore:%s,%d\n", hs_nom, hs_score);
#endif
      fclose (entree);
    }
  else
    {
#ifdef DEBUG
      printf ("Failed to load highscore\n");
#endif
      hs_score = 0;
      hs_nom = (char *) calloc (sizeof (char), strlen ("nobody") + 1);
      strcpy (hs_nom, "nobody");
      hs_nom[6] = 0;
    }
}

void 
hs_store_maximum (int score, char *nom)
{
  FILE *sortie;
  if ((sortie = fopen (high, "w")) != NULL)
    {
      fprintf (sortie, "%s\n%d\n", nom, score);
      fclose (sortie);
#ifdef DEBUG
      printf ("saved highscores\n");
#endif
    }
  else
    {
#ifdef DEBUG
      printf ("Impossible de creer le fichier de highscore.\n");
      printf ("Veuillez verifier vos droits d'ecriture\n");
#endif
    }
}

void 
hs_afficher_hs (char *nom, int score, int new)
{
  int x, y, i;
  int pl = 0;

#ifdef DEBUG
  printf ("Current high score : %s,%d\n", nom, score);
#endif


  x = OFFSET_X + 10;
  y = OFFSET_Y + 20;

  GAfficheFin (pl);

  if (new)
    XDrawString (canal_aff[pl], fenetre[pl], gc[pl],
		 x, y,
		 say (SAY_RECORD), strlen (say (SAY_RECORD)));

  else
    XDrawString (canal_aff[pl], fenetre[pl], gc[pl],
		 x, y, say (SAY_REC), strlen (say (SAY_REC)));

  y += 20;

  for (i = 0; i < MAXIMUM; i++)
    {

      XDrawString (canal_aff[pl], fenetre[pl], gc[pl],
		   x, y,
		   nom, strlen (nom));

      GAfficheChiffre (pl, x + 6 * (strlen (nom) + 7) , y, score);

#ifdef DEBUG
      printf("%f:%d\n",(float)log10(score),(int)log10(score));
#endif

      y += 20;

    }

  XDrawString (canal_aff[pl], fenetre[pl], gc[pl],
	       x, y,
	       say (SAY_SPACE), strlen (say (SAY_SPACE)));

  XFlush (canal_aff[pl]);

}

void 
hs_show (char *nom, int score, int new)
{

  int i, choix_effectue, Touche;

  i=0;

  choix_effectue = 0;

  hs_afficher_hs (nom, score, new);

  while (!choix_effectue)
    {

      i++;
      if (i >= MAXIMUM)
	i = 0;

      if (XEventsQueued (canal_aff[i], QueuedAfterReading))
	{

	  XNextEvent (canal_aff[i], &(evenem[i]));

	  if (evenem[i].type == KeyPress)
	    {
/*- Regarder si c'est la barre d'espace... -*/

	      Touche = XKeycodeToKeysym (canal_aff[i], evenem[i].xkey.keycode, 0);

	      if (Touche == XK_space)
		choix_effectue = 1;

	    }

	  if (evenem[i].type == Expose)
	    {

	      hs_afficher_hs (nom, score, new);

	      XFlush (canal_aff[i]);

	    }

	}

    }

}

void 
do_high_score (void)
{

#ifdef DEBUG
  printf ("Doing high scores\n");
#endif

  hs_load_maximum ();
  if (score[0] > hs_score)
    {
      hs_store_maximum (score[0], names[0]);
      hs_show (names[0], score[0], 1);
    }
  else
    hs_show (hs_nom, hs_score, 0);
  free (hs_nom);
}

void 
hs_afficher_victoires (int pl)
{

  int i;
  int x, y;

  x = OFFSET_X + 10;
  y = OFFSET_Y + 20;

  GAfficheFin (pl);

  for (i = 0; i < MAXIMUM; i++)
    {

      XDrawString (canal_aff[pl], fenetre[pl], gc[pl],
		   x, y,
		   names[i], strlen (names[i]));

      GAfficheChiffre (pl, x + 6 * (strlen (names[i]) + 3), y, victory[i]);

      y += 20;

    }

  XDrawString (canal_aff[pl], fenetre[pl], gc[pl],
	       x, y,
	       say (SAY_SPACE), strlen (say (SAY_SPACE)));

}

void 
hs_victory (void)
{
  int i;
  int choix_effectue, Touche;
/*- Cette fonction servira a afficher le nombre de victoire des coureurs en mode multijoueur -*/

#ifdef DEBUG
  for (i = 0; i < MAXIMUM; i++)
    printf ("%s : %d\n", names[i], victory[i]);
#endif

  for (i = 0; i < MAXIMUM; i++)
    {

      hs_afficher_victoires (i);

      XFlush (canal_aff[i]);

    }

  choix_effectue = 0;

  while (!choix_effectue)
    {

      i++;
      if (i >= MAXIMUM)
	i = 0;

      if (XEventsQueued (canal_aff[i], QueuedAfterReading))
	{

	  XNextEvent (canal_aff[i], &(evenem[i]));

	  if (evenem[i].type == KeyPress)
	    {
/*- Regarder si c'est la barre d'espace... -*/

	      Touche = XKeycodeToKeysym (canal_aff[i], evenem[i].xkey.keycode, 0);

	      if (Touche == XK_space)
		choix_effectue = 1;

	    }

	  if (evenem[i].type == Expose)
	    {

	      hs_afficher_victoires (i);

	      XFlush (canal_aff[i]);

	    }

	}

    }

}
