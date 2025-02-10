/*
 * Tutorial 4 Jeopardy Project for SOFE 3950U / CSCI 3020U: Operating Systems
 *
 * Copyright (C) 2024, <GROUP 6>
 * All rights reserved.
 * Kishan,Hermon,Ronald,Kanishk
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "questions.h"
#include "players.h"
#include "jeopardy.h"

// Put macros or constants here using #define
#define BUFFER_LEN 256
#define NUM_PLAYERS 4

// Put global environment variables here

// Processes the answer from the user containing what is or who is and tokenizes it to retrieve the answer.
void tokenize(char *input, char **tokens) {
    char *token = strtok(input, " ");
    int i = 0;
    while (token != NULL) {
        tokens[i++] = token;
        token = strtok(NULL, " ");
    }
    tokens[i] = NULL;
}

// Displays the game results for each player, their name and final score, ranked from first to last place
void show_results(player *players, int num_players) {
    // Sort players by score in descending order
    for (int i = 0; i < num_players - 1; i++) {
        for (int j = i + 1; j < num_players; j++) {
            if (players[i].score < players[j].score) {
                player temp = players[i];
                players[i] = players[j];
                players[j] = temp;
            }
        }
    }

    // Display the results
    printf("Final Results:\n");
    for (int i = 0; i < num_players; i++) {
        printf("%s: %d\n", players[i].name, players[i].score);
    }
}

// Initializes the players
void initialize_players(player *players, int num_players) {
    for (int i = 0; i < num_players; i++) {
        printf("Enter name for player %d: ", i + 1);
        fgets(players[i].name, MAX_LEN, stdin);
        // Remove newline character from the name
        players[i].name[strcspn(players[i].name, "\n")] = '\0';
        players[i].score = 0;
    }
}

// Updates the score of a player
void update_score(player *players, int num_players, char *name, int score) {
    for (int i = 0; i < num_players; i++) {
        if (strcmp(players[i].name, name) == 0) {
            players[i].score += score;
            return;
        }
    }
}

int gameState;
int numQ = NUM_QUESTIONS;

int main(void){
       
    // Buffer for user input
    char buffer[BUFFER_LEN] = { 0 };
        
    // An array of 4 players, may need to be a pointer if you want it set dynamically
        player players[NUM_PLAYERS];    

    // a exapmle: player 1 is named Omar
	// players[0].name = "Omar";
    strcpy(players[0].name, "Omar");
    printf("%s\n", players[0].name);

    

    // Display the game introduction aswell as initialize the questions
    initialize_game();

    printf("%s\n", "PLEASE USE ALL CAPS WHEN RESPONDING");
    printf("%s\n", "Before answering a question PLEASE reply with name first");
    printf("%s\n", "Answer must begin with what or who");
    // Prompt for players names
    // initialize each of the players in the array
    for(int i = 0; i < NUM_PLAYERS; i++){
        printf("%s %d: ", "Enter Player", i+1);
        scanf("%[^\n]%*c", players[i].name);
        players[i].score = 0;
        printf("\n");
    }

    // Perform an infinite loop getting command input from users until game ends
    gameState = 1;
    char str[4][BUFFER_LEN] = {{0}};
    while (gameState == 1){
        char *token;
        char *name, *word;
        //display questions
        display_categories();

        //get name
        printf("%s\n", "Please enter your name to select a category");
        fgets(buffer, BUFFER_LEN, stdin);
        name = strtok(buffer, "\n");

        //check if player is in game
        if(player_exists(players, NUM_PLAYERS, name) == true){
            //ask player to pick category and value
            printf("%s\n", "Please enter a category value");
            fgets(buffer, BUFFER_LEN, stdin);

            //rmv \n
            token = strtok(buffer, "\n");
            //get category
            word = strtok(token, " ");
            strcpy(str[0], word);
            //get val
            word = strtok(NULL, " ");
            strcpy(str[1], word);
            token = NULL;

            if(already_answered(str[0], atoi(str[1])) == true){
                printf("%s\n", "please select an unselected value and category");
                //display question
                display_question(str[0], atoi(str[1]));
            }else{
                //display question
                display_question(str[0], atoi(str[1]));
            }

            memset(buffer, 0, BUFFER_LEN);
            fgets(buffer, BUFFER_LEN, stdin);

            //rmv \n
            token = strtok(buffer, "\n");

            //get beginning
            word = strtok(token, " ");
            strcpy(str[2], word);

            //get rest of answer
            word = strtok(NULL, "");
            strcpy(str[3], word);
            token = NULL;

            //1 less question to do
            numQ--;

            //validate question
            if(valid_answer(str[0], atoi(str[1]), str[3], str[2]) == true){
                printf("%s\n", "Correct!");
                update_score(players, NUM_PLAYERS, name, atoi(str[1]));
            }else{
                printf("%s\n", "Incorrect!");
                display_answer(str[0], atoi(str[1]));
            }

        }else{
            printf("%s\n", "Enter a players name that already exists");
        }

        //check how many questions left
        if(numQ <= 0){
            gameState = 0;
        }
    }

    show_results(players, NUM_PLAYERS);

    return EXIT_SUCCESS;
}
