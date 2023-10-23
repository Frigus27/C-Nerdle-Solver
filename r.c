#include <windows.h>
#include <stdio.h>

int main() {
    POINT p;
    while (1) {
        GetCursorPos(&p);
        printf("\r (%ld, %ld)", p.x, p.y);
        Sleep(100);
    }
}