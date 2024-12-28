#include <iostream>
#include <cstdlib>
#include <ctime>
#include <unistd.h>
#include <termios.h>
#include <fcntl.h>
#include <vector>
#include "maze.h"


#define WALL '#'
#define PATH '.'
#define ENDPOINT '*'
#define SPRITE '@'



// Function to clear the screen (platform-specific)
void clearScreen() {
    // On Linux/macOS, use the 'clear' command
    // On Windows, use the 'cls' command
    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif
}

// Function to display the grid
/*void displayGrid(int playerX, int playerY, int targetX, int targetY) {
    for (int y = 0; y < HEIGHT; y++) {
        for (int x = 0; x < WIDTH; x++) {
            if (x == playerX && y == playerY)
                std::cout << "@";  // Player
            else if (x == targetX && y == targetY)
                std::cout << "*";  // Target
            else
                std::cout << ".";  // Empty space
        }
        std::cout << std::endl;
    }
}*/

// Function to get a non-blocking keypress
char getKeyPress() {
    struct termios oldt, newt;
    char ch;
    tcgetattr(STDIN_FILENO, &oldt); // Get the current terminal settings
    newt = oldt;
    newt.c_lflag &= ~(ICANON | ECHO); // Disable canonical mode and echoing
    newt.c_cc[VMIN] = 1;             // Minimum number of characters to read
    newt.c_cc[VTIME] = 0;            // Timeout for read
    tcsetattr(STDIN_FILENO, TCSANOW, &newt); // Apply new terminal settings

    ch = getchar(); // Get the keypress
    tcsetattr(STDIN_FILENO, TCSANOW, &oldt); // Restore the original terminal settings
    return ch;
}

int main() {
int playerX=1;
int playerY=1;
int n=21;
int thicc=2;
int targetX=n-thicc;
int targetY=n-thicc;


srand(time(0));
std::vector<std::vector<char>> maz = create_maze(n,playerX,playerY,targetX,targetY,thicc);
    bool gameWon = false;
    char move;

    while (!gameWon) {
        // Clear the screen and display the grid
        clearScreen();

   
show_maze(maz);


        // Get the key press without blocking
        move = getKeyPress();

        // Process the move
        switch (move) {
            case 'h':
                if (playerX > 0 && maz[playerX-1][playerY]=='.'){ maz[playerX][playerY]=PATH;playerX--; maz[playerX][playerY]=SPRITE;}  // Move left
	//	std::cout<<"h"<<std::endl;
	//	std::cout<<playerX<<" "<<playerY<<std::endl;
		break;
            case 'j':
                if (playerY < n - 1 &&  maz[playerX][playerY+1]=='.'){ maz[playerX][playerY]=PATH;playerY++; maz[playerX][playerY]=SPRITE; } // Move down
                break;
            case 'k':
                if (playerY > 0&&  maz[playerX][playerY-1]=='.' ){ maz[playerX][playerY]=PATH;playerY--;maz[playerX][playerY]=SPRITE;}  // Move up
                break;
            case 'l':
                if (playerX < n - 1 &&  maz[playerX+1][playerY]=='.'){ maz[playerX][playerY]=PATH;playerX++;  maz[playerX][playerY]=SPRITE;} // Move right
                break;
            default:
                break; // Do nothing for invalid keys
        }

        // Check if the player has reached the target
        if (playerX == targetX && playerY == targetY) {
            gameWon = true;
        }

        usleep(100000); //Sleep for a short time to make the game real-time
    }

    // Game won message
   clearScreen();
   // displayGrid(playerX, playerY, targetX, targetY);
  //  std::cout << "Congratulations! You've reached the target!" << std::endl;


	return 0;
}

