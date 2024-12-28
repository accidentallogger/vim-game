#ifndef MAZE_H
#define MAZE_H

#include <vector>
#include <utility>
#include <cstdlib>
#include <ctime>

//const char WALL = '#';
//const char PATH = '.';
//const char ENDPOINT = '*';

std::vector<std::vector<char>> create_maze(int n, int startX, int startY, int stopX, int stopY, int wallthicc);


void show_maze(const std::vector<std::vector<char>>& maze);


#endif
