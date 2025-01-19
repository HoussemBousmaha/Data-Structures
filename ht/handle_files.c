#include "../lib/Files_handling.h"

int num_chars(const char *fname) {
    FILE *f;

    f = fopen(fname, "r");

    int number_of_chars = 0;
    char ch;

    while ((ch = fgetc(f)) != EOF)
        number_of_chars++;

    fclose(f);

    return number_of_chars;
}

char *texte_from_file(const char *fname) {
    FILE *f;
    f = fopen(fname, "r");

    int i = 0;

    char ch;

    int number_of_chars = num_chars(fname);

    char *texte = (char *)malloc(number_of_chars * sizeof(char));

    while ((ch = fgetc(f)) != EOF)
        texte[i++] = ch;

    texte[i] = '\0';

    fclose(f);

    return texte;
}