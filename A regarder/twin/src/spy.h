/*- Module de gestion des espion,
  Ce module affiche une petite fenetre dans laquelle on peut voir affiche
  les ecrans des autres joueurs -*/

#ifndef __SPY_H__
#define __SPY_H__

#include <stdio.h>
#include <stdlib.h>

#include "graphics.h"   /*- On en a besoin pour chopper les displays -*/
#include "constantes.h" /*- On en a toujours besoin -*/

void spy_init ( void );

void spy_update ( int i );

void spy_expose ( int i );

void spy_win ( int i );

void spy_free ( void );

#endif
