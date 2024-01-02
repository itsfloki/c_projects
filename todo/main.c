#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUFFER_SIZE 1000

char* FILE_PATH = "/home/floki/Documents/todo.txt";
char* TEMP_FILE_PATH = "/home/floki/Documents/temp.txt";

int init() {
    FILE* fptr;

    fptr = fopen(FILE_PATH, "a");

    if(fptr == NULL) {
        printf("error: while creating file.\n");
        return -1;
    }

    fclose(fptr);
    return 0;
}

int add(char* todo) {
    FILE* fptr;

    fptr = fopen(FILE_PATH, "a");

    if(fptr == NULL) {
        printf("error: while creating file.\n");
        return -1;
    }

    if(fputs(todo, fptr) == EOF) {
        printf("error: not able to add todo.\n");
        return -1;
    }

    fclose(fptr);
    return 0;
}

int view() {
    FILE* fptr;

    fptr = fopen(FILE_PATH, "r");
    char line[200];

    if(fptr == NULL) {
        printf("error: while creating file.\n");
        return -1;
    }

    int count = 1;
    while(fgets(line, 200, fptr)) {
        printf("%d) %s", count++, line);
    }

    fclose(fptr);
    return 0;
}

int remove_todo(char* todo_number) {
    int todo_num = atoi(todo_number);
    char buffer[BUFFER_SIZE];

    FILE* fptr;
    FILE* temp_fptr;

    fptr = fopen(FILE_PATH, "r");
    temp_fptr = fopen(TEMP_FILE_PATH, "w");

    if(fptr == NULL || temp_fptr == NULL) {
        printf("error: while creating file.\n");
        return -1;
    }

    int count = 1;
    while(fgets(buffer, BUFFER_SIZE, fptr)) {
        if(count != todo_num)
            fputs(buffer, temp_fptr);
        count++;
    }


    fclose(fptr);
    fclose(temp_fptr);

    remove(FILE_PATH);
    rename(TEMP_FILE_PATH, FILE_PATH);

    return 0;
}

int main(int argc, char *argv[]) {
    if(argc < 2) {
        printf("arguments missing.\n");
        return -1;
    }

    if(strcmp(argv[1], "init") == 0) {
        printf("init...\n");
        return init();
    } else if(strcmp(argv[1], "add") == 0) {
        char* new_todo = (char*) malloc(sizeof(argv[1]) + 2);
        strcpy(new_todo, argv[2]);
        strcat(new_todo, "\n");
        return add(new_todo);
    } else if(strcmp(argv[1], "remove") == 0) {
        return remove_todo(argv[2]);
    } else if(strcmp(argv[1], "view") == 0) {
        return view();
    } else {
        printf("Please use arguments only init, add or remove.\n");
    }

    return 0;
}

