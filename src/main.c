#include "common.h"

#include "keymapper.h"
#include "statemachine.h"

static void finish(int sig);
void main_loop(struct state *s, struct game_data *gd); 

static void nc_init();
static void sig_reg();

const struct action_key default_keymap[ACTION_COUNT] = {
	{WA_PROTAG_MOVE_N, {'e',0,0,0,0,0,0,0,0,0}},
	{WA_PROTAG_MOVE_S, {'j',0,0,0,0,0,0,0,0,0}},
	{WA_PROTAG_MOVE_E, {'o',0,0,0,0,0,0,0,0,0}},
	{WA_PROTAG_MOVE_W, {'u',0,0,0,0,0,0,0,0,0}}
};

int
main(int argc, char *args[])
{
	struct action_key km[ACTION_COUNT]; 
	memcpy((void *) km, (void *) default_keymap, sizeof(struct action_key) * ACTION_COUNT);
	struct state_machine sm;
	struct game_data gd;

	init_key_action_pairs((struct action_key *) &km);
	init_statemachine(&sm,(struct action_key *) &km);

	printf_state_machine_debug(&sm);
	seed_map(&gd);

	sig_reg();
	nc_init();

	main_loop((sm.cur), &gd);

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
	struct game_data *gd
) {
	wint_t k;
	struct action_list *al;

	for (;;) {
		wget_wch(stdscr, &k);

		al = get_state_action(s, k);
		while (al != NULL) {
			printf("found action");
			al->action(s, gd);
			al = al->next;
		}

		wrefresh(stdscr);
	}
}

static void finish(int sig)
{
	endwin();

	exit(0);
}
