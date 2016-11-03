/* 
 * File:   main.c
 * Author: DELL
 *
 * Created on July 13, 2015, 8:34 AM
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "FilterNum.h"
#include "TrimString.h"

int currentSize=0;
/*
 * 
 */
typedef struct ID { // Struck
    char name[40];
    char email[100];
    int yob;
    char id[7];
} ID;

void addAStudent(int SIZE, struct ID table[]);
void printStudentList( struct ID table[]);
int searchAStudent(char name[], struct ID table[]);
int searchStudents(char searchName[], int SIZE, struct ID table[]);
void removeAStudent(char removeName[], struct ID table[]);
void removeStudents(char removeName[], struct ID table[]);

int main(int argc, char** argv) {
    int snum, i;
    snum = filterNum(0);
    ID table[snum];
    int count = 0;
    int loop, menu, SIZE = 0;
    des:;
    do {
        printf("1. Add a student\n");
        printf("2. Remove a student\n");
        printf("3. Find a student\n");
        printf("4. Quit\n");
        menu = filterInput(1, 4, "Choose from 1 to 4: ");
        fpurge(stdin);
        switch (menu) {
            case 1:
                {
                    addAStudent(snum, table);
                    printStudentList(table);
                    printf("\n\n");
                    goto des;
                    break;
                }
            case 2:
                {
                    char tmpName[40];
                    printf("Input name to remove: ");
                    gets(tmpName);
                    removeStudents(tmpName, table);
                    printf("\nList of student after remove student name %s", nameStr(tmpName));
                    printStudentList(table);
                    break;
                }
            case 3:
                {
                    char tmpName[60];
                    printf("Input name to search: ");
                    gets(tmpName);
                    searchStudents(tmpName, snum, table);
                    break;
                }
            case 4:
                ;
                break;
        }
        printf("\n\nContinue? \n1. Yes\n2. No\n====> ");
        scanf("%d", &loop);
    } while (loop == 1);
    return (EXIT_SUCCESS);
}

//ADD STUDENT DATABASE

void addAStudent(int SIZE, struct ID table[]) {
    char tmpName[40];
    char tmpID[10];
    printf("Max student can be input is %d\nInput \"0\" to end the input\n", SIZE - (currentSize));
    do {
        fpurge(stdin);
        printf("Input name[%d] (max 40 chars): ", currentSize + 1);
        gets(tmpName);
        nameStr(tmpName);
        strcpy(table[currentSize].name, tmpName);
        if (strcmp(tmpName, "End") == 0) break;
        fpurge(stdin);
        printf("Input email[%d]: ", (currentSize) + 1);
        scanf("%s", table[(currentSize)].email);
        table[currentSize].yob = filterInput(1900, 2015, "Input year of birth: ");
        int flag;
        int check=0;
        do{
            flag=0;
            printf("\nInput ID[%d]: ", (currentSize) + 1);
            scanf("%10s", tmpID);
            strupr(tmpID);
            check = checkID(tmpID);
            for(int i = 0; i < (currentSize); i++){
                if(strcmp(tmpID, table[i].id) == 0)
                flag = 1;
            }
        }while(strlen(tmpID) != 7 || flag==1 || check <0);
        strcpy(table[(currentSize)].id, tmpID);
        (currentSize)++;
    } while ((currentSize) < SIZE);
    }

//PRINT LIST

void printStudentList(struct ID table[]) {
    if (currentSize <= 0) {
        printf("\nSorry, the list is empty!\n");
        return;
    }
    int i;
    printf("\nHere is the list of %d students: \n", currentSize);
    fpurge(stdin);
    printf("\n|%20s\t|%8s\t|%20s\t\t|%15s|\n", "Name", "ID", "Email", "Year Of Birth ");
    for (i = 0; i <= 98; i++) printf("-");
    printf("\n");
    for (i = 0; i < currentSize; i++)
        printf("|%20s\t|%10s\t|%30s\t|%10d\t|\n", (table[i].name), (table[i].id), (table[i].email), (table[i].yob));
    printf("\n");
}

//SEARCH A STUDENT

int searchAStudent(char name[], struct ID table[]) {
    char tmpName[50];
    strcpy(tmpName, name);
    nameStr(tmpName);
    int i;
    for (i = 0; i < currentSize; i++)
        if (strcmp(tmpName, table[i].name) == 0)
            return i;
    return -1;
}

//SEARCH STUDENTS

int searchStudents(char searchName[], int SIZE, struct ID table[]) {
    char tmpName[50], a[SIZE];
    int count;
    strcpy(tmpName, searchName);
    nameStr(tmpName);
    int i, j=0;
    for (i = 0; i < currentSize; i++){
        if (strcmp(tmpName, table[i].name) == 0){
            a[j]=i+1;
            j++;
            count++;
        }
        if (i==(currentSize) &&(strcmp(tmpName, table[i].name) != 0)){
            printf("Not found student name %s", nameStr(tmpName));
            break;
        }
    }
    for (i = 0; i < count-1; i++) 
        printf("Found student name %s at element %d\n", nameStr(tmpName), a[i]);
    printf("\n");
}

//REMOVE A STUDENT

void removeAStudent(char removeName[], struct ID table[]){
    int pos;
    pos = searchAStudent(removeName, table);
    if(pos < 0){
        printf("This student is not found. Can not remove!");
        return ;
    }
    for(int i = pos; i < currentSize - 1; i++)
    {
        strcpy(table[i].id, table[i+1].id);
        strcpy(table[i].name, table[i+1].name);
        strcpy(table[i].email, table[i+1].email);
        table[i].yob = table[i+1].yob;
    }
    currentSize--;
}

//REMOVE STUDENTS

void removeStudents(char removeName[], struct ID table[]){
    int pos;
    do {
        pos = searchAStudent(removeName,table);
        if (pos >= 0)
            removeAStudent(removeName,table);
    } while (pos >= 0);
}