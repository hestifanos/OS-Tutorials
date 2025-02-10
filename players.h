/*
 * Tutorial 4 Jeopardy Project for SOFE 3950U / CSCI 3020U: Operating Systems
 *
 * Copyright (C) 2015, <GROUP MEMBERS>
 * All rights reserved.
 *
 */
#ifndef PLAYERS_H_
#define PLAYERS_H_

#include <stdbool.h>

#define MAX_LEN 256

// Player struct for each player:
typedef struct {
    char name[MAX_LEN];
    int score;
} player;

// Initialize the players by setting names and scores to 0:
extern void initialize_players(player *players, int num_players);

// Return true if the player name matches one of the existing players:
extern bool player_exists(player *players, int num_players, char *name);

// Go through the list of players and update their scores given their name:
extern void update_score(player *players, int num_players, char *name, int score);

// Display the players and their scores in descending order:
extern void show_results(player *players, int num_players);

#endif /* PLAYERS_H_ */
