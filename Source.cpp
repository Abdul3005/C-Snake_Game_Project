#include <iostream>
#include <conio.h>
#include <fstream>
#include <Windows.h>
#include <stdlib.h>
#include <string>
using namespace std;

// constants keys to move the snake
#define KEY_UP 72
#define KEY_DOWN 80
#define KEY_LEFT 75
#define KEY_RIGHT 77

// to clear the console screen
void ScreenClear() {
    system("CLS");
}

// Players enters their name
void PlayerName(string& player) {
    ScreenClear();
    cout << "Enter your name: ";
    cin >> player;
    cout << "Welcome! " << player << " :)" << endl;

    // options for back to the main menu
    int user_choice;
    cout << "\n1) Return to Main Menu" << endl;
    cout << "Choose an option (1): ";
    cin >> user_choice;

    if (user_choice == 1) {
        return;
    }
}

// this function reads the scores from file named scores.txt
int ScoresReader(const string& filename, int score[], int max) {
    ifstream inputFile(filename);
    int count = 0;

    if (inputFile.is_open()) {
        while (inputFile >> score[count] && count < max) {
            count++;
        }
        inputFile.close();
    }

    return count;  // it tells how many scores were successfully read
}

// Selection Sorting to sort the scores 
void Selection_Sort(int score[], int count) {
    for (int i = 0; i < count - 1; i++) {
        int maximum_num = i;

        // largest score 
        for (int j = i + 1; j < count; j++) {
            if (score[j] > score[maximum_num]) {
                maximum_num = j;
            }
        }

        // swap the largest score with that one at position i
        if (maximum_num != i) {
            int temp = score[i];
            score[i] = score[maximum_num];
            score[maximum_num] = temp;
        }
    }
}

void printthreehighscores(int score[], int count) {
    int printscores = (count < 3) ? count : 3;

    cout << "Top " << printscores << " highest scores: " << endl;
    for (int i = 0; i < printscores; i++) {
        cout << score[i] << endl;
    }
}

void highestscores() {
    ScreenClear();
    cout << "High Scores: " << endl;

    int score[100];
    string filename = "scores.txt";

    int count = ScoresReader(filename, score, 100);
    Selection_Sort(score, count);
    printthreehighscores(score, count);

    int user_choice;
    cout << "\n1. Return to Main Menu" << endl;
    cout << "Choose an option (1): ";
    cin >> user_choice;

    if (user_choice == 1) {
        return;
    }
}

// this function writes a player's final score to a file
void Notescores(const string& filename, int score) {
    ofstream outFile(filename, ios::app);  // it will start writing from where it left

    if (outFile.is_open()) {
        outFile << score << endl;  // Write score to the file
        outFile.close();  // Close the file after writing
    }
}

void GameStart(const string& player) {
    ScreenClear();
    system("Color 01");
    char arr[20][30];
    int i, j, k = 10, l = 10, a = rand() % 19, score = 0;
    int lives = 3;

    int snakex[100], snakey[100];
    int snakelength = 1;
    int dir = -1;
    bool firstinput = true;

    snakex[0] = k;
    snakey[0] = l;

    int delay = 200;  // Game speed

    while (lives > 0) {  // loop for 3 lives

        for (i = 0; i < 20; i++) {
            for (j = 0; j < 30; j++) {
                arr[i][j] = ' ';
            }
        }

        arr[a][a] = '*';  // food inside the grid is placed here 

        // snake grid
        for (i = 0; i < 30; i++) arr[0][i] = '#';
        for (i = 0; i < 20; i++) {
            arr[i][0] = '#';
            arr[i][29] = '#';
        }
        for (i = 0; i < 30; i++) arr[19][i] = '#';

        // snake 
        for (int a = 0; a < snakelength; a++) {
            arr[snakex[a]][snakey[a]] = 'O';  // Snake body
        }

        // print the grid on screen
        for (i = 0; i < 20; i++) {
            for (j = 0; j < 30; j++) {
                cout << arr[i][j];
            }
            cout << endl;
        }

        cout << "Score: " << score << " Lives: " << lives << endl;

        // Get user input for direction 
        if (_kbhit()) {
            switch (_getch()) {
            case KEY_UP:
                if (dir != KEY_DOWN) dir = KEY_UP;
                firstinput = false;  // after first input by the user then allow movement
                break;
            case KEY_DOWN:
                if (dir != KEY_UP) dir = KEY_DOWN;
                firstinput = false;
                break;
            case KEY_LEFT:
                if (dir != KEY_RIGHT) dir = KEY_LEFT;
                firstinput = false;
                break;
            case KEY_RIGHT:
                if (dir != KEY_LEFT) dir = KEY_RIGHT;
                firstinput = false;
                break;
            }
        }

        if (!firstinput) {
            int headx = snakex[0];
            int heady = snakey[0];

            // snake head position based on direction
            if (dir == KEY_UP) headx--;
            else if (dir == KEY_DOWN) headx++;
            else if (dir == KEY_LEFT) heady--;
            else if (dir == KEY_RIGHT) heady++;

            // snake body shifted
            for (int i = snakelength; i > 0; i--) {
                snakex[i] = snakex[i - 1];
                snakey[i] = snakey[i - 1];
            }

            // new head added
            snakex[0] = headx;
            snakey[0] = heady;

            // Check if snake eats food
            if (headx == a && heady == a) {
                score += 10;
                a = rand() % 19;  // new food position
                snakelength++;  // snake grows by one O
                delay -= 10;  // speed up the snake
                if (delay < 50) delay = 50;  //  this limits the speed to a minimum speed
            }
        }

        // if snake hits the grid
        if (snakex[0] <= 0 || snakex[0] >= 19 || snakey[0] <= 0 || snakey[0] >= 29) {
            lives--;
            score -= 2;  // score decreased
            snakex[0] = 10;  // reset snake position
            snakey[0] = 10;
            dir = -1;  // reset direction
            firstinput = true;
        }

        // if snake hits itself
        for (int i = 1; i < snakelength; i++) {
            if (snakex[0] == snakex[i] && snakey[0] == snakey[i]) {
                lives--;
                score -= 2;
                snakex[0] = 10;
                snakey[0] = 10;
                dir = -1;
                firstinput = true;
            }
        }

        // game speed
        Sleep(delay);
        system("cls");  // Clear the screen 
    }

    // write the score to the file
    Notescores("scores.txt", score);
    system("Color 05");
    cout << "Oops! You lost the game." << endl;

    bool valid = false;
    int choice;
    while (!valid) {
        cout << "Your score: " << score << endl;
        cout << "1. Play Again" << endl;
        cout << "2. Return to Main Menu" << endl;
        cout << "Choose an option (1-2): ";
        cin >> choice;

        switch (choice) {
        case 1:
            GameStart(player);  // Restart the game
            valid = true;
            break;
        case 2:
            cout << "Returning to Main Menu..." << endl;
            valid = true;
            break;
        default:
            cout << "Invalid choice! Please choose a number between 1 and 2." << endl;
        }
    }
}

void GameExit() {
    system("Color 0E");
    ScreenClear();
    cout << "Thank you for playing the Snake Game!" << endl;
    cout << "Goodbye!" << endl;
    exit(0);  // exit the game
}

void menu() {
    ScreenClear();
    system("Color 03");

    cout << endl;
    cout << "        WELCOME TO  SNAKE GAME MENU        " << endl;
    cout << endl;
    cout << "1) Enter Player Name" << endl;
    cout << "2) View High Scores" << endl;
    cout << "3) Start Game" << endl;
    cout << "4) Exit" << endl;
    cout << "___________________________________________" << endl;
    cout << "Choose an option (1-4): ";
}

int main() {
    int choice;
    string player = "";

    while (true) {
        menu();

        cin >> choice;

        switch (choice) {
        case 1:
            PlayerName(player);
            break;
        case 2:
            highestscores();
            break;
        case 3:
            GameStart(player);
            break;
        case 4:
            GameExit();
            break;
        default:
            cout << "Invalid choice! Please choose a number between 1 and 4." << endl;
        }
    }

    return 0;
}
