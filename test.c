#include <stdio.h>

int main() {
    char line[70];
    scanf(" %[^\n]", line);
    printf("%s", line);
    printf("zz");
}
