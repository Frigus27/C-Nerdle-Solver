#ifndef NERDLE_VISUAL_H
#define NERDLE_VISUAL_H

#include "nerdle.h"
#include "color.h"
#include <conio.h>

// inner functions

typedef void (*CallbackDisplayer)(Word word);

Color stateToWord[NotJudged + 1] = {
    { White, Gray },
    { White, Purple},
    { White, Green },
    { White, Black}
};

void printWord(Word word) {
    printf("\r");
    for (int i = 0; i < NERDLE_WORD_LENGTH; i ++) {
        setColor(stateToWord[word.cells[i].state]);
        printf("%c", word.cells[i].symbol);
    }
    setColorDefault();
}

void toggleStateEach(Word *in_out_word, int index, char key, CallbackDisplayer cd) {
    in_out_word->cells[index].state = charToState(key);
    cd(*in_out_word);
}

typedef enum {
    InvalidKey = -1, 
    Enter = '\r', 
    Backspace = '\b',
    StateKey = 114514
} InputKeyState;

InputKeyState checkStateCharacterInput(char key) {
    if (key == '\r') {
        return Enter;
    }
    else if (key == '\b') {
        return Backspace;
    }
    else if (isStateCharacterValid(key)) {
        return StateKey;
    }
    return InvalidKey;
}

bool isCharacterMathOp(char a) {
    return ('0' <= a && a <= '9') || (a == '+' || a == '-' || a == '*' || a == '/' || a == '=');
}

void inputState(Word *in_out_word, CallbackDisplayer cd) {
    int index = 0;
    char key;
    InputKeyState keyState;

    while (true) {
        cd(*in_out_word);
        key = getch();
        keyState = checkStateCharacterInput(key);

        if (keyState == InvalidKey) {
            continue;
        }
        else if (keyState == Backspace) {
            if (index != 0) {
                index --;
                in_out_word->cells[index].state = NotJudged;
            }
        }
        else if (keyState == Enter) {
            if (index == NERDLE_WORD_LENGTH) {
                break;
            }
        }
        else if (keyState == StateKey) {
            if (index <= NERDLE_WORD_LENGTH - 1) {
                in_out_word->cells[index].state = charToState(key);
                index ++;
            }
        }
        
    }
    
    printf("\n");
}

Word inputWord(char out_result[NERDLE_WORD_LENGTH+1], CallbackDisplayer cd) {
    Word word = initWord();
    char key;
    int index = 0;
    while (true) {
        cd(word);
        key = getch();

        if (key == '\b') {
            if (index != 0) {
                index --;
                word.cells[index].symbol = ' ';
            }
        }
        else if (key == '\r') {
            if (index == NERDLE_WORD_LENGTH) {
                break;
            }
        }
        else if (isCharacterMathOp(key)) {
            if (index <= NERDLE_WORD_LENGTH - 1) {
                word.cells[index].symbol = key;
                index ++;
            }
        }
        
    }
    for(int i = 0; i < NERDLE_WORD_LENGTH; i ++) {
        out_result[i] = word.cells[i].symbol;
    }

    //printf("\n");
    return word;
}


#endif