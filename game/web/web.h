#ifndef NERDLE_WEB_WEB_H
#define NERDLE_WEB_WEB_H

#include "py.h"
#include "base.h"

#define getNerdleRaw nerdleGetterPython
#define NERDLE_MAGIC_OFFSET 13

void getNerdleSimpleDecryption(char out_result[NERDLE_WORD_LENGTH]) {
    char buf[NERDLE_WORD_LENGTH + 1] = { 0 };
    getNerdleRaw(buf);
    for (int i = 0; i < NERDLE_WORD_LENGTH; i ++) {
        buf[i] -= NERDLE_MAGIC_OFFSET;
    }
    strncpy(out_result, buf, NERDLE_WORD_LENGTH);
}


#endif