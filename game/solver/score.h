#ifndef NERDLE_SOLVER_SCORE_H
#define NERDLE_SOLVER_SCORE_H

#define OBSOLETE_CONTENT

#include "base.h"
#include "match.h"
#include <math.h>
#include <assert.h>

// we use informational entropy to measure the score.

int countMatch(WordList word_list, int word_count, const char* word_range[], int word_range_count) {
    int sum = 0;
    for (int i = 0; i < word_range_count; i++) {
        if (isWordListMatch(word_list, word_count, word_range[i]) == true) {
            sum += 1;
        }
    }
    return sum;
}


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


double calcInfoEntropyOfText(char smaller_word_range[][NERDLE_WORD_LENGTH + 1], const int len, char text[]) {
    OBSOLETE_CONTENT{
        //assert(pre_count < NERDLE_WORD_MAX_COUNT);
        /*
        Word word_list[NERDLE_WORD_MAX_COUNT];
        memset(word_list, 0, sizeof(word_list));
        for (int i = 0; i < pre_count; i ++) {
            word_list[i] = pre_list[i];
        }
        int word_count = pre_count + 1;
        */



        /* obsolete method which gens a HUGE constant
        // form a (3,3,3,...,3) list
        for (int i = 0; i < pow(3, NERDLE_WORD_LENGTH); i ++) {
            Word new_word_to_test = formWordByStateIndex(text, i);
            word_list[word_count - 1] = new_word_to_test;
            int match_count = countMatch(word_list, word_count);
            if (match_count != 0) {
                possibility = (double) match_count / (double) TOTAL_WORD_COUNT;
                infoEntropy -= possibility * log2(possibility);
            }
        }
        */

        // get a smaller word range


        // calc entropy
    }
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