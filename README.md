**Jeopardy Game (C)**
A command-line implementation of the classic Jeopardy game for SOFE 3950U: Operating Systems.

**Features**
Supports 4 players with names and score tracking.
Categories: Programming, Algorithms, Databases.
Players select category & question value, answer in Jeopardy format ("What is" / "Who is").
Automatic score updating for correct answers.
Tracks answered questions to prevent reuse.
Final scoreboard ranking players at the end.

**How to Build & Run**
1. Compile the program using make
**make**
2. Run the Jeopardy game
**./jeopardy**
   

**Project Structure**

├── jeopardy.c      # Main game logic
├── jeopardy.h      # Function declarations
├── players.c       # Player-related functions
├── players.h       # Player struct and function prototypes
├── questions.c     # Question-related functions
├── questions.h     # Question struct and function prototypes
├── Makefile        # Compilation instructions
Game Rules

**Game Setup**
Enter names of 4 players.
Game starts with all questions available.
Turn-Based Play

A player picks a category & dollar value.
The question is displayed.
Player answers starting with "What is" or "Who is".

**Scoring**

Correct Answer → Earns the question’s value.
Incorrect Answer → No points awarded.

**Game End**

Once all questions are answered, the final rankings are displayed.
The player with the highest earnings wins.
Enhancements
Randomized questions for multiple playthroughs.
Automatic player ranking after the game.
Category & question validation to ensure proper gameplay.
