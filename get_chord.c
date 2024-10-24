#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* To encode the chords, we use 2 digits in the
 * base 12: from the left, we have:
 *  1: the root (in ascending order of indicator)
 *       A, A#, B, C, C#, D, D#, E, F, F#, G, G#
 *  2: the type (in ascending order of indicator)
 *       M, m, -, +, sus2, sus4, 7, maj7, m7, m7b5
 */
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

const char *NOTES[12][3] = {{"a", "\0"},        {"a#", "bb", "\0"}, {"b", "\0"},        {"c", "\0"},
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
  printf("error : unwnown note\n");
  return -1;
}


int modcmp(int x, int y) {
    return ((x%12)==(y%12));
}

int inversions_triads(int* notes, int int1, int int2) {
    int a=notes[0], b=notes[1], c=notes[2];
    printf("%d, %d, %d\n", a,b,c);
    // classic triad, root position
    if (modcmp(b-a, int1) && modcmp(c-a, int2)) return 1;
    // first inversion
    else if (modcmp(a-c, int1) && modcmp(b-c, int2)) return 3;
    // second inversion
    else if (modcmp(c-b, int1) && modcmp(a-b, int2)) return 2;
    // nothing at all
    else return 0;
}

int which_chord(int* notes, int nb_notes) {
    if (nb_notes == 3) {
        int chord;
        int test_M = inversions_triads(notes, 4, 7);
        int test_m = inversions_triads(notes, 3, 7);
        int test_dism = inversions_triads(notes, 3, 6);
        int test_augm = inversions_triads(notes, 4, 8);
        int test_sus2 = inversions_triads(notes, 2, 7);
        int test_sus4 = inversions_triads(notes, 5, 7);
        if (test_M) chord=0;
        if (test_m) chord=1;
        if (test_augm) chord=2;
        if (test_dism) chord=3;
        if (test_sus2) chord=4;
        if (test_sus4) chord=5;
        int is_chord = test_M+test_m+test_augm+test_dism+test_sus2+test_sus4;
        if (is_chord) return chord + 16*notes[is_chord];
        else {
            printf("error : not a chord\n");
            return -1;
        }
    }
    else if (nb_notes == 4) {
        /*int a=notes[0], b=notes[1], c=notes[2], d=notes[3];*/
        printf("to implement\n");
    }
    else if (nb_notes == 5) {
        /*int a=notes[0], b=notes[1], c=notes[2], d=notes[3], e=notes[4];*/
        printf("to implement\n");
    }
    else {
        printf("error : not the correct number of notes\n");
        return -1;
    }
}

char* KEYS = {"A", "A#", "B", "C", "C#", "D", "D#", "E", "F", "F#", "G", "G#"};
const char* CHORD_TYPE = {"\0", "m", "-", "+", "sus2", "sus4"};

void display_chord(int chord) {
    int chord_type = chord%12;
    int chord_key = chord/12;
    printf("%d, %d\n", chord_key, chord_type);
    printf("%s\n", KEYS[chord_key]);
    fprintf(stdout, "Chord found: %s%s\n", KEYS[chord_key], CHORD_TYPE[chord_type]);
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
  for (int i=0; i<nb_notes; i++) notes_tones[i] = which_note(notes[i]);

  display_chord(which_chord(notes_tones, nb_notes));

  free(notes);
  return 0;
}
