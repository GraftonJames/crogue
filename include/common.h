
// Required to get wide char support, needs to be before ncurses include
#undef _XOPEN_SOURCE 
#define _XOPEN_SOURCE 700


#ifndef _CROGUE_COMMON_INCLUDES 
#define _CROGUE_COMMON_INCLUDES
#include <stdlib.h>
#include <limits.h>
#include <locale.h>

#include <ncurses.h>
#include <signal.h>
#include <panel.h>
#include <menu.h>

#endif
