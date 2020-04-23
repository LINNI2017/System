// LINNI CAI
// 2017/11/09
// Trie is a file, builds up a trie.

#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include "trie.h"    // Include the trie header file

// Create and initialize a trie root.
struct node* makeRoot() {
    struct node* root = (struct node*)malloc(sizeof(struct node));
    if (!root) {
        exit(EXIT_FAILURE);
    }
    for (int i = 0; i < CHILD_NUM; i++) {
        root->child[i] = NULL;
    }
    root->wordList = NULL;
    return root;
}

// Take the trie root and a string, build up the trie.
void makeTrie(struct node* root, char *word) {
    int length = strlen(word);
    struct node* now = root;
    for (int i = 0; i < length; i++) {
        int key = charKey(word[i]);
        if (!now->child[key]) {
            now->child[key] = makeRoot();
        }
        now = now->child[key];
    }
    struct sameDList* list = now->wordList;
    // update the same digit list
    if (list) {
        // get the last word
        while (list->nextWord) {
            list = list->nextWord;
        }
        list->nextWord = addWord(word);
    } else {
        now->wordList = addWord(word);
    }
}

// Return a same digit list of words, add the given string to the list.
struct sameDList* addWord(char *word) {
    int len = strlen(word) + 1;
    struct sameDList* list =
        (struct sameDList*)malloc(sizeof(struct sameDList));
    char *wordCp = (char *)malloc(len);
    wordCp = strncpy(wordCp, word, len);
    if (!list || !wordCp) {
        exit(EXIT_FAILURE);
    }
    list->nowWord = wordCp;
    list->nextWord = NULL;
    return list;
}

// Return the T9 key of the given letter.
int charKey(char letter) {
    char key[] = "abccdeffghiijkllmnoopqrstuvvwxyz";
    for (int i = 0; i < strlen(key); i++) {
        if (letter == key[i]) {
            return i / 4;
        }
    }
    return -1;
}

// Free the trie, take the trie root.
void freeChild(struct node* root) {
    if (root) {
        // free the children of the root
        for (int i = 0; i < CHILD_NUM; i++) {
            struct node* cNode = root->child[i];
            if (cNode) {
                freeChild(cNode);
                cNode = NULL;
            }
        }
        struct sameDList* list = root->wordList;
        if (list) {
            freeSameDList(list);
        }
        free(root);
    }
}

// Free the given same digit list of words.
void freeSameDList(struct sameDList* wordList) {
    struct sameDList* next = wordList->nextWord;
    if (next) {
        freeSameDList(next);
    }
    char *now = wordList->nowWord;
    if (now) {
        free(now);
    }
    free(wordList);
}
