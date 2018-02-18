#ifndef __WIDGET_H__DALOX__
#define __WIDGET_H__DALOX__

#include <stdio.h>
#include <stdlib.h>
#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <X11/keysym.h>

/*- Les differents types de widget -*/
#define NOTHING        0
#define BUTTON         1
#define PICTURE        2
#define EDIT_BOX       3
#define RADIO          4
#define CHEK_BOX       5
#define SELECT         6
#define MENU           7
#define INFO_ZONE      8

/*- Les differents types d'action utilisateur -*/
#define NO_ACTION      0
#define ACTION_CLICK   1
#define ACTION_TOUCHE  2
#define FOCUS_CHANGE   4

/*- Selected or not -*/
#define SELECTED       1
#define UNSELECTED     0

/*- La structure de fenetre -*/
struct SWidWindow;
typedef struct SWidWindow widwindow;

/*- Celle d'objet -*/
struct SWidget;
typedef struct SWidget widget;

typedef KeySym KeyPressedCode;

/*- Flush -*/
void widget_flush( widwindow *fen );

/*- Creation et affichage des structures -*/
widwindow *widget_creer_fenetre (char *display, char *title, int x, int y);
void widget_afficher_fenetre (widwindow * moi);
void widget_tout_detruire (widwindow *moi);
void widget_tout_afficher (widwindow *moi);
widget *widget_creer (int type, widwindow * motherwin, char *valeur,
		      int px,int py,int size);
void widget_on_click(widget *moi,void(*func)(void));

/*- Interractions -*/
void widget_update (widwindow * mom);
void widget_event (widwindow * mom);
void widget_appuyer_bouton ( widget * moi ) ;
void widget_reset ( widget * moi );

int widget_click (widget * moi);
void widget_update_texte (widwindow *fen);
int action_type(widwindow *fen);
KeyPressedCode widget_key_pressed ( widwindow * moi );

/*- Recuperation de l'information -*/
int widget_is_selected (widget * moi);

char *widget_donner_info (widget * moi);
char *widget_copier_info (widget * moi);
void widget_prendre_info (widget * moi, char *info);

#endif
