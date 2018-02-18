#include "keys.h"

char *message[8] = {
    "Gauche",
    "Droite",
    "Rotation Gauche",
    "Rotation Droite",
    "Descente",
    "Descente rapide",
    "Quitter",
    "Abandon"
};

int barrer = 0 ;

void quitter_keys ( void ) {

    barrer = 1 ; 

}

void keys_set_keys ( TypeDeTouche that_key , KeyPressedCode * keycode , widwindow * keyfen ) {

    KeyPressedCode choix ;

    choix = *keycode;

    while ( !barrer ) {

	widget_flush ( keyfen ) ;

#ifdef DEBUG
	printf("Dans la boucle barrer vaut:%d\n",barrer);
#endif

	if ( widget_key_pressed ( keyfen ) ) {

	    choix = widget_key_pressed ( keyfen ) ;

	    if ( XKeysymToString ( choix ) != NULL ) {

		barrer = 1 ;

	    }

	}

	widget_event ( keyfen ) ;

    }


    barrer = 0 ;

    if ( choix != 0 ) *keycode = choix ;


}

void keys_load_keys ( FILE * entree ) {

/*- Penser a utiliser XKeysymToString.
Dans un fichier de profil, on store la String correspondant au Keysym... -*/

}

void keys_set_default_keys ( int player ) {

    Touches [ Gauche ][ player ] =         XK_Left ;
    Touches [ Droite ][ player ] =         XK_Right ;
    Touches [ RotationDroite ][ player ] = XK_g ;
    Touches [ RotationGauche ][ player ] = XK_space ;
    Touches [ Abandon ][ player ] =        XK_a ;
    Touches [ Quitter ][ player ] =        XK_q ;
    Touches [ Flash ][ player ] =          XK_Up ;
    Touches [ Descente ][ player ] =       XK_Down ;

}

void keys_set_all_keys ( void ) {

    int i;

    for (i = 0 ; i < NOMBRE ; i++ )

	keys_set_default_keys ( i ) ;

}

void keys_set_players_keys ( int player ) {

    widwindow * keyfen ;
    widget *up , *down , *left , *right ,
	*quit , *giveup , *rleft , *rright ;
    widget *finished ; int i;

    barrer = 0 ;

    keyfen = widget_creer_fenetre ( "" , "Choose your keys" ,
				    173 , 210 ) ;

    for ( i = 0 ; i < 8 ; i ++ )

	( void )widget_creer ( INFO_ZONE , keyfen , message [ i ] , 10 , 45 + i * 20 , strlen ( message [ i ] ) ) ;

    ( void ) widget_creer ( INFO_ZONE , keyfen , "Click to set a key:" , 10 , 20 , 33 ) ;

    finished = widget_creer ( BUTTON , keyfen , " Done " , 10 , 205 , 6 ) ;
    widget_on_click ( finished , quitter_keys ) ;

    up = widget_creer ( BUTTON , keyfen , XKeysymToString ( Touches [ Flash ] [ player ] ) , 110 , 145 , 8 );
    down = widget_creer ( BUTTON , keyfen , XKeysymToString ( Touches [ Descente ] [ player ] ) ,110 , 125 , 8 );
    left = widget_creer ( BUTTON , keyfen , XKeysymToString ( Touches [ Gauche ] [ player ] ) , 110 , 45 , 8 );
    right = widget_creer ( BUTTON , keyfen , XKeysymToString ( Touches [ Droite ] [ player ] ) , 110 , 65 , 8 );

    quit = widget_creer ( BUTTON , keyfen , XKeysymToString ( Touches [ Quitter ] [ player ] ) , 110 , 165 , 8 );
    giveup = widget_creer ( BUTTON , keyfen , XKeysymToString ( Touches [ Abandon ] [ player ] ) , 110 , 185 , 8 );
    rleft = widget_creer ( BUTTON , keyfen , XKeysymToString ( Touches [ RotationGauche ] [ player ] ) , 110 , 85 , 8 );
    rright = widget_creer ( BUTTON , keyfen , XKeysymToString ( Touches [ RotationDroite ] [ player ] ) , 110 , 105 , 8 );

    widget_afficher_fenetre ( keyfen ) ;
    widget_tout_afficher ( keyfen ) ;

    while (!barrer) {
	widget_flush ( keyfen ) ;
	widget_event ( keyfen ) ;

	switch (action_type (keyfen)) {  
	case ACTION_CLICK:

	    if ( widget_click ( up ) ) {
		widget_appuyer_bouton ( up ) ;
		keys_set_keys ( Flash , & ( Touches [ Flash ] [ player ] ) , keyfen );
	        widget_prendre_info ( up , XKeysymToString ( Touches [ Flash ] [ player ] ) ) ;
		widget_reset ( up ) ;
	    }
	    else if ( widget_click ( down ) ) {
		widget_appuyer_bouton ( down ) ;
		keys_set_keys ( Descente , & ( Touches [ Descente ] [ player ] ) , keyfen );
		widget_prendre_info ( down , XKeysymToString ( Touches [ Descente ] [ player ] ) ) ;
		widget_reset ( down );
	    }
	    else if ( widget_click ( left ) ) {
		widget_appuyer_bouton ( left ) ;
		keys_set_keys ( Gauche , & ( Touches [ Gauche ] [ player ] ) , keyfen );
	        widget_prendre_info ( left , XKeysymToString ( Touches [ Gauche ] [ player ] ) ) ;
		widget_reset ( left );
	    }
	    else if ( widget_click ( right ) ) {
		widget_appuyer_bouton ( right ) ;
		keys_set_keys ( Droite , & ( Touches [ Droite ] [ player ] ) , keyfen );
	        widget_prendre_info ( right , XKeysymToString ( Touches [ Droite ] [ player ] ) ) ;
		widget_reset (right);
	    }
	    else if ( widget_click ( rleft ) ) {
		widget_appuyer_bouton ( rleft ) ;
		keys_set_keys ( RotationGauche , & ( Touches [ RotationGauche ] [ player ] ) , keyfen );
	        widget_prendre_info ( rleft , XKeysymToString ( Touches [ RotationGauche ] [ player ] ) ) ;
		widget_reset ( rleft );
	    }
	    else if ( widget_click ( rright ) ) {
		widget_appuyer_bouton ( rright ) ;
		keys_set_keys ( RotationDroite , & ( Touches [ RotationDroite ] [ player ] ) , keyfen );
	        widget_prendre_info ( rright , XKeysymToString ( Touches [ RotationDroite ] [ player ] ) ) ;
		widget_reset ( rright );
	    }
	    else if ( widget_click ( giveup ) ) {
		widget_appuyer_bouton ( giveup ) ;
		keys_set_keys ( Abandon , & ( Touches [ Abandon ] [ player ] ) , keyfen );
	        widget_prendre_info ( giveup , XKeysymToString ( Touches [ Abandon ] [ player ] ) ) ;
		widget_reset ( giveup ) ;
	    }
	    else if ( widget_click ( quit ) ) {
		widget_appuyer_bouton ( quit ) ;
		keys_set_keys ( Quitter , & ( Touches [ Quitter ] [ player ] ) , keyfen );
	        widget_prendre_info ( quit , XKeysymToString ( Touches [ Quitter ] [ player ] ) ) ;
		widget_reset ( quit );
	    }
	    widget_tout_afficher (keyfen);
	    break;

	  default:
	      break;
	} /*- fin du switch -*/
    } /*- Fin du while -*/

    widget_tout_detruire ( keyfen ) ;

    barrer = 0 ;

}




