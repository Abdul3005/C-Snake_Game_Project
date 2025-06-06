# C-Snake_Game_Project
🐍 Snake Game (Console-Based)
A classic Snake game built using C++, running in the Windows console. Eat food to grow, avoid walls and yourself, and try to get the highest score!

🎮 Features
Grid-based snake movement.

Random food placement.

Score tracking and high score saving.

Life system (3 lives per game).

Persistent leaderboard via scores.txt.

Color-coded console interface.

Keyboard navigation using arrow keys.

🛠 Requirements
Windows OS (due to usage of <Windows.h> and <conio.h>)

C++ compiler (e.g., MinGW, MSVC)

🚀 How to Play
Clone or Download the repository.

Compile Source.cpp using any C++ compiler:
g++ Source.cpp -o SnakeGame

Run the game:
SnakeGame.exe

🎯 Controls
Arrow Keys:

↑ → Move Up

↓ → Move Down

← → Move Left

→ → Move Right

Navigate menus with number keys.

📁 Files
Source.cpp: Main source code file containing all game logic and menu handling.

scores.txt: Stores players' scores persistently (used to display top 3 scores).

🧠 Game Logic Overview
The snake moves inside a 20x30 grid.

Eating food (*) increases your score by +10 and grows the snake.

Hitting a wall or yourself:

Decreases score by -2

Costs one of your three lives.

After 3 lives, the game ends and your score is saved to scores.txt.

📊 High Scores
Top 3 scores are displayed from scores.txt. Scores are sorted in descending order using Selection Sort.

✨ Menu Options
Enter Player Name: Set your name for the session.

View High Scores: View the top 3 scores saved in scores.txt.

Start Game: Begin playing with 3 lives.

Exit: Close the application.

📌 Sample Output (High Scores)

Top 3 highest scores:
74
44
-6
📬 Author Notes
This project is a console-based implementation created for learning and entertainment purposes. Future improvements may include:

Adding sound effects

Custom difficulty levels

Snake body collision improvements
