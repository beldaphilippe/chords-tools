#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void paste(char *src, char *dst) {
  while (*src != '\0') {
    *dst = *src;
    dst++;
    src++;
  }
  *dst = '\0';
}

void tolowercase(char *word) {
  while (*word != '\0') {
    if (*word >= 'A' && *word <= 'Z') {
      *word += 'a' - 'A';
    }
    word++;
  }
}

char **split(char *line, char delimiter) {
  char **split_line = malloc(sizeof(char *) * 5);
  for (int i = 0; i < 5; i++)
    split_line[i] = NULL;
  int i = 0;
  int w_n = 0;
  while (line[i] != '\0') {
    int w_start = i;
    while (line[i] != delimiter && line[i] != '\0') {
      i++;
    }
    if (w_start != i) {
      int tmp = line[i];
      line[i] = '\0';
      split_line[w_n] = malloc(sizeof(char) * (i - w_start + 1));
      paste(&line[w_start], split_line[w_n]);
      line[i] = tmp;
      w_n++;
    } else
      i++;
  }
  return split_line;
}

char *NOTES[12][2] = {{"a", NULL},        {"a#", "bb", NULL}, {"b", NULL},        {"c"},
                      {"c#", "db"}, {"d"},        {"d#", "eb"}, {"e"},
                      {"f"},        {"f#", "gb"}, {"g"},        {"g#", "ab"}};

int which_note(char *note) {
  for (int cmt = 0; cmt < 12; cmt++) {
    int j = 0;
    while (*NOTES[cmt][j] != NULL) {
      if (*NOTES[cmt][j] == *note) {
        return cmt;
      }
      j++;
    }
  }
  printf("error : unwnown note");
  return -1;
}

int main() {
  printf("==== Chord detector ====\n");
  printf(
      "Give the notes of the chord, on a single line, separated by spaces\n");
  char line[71];
  // char *line = malloc(sizeof(char)*10);
  scanf(" %[^\n]", line);
  tolowercase(line);
  char **notes = split(line, ' ');

  int i = 0;
  printf("%d\n", which_note(notes[0]));
  /*
  while (notes[i] != '\0' && notes[i] != NULL) {
    notes[i] = which_note(notes[i]);
  }

  printf("%s , %s\n", notes[0], notes[1])*/

  free(notes);
  return 0;
}
