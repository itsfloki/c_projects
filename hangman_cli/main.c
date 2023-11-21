#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

int get_random_int(int min, int max);
void get_random_word(char *word);

int main() {
    // seed initialization for random number
    srand(time(NULL));
    char word[100];
    char guess;

    get_random_word(word);

    printf("Let's play hangman!\n");
    printf("Your word is %ld letters long.\n", strlen(word));
    
    while(1) {
        printf("Guess a letter: ");
        guess = getchar();

        if(guess == EOF) break;
        while(getchar() != '\n');
    }

    return 0;
}

int get_random_int(int min, int max){
   return min + rand() / (RAND_MAX / (max - min + 1) + 1);
}

void get_random_word(char *kept_word) {
    FILE *words;

    char word[100];
    int random_number = get_random_int(0, 100);
    int count = 0;

    if((words = fopen("words.txt", "r")) == NULL) {
        printf("[ERROR] opening file\n");
        exit(1);
    }

    // fscanf(words, "%[^\n]", word);
    while(fgets(word, 100, words)) {
        if(count++ == random_number) {
            // remove newline from string
            word[strcspn(word, "\n")] = 0;
            strcpy(kept_word, word);
            return;
        }
    }
}
