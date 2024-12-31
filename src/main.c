#include "common.h"

#include "keymapper.h"
#include "mapper.h"

struct gamestate {
};

static void finish(int sig);
void main_loop(
	struct tile_map *tm,
	struct obj_def *od,
	struct action_key *km
); 
void print_map(
	struct tile_map *tm,
	struct obj_def *od
); 

static void nc_init();
static void sig_reg();
struct gamestate *init_gamestate();

int
main(int argc, char *args[])
{
	printf("start");
	struct action_key *km = init_key_action_pairs();
	struct obj_def *od = malloc(sizeof(struct obj_def)*3);
	struct tile_map *tm = malloc(sizeof(struct tile_map));

	printf("before");
	seed_map(od, tm);
	sig_reg();
	nc_init();

	main_loop(tm, od, km);

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
	struct tile_map *tm,
	struct obj_def *od,
	struct action_key *km
) {
	wint_t wc;

	for (;;) {
		wget_wch(stdscr, &wc);

		print_map(tm, od);

		refresh();
	}
}

void print_map(
	struct tile_map *tm,
	struct obj_def *od
) {
	for (int x = 0; x < tm->height * tm->width; x++) {
		wadd_wch(stdscr, tm->tiles[x].obj->def->paint);
		if (x % tm->width == 0)
			wmove(stdscr, x / tm->width, 0);
	}
}

static void finish(int sig)
{
	endwin();

	exit(0);
}
