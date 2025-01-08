#include "common.h"

#include "keymapper.h"
#include "statemachine.h"
#include "mapper.h"

static void finish(int sig);
void main_loop(struct state *s, struct grid *g, struct obj_def *od); 

static void nc_init();
static void sig_reg();

int
main(int argc, char *args[])
{
	struct action_key km[ACTION_COUNT]; 
	struct state_machine sm;
	struct grid g;
	struct obj_def od;

	init_key_action_pairs((struct action_key *) &km);

	seed_map(&od, &g);

	sig_reg();
	nc_init();

	main_loop((sm.current), &g, &od);

	finish(0);         
}

static void sig_reg()
{
	signal(SIGINT, finish); 
}

static void nc_init()
{
	setlocale(LC_ALL, "en_US.UTF-8");
	initscr();
	keypad(stdscr, FALSE);
	nonl(); cbreak(); noecho();
}

void main_loop(
	struct state *s,
	struct grid *g,
	struct obj_def *od
) {
	wint_t k;
	struct action_list *al;

	for (;;) {
		wget_wch(stdscr, &k);

		s->key_handle(k);
		s->print_fn();

		wrefresh(stdscr);
	}
}

static void finish(int sig)
{
	endwin();

	exit(0);
}
