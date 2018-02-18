#include "config.h"

#define IS_A_NAME 1
#define IS_A_DISP 2
#define SPEEDNB 6
#define STARTSPEED 3

char speedch[][SPEEDNB] =
{"dead",
 "hard",
 "fun!",
 "cool",
 "nice",
 "easy"};

#define WIDTHNB 11
char widthch[][WIDTHNB] =
{ " 0",
  " 1",
  " 2",
  " 3",
  " 4",
  " 5",
  " 6",
  " 7",
  " 8",
  " 9",
  "10",
  "11",
  "12",
  "13" /*- Il paraitrait que ca porte malheur-*/ };

/*- Machine bourrin genre Pentium ou ultraSparc... -*/
int speedval[SPEEDNB] =
{5000, 10000, 25000, 50000, 75000, 100000};

int sv;
/*- La valeur de la vitesse dans le tableau -*/

widwindow *fen;

/*- 1° partie -*/
widget *quitb, *playb, *teamc, *nbplayers, *plusb, *moinsb, *reset;
widget *speedb, *pluss, *moinss;
widget *teami, *inci, *incc;
widget *piecesc;
widget *playi,*speedi;
widget *handicp,*handim,*handinf;
widget *width,*widthp,*widthm,*winf;
widget *tournp, *tournm, *tourni;
widget *timep, *timem, *timei;

/*- 2° partie -*/
widget *tinom,*poste,*equipe;

widget *noms[NOMBRE];
widget *display[NOMBRE];
widget *teams[NOMBRE];
widget *teamplus[NOMBRE];
widget *teammoins[NOMBRE];
widget *keysb[NOMBRE];


int sortir;
int RETOUR;
int SPEEDV;

void quitter( void ) { MAXIMUM=0; RETOUR=QUIT; sortir=1; }
void launch_game(void) { RETOUR=PLAY; sortir=1; }
void more_players(void) { if (MAXIMUM < MAXPLAYERS) MAXIMUM++; }
void less_players(void) { if (MAXIMUM >1) MAXIMUM--; }
void faster (void) { SPEEDV--; if (SPEEDV < 0) SPEEDV = 0; }
void slower (void) { SPEEDV++; if (SPEEDV >= SPEEDNB ) SPEEDV = SPEEDNB-1; }
void larger (void) { TAILLE_TAB_X++; if (TAILLE_TAB_X >= WIDTHNB) TAILLE_TAB_X--; }
void smaller (void) { TAILLE_TAB_X--; if (TAILLE_TAB_X < 3) TAILLE_TAB_X = 3; }
void longer_tournament(void) { TOURNOI ++ ; if ( TOURNOI > WIDTHNB -1 ) TOURNOI = WIDTHNB - 1 ; }
void shorter_tournament(void) { TOURNOI -- ; if ( TOURNOI <1 ) TOURNOI = 1 ; }
void higher(void) { if ( HANDICAP<8) HANDICAP++; }
void downer(void) {if (HANDICAP>0) HANDICAP--; }

void more_time ( void ) { if ( TIME < 10 ) TIME ++; else TIME=10; }
void less_time ( void ) { if ( TIME > 0 ) TIME --; else TIME = 0; }

/*- Cette fonction renvoie l'indice de la vitesse courante... -*/
int current_speed ( int SPEED ) {

    int i;

    i=0;
    while ( i < SPEEDNB ) {
	if ( speedval [ i ] == SPEED )
	    return i ;

	i++ ;
    }
    return STARTSPEED ;

}

/*- Cette fonction permet de choisir le mode de jeu... -*/
void 
do_sel_mode (void)
{
  TEAM_MODE = NO;
  SPEEDV = current_speed ( SPEED ) ;
  sortir = 0;
  RETOUR = QUIT;
  INCREASE_SPEED = NO;

/*- La fenetre -*/
  fen = widget_creer_fenetre ("", /*-"Welcome to TWINTRIS"-*/ say (SAY_BIENVENUE), 150, 225);
  quitb = widget_creer (BUTTON, fen, /*-"Quitter"-*/ say (SAY_QUITTER), 10, 35, 8);
  playb = widget_creer (BUTTON, fen, /*-"Jouer"-*/ say (SAY_JOUER), 10, 17, 8);

/*- Le bouton qui reset les victories -*/
  reset = widget_creer (BUTTON, fen, "Reset", 90, 17, 8);

/*- La check box  du mode team -*/
  teamc = widget_creer (CHEK_BOX, fen, "", 10, 75, 8);
  teami = widget_creer (INFO_ZONE, fen, say (SAY_EQUIPES), 20, 75, 12);

/*- La check Box pour Increase speed -*/
  incc = widget_creer (CHEK_BOX, fen, "", 10, 55, 8);
  inci = widget_creer (INFO_ZONE, fen, say (SAY_ACCEL), 20, 55, 14);

/*- La check box pour le mode pieces etendues -*/
  piecesc=widget_creer(CHEK_BOX,fen,"",10,95,8);
  (void*)widget_creer(INFO_ZONE,fen,"Ext.",20,95,4);

/*- Le nb de players -*/
  nbplayers = widget_creer (INFO_ZONE, fen, widthch[MAXIMUM], 90,115, 2);
  plusb = widget_creer (BUTTON, fen, "+ ",110,115, 2);
  moinsb = widget_creer (BUTTON, fen, " -", 65,115, 2);

/*- La vitesse -*/
  speedb = widget_creer (INFO_ZONE, fen, speedch[SPEEDV], 85, 135, 5);
  pluss = widget_creer (BUTTON, fen, ">>", 110, 135, 2);
  moinss = widget_creer (BUTTON, fen, " <", 65, 135, 2);

/*- Les messages -*/
  playi=widget_creer(INFO_ZONE,fen,"Players:",10,115,8);
  speedi=widget_creer(INFO_ZONE,fen,"Speed:",10,135,8);

  width=widget_creer(INFO_ZONE, fen, widthch[TAILLE_TAB_X], 90,155,2);
  widthp = widget_creer (BUTTON, fen, "+ ", 110, 155, 2);
  widthm = widget_creer (BUTTON, fen, " -", 65, 155, 2);

  handinf=widget_creer(INFO_ZONE, fen, widthch[TAILLE_TAB_X], 90,195,2);
  handicp = widget_creer (BUTTON, fen, "+ ", 110, 195, 2);
  handim = widget_creer (BUTTON, fen, " -", 65, 195, 2);


  winf=widget_creer(INFO_ZONE,fen,"Width:",10,155,6);
  winf=widget_creer(INFO_ZONE,fen,"Victory:",10,175,9);
  winf=widget_creer(INFO_ZONE,fen,"Handicap:",10,195,9);
  tournm=widget_creer(BUTTON,fen," -",65,175,2);
  tournp=widget_creer(BUTTON,fen,"+ ",110,175,2);
  tourni=widget_creer(INFO_ZONE,fen,widthch[HANDICAP],90,175,2);

  winf=widget_creer(INFO_ZONE,fen,"Time limit:",10,215,9);
  timem=widget_creer(BUTTON,fen," -",65,215,2);
  timep=widget_creer(BUTTON,fen,"+ ",110,215,2);
  timei=widget_creer(INFO_ZONE,fen,widthch[TIME],90,215,2);

  widget_on_click(quitb,quitter);
  widget_on_click(reset,hs_reset_victory);
  widget_on_click(playb,launch_game);
  widget_on_click(plusb,more_players);
  widget_on_click(moinsb,less_players);
  widget_on_click(pluss,faster);
  widget_on_click(moinss,slower);
  widget_on_click(widthm,smaller);
  widget_on_click(widthp,larger);
  widget_on_click(tournp,longer_tournament);
  widget_on_click(tournm,shorter_tournament);
  widget_on_click(handicp,higher);
  widget_on_click(handim,downer);

/*- Plus ou moins de temps -*/
  widget_on_click(timep,more_time);
  widget_on_click(timem,less_time);



  widget_afficher_fenetre (fen);

  widget_tout_afficher(fen);
  
  while (!sortir)
    {
/*- Affichage de la fenetre tout entiere -*/
 	widget_flush(fen);

/*- Attente d'une reaction de l'utilisateur -*/
	widget_prendre_info (nbplayers, widthch[MAXIMUM]);
	widget_prendre_info (speedb, speedch[SPEEDV]);
	widget_prendre_info (width, widthch[TAILLE_TAB_X]);
	widget_prendre_info (tourni,widthch[TOURNOI]);
	widget_prendre_info (handinf,widthch[HANDICAP]);
	widget_prendre_info (timei,widthch[TIME]);
	widget_event(fen);

    }

  ONE_PLAYER = NO;
  if (widget_is_selected (teamc)) TEAM_MODE = YES;
  else TEAM_MODE = NO;

  if ( widget_is_selected ( incc ) || ( MAXIMUM == 1 ) ) INCREASE_SPEED = YES;
  else INCREASE_SPEED = NO;

  if ( widget_is_selected ( piecesc ) ) MAXPIECES = PIECES_EXTENDED ;
  else MAXPIECES = PIECES_CLASSIC ;

  if ( MAXIMUM == 1 ) TOURNOI = 1 ;

/*- Destruction et fermeture de la premiere fenetre -*/
  widget_tout_detruire (fen);
  sortir = 0;

#ifdef DEBUG
  printf ("Freed\n");
#endif
}

void 
set_teams (void)
{
  int i;
  if (TEAM_MODE == NO)
    {
      for (i = 0; i < MAXIMUM; i++)
	team[i] = i + 1;
    }
  else
    {
      for (i = 0; i < MAXIMUM; i++)
	team[i] = i / 2 + 1;
    }
}

void team_moins(int i) {team[i]--; if(team[i]<0) team[i]=0; }
void team_plus (int i) {team[i]++; if(team[i]>9) team[i]=9; }

void 
do_sel_disp (void)
{

  set_teams ();

#ifdef DEBUG
  printf ("players:%d\n", MAXIMUM);
#endif

  if (MAXIMUM >= 1)
    {
      int i, SEL;

      SEL = IS_A_NAME;

      fen = widget_creer_fenetre ("", say (SAY_NOM) /*-"Choose your name"-*/ , 340,20 * MAXIMUM + 50);
      playb = widget_creer (BUTTON, fen, say (SAY_JOUER), 110, 20 * MAXIMUM + 40, 6);
      quitb = widget_creer( BUTTON, fen, say (SAY_QUITTER), 152 ,20 * MAXIMUM + 40, strlen(say (SAY_QUITTER)));
      widget_on_click(playb,launch_game);
      widget_on_click(quitb,quitter);

#ifdef DEBUG
      printf ("widget window creee\n");
#endif

      for (i = 0; i < MAXIMUM; i++)
	{
	  noms[i] = widget_creer (EDIT_BOX, fen, names[i], 10, i * 20 + 40, 15);
	  display[i] = widget_creer (EDIT_BOX, fen, machines[i], 120, i * 20 + 40, 20);
	  teams[i] = widget_creer (INFO_ZONE, fen, widthch[team[i]], 270, i * 20 + 40, 2);
	  teammoins[i] = widget_creer (BUTTON, fen, " -", 255, i * 20 + 40, 2);
	  teamplus[i] = widget_creer (BUTTON, fen, "+ ", 285, i * 20 + 40, 2);

	  keysb[i] = widget_creer ( BUTTON , fen , "Keys" ,305, i*20 + 40 , 4 );
	}
      tinom=widget_creer (INFO_ZONE,fen,"Nom:",10,20,4);
      poste=widget_creer (INFO_ZONE,fen,"Display:",120,20,8);
      equipe=widget_creer (INFO_ZONE,fen,"Eq:",270,20,3);

      widget_afficher_fenetre (fen);
      widget_tout_afficher (fen);

      while (!sortir) {

	  widget_flush(fen);
	  widget_event (fen);
	  
	  switch (action_type (fen)) {  
	  case ACTION_CLICK:
	      for (i = 0; i < MAXIMUM; i++) {
		  if (widget_click (teammoins[i])) team_moins(i);
		  if (widget_click (teamplus[i])) team_plus(i);
		  if (widget_click (keysb[i])) keys_set_players_keys(i);
		  widget_prendre_info (teams[i], widthch[team[i]]);
	      }
	      widget_tout_afficher (fen);
	      break;
	  default:
	      break;
	  } /*- fin du switch -*/
      } /*- Fin while(!sortir) -*/
      
      /*- Liberation et recuperation -*/
      for (i = 0; i < MAXIMUM; i++)
	{
/*- team[i] est deja a la page... -*/
	    if (names[i]) free(names[i]);
	    names[i] = widget_copier_info (noms[i]);
	    if (machines[i]) free(machines[i]);
	    machines[i] = widget_copier_info (display[i]);
	}
/*- Fin for(i=0;... -*/
      widget_tout_detruire (fen);
    }
/*- Fin if(MAXIMUM>1) -*/

  SPEED = speedval[SPEEDV];

#ifdef DEBUG
  printf ("SPEEDV:%d\n", SPEEDV);
  printf ("SPEED :%d\n", SPEED);
#endif
}

int 
make_config (void)
{
  do_sel_mode ();

  if (RETOUR != QUIT)
      do_sel_disp ();

  return RETOUR;
}






