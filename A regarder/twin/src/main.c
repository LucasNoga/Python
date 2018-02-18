/*- C'est dalox le bot -*/

#include <stdio.h>
#include <stdlib.h>
#include "constantes.h"
#include "twin.h"
#include "config.h"
#include "theme.h"

/* Ya de fortes chances que ca soit mieux en globales... */
time_t t;

int 
main (int argc, char **argv)
{
  int sortir = 0;

  int nb;

  /* Initialisation du generateur de nombre aleatoire */
  srand ((unsigned) time (&t));

/*- Initialiser toutes les variables a "" -*/
/*- names et machines -*/

  process_command_line (argc, argv);

#ifdef DEBUG
	printf(" Command line done\n");
#endif
  theme_set ("theme");

#ifdef DEBUG
	printf("Theme setted, SPYMODE:%d\n",SPY);
#endif

/*- Mettre MAXIMUM a 1 et tout les victory a 0 -*/
  init_all_the_mem ();

#ifdef DEBUG
  printf("SPY_MODE:%d\n",SPY);
#endif

  keys_set_all_keys ( ) ;

  while (!sortir) {

      sortir = 0;
      nb = 0;

      /*- Configuration de la partie -*/
      if (!make_config ())
	  sortir = 1;
	    

      /*- Creation des structures -*/
      if (!sortir)
	  init_all_windows ();
      
      /*- Debut du mode tournoi -*/
      while ( nb < TOURNOI && !sortir ) {
	  
	  /*- Ready, goooooooooooooo! -*/
	  if (!sortir)
	      intro ();

	  /*- Le jeu -*/
	  if (!sortir)
	      if (!run_game (argc, argv))
		  sortir = 1;
	  /*- Quitter -*/
	  
	  /*- Bien joue au vainqueur -*/
	  if (!sortir)
	      show_winner (); /*- Affichage des scores ;-*/
	  
	  nb++; /*- Incrementer le nombre de parties jouees -*/
      }/*- Fin du mode tournoi -*/

      if (!sortir)
	  close_all_windows ();

    }
/*- EndWhile -*/

  free_all_the_mem ();

  return (0);
}
