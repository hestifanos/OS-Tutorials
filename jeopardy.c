/*
 * Tutorial 4 Jeopardy Project for SOFE 3950U / CSCI 3020U: Operating Systems
 *
 * Copyright (C) 2015, <GROUP MEMBERS>
 * All rights reserved.
 *
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

int main(void) {
    char buffer[BUFFER_LEN];
    player players[NUM_PLAYERS];

    // Initialize the game
    initialize_game();
    initialize_players(players, NUM_PLAYERS);

    // Main game loop
    while (1) {
        // Display the remaining categories and question values
        display_categories();

        // Get the player's choice of category and value
        printf("Enter category and value (e.g., programming 100): ");
        fgets(buffer, BUFFER_LEN, stdin);
        buffer[strcspn(buffer, "\n")] = '\0'; // Remove newline character

        // Tokenize the input
        char *tokens[3];
        tokenize(buffer, tokens);

        if (tokens[0] == NULL || tokens[1] == NULL) {
            printf("Invalid input. Please enter a category and value.\n");
            continue;
        }

        char *category = tokens[0];
        int value = atoi(tokens[1]);

        // Display the question
        display_question(category, value);

        // Get the player's answer
        printf("Enter your answer: ");
        fgets(buffer, BUFFER_LEN, stdin);
        buffer[strcspn(buffer, "\n")] = '\0'; // Remove newline character

        // Check if the answer is correct
        if (valid_answer(category, value, buffer)) {
            printf("Correct!\n");
            // Update the player's score
            printf("Enter your name: ");
            fgets(buffer, BUFFER_LEN, stdin);
            buffer[strcspn(buffer, "\n")] = '\0'; // Remove newline character
            update_score(players, NUM_PLAYERS, buffer, value);
        } else {
            printf("Incorrect. The correct answer was: %s\n", questions[0].answer);
        }

       

        // Check if all questions have been answered
        bool all_answered = true;
        for (int i = 0; i < NUM_QUESTIONS; i++) {
            if (!questions[i].answered) {
                all_answered = false;
                break;
            }
        }
        if (all_answered) {
            break;
        }
    }

    // Display the final results and exit
    show_results(players, NUM_PLAYERS);
    return EXIT_SUCCESS;
}
