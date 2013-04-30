#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <time.h>

#define ERROR(msg) error(msg, __FILE__, __LINE__)
#define FAIL() error(__FUNCTION__, __FILE__, __LINE__)
#define ASSERT(expr) do { if (!(expr)) { error(#expr, __FILE__, __LINE__); } } while (0)

void error(const char *msg, const char *file, int line)
{
    fprintf(stderr, "%s:%d: %s\n", file, line, msg);
    exit(1);
}

enum keyword_ {
    kw_up,
    kw_down,
    kw_left,
    kw_right,
    kw_pass,
    kw_out
};

typedef enum keyword_ keyword;

struct action_ {
    bool place_bomb;
    keyword non_bomb_action;
    int bomb_delay;
};

typedef struct action_ action;

const action action_up    = {false, kw_up,    -1};
const action action_down  = {false, kw_down,  -1};
const action action_left  = {false, kw_left,  -1};
const action action_right = {false, kw_right, -1};
const action action_pass  = {false, kw_pass,  -1};
const action action_out   = {false, kw_out,   -1};

struct parameters_ {
    int player_id;
    int number_of_players;
    int max_number_of_turns;
};

typedef struct parameters_ parameters;

struct map_ {
    int width;
    int height;
    char *data;
};

typedef struct map_ map;

struct bomb_ {
    int pos_x;
    int pos_y;
    int ticks_left;
};

typedef struct bomb_ bomb;

struct player_ {
    int pos_x;
    int pos_y;
    int bomb_count;
    bomb *bombs;
    action last_action;
};

typedef struct player_ player;

struct state_ {
    parameters parameters;
    map map;
    player *players;
};

typedef struct state_ state;

const int max_bombs_per_players = 5;

bool is_whitespace(char c)
{
    return (c == ' ') || (c == '\t') || (c == '\r') || (c == '\n');
}

bool is_digit(char c)
{
    return (c >= '0') && (c <= '9');
}

char *map_pos(map *m, int row, int col)
{
    return &m->data[m->width * row + col];
}

int read_integer_token(void)
{
    int i;
    int res = scanf("%d", &i);
    if (res != 1) {
        FAIL();
    }
    return i;
}

void read_character_tokens(int n, char *buffer)
{
    int i;
    for (i = 0; i < n; i++) {
        int c;
        do {
            c = getchar();
            if (c == EOF) {
                FAIL();
            }
        } while (is_whitespace((char) c));
        buffer[i] = (char) c;
    }
}

keyword read_keyword_token(void)
{
    char buffer[6];
    int res = scanf("%5s", buffer);
    if (res != 1) {
        FAIL();
    }
    if (strcmp(buffer, "up") == 0) {
        return kw_up;
    } else if (strcmp(buffer, "down") == 0) {
        return kw_down;
    } else if (strcmp(buffer, "left") == 0) {
        return kw_left;
    } else if (strcmp(buffer, "right") == 0) {
        return kw_right;
    } else if (strcmp(buffer, "pass") == 0) {
        return kw_pass;
    } else if (strcmp(buffer, "out") == 0) {
        return kw_out;
    } else {
        ERROR("invalid keyword");
        return kw_out;
    }
}

action read_action_token(void)
{
    action a;
    int c;
    do {
        c = getchar();
        if (c == EOF) {
            FAIL();
        }
    } while (is_whitespace((char) c));
    a.place_bomb = is_digit((char) c);
    int res = ungetc(c, stdin);
    if (res == EOF) {
        FAIL();
    }
    if (a.place_bomb) {
        a.bomb_delay = read_integer_token();
    } else {
        a.non_bomb_action = read_keyword_token();
    }
    return a;
}

void read_parameters(parameters *p)
{
    p->player_id           = read_integer_token();
    p->number_of_players   = read_integer_token();
    p->max_number_of_turns = read_integer_token();
}

void read_map(map *m)
{
    read_character_tokens(m->width * m->height, m->data);
}

void read_bomb(bomb *b)
{
    b->pos_x = read_integer_token();
    b->pos_y = read_integer_token();
    b->ticks_left = read_integer_token();
}

void read_round(state *state)
{
    int player_count = state->parameters.number_of_players;
    for (int i = 0; i < player_count; i++) {
        state->players[i].bomb_count = 0;
    }
    read_map(&state->map);
    int live_player_count = read_integer_token();
    for (int i = 0; i < live_player_count; i++) {
        int player_id = read_integer_token();
        ASSERT(player_id < player_count);
        player *player = &state->players[player_id];
        player->pos_x = read_integer_token();
        player->pos_y = read_integer_token();
    }
    int bomb_count = read_integer_token();
    for (int i = 0; i < bomb_count; i++) {
        int player_id = read_integer_token();
        ASSERT(player_id < player_count);
        player *player = &state->players[player_id];
        ASSERT(player->bomb_count < max_bombs_per_players);
        bomb *bomb = &player->bombs[player->bomb_count];
        read_bomb(bomb);
        player->bomb_count++;
    }
    for (int i = 0; i < player_count; i++)
    {
        int player_id = read_integer_token();
        ASSERT(player_id < player_count);
        player *player = &state->players[player_id];
        player->last_action = read_action_token();
    }
}

bool no_more_tokens(void)
{
    int c;
    do {
        c = getchar();
        if (c == EOF) {
            return true;
        }
    } while (is_whitespace((char) c));
    ungetc(c, stdin);
    return false;
}

void setup(state *state)
{
    read_parameters(&state->parameters);
    state->map.width  = read_integer_token();
    state->map.height = read_integer_token();
    state->map.data   = malloc(sizeof(char) * state->map.width * state->map.height);
    state->players    = malloc(sizeof(player) * state->parameters.number_of_players);
    for (int i = 0; i < state->parameters.number_of_players; i++)
    {
        state->players[i].bombs = malloc(sizeof(bomb) * max_bombs_per_players);
    }
    srand(time(NULL) ^ state->parameters.player_id);
}

void write_action(action a)
{
    if (a.place_bomb) {
        printf("%d\r\n", a.bomb_delay);
    } else {
        const char *s;
        switch (a.non_bomb_action) {
        case kw_up:
            s = "up";
            break;
        case kw_down:
            s = "down";
            break;
        case kw_left:
            s = "left";
            break;
        case kw_right:
            s = "right";
            break;
        case kw_pass:
            s = "pass";
            break;
        default:
            FAIL();
            break;
        }
        printf("%s\r\n", s);
    }
    fflush(stdout);
}

bool can_move_to(state *state, int pos_x, int pos_y)
{
    map *m = &state->map;
    if(*map_pos(m, pos_x, pos_y) != '.') {
        return false;
    }
    for (int i = 0; i < state->parameters.number_of_players; i++) {
        player *player = &state->players[i];
        for (int j = 0; j < player->bomb_count; j++) {
            bomb *bomb = &player->bombs[j];
            if ((bomb->pos_x == pos_x) && (bomb->pos_y == pos_y)) {
                return false;
            }
        }
    }
    return true;
}

void make_move(state *state)
{
    player *player = &state->players[state->parameters.player_id];
    int x = player->pos_x;
    int y = player->pos_y;
    action possible_actions[6];
    int number_of_actions;
    possible_actions[0] = action_pass;
    number_of_actions = 1;
    if (can_move_to(state, x, y - 1)) {
        possible_actions[number_of_actions] = action_up;
        number_of_actions++;
    }
    if (can_move_to(state, x, y + 1)) {
        possible_actions[number_of_actions] = action_down;
        number_of_actions++;
    }
    if (can_move_to(state, x - 1, y)) {
        possible_actions[number_of_actions] = action_left;
        number_of_actions++;
    }
    if (can_move_to(state, x + 1, y)) {
        possible_actions[number_of_actions] = action_right;
        number_of_actions++;
    }
    if (player->bomb_count < max_bombs_per_players) {
        action bomb_action;
        bomb_action.place_bomb = true;
        bomb_action.bomb_delay = (rand() % 21) + 5;
        possible_actions[number_of_actions] = bomb_action;
        number_of_actions++;
    }
    int choice = rand() % number_of_actions;
    write_action(possible_actions[choice]);
}

int main(int argc, char **argv)
{
    state state;
    setup(&state);
    while (!no_more_tokens()) {
        read_round(&state);
        make_move(&state);
    }
    return 0;
}
