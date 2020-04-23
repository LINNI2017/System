#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "euchre.h"


int main(void) {
    printf("hello\n\n");

    Deck* deck = PopulateDeck();
    PrintDeck(deck);

    // Card* card_1 = CreateCard(-1, -1);
    // printf("is empty: %d\n", IsEmptyCard(card_1));
    // char* a = "aaac";
    // char* ac = "aaab";
    // int size = strlen(a) * sizeof(char);
    // printf("haha: %d\n", strncmp(a,ac,3) == 0);
    // printf("size %d\n", size);
    // Deck* deck = CreateDeck();
    // printf("empty deck status: %d\n\n", IsDeckEmpty(deck));
    // // PrintDeck(deck);
    // // DestroyDeck(deck);

    // Card* card_1 = CreateCard(HEARTS, 9);
    // // PrintCard(card_1);
    // // printf("\n");
    // deck = PushCardToDeck(card_1, deck);
    // // // PrintDeck(deck);

    // Card* card_2 = CreateCard(CLUBS, 12);
    // // PrintCard(card_2);
    // // printf("\n");
    // deck = PushCardToDeck(card_2, deck);
    // // PrintDeck(deck);

    // Card* card_3 = CreateCard(SPADES, 13);
    // deck = PushCardToDeck(card_3, deck);
    // // PrintDeck(deck);

    // Card* card_4 = PopCardFromDeck(deck);
    // PrintCard(card_4);
    // printf("\n\n");
    // // PrintDeck(deck);
    // // printf("not empty deck status: %d\n\n", IsDeckEmpty(deck));

    // Card* card_5 = PeekAtTopCard(deck);
    // PrintCard(card_5);
    // printf("\n\n");

    // Card* card_6 = PeekAtTopCard(deck);
    // PrintCard(card_6);
    // printf("\n\n");
    // PrintCard(card_3);
    // printf("\n\n");
    // PrintDeck(deck);
    // DestroyCard(new_card);
    // PrintCard(new_card);
    // for (int i = NINE; i <= ACE; i++) {
    //     printf("%s\n", GetName(i));
    // }
    // for (int i = HEARTS; i <= DIAMONDS; i++) {
    //     printf("%s\n", GetSuit(i));
    // }
    return -1;
}
