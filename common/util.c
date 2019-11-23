//
// Created by Valerio on 23/11/2019.
//

#include <ctype.h>
#include <stdio.h>
#include "util.h"


void prettyPrint(char* str) {
    int i;
    for (i = 0; str[i]; i++) {
        char c = str[i];
        if (i) {
            if (isdigit(str[i]) && !isdigit(str[i - 1])) {
                putchar(' ');
            } else if (!isdigit(c) && !between('a', str[i], 'z')) {
                putchar(' ');
            }
        } else if (!between('A', str[i], 'Z')) {
            c -= 32;
        }

        putchar(c);
    }
}
