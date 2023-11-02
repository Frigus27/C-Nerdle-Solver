#ifndef NERDLE_SOLVER_SOLVER_H
#define NERDLE_SOLVER_SOLVER_H

#include "base.h"
#include "score.h"
#include "match.h"

// The best startup of a game that is calculated before
#define SOLVER_FIRST_WORD "5*8/10=4"
#define SOLVER_FIRST_WORD_SCORE 8973989

// search a proper word.
// return false if the search failed.
bool searchWord(char smaller_word_range[][NERDLE_WORD_LENGTH + 1], const int len, char out_result[], long long* out_score_max) {
    double current_entropy = 0;
    long long score_max = 0;
    char winner_word[NERDLE_WORD_LENGTH + 1];
    bool flag = false;

    for (int i = 0; i < len; i++) {
        current_entropy = 1e6 * calcInfoEntropyOfText(smaller_word_range, len, smaller_word_range[i]);
        if (current_entropy >= score_max) {
            flag = true;
            score_max = (long long)current_entropy;
            strncpy(winner_word, smaller_word_range[i], NERDLE_WORD_LENGTH + 1);
        }
    }
    if (flag == true) {
        *out_score_max = score_max;
        strcpy(out_result, winner_word);
    }
    return flag;
}

// get the next guess from the program.
// the *only* interface that is recommended to use in the outer environment.
bool getNextGuess(Word previous_guessed_feedback_list[NERDLE_WORD_MAX_COUNT], int list_length, char out_next_guess[NERDLE_WORD_LENGTH + 1], long long *out_next_guess_score) {
    assert(list_length >= 0);
    if (list_length > NERDLE_WORD_MAX_COUNT) {
        return false;
    }

    else if (list_length == 0) {
        strcpy(out_next_guess, SOLVER_FIRST_WORD);
        *out_next_guess_score = SOLVER_FIRST_WORD_SCORE;
        return true;
    }
    else {
        int len;
        char smaller_word_range[TOTAL_WORD_COUNT][NERDLE_WORD_LENGTH + 1] = { 0 };
        long long current_score = 0;
        char selected_word[NERDLE_WORD_LENGTH + 1] = { 0 };

        filterSmallerWordRange(previous_guessed_feedback_list, list_length, smaller_word_range, &len);
        bool is_succeeded = searchWord(smaller_word_range, len, selected_word, &current_score);
        if (is_succeeded == false) {
            return false;
        }
        strcpy(out_next_guess, selected_word);
        *out_next_guess_score = current_score; 
        return true;
    }
    return false;
}

#endif