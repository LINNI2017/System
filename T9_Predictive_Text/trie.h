// LINNI CAI
// 2017/11/09
// This is a header file of Trie, defines the struct node
// and the same digit list.

#ifndef TRIE_H
#define TRIE_H
// Defines the number of children
#define CHILD_NUM 8

// A node has a list of child node,
// and a same digit list.
struct node {
    struct node* child[CHILD_NUM];
    struct sameDList* wordList;
};

// A sameDList is a same digit list,
// has a string and next sameDList.
struct sameDList {
    char *nowWord;
    struct sameDList* nextWord;
};

struct node* makeRoot();
void makeTrie(struct node* root, char *word);
struct sameDList* addWord(char *word);
int charKey(char letter);
void freeChild(struct node* root);
void freeSameDList(struct sameDList* wordList);
#endif
