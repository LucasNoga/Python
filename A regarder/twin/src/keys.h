/*- Ce module permet de personnaliser les touches des joueurs . -*/
/*- On va commencer par tout les joueurs ont les memes touches.
Puis tout les joueurs auront des touches privees avec des profils. -*/

#ifndef __K3ys__
#define __K3ys__

/*- Les includes -*/
#include "constantes.h"
#include "widget.h"
#include "graphics.h"

/*- Les differentes touches -*/
enum ETypeDeTouche {
    Gauche ,
    Droite ,
    RotationGauche ,
    RotationDroite ,
    Descente ,
    Flash ,
    Quitter ,
    Abandon
};
typedef enum ETypeDeTouche TypeDeTouche ;

KeyPressedCode Touches [ 8 ][ NOMBRE ];

/*- Les fonctions de modification des touches -*/
void keys_set_players_keys ( int player );

void keys_set_all_keys ( void );

#endif
