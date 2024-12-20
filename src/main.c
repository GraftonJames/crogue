#include "common.h"

#include "keymapper.h"
#include "mapper.h"
#include "world_actions.h"

static void finish(int sig);
void main_loop(
	struct grid *g,
	struct obj_def *od,
	struct action_key *km,
	struct wa_vtab *wam
); 
void print_map(
	struct grid *tm,
	struct obj_def *od
); 

static void nc_init();
static void sig_reg();
struct gamestate *init_gamestate();

int
main(int argc, char *args[])
{
	struct action_key *km = init_key_action_pairs();
	struct obj_def *od = malloc(sizeof(struct obj_def)*3);
	struct grid *g = malloc(sizeof(struct grid));
	struct wa_vtab *wam = malloc(sizeof(struct wa_vtab)*KEYBIND_HASH_MAP_SIZE);

	unpack_action_hashtable(ACTION_TYPE_WORLD, wam, km);

	seed_map(od, g);


	for (int x = 0; x < g->height * g->width; x++) {
		printf("(%d, %d)\n", g->height, g->width);
	}
	printf("asntoehunsatoehu\n");

	sig_reg();
	nc_init();

	main_loop(g, od, km, wam);

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
	struct grid *g,
	struct obj_def *od,
	struct action_key *km,
	struct wa_vtab *wam
) {
	wint_t k;
	struct action_list *al;

	for (;;) {
		wget_wch(stdscr, &k);

		al = w_action(k, wam);
		if (al != NULL)
			al->action(g);

		print_map(g, od);
		wrefresh(stdscr);
	}
}

void print_map(
	struct grid *g,
	struct obj_def *od
) {
	wmove(stdscr, 0, 0);
	for (int x = 0; x < g->height * g->width; x++) {
		wadd_wch(stdscr, g->items[x]->obj->def->paint);
		if (x % g->width == 0)
			wmove(stdscr, x / g->width, 0);
	}

}

static void finish(int sig)
{
	endwin();

	exit(0);
}
