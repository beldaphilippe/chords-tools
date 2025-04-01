#ifndef _GET_CHORD_H_
#define _GET_CHORD_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

const char *NOTES[12][3] = {
    {"a", "\0"},        {"a#", "bb", "\0"}, {"b", "\0"},
    {"c", "\0"},        {"c#", "db", "\0"}, {"d", "\0"},
    {"d#", "eb", "\0"}, {"e", "\0"},        {"f", "\0"},
    {"f#", "gb", "\0"}, {"g", "\0"},        {"g#", "ab", "\0"}};

const char KEYS[12][3] = {"A",  "A#", "B", "C",  "C#", "D",
                          "D#", "E",  "F", "F#", "G",  "G#"};

const char CHORD_TYPE[6][5] = {"\0", "m", "-", "+", "sus2", "sus4"};

/* parse the input line to extract */
int getstr_nbo(char* line, int len_line);

/* paste the _src_ string into _dst_*/
void paste(char *src, char *dst);

/* converts any capital of the string _word_ into the corresponding lowercase*/
void tolowercase(char *word);

/* splits the string _line_ around _delimiter_ */
char **split(char *line, char delimiter);

/* return the interger corresponding to _note_ */
int which_note(char *note);

/* comparison modulo 12 */
int modcmp(int x, int y);

/* reorganize triads into standard order */
int inversions_triads(int *notes, int int1, int int2);

/* returns the name of the chord formed by the notes in _notes_ string */
int which_chord(int *notes, int nb_notes);

/* prints in stdout the name of _chord_ */
void display_chord(int chord);

#endif /* _GET_CHORD_H */
