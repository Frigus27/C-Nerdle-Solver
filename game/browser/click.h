#ifndef NERDLE_BROWSER_CLICK_H
#define NERDLE_BROWSER_CLICK_H

#include "base.h"

#define POS_ACTIVATE_WINDOW_X 161
#define POS_ACTIVATE_WINDOW_Y 285

void click(int x, int y) {
    SetCursorPos(x, y);
    mouse_event(MOUSEEVENTF_LEFTDOWN|MOUSEEVENTF_LEFTUP,0,0,0,0);
}

bool getPos(char key_to_press, int *out_x, int *out_y) {
    if ('0' <= key_to_press && key_to_press <= '9') {
        *out_y = pos_numbers_y;
        if ('0' == key_to_press) {
            *out_x = pos_numbers_x[NERDLE_NUMBER_COUNT - 1];
        }
        else {
            *out_x = pos_numbers_x[key_to_press - '0' - 1];
        }
        return true;
    }
    else if (isOperationButton(key_to_press)) {
        *out_x = pos_operation_button_x[getOperationButtonPos(key_to_press)];
        *out_y = pos_operation_button_y;
        return true;
    }
    else if (key_to_press == 'A') {
        *out_x = pos_activate_window_x;
        *out_y = pos_activate_window_y;
        return true;
    }
    return false;
}

void activateWindow() {
    int x, y;
    getPos('A', &x, &y);
    click(x, y);
    Sleep(250);
}

void sendAnswer(char word_to_send[NERDLE_WORD_LENGTH + 1]) {
    int x, y;
    activateWindow();
    for (int i = 0; i < NERDLE_WORD_LENGTH; i ++) {
        getPos(word_to_send[i], &x, &y);
        click(x, y);
        // to lengthen the click process
        Sleep(250);
    }
    getPos('E', &x, &y);
    click(x, y);
    Sleep(250);
}

#endif