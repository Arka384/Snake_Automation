#include <SFML/Graphics.hpp>
#include <iostream>
#include <sstream>
#include <list>
using namespace sf;

//constants
constexpr int window_dimensions = 480;
constexpr int block_size = 24;
constexpr int max = window_dimensions / block_size;
constexpr int max_size = 400;
constexpr int vertex = max * max;

//////////////////////////////
typedef struct ground {
	Sprite box;
	int visited;
	int wall;
	int vertex;
}ground;
ground matrix[max][max];

typedef struct path_index {
	int x;
	int y;
}path_index;
path_index final_path[vertex];

int path_matrix[vertex][vertex] = { 0 };
//std::list<int>traverse;
int pred[vertex] = { -1 };
int path[vertex] = { 0 };
int source = 0, des = 0;
int length;
bool new_food = true;
bool failed = false;
Vector2i des_index = Vector2i(-1, -1);
int index = 0;
//////////////////////////////

//other
typedef struct Snake {
	int x, y;
}Snake;
Snake s[max_size];

typedef struct fruits {
	int x, y;
}fruits;
fruits f;

int score = 0;
int current_size = 4;
int state = 0;	//0 -> start 1 -> Play

//textures and sprites
Texture green, red, white, head;
Sprite fruit, cell;
Font font;
Text score_text, score_string;
Clock clk;
Time t;

//functions
void init(void);
void render(RenderWindow &);
void updates(void);
void create_path_mat(void);
void add_path_mat_elm(int, int);
void find_way(void);
int get_path(void);
void reset(void);
void movement(void);
void set_next_iter(void);
