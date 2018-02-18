#ifndef ___TIME_dalox_
#define ___TIME_dalox_

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

/*- Mise a zero du compteur -*/
/*- Compte a rebours -*/
void time_set_counter ( int secondes ) ;

/*- Temps ecoule depuis la mise a zero du compteur ( resultat en secondes ) -*/
int time_temps_ecoule ( void ) ;

/*- Compte a rebours termine? -*/
int time_out_of_time ( void ) ;

/*- Temps restant avant expiration du chronometre -*/
int time_temps_restant ( void ) ;

#endif
