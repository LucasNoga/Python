#ifndef __TWIN_HHH____
#define __TWIN_HHH____


#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <math.h>

#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <X11/keysym.h>
#include <X11/xpm.h>

#include "init.h"
#include "constantes.h"
#include "gestion.h"
#include "graphics.h"
#include "team.h"
#include "my_string.h"
#include "language.h"
#include "spy.h"
#include "highscore.h"
#include "keys.h"
#include "my_time.h"

/*- Les differentes phases du jeu... -*/
void intro (void);
int run_game (int argc, char **argv);
void show_winner (void);
void init_all_the_mem (void);
void close_all_windows (void);
void free_all_the_mem (void);

#endif
