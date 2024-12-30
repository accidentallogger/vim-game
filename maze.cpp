#include <bits/stdc++.h>
using namespace std;
#include "config.h"

/*
#define WALL '#'
#define PATH '.'
#define ENDPOINT '*'
#define SPRITE '@'
#define textcolorwall "\033[32m"
#define defaultcolor "\033[0m"
//#define n 31 // The maze size should be odd for proper wall spacing
*/
// Function to create a randomized maze
vector<vector<char>> create_maze(int n,int startX,int startY,int stopX,int stopY,int wallthicc) {
    vector<vector<char>> map(n, vector<char>(n, WALL));
vector<pair<int, int>> directions = {{0, wallthicc}, {0, -wallthicc}, {wallthicc, 0}, {-wallthicc, 0}};



    // Initialize the start and end points
    map[startX][startY] = SPRITE;
   map[stopX][stopY] = ENDPOINT;

    // Recursive function to generate the maze
    function<void(int, int)> gen_maze = [&](int x, int y) {
        vector<pair<int, int>> shuffled_directions = directions;
        random_shuffle(shuffled_directions.begin(), shuffled_directions.end());

        for (auto& d : shuffled_directions) {
            int newX = x + d.first;
            int newY = y + d.second;
            int wallX = x + d.first / wallthicc;
            int wallY = y + d.second / wallthicc;

            // Check bounds and ensure the target cell is a wall
            if (newX > 0 && newX < n - 1 && newY > 0 && newY < n - 1 && (map[newX][newY] == WALL || map[newX][newY]==ENDPOINT)) {
                // Carve a path through the wall
		map[wallX][wallY] = PATH;
                map[newX][newY] = PATH;

                // Recur to continue carving
                gen_maze(newX, newY);
            }
        }
	map[stopX][stopY]=ENDPOINT;
    };

    // Generate the maze starting from (1,1)
    gen_maze(startX, startY);

    return map;
}

// Function to display the maze
void show_maze(const vector<vector<char>>& maze) {
    
for (const vector<char>& row : maze) {
	cout<<"\t \t \t";
cout<<textcolorwall;
        for (char cell : row) {
            if (cell==SPRITE){ cout<<defaultcolor;cout<<cell;cout<<textcolorwall;}
	else cout << cell;

        }
        cout << endl;
    }
}


// n,startX,startY,stopX(n-wallthicc),stopY(n-wallthicc),wallthicc




/*
int main() {
    srand(time(0)); // Seed random number generator
    vector<vector<char>> maze = create_maze(21,1,1,21-2,21-2,2);
    show_maze(maze);
    return 0;
}*/

