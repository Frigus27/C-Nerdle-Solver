#ifndef NERDLE_BROWSER_DETECT_H
#define NERDLE_BROWSER_DETECT_H

#include "base.h"

State all_states[NERDLE_WORD_LENGTH][NERDLE_WORD_MAX_COUNT];
HDC hDC;

const int RValues[] = {22, 130, 57, 152};
const int GValues[] = {24, 4, 136, 148};
const int BValues[] = {3, 88, 116, 132};

void initDetectModule() {
    for (int i = 0; i < NERDLE_WORD_LENGTH; i ++) {
        for (int j = 0; j < NERDLE_WORD_MAX_COUNT; j ++) {
            all_states[i][j] = NotJudged;
        }
    }
    hDC = GetDC(NULL);
}

void releaseDetectModule() {
    ReleaseDC(NULL, hDC);
}

void scanFrameStates() {
    COLORREF color;
    for (int j  = 0; j < NERDLE_WORD_MAX_COUNT; j ++) {
        for (int i = 0; i < NERDLE_WORD_LENGTH; i ++) {
            color = GetPixel(hDC, pos_word_frames_x[i], pos_word_frames_y[j]);
            for (int m = Excluded; m < NotJudged; m ++) {
                if (RValues[m] == GetRValue(color)) {
                    all_states[i][j] = (State)m;
                    break;
                }
            }
            
        }
    }
}

void getLineStates(int line_index, State out_line_state[NERDLE_WORD_LENGTH]) {
    for (int i = 0; i < NERDLE_WORD_LENGTH; i ++) {
        out_line_state[i] = all_states[i][line_index];
    }
}

#endif