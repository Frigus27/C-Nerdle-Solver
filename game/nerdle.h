#ifndef NERDLE_NERDLE_H
#define NERDLE_NERDLE_H

#include "solver/solver.h"
#include "web/web.h"
#include "browser/browser.h"

bool getNerdleToday(char out_nerdle_today[NERDLE_WORD_LENGTH + 1]) {
    // Try simple decryption first
    char buf[128] = { 0 }, test_buf[128] = { 0 };
    getNerdleSimpleDecryption(buf);

    if (isWordInBank(buf)) {
        strncpy(out_nerdle_today, buf, NERDLE_WORD_LENGTH);
        return true;
    }
    else {
        // Use stupid method
        getNerdleRaw(buf);
        int offset;
        for (int i = 0; i < 3; i ++) {
            offset = buf[i + 4] - '=';
            for (int j = 0; j < NERDLE_WORD_LENGTH; j ++) {
                test_buf[j] = buf[j] - offset;
            }
            if (isWordInBank(test_buf)) {
                strncpy(out_nerdle_today, test_buf, NERDLE_WORD_LENGTH);
                return true;
            }
        }
    }
    return false;
}

#endif