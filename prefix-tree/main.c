#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define NUM_CHARS 256

typedef struct trienode {
    struct trienode *children[NUM_CHARS];
    bool terminal;
} trienode;

trienode *createnode() {
    trienode *newnode = (trienode *)malloc(sizeof *newnode);

    for (int i = 0; i < NUM_CHARS; i++) {
        newnode->children[i] = NULL;
    }
    newnode->terminal = false;

    return newnode;
}

bool trieinsert(trienode **root, char *signedtext) {
    if (*root == NULL)
        *root = createnode();

    unsigned char *text = (unsigned char *)signedtext;
    trienode *tmp = *root;
    int lenght = strlen(signedtext);

    for (int i = 0; i < lenght; i++) {
        if (tmp->children[text[i]] == NULL) { // create a new node
            tmp->children[text[i]] = createnode();
        }

        tmp = tmp->children[text[i]];
    }

    if (tmp->terminal)
        return false;
    else {
        tmp->terminal = true;
        return true;
    }
}

void printtrie_rec(trienode *node, unsigned char *prefix, int lenght, FILE *f, int *num_words) {
    unsigned char newprefix[lenght + 2];

    memcpy(newprefix, prefix, lenght);
    newprefix[lenght + 1] = 0;

    if (node->terminal)
        fprintf(f, "Word[%d] : %s\n", (*num_words)++, prefix);

    for (int i = 0; i < NUM_CHARS; i++) {
        if (node->children[i] != NULL) {
            newprefix[lenght] = i;
            printtrie_rec(node->children[i], newprefix, lenght + 1, f, num_words);
        }
    }
}

void printtrie(trienode *root, FILE *f) {
    if (root == NULL) {
        printf("Trie is Empty!\n");
        return;
    }
    int num_words = 0;
    printtrie_rec(root, NULL, 0, f, &num_words);
}

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

    texte[i - 1] = '\0';

    fclose(f);

    return texte;
}
int main() {
    trienode *root = NULL;

    char *texte = texte_from_file("texte.txt");

    char *text;
    const char *separators = "1234567890±(),.-!%% \n";
    text = strtok(texte, separators);
    while (text) {
        for (int i = 0; text[i] != '\0'; i++)
            text[i] = tolower(text[i]);
        trieinsert(&root, text);
        // printf("%s\n", text);
        text = strtok(NULL, separators);
    }

    FILE *f;

    f = fopen("output.txt", "w");
    printtrie(root, f);

    return 0;
}
