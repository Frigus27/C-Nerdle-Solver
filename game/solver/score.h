#ifndef NERDLE_SOLVER_SCORE_H
#define NERDLE_SOLVER_SCORE_H

#define OBSOLETE_CONTENT

#include "base.h"
#include "match.h"
#include <math.h>
#include <assert.h>

// we use informational entropy to measure the score.

// count how many word matches the current word list, i.e. the words that are guessed previously.
int countMatch(WordList word_list, int word_count, const char* word_range[], int word_range_count) {
    int sum = 0;
    for (int i = 0; i < word_range_count; i++) {
        if (isWordListMatch(word_list, word_count, word_range[i]) == true) {
            sum += 1;
        }
    }
    return sum;
}

// filter out a small range of possible words that match the current word list.
void filterSmallerWordRange(WordList pre_list, int pre_count, char out_smaller_word_range[TOTAL_WORD_COUNT][NERDLE_WORD_LENGTH + 1], int* out_len) {
    int index = 0;
    for (int i = 0; i < TOTAL_WORD_COUNT; i++) {
        if (isWordListMatch(pre_list, pre_count, TotalWordList[i])) {
            strncpy(out_smaller_word_range[index], TotalWordList[i], NERDLE_WORD_LENGTH + 1);
            index ++;
        }
    }
    *out_len = index;
}

// calculate the "recommendation score" of a text-based "word", i.e. the string part of the word.
// The score is actually the infomation entropy of the word. 
double calcInfoEntropyOfText(char smaller_word_range[][NERDLE_WORD_LENGTH + 1], const int len, char text[]) {
    double infoEntropy = 0, possibility = 0;

    int count[SITUATION_COUNT] = { 0 };
    for (int i = 0; i < len; i++) {
        count[judgeWordIntoStateIndex(text, smaller_word_range[i])]++;
    }

    for (int j = 0; j < SITUATION_COUNT; j++) {
        if (count[j] != 0) {
            possibility = (double)count[j] / len;
            infoEntropy -= possibility * log2(possibility);
        }
    }

    return infoEntropy;
}





#endif