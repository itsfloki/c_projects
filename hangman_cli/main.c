#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define IN 1
#define OUT 0

void init_guess(char *, char, int);
int get_random_int(int, int);
void get_random_word(char *);
int check_word(char *, char *, char);

int main() {
    // seed initialization for random number
    srand(time(NULL));
    char answer[100], guess_word[100];
    char guess;
    int body_parts = 6;

    get_random_word(answer);

    printf("Let's play hangman!\n");
    printf("Your word is %ld letters long.\n", strlen(answer));

    init_guess(guess_word, '-', strlen(answer));
    
    while(1) {
        printf("%s\n", guess_word);

        if(body_parts == 0) {
            printf("You are hanged!\n");
            break;
        }

        printf("Guess a letter: ");
        guess = getchar();

        if(guess == EOF) break;
        while(getchar() != '\n');

        if(check_word(guess_word, answer, guess) == OUT)
            printf("Wrong guess. %d body part remains\n", --body_parts);


        if(strcmp(guess_word, answer) == 0) {
            printf("You are winner!\n");
            break;
        }
    }

    return 0;
}

void init_guess(char *word, char ch, int len) {
    int i;

    for(i = 0; i < len; i++) {
        *(word + i) = ch;
    }

    *(word + i) = '\0';
}

int get_random_int(int min, int max) {
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

int check_word(char *guess_word, char *answer, char ch) {
    int flag = OUT;

    while(*answer) {
        if(*answer == ch) {
            flag = IN;
            *guess_word = ch;
        }

        *guess_word++;
        *answer++;
    }

    return flag;
}
