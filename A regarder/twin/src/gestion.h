#ifndef __GESTION_H__
#define __GESTION_H__






#include <stdio.h>
#include <stdlib.h>
#include "constantes.h"

#define NB_BLOCKS_IN_TRIS 6

struct STwintris {
    int nb_blocks;
    int positions[NB_BLOCKS_IN_TRIS][2];
    int couleur;
};
typedef struct STwintris twintris;


/* Gestion du niveau */
int tableau[NOMBRE][MAX_TAB_X][MAX_TAB_Y];
twintris pieces_courante[NOMBRE], pieces_suivante[NOMBRE];

/* gestion des joueurs */
int positionx[NOMBRE], positiony[NOMBRE];
int lastpx[NOMBRE], lastpy[NOMBRE];
int etat[NOMBRE];
int speed[NOMBRE];
int lignes[NOMBRE], team[NOMBRE], score[NOMBRE], tetris[NOMBRE], victory[NOMBRE],
  vertical_speed[NOMBRE], joueurs_restants, choix_effectue, play_again;

int INCREASE_SPEED;

int GFilledLine (int tab[TAILLE_TAB_X][TAILLE_TAB_Y], int ligne);
void GRotatePoint (int *x, int *y);
void GRotateBackPoint (int *x, int *y);
void GRotatePiece (twintris *moi);
void GRotateBackPiece (twintris *moi);
void GCreatePiece(twintris *moi);
int GPieceOut (twintris moi, int posx, int posy);
int GPieceBlocked (int tableau[TAILLE_TAB_X][TAILLE_TAB_Y], twintris moi, int posx, int posy);
void GRemplitLigne (int tab[][TAILLE_TAB_X][TAILLE_TAB_Y], int entier);
void GDecaleTableauUp (int tab[][TAILLE_TAB_X][TAILLE_TAB_Y]);

#endif
