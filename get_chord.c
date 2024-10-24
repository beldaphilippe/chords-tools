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
  const int MAX_NOTES = 5;
  char **split_line = malloc(sizeof(char *) * (MAX_NOTES+1));
  for (int i = 0; i < MAX_NOTES; i++)
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
  split_line[w_n] = "\0";
  return split_line;
}

char *NOTES[12][3] = {{"a", "\0"},        {"a#", "bb", "\0"}, {"b", "\0"},        {"c", "\0"},
                      {"c#", "db", "\0"}, {"d", "\0"},        {"d#", "eb", "\0"}, {"e", "\0"},
                      {"f", "\0"},        {"f#", "gb", "\0"}, {"g", "\0"},        {"g#", "ab", "\0"}};

int which_note(char *note) {
  for (int cmt = 0; cmt < 12; cmt++) {
    int j = 0;
    while (strcmp(NOTES[cmt][j], "\0") != 0) {
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
  int nb_notes = 0;
  while (strcmp(notes[nb_notes], "\0")) nb_notes++;
  int* notes_tones = malloc(sizeof(int) * (nb_notes+1));

  /*printf("%d\n", which_note(notes[0]));*/

  for (int i=0; i<nb_notes; i++) notes_tones[i] = which_note(notes[i]);

  printf("%d , %d\n", notes_tones[0], notes_tones[1]);

  free(notes);
  return 0;
}
