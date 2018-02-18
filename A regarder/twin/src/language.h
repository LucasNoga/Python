


#ifndef __LANG_H__
#define __LANG_H__

#include <stdio.h>
#include <stdlib.h>

#include "constantes.h"

#define SAY_BIENVENUE 0
#define SAY_NOM 1
#define SAY_JOUER 2
#define SAY_QUITTER 3
#define SAY_ACCEL 4
#define SAY_EQUIPES 5
#define SAY_SCORE 6
#define SAY_LIGNES 7
#define SAY_BIEN 8
#define SAY_PASBIEN 9
#define SAY_GAGNE 10
#define SAY_PERDU 11
#define SAY_VAINQUEUR 12
#define SAY_ELIMINE 13
#define SAY_FROM 14
#define SAY_SPACE 15
#define SAY_RECORD 16
#define SAY_REC 17
#define PHRASEMAX 18

char *say (int phrase);

#endif
