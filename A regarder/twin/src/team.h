#ifndef __TEAM__H__
#define __TEAM__H__

#include <stdio.h>
#include <stdlib.h>

#include "constantes.h"
#include "gestion.h"

#define DEJAPASSE 1
#define PASENCORE 0

int nb_team ();
void init_team (void);
int nb_gars (int mon_team);
int nb_gars_restant (int mon_team);
int nb_team_restants ();
void eliminer (int joueur);
int winner_team ();

#endif
