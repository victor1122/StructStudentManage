#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include "FilterNum.h"


// Clear buffer
int clean_stdin(){
    while (getchar()!='\n');
    return 1;
}
// Number of Student Filter
int filterNum(int a){
    int num=0;
    char dump=0;
    do{  
        printf("\nInput MAX number of student you want to manage (greater than %d): ", a);
    }
    while (((scanf("%d%c", &num, &dump)!=2 || dump!='\n') && clean_stdin()) || num<=a);
    return num;
}

// Input Filter

int filterInput(int MIN, int MAX, char *input) {
    int num = 0;
    char dump = 0;
    do {
        printf("%s ", input);
    } while (((scanf("%d%c", &num, &dump) != 2 || dump != '\n') && clean_stdin()) || num < MIN || num > MAX);
    return num;
}
