#ifndef NERDLE_WEB_PY_H
#define NERDLE_WEB_PY_H

#include "base.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

const char PythonCode[] = "import sys\nimport requests\ndata=requests.get(sys.argv[1])\nwith open(\"data.txt\",\"w+\",encoding=\"utf-8\") as f:\n\tf.write(data.text)\n";

void nerdleGetterPython(char out_result[]) {
    FILE *fp = fopen("_getdata_.py","w+");
    fprintf(fp, "%s", PythonCode);
    fclose(fp);
    fp = NULL;

    char link[128] = { 0 }, url[128] = { 0 }, command[1024] = { 0 };
    getLink(link, url);
    strcat(link, url);
    sprintf(command, "python _getdata_.py %s > nul", link);
    system(command);
    fp = fopen("data.txt", "r");
    char buf[128];
    fscanf(fp, "%s", buf);
    strncpy(out_result, buf, NERDLE_WORD_LENGTH);

    fclose(fp);
    fp = NULL;
    system("del /f /s /q _getdata_.py > nul");
    system("del /f /s /q data.txt > nul");
}


#endif