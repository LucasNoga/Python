#ifndef __CONSTANTES__
#define __CONSTANTES__

#include <unistd.h>

/*- Pour les fichiers -*/
#define DIR "pixart"

/*- Specificite du niveau -*/
#define YPIECE 1
#define XPIECE 0
#define DEPART_PIECE 1

/*- Etat du joueur courant -*/
#define ENCORE_EN_COURSE 1
#define PERDU 0


/*- Position de la fenetre -*/
#define FEN_X 100
#define FEN_Y 100

/*- Nombre de pixmaps par joueur -*/
#define PIXMAX   13
#define BACK_PIX 0
#define BL_BCK   1
#define SPY_BCK  2

/*- eh ben non, c'est pas des constantes ces deux la,
 mais ici au moins je suis tranquille -*/
int MAXIMUM;
/*- nb player -*/
int SPEED;
/*- vitesse de jeu -*/
int MAXPIECES;
/*- Nombre de pieces en jeu Default:7 -*/

/*- Nombre de parties d'un tournoi... -*/
int TOURNOI;
/*- Handicap de depart -*/
int HANDICAP;
/*- Temps de la partie : en secondes -*/
int TIME;


#define PIECES_CLASSIC 7   /*- Tetris classique -*/
#define PIECES_EXTENDED 10 /*- Utilisations des pieces etendues. -*/

/*- True or False -*/
#define QUIT 0
#define PLAY 1

/*- True or False, en plus clair -*/
#define YES 1
#define NO 0

/*- Langage -*/
#define FR 0
#define GB 1

/*- Pour la config -*/
int TEAM_MODE;
int ONE_PLAYER;

/*- Gestion de la vitesse -*/
#define PERCENT 15

/*- Gestion du plafond de changement de level -*/
#define SCORE_FLOOR 2000

/*- Position du niveau dans l'ecran -*/
#define LEVELX
#define LEVELY

/*- Pour la ligne de commande -*/
int BGMODE;
int LANG;
int SPY;
int MAXPLAYERS;


/*- Bientot disparu -*/
#define ECART_ENTRE_SPYS 5
#define ECART_TOP_WINDOW 5
#define ECART_BOT_WINDOW 15
#define SPY_POS_NOM_Y 7
#define SPY_HAUTEUR_FENETRE 150

/*- Mode debuggage -*/
/*- #define DEBUG -*/


/*- Pour le theme support -*/

/*- Nombre maximal de players -*/
#define NOMBRE 8

#define MAX_TAB_X 10
#define MAX_TAB_Y 20

/*------------Ne pas sortir de #define-------------------*/

/*- Specificite des pieces et du niveau -*/
int TAILLE_CARRE;
int TAILLE_TAB_X;
int TAILLE_TAB_Y;

/*- Position du tableau de jeu -*/
int OFFSET_X;
int OFFSET_Y;

/*- La piece suivante -*/
int PSUIVANTEX;
int PSUIVANTEY;

/*- Affichage du score -*/
int SCOREX;
int SCOREY;

/*- Affichage du temps -*/
int TIMEX;
int TIMEY;

/*- Affichage des lignes -*/
int LIGNEX;
int LIGNEY;

/*- Coordonnees d'affichage des messages -*/
int MESSAGEX;
int MESSAGEY;

/*- Dimension de ma fenetre -*/
int FEN_W;
int FEN_H;

/*- Deux ou trois constantes du spyscreen -*/
int TAILLE_PETIT_CARRE;

/*- Les positions des fenetres espions: -*/
int SPYX[NOMBRE];
int SPYY[NOMBRE];

/*- Et celles des noms, sous les fenetres espions -*/
int SPYNX[NOMBRE];
int SPYNY[NOMBRE];

#endif
