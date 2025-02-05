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
#include "questions.h"

// Initializes the array of questions for the game
void initialize_game(void)
{
    // initialize each question struct and assign it to the questions array
    strcpy(questions[0].category, "programming");
    questions[0].value = 100;
    strcpy(questions[0].question, "What is the keyword used to define a function in C?");
    strcpy(questions[0].answer, "void");
    questions[0].answered = false;

    strcpy(questions[1].category, "programming");
    questions[1].value = 200;
    strcpy(questions[1].question, "What is the output of printf(\"%d\", 10 + 20);?");
    strcpy(questions[1].answer, "30");
    questions[1].answered = false;

    strcpy(questions[2].category, "algorithms");
    questions[2].value = 100;
    strcpy(questions[2].question, "What is the time complexity of binary search?");
    strcpy(questions[2].answer, "O(log n)");
    questions[2].answered = false;

    strcpy(questions[3].category, "algorithms");
    questions[3].value = 200;
    strcpy(questions[3].question, "What is the name of the algorithm used to sort an array in O(n log n) time?");
    strcpy(questions[3].answer, "Merge Sort");
    questions[3].answered = false;

    strcpy(questions[4].category, "databases");
    questions[4].value = 100;
    strcpy(questions[4].question, "What does SQL stand for?");
    strcpy(questions[4].answer, "Structured Query Language");
    questions[4].answered = false;

    strcpy(questions[5].category, "databases");
    questions[5].value = 200;
    strcpy(questions[5].question, "What is a primary key in a database?");
    strcpy(questions[5].answer, "A unique identifier for a record");
    questions[5].answered = false;
}

// Displays each of the remaining categories and question dollar values that have not been answered
void display_categories(void)
{
    // print categories and dollar values for each unanswered question in questions array
    for (int i = 0; i < NUM_QUESTIONS; i++) {
        if (!questions[i].answered) {
            printf("Category: %s, Value: %d\n", questions[i].category, questions[i].value);
        }
    }
}

// Displays the question for the category and dollar value
void display_question(char *category, int value)
{

 for (int i = 0; i < NUM_QUESTIONS; i++) {
        if (strcmp(questions[i].category, category) == 0 && questions[i].value == value) {
            printf("Question: %s\n", questions[i].question);
            return;
        }
    }
    printf("Question not found for category: %s and value: %d\n", category, value);
}

// Returns true if the answer is correct for the question for that category and dollar value
bool valid_answer(char *category, int value, char *answer)
{
    // Look into string comparison functions
    for (int i = 0; i < NUM_QUESTIONS; i++) {
        if (strcmp(questions[i].category, category) == 0 && questions[i].value == value) {
            return strcmp(questions[i].answer, answer) == 0;
        }
    }
    
    return false;
}

// Returns true if the question has already been answered
bool already_answered(char *category, int value)
{
    // lookup the question and see if it's already been marked as answered
    for (int i = 0; i < NUM_QUESTIONS; i++) {
        if (strcmp(questions[i].category, category) == 0 && questions[i].value == value) {
            return questions[i].answered;
        }
    }
    return false;
}
