/* Gestion de plein de fenetres sur un ordi */
/* C'est devenu un tetris en reso */
/* Avec les xpms */
/* huit players extensible en 30 secondes a 100 si je veux... */

#include "twin.h"

char chiffre[] =
{"123456789"};

void
clear_all_windows (void)
{
  int i;
  for (i = 0; i < MAXIMUM; i++)
    GAffBackground (i);
}

void 
intro (void)
{
  int i;
  clear_all_windows ();
  for (i = 0; i < MAXIMUM; i++)
/*- Afficher un beau texte -*/ ;
}


/* Procedure Principale */
int 
run_game (int argc, char **argv)
{
  int un_vainqueur, fin_jeu, mouvement[NOMBRE];
  int courant, i, j, k;
  int bybye = 1;
  long Touche;
  char *temp_str;
  int spstep[NOMBRE];

  fin_jeu = 0;

/*- Quelques commentaires -*/
  joueurs_restants = MAXIMUM;
  un_vainqueur = 0;

  play_again = 0;

#ifdef DEBUG
  printf("SPY_MODE au debut de run game:%d\n",SPY);
#endif
/*- La fenetre du mode espion -*/
  spy_init ();

#ifdef DEBUG
  printf("apres le SPY_INIT :SPY_MODE:%d\n",SPY);
#endif
/*- Mode par equipe -*/
  init_team ();


#ifdef DEBUG
  printf ("Nombre d'equipes en jeu:%d\n", nb_team ());
#endif

#ifdef DEBUG
  printf("SPY_MODE:%d\n",SPY);
#endif
  clear_all_windows ();

#ifdef DEBUG
  printf("Clear all windows :SPY_MODE:%d\n",SPY);
#endif
/*- Initialisation des variables de chaque joueurs -*/
  for (courant = 0; courant < MAXIMUM; courant++)
    {
      etat[courant] = ENCORE_EN_COURSE;
      positionx[courant] = TAILLE_TAB_X / 2;
      positiony[courant] = DEPART_PIECE;
      speed[courant] = DEPART_PIECE;
      lignes[courant] = 0;
      score[courant] = 0;
      mouvement[courant] = 0;
      vertical_speed[courant] = SPEED / MAXIMUM;
      spstep[courant] = vertical_speed[courant] * PERCENT / 100;

#ifdef DEBUG
  printf(" Moitie de l'init des variables;SPY_MODE:%d\n",SPY);
#endif

      /* Choix de la piece */
      GCreatePiece (&(pieces_suivante[courant]));
      GCreatePiece (&(pieces_courante[courant]));

      /* Vidage du tableau de niveau */
      for (i = 0; i < TAILLE_TAB_X; i++)
	for (j = 0; j < TAILLE_TAB_Y; j++)
	  tableau[courant][i][j] = 0;

      /*- Mise en place du handicap -*/
      for ( i = 0 ; i < HANDICAP ; i ++ )
	  GDecaleTableauUp(&tableau[courant]);

      GAffBackground (courant);
      GAfficheTableau (courant);

#ifdef DEBUG
  printf("Fin de creation, tableau affiche :SPY_MODE:%d\n",SPY);
#endif
    }				/* Fin du for courant de 1 a maximum */

#ifdef DEBUG
  printf("Avant la boucle principale: SPY_MODE:%d\n",SPY);
#endif
  /**************************************************************************************
   *                                                                                    *
   *                            Boucle Principale du jeu                                *
   *                                                                                    *
   *************************************************************************************/
  courant = 0;

#ifdef DEBUG
  printf("premier soit disant affichage : SPY_MODE:%d\n",SPY);
#endif

  /*- Mise en place du compte a rebours -*/
  time_set_counter ( TIME * 60 ) ;

#ifdef DEBUG
  printf ("Game Time:%d minute(s)\n" ,TIME ) ;
#endif

/*- Tant que personne n'a gagne -*/
  while (((!winner_team ()) || (MAXIMUM == 1)) && (bybye) && !time_out_of_time())
    {

#ifdef DEBUG
  printf("Debut de boucle\n");
#endif
      if (etat[courant] == ENCORE_EN_COURSE)
	{

#ifdef DEBUG
  printf("Raffraichissement\n");
#endif
/*- Rafraichissement ssi on a bouge -*/
	  if ((positionx[courant] != lastpx[courant]) || (positiony[courant] != lastpy[courant]) || mouvement[courant])
	    {
	      mouvement[courant] = 0;
/*- Effacement -*/

#ifdef DEBUG
  printf("Effacement\n");
#endif
	      GDrawPiece (courant, lastpx[courant], lastpy[courant],
		 ERASE_MODE, pieces_courante, 
			  OFFSET_X, OFFSET_Y);

/*- Affichage -*/

#ifdef DEBUG
  printf("Affichage\n");
#endif
	      GDrawPiece (courant, positionx[courant], positiony[courant],
		  DRAW_MODE, pieces_courante,
			  OFFSET_X, OFFSET_Y);

	      GAfficherTemps ( courant ) ;
	    }

/*- Sauvegarde des positions -*/

#ifdef DEBUG
	  printf("Sauvegarde\n");
#endif	  
	  lastpx[courant] = positionx[courant];
	  lastpy[courant] = positiony[courant];

#ifdef DEBUG
	  printf("Affichage fait\n");
#endif
/*- Si la piece touche le fond -*/
	  if ((GPieceOut (pieces_courante[courant], positionx[courant], positiony[courant] + 1) ||
	       GPieceBlocked (tableau[courant], pieces_courante[courant], positionx[courant], positiony[courant] + 1)) &&
	      speed[courant] >= vertical_speed[courant] - 1)
	    {

	      GFlush (courant);
/*- Vidage du buffer clavier -*/

#ifdef DEBUG
  printf("Flush\n");
#endif
	      score[courant]++;

	      for (i = 0; i < pieces_courante[courant].nb_blocks; i++)
		tableau[courant][lastpx[courant] + (pieces_courante[courant].positions)[i][XPIECE]][lastpy[courant] + (pieces_courante[courant].positions)[i][YPIECE]] = pieces_courante[courant].couleur;

/*- Ici les effacements -*/

#ifdef DEBUG
  printf("Effacements\n");
#endif
	      GDrawPiece (courant, 0, 0,
			  ERASE_MODE,
			  pieces_suivante,
			  PSUIVANTEX, PSUIVANTEY);
	      GClearMessageZone (courant);


/*- Nouvelle piece -*/

#ifdef DEBUG
  printf("Nouvelles piece\n");
#endif
	      GFlush (courant);
	      lastpy[courant] = 0;
	      lastpx[courant] = TAILLE_TAB_X / 2;
	      speed[courant] = DEPART_PIECE;
	      positiony[courant] = DEPART_PIECE;
	      positionx[courant] = lastpx[courant];

/*- Choix de la forme -*/

#ifdef DEBUG
  printf("Transfert\n");
#endif
	      for (i = 0; i < 6; i++)
		{
		  (pieces_courante[courant].positions)[i][XPIECE] = (pieces_suivante[courant].positions)[i][XPIECE];
		  (pieces_courante[courant].positions)[i][YPIECE] = (pieces_suivante[courant].positions)[i][YPIECE];
		}
	      pieces_courante[courant].couleur = pieces_suivante[courant].couleur;
	      pieces_courante[courant].nb_blocks=pieces_suivante[courant].nb_blocks;
	      GCreatePiece (&(pieces_suivante[courant]));

/*- Si la nouvelle piece est battue ie qu'elle override une piece alors le gars a perdu -*/
	      if ( GPieceBlocked (tableau[courant], pieces_courante[courant], positionx[courant], positiony[courant] )) {

#ifdef DEBUG
  printf("Le gars a perdu\n");
#endif
/*- Le joueur a perdu -*/
		  etat[courant] = PERDU;
/*- joueurs_restants--; -*/
		  eliminer (courant);	/* Pour le mode team */
		  GAfficheTout(courant);
		  spy_update(courant);
		  spy_expose(courant);
		  for (i = 0; i < MAXIMUM; i++)
/*- Pour tout les gars autres que courant -*/
		    if (i != courant)
		      {
			temp_str = concat_chaine (names[courant], say (SAY_ELIMINE) /*-" a ete elimine!"-*/ );
			GAfficheMessage (i, temp_str);
			free (temp_str);
		      }
	      }
/*- Sinon, on peut passer au reste. -*/
	      /* Combien de lignes d'un coup */
	      tetris[courant] = 0;

	      /* Ya t'il une ligne pleine */
	      for (i = 0; i < TAILLE_TAB_Y; i++)
		if (GFilledLine (tableau[courant], i))
		  {
		    lignes[courant]++;
		    tetris[courant]++;

		    for (j = i; j > 0; j--)	/* decalage du tableau */
		      for (k = 0; k < TAILLE_TAB_X; k++)
			tableau[courant][k][j] = (tableau[courant][k][j - 1]);
/*- if (MAXIMUM==1) -*/		    GAfficheTableau(courant);

		  }

	      score[courant] = score[courant] + (tetris[courant] == 1) * 100 + (tetris[courant] == 2) * 250 + (tetris[courant] == 3) * 450 + (tetris[courant] == 4) * 1000;

#ifdef DEBUG
  printf("Incrementation du score\n");
#endif
	      /*- Si la case est cochee -*/
	      if (INCREASE_SPEED == YES) {
		vertical_speed[courant] = SPEED / MAXIMUM - (score[courant] / SCORE_FLOOR) * spstep[courant];
  }
#ifdef DEBUG
  printf("Decalage des tableaux\n");
#endif
              if (tetris[courant] > 1)
/*- Si plus de deux lignes -*/
		for (i = 0; i < MAXIMUM; i++)
/*- Pour chaque joueur -*/
		  if (team[i] != team[courant])
/*- Si ce n'est pas moi ni un pote -*/
		    {
		      for (j = 0; j < tetris[courant]; j++)
			{

/*- Les coordonnees de la piece doivent etre remises a jour... -*/

			    GDecaleTableauUp (&(tableau[i]));
			    GAfficheTableau(i);

			  if (positiony[i] > 2)
			    positiony[i]--;

			  lastpx [i] = positionx [i] ;
			  lastpy [i] = positiony [i] ;

			}

		      GAfficheTableau (i);
/*- Cadeau de la part de courant -*/
		      temp_str = concat_chaine (say (SAY_FROM), names[courant]);
		      GAfficheMessage (i, temp_str /*-"Goute a nou!"-*/ );
		      free (temp_str);
		    }

		  else
		    {
/*- Tel joueur a envoye tant de lignes -*/
		      GAfficheMessage (courant, say (SAY_BIEN) /*-"Bien ouej!"-*/ );
		    }

/*- Rafraichissement de l'affichage -*/
/*-	      if (tetris[courant]) -*/
		GAfficheTableau (courant);
	      spy_update (courant);

#ifdef DEBUG
  printf("Reaffichage\n");
#endif
/*- Affichage de la suivante -*/
	      GDrawPiece (courant, 0, 0,
			  DRAW_MODE,
			  pieces_suivante,
			  PSUIVANTEX, PSUIVANTEY);

	      GAfficherScore (courant);

	    }
/*- fin de if GPieceOut|GPieceBlocked -*/

	  else
	    {
/*- Descente de la piece -*/
	    /*-  speed[courant]++;-*/

#ifdef DEBUG
  printf("Descente de la piece,%d\n",positiony[courant]);
#endif
	      if (speed[courant] >= vertical_speed[courant])
		{

		  positiony[courant]++;

		  speed[courant] = 0;

		}

	    }			/* fin de  else GPieceOut|GPieceBlocked */

	}			/* Fin de if not perdu */

#ifdef DEBUG
      printf("C'est pas ici:%d\n",speed[courant]);
#endif
speed[courant]++;
/*- Ici c'est le code du gars qui a perdu. -*/
      if (etat[courant] == PERDU)
	if (MAXIMUM == 1)
	  return 1;

      /* Gestion des evenements: Clavier en particulier */

      if (XEventsQueued (canal_aff[courant], QueuedAfterReading))
	{

	  XNextEvent (canal_aff[courant], &evenem[courant]);

	  switch (evenem[courant].type)
	    {

	    case Expose:

#ifdef DEBUG
  printf("Expose\n");
#endif
/*- Reafficher le tableau -*/
	      GAfficheTout (courant);

	      if (etat[courant] == ENCORE_EN_COURSE)
		{
		    GAfficheTableau (courant);

		  GDrawPiece (courant, 0, 0,
		  DRAW_MODE, pieces_suivante,
			      PSUIVANTEX, PSUIVANTEY);
		  GDrawPiece (courant, positionx[courant], positiony[courant],
		  DRAW_MODE, pieces_courante,
			      OFFSET_X, OFFSET_Y);

		}
	      spy_expose (courant);
	      break;

	    case KeyPress:

#ifdef DEBUG
  printf("Keypress\n");
#endif
	      Touche = XKeycodeToKeysym (canal_aff[courant], evenem[courant].xkey.keycode, 0);
	      /* Droite */
	      if (etat[courant] == ENCORE_EN_COURSE)
		{
		  if ((Touche == Touches [ Droite ][ courant ] ) &&
		      (positionx[courant] < (TAILLE_TAB_X - 1)))
		    if (!(GPieceOut (pieces_courante[courant], positionx[courant] + 1, positiony[courant]) ||
			  GPieceBlocked (tableau[courant], pieces_courante[courant], positionx[courant] + 1, positiony[courant])))
		      {
			positionx[courant]++;
		      }

		  /* Gauche */

		  if ((Touche == Touches [ Gauche ][ courant ] ) &&
		      (positionx[courant] > 0))
		    if (!(GPieceOut (pieces_courante[courant], positionx[courant] - 1, positiony[courant]) || GPieceBlocked (tableau[courant], pieces_courante[courant], positionx[courant] - 1, positiony[courant])))
		      {
			positionx[courant]--;
		      }

		  /* Bas */

		  if (Touche == Touches [ Descente ][ courant ] )
		    if (!(GPieceOut (pieces_courante[courant], positionx[courant], positiony[courant] + 1) || GPieceBlocked (tableau[courant], pieces_courante[courant], positionx[courant], positiony[courant] + 1)))
		      {
			speed[courant] = vertical_speed[courant] - 1;
		      }

		  /* Bas a fond */

		  if (Touche == Touches [ Flash ][ courant ] )
		    {
		      /* Ici on fait descendre la piece */
		      while (!(GPieceOut (pieces_courante[courant], positionx[courant], positiony[courant] + 1) || GPieceBlocked (tableau[courant], pieces_courante[courant], positionx[courant], positiony[courant] + 1)))
			positiony[courant]++;
		    }
		  /* Dans un sens */
		  if (Touche == Touches [ RotationDroite ][ courant ] )
		    {

		      GDrawPiece (courant, lastpx[courant], lastpy[courant],
				  ERASE_MODE, pieces_courante,
				  OFFSET_X, OFFSET_Y);

		      GRotatePiece (&(pieces_courante[courant]));
		      mouvement[courant] = 1;
		      /* Verifier si la rotation est possible, si non, on revient */
		      if (GPieceOut (pieces_courante[courant], positionx[courant], positiony[courant]) || GPieceBlocked (tableau[courant], pieces_courante[courant], positionx[courant], positiony[courant]))
			{
			  GRotateBackPiece (&(pieces_courante[courant]));
			}
		    }
		  /* Dans l'autre sens */

		  if (Touche == Touches [ RotationGauche ][ courant ] )
		    {

		      GDrawPiece (courant, lastpx[courant], lastpy[courant],
				  ERASE_MODE, pieces_courante,
				  OFFSET_X, OFFSET_Y);

		      GRotateBackPiece (&(pieces_courante[courant]));
		      mouvement[courant] = 1;
		      /*- Verifier si la rotation est possible, si non, on revient -*/
		      if (GPieceOut (pieces_courante[courant], positionx[courant], positiony[courant]) || GPieceBlocked (tableau[courant], pieces_courante[courant], positionx[courant], positiony[courant]))
			{
			  GRotatePiece (&(pieces_courante[courant]));
			}
		    }

		  /* [ a ] qd il y a plus d'espoir... */
		  if (Touche == Touches [ Abandon ][ courant ] )
		    {
		      etat[courant] = PERDU;
		      eliminer (courant);
		      GAfficheFin (courant);
		      spy_update(courant);
		      spy_expose(courant);
		    }
		}
	      /* [ q ] pour quitter */
	      if ( Touche == Touches [ Quitter ][ courant ] )
		bybye = 0;

	      break;
	    }
	}

#ifdef DEBUG
  printf("Avant le XFlush\n");
#endif
/*- Je suis sur que ca va aider... -*/
      XFlush (canal_aff[courant]);

#ifdef DEBUG
  printf("Xflush et nouveau joueur\n");
#endif
/*- Changement de joueur -*/
      courant++;
      if (courant >= MAXIMUM)
	courant = 0;


    }				/* Fin de while !joueurs_restants<1 */

  return (bybye);
}





/**********************************************************
*                                                          *
*      Affichage du nom du vainqueur                       *
*                                                          *
 **********************************************************/

void 
show_single_winner (void)
{
  int choix_effectue = 0;
  char *temp_str;
  KeySym Touche;

/*-  clear_all_windows(); -*/
  temp_str = concat_chaine (say (SAY_PERDU) /*-"Vous avez perdu, "-*/ , names[0]);

  GAfficheFin (0);

  GAfficheMessage (0, temp_str);

  GAfficherScore (0);

  XFlush (canal_aff[0]);

  while (!choix_effectue)
    {
/*- Appuyer sur la barre d'espace... -*/

      if (XEventsQueued (canal_aff[0], QueuedAfterReading))
	{

	  XNextEvent (canal_aff[0], &(evenem[0]));

	  if (evenem[0].type == KeyPress)
	    {

/*- Regarder si c'est la barre d'espace... -*/

	      Touche = XKeycodeToKeysym (canal_aff[0], evenem[0].xkey.keycode, 0);

	      if (Touche == XK_space)
		choix_effectue = 1;

	    }

	  if (evenem[0].type == Expose)
	    {

	      GAfficheFin (0);

	      GAfficheMessage (0, temp_str);

	      XFlush (canal_aff[0]);

	    }

	}

    }

  free (temp_str);

}

void 
show_multiple_winner_main (void)
{
  int un_vainqueur=0;
  int i;
  int choix_effectue = 0;
  KeySym Touche;

/*-  clear_all_windows(); -*/

#ifdef DEBUG
  printf ("Showing winner\n");
#endif

/*- Recherche d'un gars encore en course -*/
  for (i = 0; i < MAXIMUM; i++)
    if (etat[i] == ENCORE_EN_COURSE)
      un_vainqueur = i;
  if (un_vainqueur < 0 || un_vainqueur >= MAXIMUM)
    printf ("Erreur pas de vainqueur!\n");

#ifdef DEBUG
  printf ("The winner is %d,%s\n", un_vainqueur, names[un_vainqueur]);
#endif

  /* Parcours des joueurs */
  for (i = 0; i < MAXIMUM; i++)
    {
      GAfficheFin (i);
      if (team[i] == team[un_vainqueur])
	{

	  /* C'est le seul encore en course */
	  GAfficheVictoire (i);
	  XFlush (canal_aff[i]);
	  victory[i]++;
#ifdef DEBUG
	  printf ("OK pour le vainqueur\n");
#endif
	}
      else
	{
	  GAfficheFin (i);

	  /* Envoi de message: The winner is un_vainqueur */
	  GAfficheVainqueur (i, un_vainqueur);
#ifdef DEBUG
	  printf ("Vainqueur affiche:%d\n", i);
#endif
	}
#ifdef DEBUG
      printf ("Now waiting for space bar\n");
#endif


      XFlush (canal_aff[i]);
    }

/*- N'importe quel gars peut decider... -*/
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
	      GAfficheFin (i);
	      if (team[i] == team[un_vainqueur])
		GAfficheVictoire (i);
	      else
		GAfficheVainqueur (i, un_vainqueur);
	      XFlush (canal_aff[i]);
	    }
	}
    }
#ifdef DEBUG
  printf ("Sortie de la boucle d'affichage du vainqueur\n");
#endif
}

void show_multiple_winner ( void ) {

  int i ;
  int choix_effectue = 0;
  KeySym Touche;


  if ( time_out_of_time ( ) ) {

    for ( i = 0 ; i < MAXIMUM ; i ++ ) GAfficheMessage ( i , "Out of time" ) ;

/*- N'importe quel gars peut decider... -*/
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
	      GAfficheMessage (i, "Out of time");
	      XFlush (canal_aff[i]);
	    }
	}
    }
    // Attente d'appui sur une touche

  } else show_multiple_winner_main ( ) ;

}

void 
show_winner (void)
{

/*- Suivant les modes on utilise differentes fins... -*/
  if (MAXIMUM == 1)
    show_single_winner ();
  else
    show_multiple_winner ();

/*- Victoire en mode un joueur -*/
  if (MAXIMUM == 1)
    do_high_score ();
/*- Mode multiplayer -*/
  else
    hs_victory ();

}

void 
init_all_the_mem (void)
{
  int courant;
#ifdef DEBUG
  printf ("Initing memory\n");
#endif
  MAXIMUM = 1;
  hs_reset_victory ();
  for (courant = 0; courant < MAXPLAYERS; courant++)
    {
      names[courant] = (char *) calloc (sizeof (char), strlen ("N°i") + 1);
      strcpy (names[courant], "N°i");
      machines[courant] = (char *) calloc (sizeof (char), strlen ("") + 1);
      strcpy (machines[courant], "");
      names[courant][2] = chiffre[courant];
    }
}

/*- Liberation des ressources X -*/
void 
close_all_windows (void)
{
  int courant, i;

  spy_free ();
  for (courant = 0; courant < MAXIMUM; courant++)
      {
	  XUnmapWindow (canal_aff[courant], fenetre[courant]);
	  for (i = 0; i < PIXMAX; i++) {
	      XFreePixmap (canal_aff[courant], sprite_img[courant][i].data);
	      XFreePixmap (canal_aff[courant], sprite_img[courant][i].mask);
	  }
	  XDestroyWindow (canal_aff[courant], fenetre[courant]);
	  XFreeGC (canal_aff[courant], gc[courant]);
	  XCloseDisplay (canal_aff[courant]);
      }
}

/*- Liberation de la memoire de type: char * malloc -*/
void 
free_all_the_mem ()
{
  int courant;

#ifdef DEBUG
  printf ("Freeing memory\n");
#endif

  /* Liberation de la memoire, ya encore du boulot... */
  for (courant = 0; courant < MAXPLAYERS; courant++)
    {
/*- Ce que moi j'ai utilise -*/
	free (machines[courant]);
	free (names[courant]);
    }
}
