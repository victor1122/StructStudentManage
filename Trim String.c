#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "TrimString.h"
#include <ctype.h>

int specialChar(char c) {
    if ((c >= 65 && c <= 90) || (c >= 97 && c <= 122) || c == '\0') //ASCII of special characters
    {
        return 0; //NOT special characters
    }
    return 1; //special characters
}

//Name Filter

char *rightName(char *name) {
    int j = 0, k;
    while (name[j] != '\0') { //till the end of string
        while (specialChar(name[j]) == 1 && specialChar(name[j + 1]) == 1) {
            k = j;
            while (name[k] != '\0') {
                name[k] = name[k + 1]; //eliminate special character
                k++;
            }
        }
        j++;
    }
    j = 0;
    while (name[j] != '\0') {
        if (specialChar(name[j]) == 1) {
            name[j] = ' '; //change all special characters into white-space
        }
        j++;
    }
    for (int i = 0; i < strlen(name); i++)
        if (i == 0 || (i > 0 && name[i - 1] == ' '))
            name[i] = toupper(name[i]);
    return name;
}

char* lTrim(char s[]) {
    int i = 0;
    while (s[i] == ' ')
        i++;
    if (i > 0)
        strcpy(&s[0], &s[i]);
    return s;
}

char* rTrim(char s[]) {
    int i = strlen(s) - 1;
    while (s[i] == ' ')
        i--;
    s[i + 1] = '\0';
    return s;
}

char* trim(char s[]) {
    rTrim(lTrim(s));
    char *ptr = strstr(s, "  ");
    while (ptr != NULL) {
        strcpy(ptr, ptr + 1);
        ptr = strstr(s, "  ");
    }
    return s;
}

char* nameStr(char s[]) {
    trim(s);
    strlwr(s);
    int l = strlen(s);
    int i;
    for (i = 0; i < l; i++)
        if (i == 0 || (i > 0 && s[i - 1] == ' '))
            s[i] = toupper(s[i]);
    return s;
}

char* strupr(char* s) {
    char* p = s;
    while (*p = toupper(*p)) p++;
    return s;
}

char* strlwr(char* s) {
    char* p = s;
    while (*p = tolower(*p)) p++;
    return s;
}

int checkID(char id[]){
    if(id[0] == 'S' || id[0]=='0') return 1;
    if(id[1] == 'E' || id[1] == 'B') return 2;
    for(int i=2; i<8; i++)
        if(id[i]>='0' && id[i]<='9') return 3;
    return -1;
}