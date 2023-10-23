#ifndef NERDLE_BROWSER_BASE_H
#define NERDLE_BROWSER_BASE_H

#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <stdio.h>
#include <stdbool.h>

#ifndef NERDLE_SOLVER_BASE_H
typedef enum {
    Excluded,
    Contained,
    Proper,
    NotJudged,
    Invalid = -1
} State;
#endif

#ifndef NERDLE_WORD_LENGTH
#define NERDLE_WORD_LENGTH 8
#endif

#ifndef NERDLE_WORD_MAX_COUNT
#define NERDLE_WORD_MAX_COUNT 6
#endif

#define NERDLE_NUMBER_COUNT 10
#define NERDLE_OPERATION_BUTTON_COUNT 7

const char PathPosData[] = ".\\data\\pos_list.txt";

int pos_word_frames_x[NERDLE_WORD_LENGTH] = { 0 };
int pos_word_frames_y[NERDLE_WORD_MAX_COUNT] = { 0 };
int pos_numbers_x[NERDLE_NUMBER_COUNT] = { 0 };
int pos_operation_button_x[NERDLE_OPERATION_BUTTON_COUNT] = { 0 };
int pos_numbers_y = 0;
int pos_operation_button_y = 0;
int pos_activate_window_x = 0;
int pos_activate_window_y = 0;

int getOperationButtonPos(char the_operator) {
    switch (the_operator) {
    case '+':
        return 0;
    case '-':
        return 1;
    case '*':
        return 2;
    case '/':
        return 3;
    case '=':
        return 4;
    case 'E':       //Enter
        return 5;
    case 'D':       //delete
        return 6;
    default:
        return -1;
    }
    return -1;
}

bool isOperationButton(char the_operator) {
    switch (the_operator) {
    case '+':
    case '-':
    case '*':
    case '/':
    case '=':
    case 'E':       //Enter
    case 'D':       //delete
        return true;
    default:
        return false;
    }
    return false;
}

void initPos() {
    FILE *fp = fopen(PathPosData, "r");
    for (int i = 0; i < NERDLE_WORD_LENGTH; i ++) {
        fscanf(fp, "%d", &pos_word_frames_x[i]);
    }
    for (int i = 0; i < NERDLE_WORD_MAX_COUNT; i ++) {
        fscanf(fp, "%d", &pos_word_frames_y[i]);
    }
    for (int i = 0; i < NERDLE_NUMBER_COUNT; i ++) {
        fscanf(fp, "%d", &pos_numbers_x[i]);
    }
    fscanf(fp, "%d", &pos_numbers_y);
    for (int i = 0; i < NERDLE_OPERATION_BUTTON_COUNT; i ++) {
        fscanf(fp, "%d", &pos_operation_button_x[i]);
    }
    fscanf(fp, "%d", &pos_operation_button_y);
    fscanf(fp, "%d", &pos_activate_window_x);
    fscanf(fp, "%d", &pos_activate_window_y);

    fclose(fp);
    fp = NULL;
}

#endif