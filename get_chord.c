#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void paste(char *src, char *dst) {
    while (*src != '\0') {
        *dst = *src;
        dst++;
        src++;
    }
}

char **split(char *line, char delimiter) {
    char **split_line = malloc(sizeof(char*)*5);
    int i=0;
    int w_n = 0;
    while (line[i] != '\0') {
        int w_start = i;
        while (line[i] != delimiter) {
            i++;
        }
        if (w_start-i>0) {
            line[i] = '\0';
            split_line[w_n] = malloc(sizeof(char)*(w_start-i+1));
            paste(&line[w_start], split_line[w_n]);
            line[i] = delimiter;
            w_n ++;
        }
        else{
            i++;
        }
    }
    return split_line;
}

int main(){
    printf("==== Chord detector ====\n");
    printf("Give the notes of the chord, on a single line, separated by spaces :\n");
    char line[71];
    // char *line = malloc(sizeof(char)*10);
    scanf(" %[^\n]", line);
    char **notes = split(line, ' ');
    printf("%s\n", line);
    printf("%s , %s\n", notes[0], notes[1]);
    return 0;
}
