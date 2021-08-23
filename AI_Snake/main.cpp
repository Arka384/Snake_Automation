
#include "Dependencies.h"
#include "Updates.h"

int main()
{
	RenderWindow window(VideoMode(window_dimensions + 100, window_dimensions), "Test", Style::Close);
	srand(time(NULL));
	float timer = 0;
	init();

	while (window.isOpen())
	{
		t = clk.restart();
		timer += t.asSeconds();

		Event e;
		while (window.pollEvent(e))
		{
			switch (e.type)
			{
			case Event::Closed:
				window.close();
			case Event::KeyPressed:
				if (Keyboard::isKeyPressed(Keyboard::Enter))
					state = 1;
			default:
				break;
			}
		}

		if (state == 1)
		{
			if (new_food) {	//until a new food is set
				new_food = false;
				reset();
				updates();
				index = 1;
			}

			
			if (s[0].x == des_index.y && s[0].y == des_index.x && failed == false) {
				std::cout << "Here\n";
				des_index = Vector2i(-1, -1);
				des = matrix[f.y][f.x].vertex;
				reset();
				updates();
				index = 1;
			}	
				

			if (s[0].x == f.x && s[0].y == f.y)
			{
				score++;
				set_next_iter();
			}
			else
				movement();
		}

		std::stringstream ss;
		ss << score;
		score_string.setString(ss.str());
		score_string.setPosition((window_dimensions + 50) - score_string.getGlobalBounds().width / 2, 60);

		window.clear();
		render(window);
		window.display();
	}
}

void init()
{
	//sprites
	white.loadFromFile("images/white.png");
	red.loadFromFile("images/red.png");
	green.loadFromFile("images/green.png");
	head.loadFromFile("images/head.png");
	cell.setScale(1.5, 1.5);
	fruit.setTexture(green);
	fruit.setScale(1.5, 1.5);
	//text
	font.loadFromFile("fonts/flappy.ttf");
	score_string.setFont(font);
	score_text.setFont(font);
	score_text.setCharacterSize(34);
	score_string.setCharacterSize(34);
	score_text.setString("SCORE");
	score_text.setPosition(window_dimensions + 2, 20);

	int count = 0;
	for (int i = 0; i < max; i++)
	{
		for (int j = 0; j < max; j++)
		{
			matrix[i][j].box.setTexture(white);
			matrix[i][j].box.setScale(1.5, 1.5);
			matrix[i][j].box.setPosition(i * block_size, j * block_size);
			matrix[i][j].visited = 0;
			matrix[i][j].wall = 0;
			matrix[i][j].vertex = count;
			count++;
		}
	}

	for (int i = 0; i < current_size; i++)
	{
		s[i].x = 4 - i;	//10 is arbitrary value
		s[i].y = 4;
	}

	f.x = rand() % (max - 1);
	f.y = rand() % (max - 1);

	source = matrix[s[0].x][s[0].y].vertex;	//head
	des = matrix[f.y][f.x].vertex;
	//std::cout << des;

}

void render(RenderWindow &thisWindow)
{
	for (int i = 0; i < max; i++)
		for (int j = 0; j < max; j++)
			thisWindow.draw(matrix[i][j].box);


	for (int i = 0; i < current_size; i++)
	{
		cell.setTexture(red);
		if (i == 0)
			cell.setTexture(head);
		cell.setPosition(s[i].x * block_size, s[i].y * block_size);
		thisWindow.draw(cell);
	}

	fruit.setPosition(f.x * block_size, f.y * block_size);
	thisWindow.draw(fruit);
	thisWindow.draw(score_text);
	thisWindow.draw(score_string);
}

void reset()
{
	length = 0;
	for (int i = 0; i < max; i++)
	{
		for (int j = 0; j < max; j++)
		{
			matrix[i][j].wall = 0;
		}
	}

	for (int i = 0; i < vertex; i++)
	{
		path[i] = 0;
		pred[i] = -1;
		for (int j = 0; j < vertex; j++)
		{
			path_matrix[i][j] = 0;
		}
	}

}