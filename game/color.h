// CUI colorful output for windows

#ifndef NERDLE_SOLVER_COLOR_H
#define NERDLE_SOLVER_COLOR_H

#include <windows.h>
#include <stdio.h>

typedef enum {
    Gray = 8, Black = 0, Blue, Green, Celeste, Red, Purple, Yellow, White, Default=White
} ColorID;


typedef struct _Color {
    ColorID fore;
    ColorID back;
} Color;

int colorToRealIndex(Color color) {
    return (int)(color.fore) + (int)(color.back) * 16;
}

Color getColor(ColorID fore, ColorID back) {
    Color color = {fore, back};
    return color;
}

Color getColorByFore(ColorID fore) {
    return getColor(fore, Black);
}

void setColor(Color color) {
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | colorToRealIndex(color));
}

void setColorDefault() {
    setColor(getColorByFore(Default));
}

#endif