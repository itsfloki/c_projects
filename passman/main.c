#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

typedef struct {
    char label[20];
    char password[20];
} Store;

void generate(char*, int);
int write_store(Store);
int read_store();

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

        Store store;

        strcpy(store.label, argv[3]);
        strcpy(store.password, password);

        return write_store(store);

    } else if(strcmp(argv[1], "view") == 0) {
        return read_store();
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

// store the generated password in inventory file
int write_store(Store store) {
    FILE* fptr = fopen(INVENTORY_FILE, "a");

    if(fptr == NULL) {
        printf("Err file opening\n");
    }

    fwrite(&store, sizeof(Store), 1, fptr);
    fclose(fptr);
    return 0;
}

// read all passwords from inventory file
int read_store() {
    Store store;
    FILE* fptr = fopen(INVENTORY_FILE, "rb+");

    if(fptr == NULL) {
        printf("Err file opening\n");
        return -1;
    }

    while(fread(&store, sizeof(Store), 1, fptr) == 1) {
        printf("%s - %s\n", store.label, store.password);
    }
    
    fclose(fptr);
    return 0;
}