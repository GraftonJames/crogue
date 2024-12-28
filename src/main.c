#include <stdlib.h>
#include <curses.h>
#include <signal.h>
#include <panel.h>
#include <menu.h>

//Project internal headers
#include "keymapper.h"
#include "keymapper.h"

struct gamestate {
};

static void finish(int sig);
static void main_loop(struct action_key *km);
static void main_loop_step(struct action_key *km);
static void nc_init();
static void sig_reg();
struct gamestate *init_gamestate();

int
main(int argc, char *args[])
{
	struct action_key *km = init_key_action_pairs();

	sig_reg();
	nc_init();

	main_loop(km);

	finish(0);         
}

void sig_reg()
{
	signal(SIGINT, finish); 
}
void nc_init()
{
	setlocale(LC_ALL, "");
	initscr();
	keypad(stdscr, FALSE);
	nonl(); cbreak(); noecho();
}

void main_loop(struct action_key *km)
{

	for (;;) main_loop_step(km);
}

static void main_loop_step(struct action_key *km)
{
	int c = wgetch(stdscr);

	clear();
	int i = 0;
	while (
		i < ACTION_COUNT &&
		km[i].keys[0] != c
	) i++;
	
	if (km[i].keys[0] != c) return;

	int a = km[i].action;
	while (a > 9) {
		addch((a % 10) + 48);
		a = a / 10;
		move(0, 1);
	}
	addch(a + 48);

	refresh();
}

static void finish(int sig)
{
	endwin();

	/* do your non-curses wrapup here */

	exit(0);
}
