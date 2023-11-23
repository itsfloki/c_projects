#include <stdio.h>
#include <stdlib.h>

// cli arguments
typedef struct {
    char *find;
    char *replace;
    char *file_name;
} Config;

int main(int argc, char *argv[]) {
    Config config;

    if(argc < 4) {
        printf("Arguments missing.\n");
        exit(1);
    }

    config.find = *(++argv);
    config.replace = *(++argv);
    config.file_name = *(++argv);

    printf("find: %s\n", config.find);
    printf("replace: %s\n", config.replace);
    printf("file: %s\n", config.file_name);

    return 0;
}
