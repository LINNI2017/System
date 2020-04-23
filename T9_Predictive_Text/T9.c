// LINNI CAI
// 2017/11/09
// T9 is a linux command, reads an input file, builds up a trie,
// allows users to type in T9 numbers to search same digit words.

#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include "trie.h"    // Include the trie header file

// Define the max length of each word
#define MAX_WORD 200
// Define the max length of input
#define MAX_INPUT 100

void search(struct node*root);

// Take the number of arguments, and strings of arguments,
// build up a trie by reading input, allow users to search.
int main(int argc, char **argv) {
    if (argc != 2) {
        fprintf(stderr, "Usage: Need one file\n");
        return EXIT_FAILURE;
    }
    FILE *f_pt = fopen(argv[1], "r");
    if (!f_pt) {
        fprintf(stderr, "Usage: Cannot open file: %s\n", argv[1]);
        return EXIT_FAILURE;
    }
    struct node* root = makeRoot();
    struct node* now;
    char line[MAX_WORD];
    // read file and build trie
    while (fgets(line, MAX_WORD, f_pt))  {
        int end = strlen(line) - 1;
        // replace the line break
        if (line[end] == '\n') {
            line[end] = '\0';
        }
        now = root;
        makeTrie(now, line);
    }
    fclose(f_pt);
    search(root);
    freeChild(root);
    return 0;
}

// Take the trie root and search word.
void search(struct node* root) {
    struct node* now = root;
    struct sameDList* nowList;
    char input[MAX_INPUT];
    int none = 0;    // more word
    int wrongInput = 0;    // no wrong input
    printf("Enter \"exit\" to quit. \n");
    while (1) {
        printf("Enter Key Sequence (or \"#\" for next word): \n");
        printf("> ");
        scanf("%s", input);
        if (feof(stdin) == 1 || strcmp(input, "exit") == 0) {
            break;
        }
        // search word with the given key pattern
        for (int i = 0; i < strlen(input); i++) {
            char single = input[i];
            int key = single - '2';
            // check type of key
            if (single == '#') {
                if (nowList && nowList->nextWord) {
                    nowList = nowList->nextWord;
                } else {
                    if (nowList) {
                        none = 1;    // no more word
                    }
                    break;
                }
            } else if (key >= 0 && key < CHILD_NUM) {
                if (!now->child[key]) {
                    nowList = NULL;
                    break;
                }
                now = now->child[key];
                nowList = now->wordList;
            } else {
                printf("\tUsage: Wrong input\n");
                wrongInput = 1;    // wrong input
                break;
            }
        }
        // print out corresponding message
        if (wrongInput == 0) {
            if (none == 0) {
                if (nowList) {
                    printf("\t\'%s\'\n", nowList->nowWord);
                } else {
                    printf("\tNot found in current dictionary.\n");
                }
            } else {
                printf("\tThere are no more T9onyms\n");
            }
        }
        // initialize flags and pointer
        none = 0;
        wrongInput = 0;
        now = root;
    }
}
