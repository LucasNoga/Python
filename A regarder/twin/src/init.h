#ifndef __INIT_TWIN_H__
#define __INIT_TWIN_H__

#include <stdio.h>
#include <stdlib.h>

#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <X11/xpm.h>

#include "gestion.h"
#include "constantes.h"
#include "graphics.h"
#include "my_string.h"

#define sprite_width 16
#define sprite_height 16
#define sprite_width_2 8
#define sprite_height_2 8

/* La seule fonction du module */
void process_command_line( int argc, char **argv );
void init_all_windows ();

#endif



