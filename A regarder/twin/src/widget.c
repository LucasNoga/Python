

#include "widget.h"

#define YES 69
#define NO 69

int FOCUSED_EDIT_BOX;

void nop(void){
#ifdef DEBUG
    printf("Doing the Nop\n");
#endif
};

int 
min (int A, int B)
{
    return (A>B)?B:A;
}

int 
max (int A, int B)
{
    return (A>B)?A:B;
}

struct SWidevent
  {
    int type;
    int mouse_x;
    int mouse_y;
    char car;
    KeySym sym;
  };
typedef struct SWidevent widevent;


struct SWidWindow
{
  Display *can;
  Window fen;
  widwindow *next_window;
  Window rac;
  GC gc;
  XSizeHints inf;
  XEvent evenem;
  Colormap pal;
  int ecran;
  XWMHints wm;
  unsigned long black;
  unsigned long white;
  unsigned long fond;
  unsigned long clair;
  unsigned long fonce;
  XColor gris_fonce;
  XColor gris_clair;
  XColor bgcolor;
  widget *focus;
  widget *next;
  widevent *action;
  int skipframe;
};


struct SWidget
  {
    int type;
/*- BUTTON, EDIT_BOX, CHEK_BOX, RADIO ou PICTURE -*/
    int x;
    int y;
    int size;
    char *txt;
    int value;
    int selected;
    unsigned long bg;
    unsigned long fg;
    unsigned long abg;
    widwindow *fen;
    int ID;
    widget *next;
    void(*on_click)(void);
    int offset; /*- Si c'est une edit_box -*/
    int curseur;
  };


widevent *
widevent_creer (void)
{
  widevent *moi;
  moi = (widevent *) malloc (sizeof (widevent));
  return moi;
}

void 
widevent_detruire (widevent * moi)
{
    free (moi);
}

/*- Nettoyage du canal d'affichage -*/
void
widget_flush( widwindow *moi )
{
    XFlush(moi->can);
}

/*- Creation -*/
widwindow *
widget_creer_fenetre (char *display, char *title, int x, int y)
{
  widwindow *moi;
  moi = (widwindow *) malloc (sizeof (widwindow));

  moi->can = XOpenDisplay (display);
  if ( moi->can == NULL ) {
    fprintf(stderr,"Couldn't open display %s\n",display);
    exit(1);
  }


  moi->rac = DefaultRootWindow (moi->can);

  moi->inf.max_width = moi->inf.min_width = moi->inf.width = x;
  moi->inf.max_height = moi->inf.min_height = moi->inf.height = y;
  moi->inf.flags = PSize | PMinSize | PMaxSize;

  moi->wm.input = True;
  moi->wm.flags = InputHint;

  moi->ecran = DefaultScreen (moi->can);
  moi->white = WhitePixel (moi->can, moi->ecran);
  moi->black = BlackPixel (moi->can, moi->ecran);
  moi->pal = DefaultColormap (moi->can, moi->ecran);

  moi->skipframe = NO ;

  if (XParseColor (moi->can, moi->pal, "Grey90", &(moi->gris_clair)))
    {
      if (XAllocColor (moi->can, moi->pal, &(moi->gris_clair)))
	{
	  moi->clair = moi->gris_clair.pixel;
	}
    }
  else
    moi->clair = BlackPixel (moi->can, moi->ecran);
  if (XParseColor (moi->can, moi->pal, "Grey50", &(moi->gris_fonce)))
    {
      if (XAllocColor (moi->can, moi->pal, &(moi->gris_fonce)))
	{
	  moi->fonce = moi->gris_fonce.pixel;
	}
    }
  else
    moi->fonce = BlackPixel (moi->can, moi->ecran);
  if (XParseColor (moi->can, moi->pal, "Grey80", &(moi->bgcolor)))
    {
      if (XAllocColor (moi->can, moi->pal, &(moi->bgcolor)))
	{
	  moi->fond = moi->bgcolor.pixel;
	}
    }
  else
    moi->fond = BlackPixel (moi->can, moi->ecran);

  /* La fen */
  moi->fen = XCreateSimpleWindow (moi->can, moi->rac,
				  moi->inf.x, moi->inf.y,
				  moi->inf.width, moi->inf.height,
				  0, moi->white,	/* bordure */
				  moi->fond);	/* background */

  if ((moi->fen == BadMatch) ||
      (moi->fen == BadAlloc) ||
      (moi->fen == BadValue) ||
      (moi->fen == BadWindow))	/* Cherchez l'erreur */
    {
      fprintf(stderr,"Couldn't open window\n");
      exit (1);
    }

  XSelectInput (moi->can, moi->fen,
		ExposureMask | ButtonPressMask | KeyPressMask);
  XSetWMHints (moi->can, moi->fen,
	       &moi->wm);
  XSetStandardProperties (moi->can, moi->fen,
			  title, title, None, 0, 0, &moi->inf);

  /* Le contexte graphique */
  moi->gc = XCreateGC (moi->can, moi->fen, 0, 0);
  XSetBackground (moi->can, moi->gc, moi->white);
  XSetForeground (moi->can, moi->gc, moi->black);

  moi->next=NULL; /*- Position du chainage a zero -*/
  moi->focus=NULL; /*- Pas de focus pour le moment -*/

  moi->action=widevent_creer();

  return moi;
}


void 
widget_detruire_fenetre (widwindow * moi)
{
  XUnmapWindow (moi->can, moi->fen);
/*- Plus joli -*/
  widevent_detruire(moi->action);
  XDestroyWindow (moi->can, moi->fen);
  XFreeGC (moi->can, moi->gc);
  XCloseDisplay (moi->can);
  free (moi);
/*- Qd meme, j'allais pas oublier ca... -*/
}

Display *
widget_donner_canal ( widwindow * moi )
{
  return ( moi->can );
}

Window
widget_donner_fenetre ( widwindow * moi )
{
  return ( moi-> fen );
}

void 
widget_afficher_fenetre (widwindow * moi)
{
  XMapRaised (moi->can, moi->fen);
  XFlush (moi->can);
  widget_update(moi);
}

int action_type(widwindow *fen)
{
    return (fen->action->type);
}

void widget_on_click(widget *moi,void(*func)(void))
{
    moi->on_click=func;
}

widget *
widget_creer (int type, widwindow * fenwin, char *valeur,
	      int px,int py,int size)
{
  widget *moi;
  moi = (widget *) malloc (sizeof (widget));
  moi->type = type;
  moi->txt = (char *) calloc (sizeof (char), strlen (valeur) + 1);
  strcpy (moi->txt, valeur);
  moi->fen = fenwin;
  moi->selected = UNSELECTED;

  moi->next=moi->fen->next;
  moi->fen->next=moi;

  moi->x = px;
  moi->y = py;
  moi->size = size;

  moi->on_click=nop;

  if ( moi->fen->focus == NULL ) moi->fen->focus = moi ;

/*- Cas de la CHEK_BOX -*/
  if (type == CHEK_BOX && strcmp (valeur, "Selected") == 0)
    moi->selected = SELECTED;
  else if ( ( type == EDIT_BOX ) && ( moi->fen->focus == NULL ) ) {
      moi->fen->focus=moi;
  }

  moi->curseur = strlen (moi->txt);

  if (strlen (moi->txt) >= moi->size)
    moi->offset = strlen (moi->txt) - moi->size;
  else moi->offset = 0;

  return moi;
}

void 
widget_detruire (widget * moi)
{
  if (moi->txt != NULL)
    free (moi->txt);
    free (moi);
}


/*- Look and style -*/
void 
dessiner_cadre (int x, int y, int x2, int y2, widwindow * mom,
		unsigned long haut, unsigned long bas)
{
  XSetForeground (mom->can, mom->gc, haut);
  XDrawLine (mom->can, mom->fen, mom->gc,
	     min (x, x2), min (y, y2),
	     min (x, x2), max (y, y2));
  XDrawLine (mom->can, mom->fen, mom->gc,
	     min (x, x2), min (y, y2),
	     max (x, x2), min (y, y2));

  XSetForeground (mom->can, mom->gc, bas);
  XDrawLine (mom->can, mom->fen, mom->gc,
	     max (x, x2), max (y, y2),
	     min (x, x2), max (y, y2));
  XDrawLine (mom->can, mom->fen, mom->gc,
	     max (x, x2), max (y, y2),
	     max (x, x2), min (y, y2));
}

void
widget_dessiner_trait (widget *moi,unsigned long color)
{
  int font_h = 11;
  int font_w = 6;
  widwindow *mom;

  mom = moi->fen;

/*- Afficher le trait d'insertion -*/
  XSetForeground(mom->can,mom->gc,color);
  XDrawLine (mom->can,mom->fen,mom->gc,
	     font_w*moi->curseur/*-(strlen(moi->txt)-moi->offset)-*/+moi->x,moi->y,
	     font_w*moi->curseur/*-(strlen(moi->txt)-moi->offset)-*/+moi->x,moi->y-font_h);

}


void 
widget_encadrer_edit_box (widget * moi)
{
  int font_h = 11;
  int font_w = 6;
  widwindow *mom;

  mom = moi->fen;

  dessiner_cadre (moi->x - 2, moi->y + 3,
		  moi->x + font_w * moi->size + 2, moi->y - font_h - 2,
		  mom, mom->black, mom->black);

  widget_dessiner_trait(moi,mom->black);
}

void widget_encadrer ( widget * moi ) {

    if ( moi->type == EDIT_BOX )
	widget_encadrer_edit_box ( moi );
    else {}
}


void 
widget_decadrer (widget * moi)
{
  int font_h = 11;
  int font_w = 6;
  widwindow *mom;

  mom = moi->fen;
  dessiner_cadre (moi->x - 2, moi->y + 3,
		  moi->x + font_w * moi->size + 2, moi->y - font_h - 2,
		  mom, mom->fond, mom->fond);

  widget_dessiner_trait(moi,mom->white);
}

void 
afficher_bouton_normal (widget * moi)
{
  widwindow *mom;
  int font_w = 6;
  int font_h = 11;

  mom = moi->fen;

  dessiner_cadre (moi->x - 1, moi->y + 2, moi->x + moi->size * font_w + 1, moi->y - font_h - 1,
		  mom, mom->clair, mom->fonce);
  XSetForeground (mom->can, mom->gc, mom->black);
  XSetBackground (mom->can, mom->gc, mom->fond);
  XDrawImageString (mom->can, mom->fen, mom->gc,
		    moi->x, moi->y,
		    moi->txt, min (moi->size, strlen (moi->txt)));

}

void 
afficher_edit_box (widget * moi)
{
  widwindow *mom;
  int font_w = 6;
  int font_h = 11;

  mom = moi->fen;
/*- Dessiner le relief de la boite -*/
  dessiner_cadre (moi->x - 1, moi->y + 2, moi->x + moi->size * font_w + 1, moi->y - font_h - 1,
		  mom, mom->fonce, mom->clair);

/*- Afficher le texte -*/
  XSetForeground (mom->can, mom->gc, mom->black);
  XSetBackground (mom->can, mom->gc, mom->white);

  XDrawImageString (mom->can, mom->fen, mom->gc,
		    moi->x, moi->y,
		    moi->txt + moi->offset, min (moi->size, strlen (moi->txt)));

/*- Encadrer la boite selectionnee -*/
  if (moi==moi->fen->focus)
    widget_encadrer (moi);
  else
    widget_decadrer (moi);
}

void
widget_clear_edit_box (widget * moi)
{
  widwindow *mom;
  int font_w = 6;
  int font_h = 11;

  mom = moi->fen;
  dessiner_cadre (moi->x - 1, moi->y + 2, moi->x + moi->size * font_w + 1, moi->y - font_h - 1,
		  mom, mom->fonce, mom->clair);


  XSetForeground (mom->can, mom->gc, mom->fond);
  XSetBackground (mom->can, mom->gc, mom->fond);
  XDrawImageString (mom->can, mom->fen, mom->gc,
		    moi->x+1, moi->y,
		    moi->txt, moi->size);

}

void widget_clear_button ( widget * moi )
{
  widwindow *mom;

  int font_w = 6;
  int font_h = 11;

  mom = moi->fen;
  dessiner_cadre (moi->x - 1, moi->y + 2, moi->x + moi->size * font_w + 1, moi->y - font_h - 1,
		  mom, mom->fonce, mom->clair);
  XSetForeground (mom->can, mom->gc, mom->fond);
  XSetBackground (mom->can, mom->gc, mom->fond);
  XDrawImageString (mom->can, mom->fen, mom->gc,
		    moi->x, moi->y,
		    moi->txt, moi->size);
}

void widget_afficher_bouton_appuye ( widget * moi )
{
  widwindow *mom;

  int font_w = 6;
  int font_h = 11;

  mom = moi->fen;
  dessiner_cadre (moi->x - 1, moi->y + 2, moi->x + moi->size * font_w + 1, moi->y - font_h - 1,
		  mom, mom->clair, mom->fonce);
  XSetForeground (mom->can, mom->gc, mom->white);
  XSetBackground (mom->can, mom->gc, mom->white);
  XDrawImageString (mom->can, mom->fen, mom->gc,
		    moi->x, moi->y,
		    moi->txt, moi->size);
}

void afficher_bouton ( widget * moi ) {
     if ( moi -> selected ) widget_afficher_bouton_appuye ( moi ) ; 
     else afficher_bouton_normal ( moi ) ;
}

void widget_reset ( widget * moi ) {
    moi->selected = UNSELECTED ;
}

void widget_appuyer_bouton ( widget * moi ) {
    moi -> selected = SELECTED;
}

void
widget_clear_info_zone (widget * moi)
{
  widwindow *mom;

  mom = moi->fen;

  XSetBackground (mom->can, mom->gc, mom->fond);
  XSetForeground (mom->can, mom->gc, mom->fond);
  if (moi->txt)
    XDrawImageString (mom->can, mom->fen, mom->gc,
		      moi->x, moi->y,
		      moi->txt, moi->size);
}
void 
afficher_info_zone (widget * moi)
{
  widwindow *mom;

  mom = moi->fen;
  XSetBackground (mom->can, mom->gc, mom->fond);
  XSetForeground (mom->can, mom->gc, mom->black);
  if (moi->txt)
    XDrawImageString (mom->can, mom->fen, mom->gc,
		      moi->x, moi->y,
		      moi->txt, min (strlen (moi->txt), moi->size));
}


void 
afficher_check_box (widget * moi)
{

  widwindow *mom;

  mom = moi->fen;

  XSetForeground (mom->can, mom->gc, mom->clair);

  XDrawLine (mom->can, mom->fen, mom->gc,
	     moi->x, moi->y,
	     moi->x + moi->size, moi->y);

  XDrawLine (mom->can, mom->fen, mom->gc,
	     moi->x + moi->size, moi->y - moi->size,
	     moi->x + moi->size, moi->y);

  XSetForeground (mom->can, mom->gc, mom->fonce);

  XDrawLine (mom->can, mom->fen, mom->gc,
	     moi->x, moi->y,
	     moi->x, moi->y - moi->size);

  XDrawLine (mom->can, mom->fen, mom->gc,
	     moi->x + moi->size, moi->y - moi->size,
	     moi->x, moi->y - moi->size);

  XSetForeground ( mom->can , mom->gc , mom->white );

  XFillRectangle( mom->can , mom->fen , mom->gc ,
		  moi->x + 1 , moi->y - moi->size + 1 ,
		  moi->size - 1 , moi->size - 1 );

  if (moi->selected) {

      XSetForeground (mom->can, mom->gc, mom->black);

      XDrawLine (mom->can, mom->fen, mom->gc,
		 moi->x, moi->y,
		 moi->x + moi->size, moi->y - moi->size);

      XDrawLine (mom->can, mom->fen, mom->gc,
		 moi->x + moi->size, moi->y,
		 moi->x, moi->y - moi->size);
  }

}

void 
widget_afficher (widget * moi)
{
  switch (moi->type)
    {
    case BUTTON:
      afficher_bouton (moi);
      break;
    case EDIT_BOX:
      afficher_edit_box (moi);
      break;
    case INFO_ZONE:
      afficher_info_zone (moi);
      break;
    case CHEK_BOX:
      afficher_check_box (moi);
      break;
    }
}



/*- Interaction -*/
int 
widget_click (widget * moi)
{
  widevent *action;
  int x;
  int y;
  int font_w = 6;
  int font_h = 12;
  int retour;
  
  action=moi->fen->action;

  x = action->mouse_x;
  y = action->mouse_y;
  retour = 0;
  switch (moi->type)
    {
    case CHEK_BOX:
      retour = (x >= moi->x &&
		y <= moi->y &&
		x <= moi->x + moi->size &&
		y >= moi->y - moi->size);
      break;
    default:
      retour = (x >= moi->x &&
		y <= moi->y &&
		x <= moi->x + font_w * moi->size &&
		y >= moi->y - font_h);
      break;
    }
  if (retour) {
      if (moi->type==EDIT_BOX) {
	  moi->selected = !(moi->selected);
	  moi->fen->focus = moi;
      } else if (moi->type==CHEK_BOX) {
	        moi->selected = !(moi->selected);
      }
      moi->on_click();
  }
  return retour;
}



void 
widget_update (widwindow * mom)
{
  widevent *action;

  action=mom->action;

  

  if (XEventsQueued (mom->can, QueuedAfterReading))
    {
      XNextEvent (mom->can, &(mom->evenem));
      switch (mom->evenem.type)
	{
	case ButtonPress:
	  action->type = ACTION_CLICK;
	  action->mouse_x = mom->evenem.xbutton.x;
	  action->mouse_y = mom->evenem.xbutton.y;
	  action->car = 0;
	  action->sym = 0;
	  break;
	case KeyPress:
	  {
	    char buffer;
	    int bufsize = 1;
	    int charcount;
	    charcount = XLookupString ((void *) &(mom->evenem), &buffer, bufsize, NULL, NULL);
	    action->type = ACTION_TOUCHE;
	    action->mouse_x = mom->evenem.xbutton.x;
	    action->mouse_y = mom->evenem.xbutton.y;
	    action->car = buffer;
	    action->sym = XKeycodeToKeysym (mom->can, mom->evenem.xkey.keycode, 0);
	    /*- Touches speciales: raccourcis clavier -*/
	    if (action->sym==XK_Tab) { /*- Chercher la prochaine edit box ou bouton -*/
		    mom->focus=mom->focus->next;
		    if ( mom->focus == NULL ) { mom->focus = mom->next ; }
	    }
	    if (action->sym==XK_Return);
	    if (action->sym==XK_space);

	    break;
	  }
	case Expose:
	  action->type = FOCUS_CHANGE;
	  break;
	}
      mom->skipframe = NO;
   }
  else {
    action->type = NO_ACTION;
  }
}

KeySym widget_key_pressed ( widwindow * moi ) {
    if ( action_type ( moi ) == ACTION_TOUCHE ) return ( moi -> action -> sym );
    else return 0;
}

void widget_event (widwindow *moi)
{
    widevent *action;
    widget *son;

    widget_update (moi);
    action=moi->action;
    son=moi->next;

    switch (action_type(moi)) {
    case ACTION_CLICK:
	while(son != NULL) {
	    widget_click(son);
	    son=son->next;
	}
	moi->skipframe=NO;
	break;
    case ACTION_TOUCHE:
	widget_update_texte(moi);
	moi->skipframe=NO;
	break;
    case FOCUS_CHANGE:
	moi->skipframe=NO;
	break;
    default:
    }
    if (action_type(moi)!=NO_ACTION) widget_tout_afficher ( moi );
    XFlush (moi->can);
}

char *
widget_ajouter_car (char c, char *moi)
{
  int len, newlen;
  char *retour;
  if (moi != NULL)
    {
      len = strlen (moi);
      newlen = len + 1;
      retour = (char *) malloc (sizeof (char) * newlen + 1);
      strcpy (retour, moi);
      retour[len] = c;
      retour[len + 1] = 0;
      free (moi);
    }
  else
    {
      len = 0;
      newlen = len + 1;
      retour = (char *) calloc (sizeof (char), newlen + 1);
      retour[0] = c;
      retour[1] = 0;
    }
  return retour;
}

void 
widget_backspace (char *moi)
{
  if (moi != NULL)
    if (strlen (moi) > 0)
      moi[strlen (moi) - 1] = 0;
}

void 
widget_update_texte (widwindow *fen)
{
    widget *moi;
    widevent *action;

    action=fen->action;
    moi=fen->focus;

    if (moi!=NULL) if (moi->type==EDIT_BOX) {
	if (action->type == ACTION_TOUCHE)
	    switch (action->sym)
		{
	     /*- L'effacement du texte -*/
		case XK_BackSpace:
		case XK_Delete:

		    widget_backspace (moi->txt);
		    if (strlen(moi->txt)<moi->size) {
			moi->offset=0; moi->curseur=strlen(moi->txt); }
		    else {
			moi->offset=strlen(moi->txt)-moi->size;
			moi->curseur=moi->size;
		    }
		    break;
	     /*- Touches a ignorer -*/
		case XK_Tab:
		case XK_Shift_L:
		case XK_Shift_R:
		case XK_Up:
		case XK_Down:
		    break;
		case XK_Left:
		    moi->curseur--;
		    if (moi->curseur<0) {
			moi->offset--;
			moi->curseur=0;
			if (moi->offset<0) moi->offset=0;
		    }
		break;
		case XK_Right:
		    moi->curseur++;
		    if (moi->curseur>moi->size) {
			moi->offset++; moi->curseur=moi->size;
			if (moi->offset>strlen(moi->txt)-moi->size) {
			    moi->offset=strlen(moi->txt)-moi->size;
			    if (moi->offset<=0) moi->offset=0;
			}
		    }
		    break;

	     /*- touche correspondant a un caractere -*/
		default:
		    moi->txt = widget_ajouter_car (action->car, moi->txt);
		    /*- Inserer a l'endroit du curseur -*/
		    if (strlen(moi->txt)<moi->size) {
			moi->offset=0; moi->curseur=strlen(moi->txt); }
		    else {
			moi->offset=strlen(moi->txt)-moi->size;
			moi->curseur=moi->size;
		    }
		    break;
		}
#ifdef DEBUG
			printf("Offset:%d, curseur:%d,somme:%d\n",moi->offset,moi->curseur,moi->curseur+moi->offset);
#endif

#ifdef DEBUG
	printf("moi->offset:%d\n",moi->offset);
	printf("moi->size:%d\n",moi->size);
	printf("moi->curseur:%d\n",moi->curseur);
#endif
	widget_clear_edit_box (moi);
    }
}

/*- Inesthetique, mais tellement pratique... -*/
void
widget_prendre_info (widget * moi, char *info)
{

    /*- Si les textes sont differents alors on realloue, on reaffiche -*/
    if ( strcmp ( moi->txt , info ) != 0 ) {

	moi->fen->skipframe = NO ;

	if (moi->txt)
	    free (moi->txt);

	moi->txt = (char *) calloc (sizeof (char), strlen (info) + 1);
	strcpy (moi->txt, info);

	if ( moi->type == BUTTON ) {
	    widget_clear_button ( moi );
	}
	widget_tout_afficher ( moi->fen );
    }

}

/*- Recuperation des informations -*/
char *
widget_donner_info (widget * moi)
{
  return moi->txt;
}
char *
widget_copier_info (widget * moi)
{
  char *retour;
  retour = (char *) calloc (sizeof (char), strlen (moi->txt) + 1);
  strcpy (retour, moi->txt);
  return retour;
}

int 
widget_is_selected (widget * moi)
{
  return moi->selected;
}


void widget_tout_afficher (widwindow *moi)
{
    widget *son,*sonext;
    if (moi->skipframe == NO) {
	son=moi->next;
	while (son!=NULL) {
	    sonext=son->next;
	    widget_afficher(son);
	    son=sonext;
	}
	XFlush(moi->can);
	moi->skipframe = YES ; /*- on ne reaffiche plus -*/
    }
}

void widget_tout_detruire (widwindow *moi)
{
    widget *son,*sonext;

    son=moi->next;

    while (son!=NULL) {
	sonext=son->next;
	widget_detruire(son);
	son=sonext;
    }
    widget_detruire_fenetre(moi);
}












