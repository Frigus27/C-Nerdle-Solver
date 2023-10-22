#ifndef NERDLE_SOLVER_MATCH_H
#define NERDLE_SOLVER_MATCH_H

#include "base.h"

// @param word The word to test
// @param text the text to be test, including at least 8 characters
bool isWordMatch(Word word, const char text[]) {
    char text_copied[NERDLE_WORD_LENGTH];
    strncpy(text_copied, text, NERDLE_WORD_LENGTH);
    // Proper
    for (int i = 0; i < NERDLE_WORD_LENGTH; i ++) {
        if (word.cells[i].state == Proper) {
            if (text_copied[i] != word.cells[i].symbol) {
                return false;
            }
            else {
                // matched successfully
                text_copied[i] = MATCHED_MARK;
                word.cells[i].symbol = MATCHED_MARK;
            }
        }
    }
    // Contained
    for (int i = 0; i < NERDLE_WORD_LENGTH; i ++) {
        if (word.cells[i].symbol == MATCHED_MARK) {
            continue;
        }
        if (word.cells[i].state == Contained) {
            if (text_copied[i] == word.cells[i].symbol) {
                return false;
            }
            else {
                char *pos = strchr(text_copied, word.cells[i].symbol);
                if (pos == NULL) {
                    return false;
                }
                else {
                    *pos = MATCHED_MARK;
                    word.cells[i].symbol = MATCHED_MARK;
                }
            }
        }
    }
    // Excluded
    for (int i = 0; i < NERDLE_WORD_LENGTH; i ++) {
        if (word.cells[i].symbol == MATCHED_MARK) {
            continue;
        }
        if (word.cells[i].state == Excluded) {
            if (strchr(text_copied, word.cells[i].symbol) != NULL) {
                return false;
            }
        }
    }
    return true;
}

// @param word_list the word list to be used to test
// @param word_count the count of the words in the word list, i.e. len(word_list)
// @param text the text to be test, including at least 8 characters
bool isWordListMatch(WordList word_list, int word_count, const char text[]) {
    for (int i = 0; i < word_count; i ++) {
        if (isWordMatch(word_list[i], text) == false) {
            return false;
        }
    }
    return true;
}

// judge the word by the template.
// @param text_source the text to be judged.
// @param text_template the text template to judge.
// @returns the word that involves the text source and its judge result.
Word judgeWord(char text_source[], char text_template[]) {
    Word word;
    char text_source_copied[NERDLE_WORD_LENGTH + 1], text_template_copied[NERDLE_WORD_LENGTH + 1];
    strncpy(text_source_copied, text_source, NERDLE_WORD_LENGTH);
    strncpy(text_template_copied, text_template, NERDLE_WORD_LENGTH);

    // judge "Proper" first
    for (int i = 0; i < NERDLE_WORD_LENGTH; i ++) {
        if (text_template_copied[i] == text_source_copied[i]) {
            word.cells[i].symbol = text_source_copied[i];
            word.cells[i].state = Proper;
            text_source_copied[i] = INVALID_SYMBOL;
            text_template_copied[i] = INVALID_SYMBOL;
        }
    }
    // then "Contained"
    for (int i = 0; i < NERDLE_WORD_LENGTH; i ++) {
        if (text_template_copied[i] == INVALID_SYMBOL) {
            continue;
        }
        char *pos = strchr(text_source_copied, text_template_copied[i]);
        if (pos != NULL) {
            int index = pos - text_source_copied;
            word.cells[index].symbol = *pos;
            word.cells[index].state = Contained;
            *pos = INVALID_SYMBOL;
            text_template_copied[i] = INVALID_SYMBOL;
        }
    }
    // then "Excluded". It is easy to confirm that all other characters are "Excluded".
    for (int i = 0; i < NERDLE_WORD_LENGTH; i ++) {
        if (text_source_copied[i] != INVALID_SYMBOL) {
            word.cells[i].symbol = text_source_copied[i];
            word.cells[i].state = Excluded;
        }
    }
    return word;
}


int judgeWordIntoStateIndex(char text_source[], char text_template[]) {
    char text_source_copied[NERDLE_WORD_LENGTH + 1], text_template_copied[NERDLE_WORD_LENGTH + 1];
    strncpy(text_source_copied, text_source, NERDLE_WORD_LENGTH);
    strncpy(text_template_copied, text_template, NERDLE_WORD_LENGTH);

    int state = 0;

    // judge "Proper" first
    for (int i = 0; i < NERDLE_WORD_LENGTH; i ++) {
        if (text_template_copied[i] == text_source_copied[i]) {
            state += Proper * pow(3, i);
            text_source_copied[i] = INVALID_SYMBOL;
            text_template_copied[i] = INVALID_SYMBOL;
        }
    }
    // then "Contained"
    for (int i = 0; i < NERDLE_WORD_LENGTH; i ++) {
        if (text_template_copied[i] == INVALID_SYMBOL) {
            continue;
        }
        char *pos = strchr(text_source_copied, text_template_copied[i]);
        if (pos != NULL) {
            state += Contained * pow(3, i);
            *pos = INVALID_SYMBOL;
            text_template_copied[i] = INVALID_SYMBOL;
        }
    }
    // then "Excluded". It is easy to confirm that all other characters are "Excluded".
    for (int i = 0; i < NERDLE_WORD_LENGTH; i ++) {
        if (text_source_copied[i] != INVALID_SYMBOL) {
            // do nothing
        }
    }
    return state;
}
#endif