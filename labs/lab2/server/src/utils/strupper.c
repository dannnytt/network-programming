#include "strupper.h"

char* strupper(char* str) {

    if (!str) return NULL;
    for (char* p = str; *p; p++)
        *p = toupper((unsigned char) *p); 

    return str;
}