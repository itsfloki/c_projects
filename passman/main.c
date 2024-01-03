#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

void generate(char*, int);

char* INVENTORY_FILE = "test.bin";

int main(int argc, char* argv[]) {
    srand(time(NULL));
    if(argc < 3) {
        printf("arguments missing.\n");
        return -1;
    }

    if(strcmp(argv[1], "gen") == 0) {
        int password_length = atoi(argv[2]);
        if(4 >= password_length || 20 < password_length) {
            printf("Password length should be between 4 to 20\n");
            return -1; 
        }

        char password[password_length];
        generate(password, password_length);

        printf("%s\n", password);
    } else if(strcmp(argv[1], "view") == 0) {

    } else if(strcmp(argv[1], "remove") == 0) {

    }

    return 0;
}

// generate new password
void generate(char* dest, int length) {
    char charset[] = "0123456789"
                     "#$@*"
                     "abcdefghijklmnopqrstuvwxyz"
                     "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    while(length-- > 0) {
        size_t index = (double) rand() / RAND_MAX * (sizeof charset - 1);
        *dest++ = charset[index];
    }
    *dest = '\0';
}
