#include <stdlib.h>
#include <curses.h>
#include <signal.h>
#include <panel.h>
#include <menu.h>

//internal headers
#include "keymapper.h"



static void finish(int sig);
static void main_loop();
static void main_loop_step();
static void nc_init();
static void sig_reg();

struct settings {
	keyaction[] keybindings;  
};

int
main(int argc, char *args[]) {
	// keymap km = create_keymaps();

	sig_reg();
	nc_init();

	main_loop();

	finish(0);         
}

void sig_reg() {
	signal(SIGINT, finish);      /* arrange interrupts to terminate */
}

void nc_init() {
	initscr();
	keypad(stdscr, FALSE);
	nonl(); cbreak(); noecho();
}

void main_loop() {
	for (;;) main_loop_step();
}

void main_loop_step() {
	long c = wgetch(stdscr);
	/* process the command keystroke */
	move(0,10);
	while (c > 10) {
		addch((c % 10) + 48);
		c = c / 10;
		move(0,-1);
	}
	addch(c % 10 + 48);
	refresh();
}

static void finish(int sig)
{
	endwin();

	/* do your non-curses wrapup here */

	exit(0);
}
