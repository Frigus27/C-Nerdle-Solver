#ifndef NERDLE_WEB_BASE_H
#define NERDLE_WEB_BASE_H

#define NERDLE_WORD_LENGTH 8

#include <stdbool.h>
#include "inner/link.h"
#include "inner/md5.h"

typedef char NerdleWord[NERDLE_WORD_LENGTH + 1];
typedef void (*NerdleWordGetter)(NerdleWord);


#endif