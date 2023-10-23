#ifndef NERDLE_SOLVER_BASE_H
#define NERDLE_SOLVER_BASE_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <time.h>
#include <stdbool.h>

#define INVALID_SYMBOL '%'
#define MATCHED_MARK '#'
#define NERDLE_WORD_LENGTH 8
#define TOTAL_WORD_COUNT 40346
#define TOTAL_ANSWER_COUNT 17723
#define NERDLE_WORD_MAX_COUNT 6
#define SITUATION_COUNT 6561  //3^8
#define STATE_INDEX_SUCCEEDED 6560
#define INPUT_BUF_LENGTH 128
#define STATE_SUCCEEDED "PPPPPPPP"

const char PathWordBank[] = ".\\data\\valid_expressions.txt";
const char PathAnswerList[] = ".\\data\\answer_list.txt";

typedef enum {
    Excluded,
    Contained,
    Proper,
    NotJudged,
    Invalid = -1
} State;

char _stateToChar[3] = { 'E', 'C', 'P' };

typedef struct _Cell {
    State state;
    char symbol;
} Cell;

typedef struct _Word {
    Cell cells[8];
} Word;

typedef Word WordList[];

void printState(Word word) {
    for (int i = 0; i < NERDLE_WORD_LENGTH; i++) {
        putchar(_stateToChar[(int)word.cells[i].state]);
    }
}

void printText(Word word) {
    for (int i = 0; i < NERDLE_WORD_LENGTH; i++) {
        putchar(word.cells[i].symbol);
    }
}

char TotalWordList[TOTAL_WORD_COUNT][NERDLE_WORD_LENGTH + 1];
char TotalAnswerList[TOTAL_ANSWER_COUNT][NERDLE_WORD_LENGTH + 1];

// init step: read the word list
void initWordList() {
    srand(time(NULL));
    memset(TotalWordList, 0, sizeof(TotalWordList));
    FILE* fp = fopen(PathWordBank, "r");
    for (int i = 0; i < TOTAL_WORD_COUNT; i++) {
        fscanf(fp, "%s", TotalWordList[i]);
    }
    fclose(fp);
    fp = fopen(PathAnswerList, "r");
    for (int i = 0; i < TOTAL_ANSWER_COUNT; i++) {
        fscanf(fp, "%s", TotalAnswerList[i]);
    }
    fclose(fp);
}

Word formWordByStateIndex(char text[], int state_index) {
    int state_index_copied = state_index;
    Word new_word;
    for (int i = 0; i < NERDLE_WORD_LENGTH; i++) {
        new_word.cells[i].symbol = text[i];
        new_word.cells[i].state = (State)(state_index_copied % 3);
        state_index_copied /= 3;
    }
    return new_word;
}

bool isWordInBank(char word[NERDLE_WORD_LENGTH + 1]) {
    for (int i = 0; i < TOTAL_WORD_COUNT; i++) {
        if (strcmp(word, TotalWordList[i]) == 0) {
            return true;
        }
    }
    return false;
}

bool isWordInputValid(char input[]) {
    if (strlen(input) != NERDLE_WORD_LENGTH) {
        return false;
    }
    if (isWordInBank(input) == false) {
        return false;
    }
    return true;
}

bool isStateCharacterValid(char stateInput) {
    if (stateInput == _stateToChar[0] || stateInput == _stateToChar[1] || stateInput == _stateToChar[2]) {
        return true;
    }
    return false;
}

bool isStateInputValid(char input[]) {
    for (int i = 0; i < NERDLE_WORD_LENGTH; i++) {
        bool flag_valid = false;
        for (int j = Excluded; j <= Proper; j++) {
            if (_stateToChar[j] == input[i]) {
                flag_valid = true;
                break;
            }
        }
        if (flag_valid == false) {
            return false;
        }
    }
    return true;
}

State charToState(char c) {
    for (int i = Excluded; i <= Proper; i++) {
        if (_stateToChar[i] == c) {
            return (State)i;
        }
    }
    return (State)Invalid;
}

Word formNotJudgedWord(char str[]) {
    Word word;
    for (int i = 0; i < NERDLE_WORD_LENGTH; i ++) {
        word.cells[i].state = NotJudged;
        word.cells[i].symbol = str[i];
    }
    return word;
}

Word initWord() {
    return formNotJudgedWord("        ");
}

bool isWordProper(Word word) {
    for (int i = 0; i < NERDLE_WORD_LENGTH; i ++) {
        if (word.cells[i].state != Proper) {
            return false;
        }
    }
    return true;
}

void pickTemplate(char out_template[]) {
    strcpy(out_template, TotalAnswerList[rand() % TOTAL_ANSWER_COUNT]);
}

#endif