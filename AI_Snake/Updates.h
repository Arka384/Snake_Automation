#pragma once
//#include "Dependencies.h"

void updates()
{
	//1 - food alredy available so set the walls here
	for (int i = 1; i < current_size; i++)
		matrix[s[i].y][s[i].x].wall = 1;

	/*	//for pirinting walls
	for (int i = 0; i < max; i++)
	{
		for (int j = 0; j < max; j++)
			std::cout << matrix[i][j].wall << " ";
		std::cout << "\n";
	}	*/


	//2 - add ways according to current position and get the path matrix
	create_path_mat();
	//3 - apply procedure on path matrix
	find_way();
	while (failed == true)
	{
		des_index.x = rand() % max;
		des_index.y = rand() % max;
		while (matrix[des_index.x][des_index.y].wall == 1) {
			des_index.x = rand() % max;
			des_index.y = rand() % max;
		}
		des = matrix[des_index.x][des_index.y].vertex;
		std::cout << des << "\n";
		find_way();
		if (failed == false)
			std::cout << "found\n";
	}

	//4 - find the path 
	length = get_path();
	//reversing the path
	for (int i = 0; i < length / 2; i++)
	{
		int t = path[i];
		path[i] = path[length - i - 1];
		path[length - i - 1] = t;
	}

	//setting the path_index
	for (int k = 0; k < length; k++)
		for (int i = 0; i < max; i++)
			for (int j = 0; j < max; j++)
				if (path[k] == matrix[i][j].vertex) {
					final_path[k].x = j;
					final_path[k].y = i;
				}

	//for (int k = 0; k < length; k++)
		//std::cout << final_path[k].x << " " << final_path[k].y << "\n";

	//	for (int i = 0; i < length; i++)
	//		std::cout << path[i] << " ";

		//during these upper steps the snake remains on the same position


		// the steps 5-7 are being performed in main function
	//5 - (Now snake starts moving) make snake head follow the path and the body will follow head


	//6 - snake head collided with food
	//7 - set new food position and go to 1

	//this whole process works for the time being of eating food and getting next food.

	//The only problem is the snake sometimes teleports itself :-| and it crashes then...
	//idk why...FFFFFFFF..... :-(
}


void create_path_mat()
{
	for (int i = 0; i < max; i++)
	{
		for (int j = 0; j < max; j++)
		{
			if (matrix[i][j].wall == 0)
			{
				if (j + 1 < max && matrix[i][j + 1].wall == 0)
					add_path_mat_elm(matrix[i][j].vertex, matrix[i][j + 1].vertex);
				if (j - 1 > 0 && matrix[i][j - 1].wall == 0)
					add_path_mat_elm(matrix[i][j].vertex, matrix[i][j - 1].vertex);
				if (i + 1 < max && matrix[i + 1][j].wall == 0)
					add_path_mat_elm(matrix[i][j].vertex, matrix[i + 1][j].vertex);
				if (i - 1 > 0 && matrix[i - 1][j].wall == 0)
					add_path_mat_elm(matrix[i][j].vertex, matrix[i - 1][j].vertex);
			}

		}
	}
}

void add_path_mat_elm(int a, int b)
{

	if (b < 0 || b > vertex - 1)
		return;
	path_matrix[a][b] = 1;
	path_matrix[b][a] = 1;
}

void find_way()
{
	failed = false;
	std::list<int> path_vector;
	bool tested[vertex] = { false };

	tested[source] = true;
	path_vector.push_back(source);

	while (path_vector.empty() != 1)
	{
		int x = path_vector.front();

		if (x == des) {
			pred[source] = -1;
			return;
		}

		path_vector.pop_front();

		for (int i = 0; i < vertex; i++)
		{
			if (path_matrix[x][i] == 1 && tested[i] == false)
			{
				tested[i] = true;
				path_vector.push_back(i);
				pred[i] = x;
			}
		}
	}

	if (path_vector.empty() == 1)
	{
		std::cout << "Path not found\n";
		failed = true;
		state = 0;
	}
}

int get_path()
{
	int k = 0, i = des;
	while (pred[i] != -1)
	{
		path[k++] = i;
		i = pred[i];
	}
	path[k++] = i;
	return k;
}

void movement()
{
	sleep(milliseconds(30));
	//for snake body movement
	for (int i = current_size - 1; i > 0; i--)
	{
		s[i].x = s[i - 1].x;
		s[i].y = s[i - 1].y;
	}

	//std::cout << matrix[s[0].x][s[0].y].vertex << " " << path[index] << "\n";
	if (index < length)
	{
		s[0].x = final_path[index].x;
		s[0].y = final_path[index].y;
		index++;
	}
}

void set_next_iter()
{
	current_size++;
	s[current_size - 1].x = -block_size;
	s[current_size - 1].y = -block_size;

again:
	f.x = rand() % (max - 1);
	f.y = rand() % (max - 1);
	for (int i = 1; i < current_size; i++)
	{
		if (s[i].x == f.x && s[i].y == f.y) {
			//std::cout << "FFFFFFFFF....." << "\n";
			goto again;
		}
	}

	source = matrix[s[0].y][s[0].x].vertex;
	des = matrix[f.y][f.x].vertex;

	new_food = true;
}