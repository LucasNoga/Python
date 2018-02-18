#include "my_time.h"

int TIME_COUNT ;
time_t TIME_instant_zero , TIME_instant_t ;
int TIME_chrono ;

/*- Mise a zero du compteur -*/
/*- Demarrage du Compte a rebours -*/
void time_set_counter ( int secondes ) {

  if ( secondes != 0 ) {

    TIME_COUNT = secondes ;

    time ( & TIME_instant_zero ) ;

    TIME_chrono = 1 ;

  } else TIME_chrono = 0 ;

}


/*- Temps ecoule depuis la mise a zero du compteur ( resultat en secondes ) -*/
int time_temps_ecoule ( void ) {

    time ( & TIME_instant_t ) ;

    return ( difftime ( TIME_instant_t , TIME_instant_zero ) ) ;

}

/*- Compte a rebours termine? -*/
int time_out_of_time ( void ) {

  if ( TIME_chrono ) {

    time ( & TIME_instant_t ) ;

    return ( difftime ( TIME_instant_t , TIME_instant_zero ) >= TIME_COUNT ) ;

  } else return 0 ;

}

int time_temps_restant ( void ) {

  return ( TIME_COUNT - time_temps_ecoule ( ) ) ;

}
