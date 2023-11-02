// calculate the proper link of today's game.

#ifndef NERDLE_WEB_LINK_H
#define NERDLE_WEB_LINK_H

#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>
#include "md5.h"

#define LENGTH_MD5 32
#define LENGTH_INPUT 8

const time_t referring_time_stamp = 1697472000 + 8 * 3600;
const int number_of_question = 635;
const char nerdle_link[] = "https://nerdlegame.com";
const char url_prefix[] = "/words/";

int getSolutionIndex() {
    time_t t_now;
    time(&t_now);
    int number = (t_now - referring_time_stamp) / 86400 + number_of_question;
    return number;
}

void getLink(char out_link[128], char out_url[128]) {
    int solution_index = getSolutionIndex();
    char solution_index_str[LENGTH_INPUT] = { 0 };
    char out_url_buffer[128] = { 0 };
    strcpy(out_url_buffer, url_prefix);
    sprintf(solution_index_str, "%d", solution_index);
    char *md5_str = getMd5((unsigned char*)solution_index_str);
    strcat(out_url_buffer, md5_str);
    strcpy(out_url, out_url_buffer);
    strcpy(out_link, nerdle_link);
    free(md5_str);
}


#endif