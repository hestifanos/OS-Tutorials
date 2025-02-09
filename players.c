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
#include "players.h"

// Initialize the players by setting their names and scores to 0:
void initialize_players(player *players, int num_players) 
{
    for (int i = 0; i < num_players; i++) 
    {
        printf("Enter player %d name: ", i + 1);
        fgets(players[i].name, MAX_LEN, stdin);
        players[i].name[strcspn(players[i].name, "\n")] = '\0'; // to remove newline character
        players[i].score = 0;
    }
}

// Return true if the player name matches one of the existing players:
bool player_exists(player *players, int num_players, char *name)
{
    for (int i = 0; i < num_players; i++)
    {
        if (strcmp(players[i].name, name) == 0)
        {
            return true;
        }
    }
    return false;
}

// Go through the list of players and update the score for each player given their name:
void update_score(player *players, int num_players, char *name, int score)
{
    for (int i = 0; i < num_players; i++)
    {
        if (strcmp(players[i].name, name) == 0)
        {
            players[i].score += score;
            return;
        }
    }
}

// Function to compare/sort players scores in descending order:
int compare_scores(const void *a, const void *b)
{
    return ((player *)b)->score - ((player *)a)->score;
}

// Show players and their scores in descending order:
void show_results(player *players, int num_players)
{
    qsort(players, num_players, sizeof(player), compare_scores);
    
    printf("\n--- FINAL RESULTS ---\n");
    for (int i = 0; i < num_players; i++)
    {
        printf("%d. %s - $%d\n", i + 1, players[i].name, players[i].score);
    }
}
