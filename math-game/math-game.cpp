#include <iostream>
#include <windows.h>
#include <conio.h>//We have this library,so that we can freely use the getch() function
#include <string>//We have this library, so that we can use strings
using namespace std;

// #define is used to allow the programmer to give a name to a constant value before the program is compiled
#define KEY_UP 72
#define KEY_DOWN 80
#define KEY_LEFT 75
#define KEY_RIGHT 77

struct CELL {
    int playerY = 1;
    int playerX = 0;
    bool isVisited = false;
    bool isWall = false;
    bool isPlayer = false;
};
CELL playerCord;

void color(int color) {
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}

void gotoxy(int x, int y) {
    COORD c;
    c.X = x;
    c.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), c);
}

void menu() {
    cout << "*-------------------------------------*" << endl;
    cout << ":            The Maze Game            :" << endl;
    cout << ":         by Team Anti-Xenon          :" << endl;
    cout << ":    (Georgi,Stanimir,Zhivko,Vasil)   :" << endl;
    cout << "*-------------------------------------*" << endl;
    cout << ":                                     :" << endl;
    cout << ":                                     :" << endl;
    cout << ":        Welcome to our simple        :" << endl;
    cout << ":             Maze game.              :" << endl;
    cout << ":                                     :" << endl;
    cout << ":                                     :" << endl;
    cout << "*-------------------------------------*" << endl;
}

// this function generates the maze,by previously entered size
void printMaze(CELL** maze, int size, char free, char player) {
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            if (maze[i][j].isPlayer == true) {
                cout << player << " ";
            }
            else if (maze[i][j].isVisited == true) {
                cout << free << " ";
            }
            else {
                cout << char(254) << " ";
            }
        }
        cout << endl;
    }
}

// this function generates the walls of the maze
void createWalls(CELL** maze, int size, int* cellCount) {
    for (int y = 0; y < size; y++) {
        for (int x = 0; x < size; x++) {
            if ((x % 2 == 0) || (y % 2 == 0)) {
                maze[y][x].isWall = true;
            }
            else {
                ++* cellCount;
            }
        }
    }
}

void toVisited(CELL** maze, int* cordY, int* cordX, int dir, int* unvisitedCells) {
    switch (dir) {
    case 0:
        if (maze[*cordY - 2][*cordX].isVisited == false) {
            maze[*cordY - 2][*cordX].isVisited = true;
            maze[*cordY - 2][*cordX].isWall = false;
            maze[*cordY - 1][*cordX].isVisited = true;
            maze[*cordY - 1][*cordX].isWall = false;
            ++* unvisitedCells;
        }
        *cordY -= 2;
        break;
    case 1:
        if (maze[*cordY][*cordX + 2].isVisited == false) {
            maze[*cordY][*cordX + 2].isVisited = true;
            maze[*cordY][*cordX + 2].isWall = false;
            maze[*cordY][*cordX + 1].isVisited = true;
            maze[*cordY][*cordX + 1].isWall = false;
            ++* unvisitedCells++;
        }
        *cordX += 2;
        break;
    case 2:
        if (maze[*cordY + 2][*cordX].isVisited == false) {
            maze[*cordY + 2][*cordX].isVisited = true;
            maze[*cordY + 2][*cordX].isWall = false;
            maze[*cordY + 1][*cordX].isVisited = true;
            maze[*cordY + 1][*cordX].isWall = false;
            ++* unvisitedCells++;
        }
        *cordY += 2;
        break;
    case 3:
        if (maze[*cordY][*cordX - 2].isVisited == false) {
            maze[*cordY][*cordX - 2].isVisited = true;
            maze[*cordY][*cordX - 2].isWall = false;
            maze[*cordY][*cordX - 1].isVisited = true;
            maze[*cordY][*cordX - 1].isWall = false;
            ++* unvisitedCells++;
        }
        *cordX -= 2;
        break;
    }
}

// this function checks if the player is trying to move towards a wall
void playerMovement(CELL** maze) {
    switch (_getch()) {
    case KEY_UP:
        if (maze[playerCord.playerY - 1][playerCord.playerX].isWall == false) {
            maze[playerCord.playerY][playerCord.playerX].isPlayer = false;
            playerCord.playerY -= 1;
            maze[playerCord.playerY][playerCord.playerX].isPlayer = true;
        }
        else {
            cout << "Can't move there!";
        }
        break;
    case KEY_DOWN:
        if (maze[playerCord.playerY + 1][playerCord.playerX].isWall == false) {
            maze[playerCord.playerY][playerCord.playerX].isPlayer = false;
            playerCord.playerY += 1;
            maze[playerCord.playerY][playerCord.playerX].isPlayer = true;
        }
        else {
            cout << "Can't move there!";
        }
        break;
    case KEY_LEFT:
        if (maze[playerCord.playerY][playerCord.playerX - 1].isWall == false) {
            maze[playerCord.playerY][playerCord.playerX].isPlayer = false;
            playerCord.playerX -= 1;
            maze[playerCord.playerY][playerCord.playerX].isPlayer = true;
        }
        else {
            cout << "Can't move there!";
        }
        break;
    case KEY_RIGHT:
        if (maze[playerCord.playerY][playerCord.playerX + 1].isWall == false) {
            maze[playerCord.playerY][playerCord.playerX].isPlayer = false;
            playerCord.playerX += 1;
            maze[playerCord.playerY][playerCord.playerX].isPlayer = true;
        }
        else {
            cout << "Can't move there!";
        }
        break;
    }
}

bool freeCheck(int dir, int size, int cordY, int cordX) {
    return (dir == 0 && cordY == 1) or
        (dir == 2 && cordY == size - 2) or
        (dir == 1 && cordX == size - 2) or
        (dir == 3 && cordX == 1);
}

//This function is used to display a text,when you win the game.
void winningText() {
    cout << "*---------------------------------------------*" << endl;
    cout << "|   __     __                    _       _    |\n"
        "|   \\ \\   / /                   (_)     | |   |\n"
        "|    \\ \\_/ /__  _   _  __      ___ _ __ | |   |\n"
        "|     \\   / _ \\| | | | \\ \\ /\\ / / | '_ \\| |   |\n"
        "|      | | (_) | |_| |  \\ V  V /| | | | |_|   |\n"
        "|      |_|\\___/ \\__,_|   \\_/ \\_/|_|_| |_(_)   |\n";
    cout << "*---------------------------------------------*" << endl;
}
void getUserName(string& userName)
{
    //Declare appropriate variables.
    int strLength, counter = 0;

    //Asks the user to type his/her name to proceed.
    cout << "*-------------------------------------*" << endl;
    cout << ":       Please enter your name.       :" << endl;
    cout << ":                                     :" << endl;
    cout << "*-------------------------------------*" << endl;
    getline(cin, userName);

    //Finding how many letters are there in the user input.
    strLength = userName.length();

    //Input Validation.
    while (counter < strLength || counter == 0)
    {
        //Validation. Only a letter and one word is allowed.
        if (!isalpha(userName[counter]))
        {
            system("cls");
            cout << "*-------------------------------------*" << endl;
            cout << ":      Please enter a valid name      :" << endl;
            cout << ":      containing one word only.      :" << endl;
            cout << "*-------------------------------------*" << endl;
            getline(cin, userName);
            strLength = userName.length();
            counter = 0;
        }
        //Validation. The name cannot have more than 10 letters.
        else if (strLength > 10)
        {
            system("cls");
            cout << "*-------------------------------------*" << endl;
            cout << ": Your name cannot exceed 10 letters. :" << endl;
            cout << ":     Please type another name.       :" << endl;
            cout << "*-------------------------------------*" << endl;
            getline(cin, userName);
            strLength = userName.length();
            counter = 0;
        }
        else
        {
            counter++;
        }
    }
}


// this is the main function
int main() {
    system("color 4");
    srand((unsigned int)time(NULL));

    int cordY, cordX = 1;
    int cellCount = 0;
    char free = ' ';
    char player = char(2);
    int size;
    string name;
    getUserName(name);
    system("cls");
    menu();
    do {
        cout << "Enter the size of the maze: ";
        cin >> size;

        if (size <= 1) {
            cout << "Enter a number of 2 and above! ";
            cin >> size;
        }
    } while (size <= 1);
    system("cls");
    cout << "Okay, " << name << " let's see how well will you go" << endl;

    cordY = 1;

    size = size * 2 + 1;

    CELL** maze = new CELL * [size];
    for (int i = 0; i < size; i++) {
        maze[i] = new CELL[size];
    }

    maze[cordY][cordX - 1].isPlayer = true;
    maze[cordY][cordX - 1].isVisited = true;
    maze[size - 2][size - 1].isVisited = true;

    createWalls(maze, size, &cellCount);

    maze[cordY][cordX - 1].isWall = false;
    maze[size - 2][size - 1].isWall = false;

    bool unvisitedCheck = true;
    int unvisitedCells = 0;

    while (unvisitedCheck) {
        if (unvisitedCells == cellCount) {
            unvisitedCheck = false;
        }
        int dir;
        do {
            dir = rand() % 4;
        } while (freeCheck(dir, size, cordY, cordX));

        toVisited(maze, &cordY, &cordX, dir, &unvisitedCells);
    }

    bool playerWon = true;
    while (playerWon) {
        if (maze[size - 2][size - 1].isPlayer == true) {
            system("cls");
            winningText();
            break;
        }
        char input;
        printMaze(maze, size, free, player);
        cout << "\n\n\n";
        cout << "*--------------------------*" << endl;
        cout << "|       Instructions:      |" << endl;
        cout << "|  Use the arrows to move  |" << endl;
        cout << "*--------------------------*";
        playerMovement(maze);
        system("cls");
    }
}