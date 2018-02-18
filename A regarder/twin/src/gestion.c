#include "gestion.h"

/* Ligne pleine */
int 
GFilledLine (int tab[MAX_TAB_X][MAX_TAB_Y], int ligne)
{
  int resultat, colonne;
  resultat = 1;
  for (colonne = 0; colonne < TAILLE_TAB_X; colonne++)
    {
      resultat = resultat && (tab[colonne][ligne] != 0);
    }
  return resultat;
}

/* Rotation d'une boite */
void 
GRotatePoint (int *x, int *y)
{
  int xx, yy;
  xx = (-1) * (*y);
  yy = (*x);
  *x = xx;
  *y = yy;
}
void 
GRotateBackPoint (int *x, int *y)
{
  int xx, yy;
  xx = (*y);
  yy = (-1) * (*x);
  *x = xx;
  *y = yy;
}

/* 90 deg vers la droite */
void 
GRotatePiece (twintris *moi)
{
  int i;
  for (i = 0; i < moi->nb_blocks; i++)
    GRotatePoint (&((moi->positions)[i][XPIECE]), &(moi->positions[i][YPIECE]));
}

void 
GRotateBackPiece (twintris *moi)
{
  int i;

  for (i = 0; i < moi->nb_blocks; i++)
    GRotateBackPoint (&(moi->positions[i][XPIECE]), &(moi->positions[i][YPIECE]));
}

/* Initialise les nouvelles pieces */
void 
GCreatePiece (twintris *moi)
{
  int alea;

#ifdef DEBUG
  printf("Dereferencing\n");
#endif

  alea = 1 + rand () % MAXPIECES;
  moi->couleur = alea;

#ifdef DEBUG
  printf("Made the color part\n");
#endif

  if (alea == 1)
    {
/* Le T */
      moi->positions[0][XPIECE] = 0;
      moi->positions[0][YPIECE] = 0;
      moi->positions[1][XPIECE] = (-1);
      moi->positions[1][YPIECE] = 0;
      moi->positions[2][XPIECE] = 1;
      moi->positions[2][YPIECE] = 0;
      moi->positions[3][XPIECE] = 0;
      moi->positions[3][YPIECE] = (-1);
      moi->nb_blocks=4;
    }

  if (alea == 2)
    {
/* Le I */
      moi->positions[0][XPIECE] = 0;
      moi->positions[0][YPIECE] = (-1);
      moi->positions[1][XPIECE] = 0;
      moi->positions[1][YPIECE] = 0;
      moi->positions[2][XPIECE] = 0;
      moi->positions[2][YPIECE] = 1;
      moi->positions[3][XPIECE] = 0;
      moi->positions[3][YPIECE] = 2;
      moi->nb_blocks=4;
    }

  if (alea == 3)
    {
/* Le L a l'envers */
      moi->positions[0][XPIECE] = 0;
      moi->positions[0][YPIECE] = 1;
      moi->positions[1][XPIECE] = 0;
      moi->positions[1][YPIECE] = 0;
      moi->positions[2][XPIECE] = 0;
      moi->positions[2][YPIECE] = (-1);
      moi->positions[3][XPIECE] = 1;
      moi->positions[3][YPIECE] = (-1);
      moi->nb_blocks=4;
    }

  if (alea == 4)
    {
/* Le L */
      moi->positions[0][XPIECE] = 0;
      moi->positions[0][YPIECE] = 1;
      moi->positions[1][XPIECE] = 0;
      moi->positions[1][YPIECE] = 0;
      moi->positions[2][XPIECE] = 0;
      moi->positions[2][YPIECE] = (-1);
      moi->positions[3][XPIECE] = (-1);
      moi->positions[3][YPIECE] = (-1);
      moi->nb_blocks=4;
    }

  if (alea == 5)
    {
/* Le carre */
      moi->positions[0][XPIECE] = 0;
      moi->positions[0][YPIECE] = 0;
      moi->positions[1][XPIECE] = 0;
      moi->positions[1][YPIECE] = 1;
      moi->positions[2][XPIECE] = 1;
      moi->positions[2][YPIECE] = 0;
      moi->positions[3][XPIECE] = 1;
      moi->positions[3][YPIECE] = 1;
      moi->nb_blocks=4;
    }

  if (alea == 6)
    {
/* La salete */
      moi->positions[0][XPIECE] = 0;
      moi->positions[0][YPIECE] = 0;
      moi->positions[1][XPIECE] = 0;
      moi->positions[1][YPIECE] = 1;
      moi->positions[2][XPIECE] = 1;
      moi->positions[2][YPIECE] = 0;
      moi->positions[3][XPIECE] = (-1);
      moi->positions[3][YPIECE] = 1;
      moi->nb_blocks=4;
    }

  if (alea == 7)
    {
/* L'autre salete */
      moi->positions[0][XPIECE] = 0;
      moi->positions[0][YPIECE] = 0;
      moi->positions[1][XPIECE] = 0;
      moi->positions[1][YPIECE] = 1;
      moi->positions[2][XPIECE] = (-1);
      moi->positions[2][YPIECE] = 0;
      moi->positions[3][XPIECE] = 1;
      moi->positions[3][YPIECE] = 1;
      moi->nb_blocks=4;
    }
  if (alea == 8)
    {
      moi->positions[0][XPIECE] = 0;
      moi->positions[0][XPIECE] = 0;
      moi->positions[0][YPIECE] = 0;
      moi->positions[1][XPIECE] = 0;
      moi->positions[1][YPIECE] = 1;
      moi->positions[2][XPIECE] = (-1);
      moi->positions[2][YPIECE] = 0;
      moi->nb_blocks=3;
    }
  if (alea == 9)
    {
      moi->positions[0][XPIECE] = 0;
      moi->positions[0][YPIECE] = 0;
      moi->positions[1][XPIECE] = 0;
      moi->positions[1][YPIECE] = 1;
      moi->positions[2][XPIECE] = 0;
      moi->positions[2][YPIECE] = (-1);
      moi->positions[3][XPIECE] = 1;
      moi->positions[3][YPIECE] = 1;
      moi->positions[4][XPIECE] = 1;
      moi->positions[4][YPIECE] = (-1);
      moi->nb_blocks=5;
    }
  if (alea == 10)
    {
      moi->positions[0][XPIECE] = 0;
      moi->positions[0][YPIECE] = 0;
      moi->positions[1][XPIECE] = 0;
      moi->positions[1][YPIECE] = 1;
      moi->positions[2][XPIECE] = 0;
      moi->positions[2][YPIECE] = (-1);
      moi->positions[3][XPIECE] = 1;
      moi->positions[3][YPIECE] = 1;
      moi->positions[4][XPIECE] = (-1);
      moi->positions[4][YPIECE] = 1;
      moi->nb_blocks=5;
    }
#ifdef DEBUG
  printf("Sortie de la boule de generation de piece\n");
#endif

}

/* Piece dans le tableau?? */
int 
GPieceOut (twintris moi, int posx, int posy)
{
  int i;
  int resultat;

  resultat = 0;
  for (i = 0; i < moi.nb_blocks; i++)
    resultat = resultat ||
      ((posy + moi.positions[i][YPIECE]) >= (TAILLE_TAB_Y)) ||
      ((posx + moi.positions[i][XPIECE]) < 0) ||
      ((posx + moi.positions[i][XPIECE]) >= (TAILLE_TAB_X));
#ifdef DEBUG
  printf("GPieceOut:%d\n",resultat);
#endif
  return resultat;
}

/* Deux pieces superposees?? */
int 
GPieceBlocked (int tableau[MAX_TAB_X][MAX_TAB_Y], twintris moi, int posx, int posy)
{
  int i;
  int resultat;
  resultat = 0;
  for (i = 0; i < moi.nb_blocks ; i++)
    {
      resultat = resultat ||
	((tableau[posx + (moi.positions)[i][XPIECE]][posy + (moi.positions)[i][YPIECE]]) != 0);
    }
#ifdef DEBUG
  printf("GPieceBlocked:%d\n",resultat);
#endif
  return resultat;
}

/* Creation d'une ligne aleatoire */
void 
GRemplitLigne (int tab[][MAX_TAB_X][MAX_TAB_Y], int entier)
{
  int i;
  for (i = 1; i < TAILLE_TAB_X; i++)
    *tab[i][0] = entier;
}

/* Decale le tableau d'une ligne vers le haut */
void 
GDecaleTableauUp (int tab[][MAX_TAB_X][MAX_TAB_Y])
{
  int i, j;
  for (i = 1; i < TAILLE_TAB_Y; i++)
    for (j = 0; j < TAILLE_TAB_X; j++)
      (*tab)[j][i - 1] = ((*tab)[j][i]);
  for (j = 0; j < TAILLE_TAB_X; j++)
    (*tab)[j][TAILLE_TAB_Y - 1] = rand () % 2;
}





























