#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "euchre.h"


#define PRINT_DEBUG 1

//----------------------------------------
// Deck functions
//----------------------------------------
// Implement these functions in deck.c.
// Creates the deck to be used for NEUchre.
// Assume that the value of cards are:
// Nine=9; Ten=10; Jack=11; and so on, up to Ace=14.

// Creates the deck, initializing any fields necessary.
// Returns a pointer to the deck, which has been allocated on the heap.
Deck* CreateDeck() {
    Deck* new_deck = (Deck*)malloc(sizeof(Deck));
    new_deck->top_card = -1;
    for (int i = 0; i < kNumCardsInDeck; i++) {
        new_deck->cards[i] = NULL;
    }
    return new_deck;
}

// Adds a card to the top of the deck.
// Returns a pointer to the deck.
Deck* PushCardToDeck(Card* new_card, Deck* deck) {
    if (deck->top_card >= -1 && deck->top_card < kNumCardsInDeck - 1) {
        deck->top_card++;
        deck->cards[deck->top_card] = new_card;
    }
    return deck;
}

// Shows the top card, but does not remove it from the stack.
// Returns a pointer to the top card.
// If the deck is empty, return NULL.
Card* PeekAtTopCard(Deck* deck) {
    if (deck->top_card >= 0 && deck->top_card < kNumCardsInDeck) {
        return deck->cards[deck->top_card];
    } else {
        return NULL;
    }
}

// Removes the top card from the deck and returns it.
// The card should NOT be freed at this point; it is the
// responsibility of the caller to free the card at the
// appropriate time.
// Returns a pointer to the top card in the deck.
// If the deck is empty, return NULL.
Card* PopCardFromDeck(Deck* deck) {
    if (deck->top_card >= 0 && deck->top_card < kNumCardsInDeck) {
        Card* pop_card = deck->cards[deck->top_card];
        deck->cards[deck->top_card] = NULL;
        deck->top_card--;
        return pop_card;
    } else {
        return NULL;
    }
}

// Determines if the deck is empty.
// Returns 1 if the Deck is empty, 0 otherwise.
int IsDeckEmpty(Deck* deck) {
    for (int i = 0; i < kNumCardsInDeck; i++) {
        if (deck->cards[i] != NULL) {
            return 0;
        }
    }
    return 1;
}

// Destroys the deck, freeing any memory allocated
// for this deck (the cards and the deck).
// DestroyDeck should call DestroyCard on all of the
// cards in the deck.
void DestroyDeck(Deck* deck) {
    for (int i = 0; i < kNumCardsInDeck; i++) {
        free(deck->cards[i]);
    }
    deck->top_card = -1;
    free(deck);
}

// Given a deck (assume that it is already shuffled),
// take the top card from the deck and alternately give
// it to player 1 and player 2, until they both have
// kNumCardsInHand.
void Deal(Deck *aDeck, Hand *p1hand, Hand *p2hand) {
    for (int i = 0; i < kNumCardsInHand; i++) {
        AddCardToHand(PopCardFromDeck(aDeck), p1hand);
        AddCardToHand(PopCardFromDeck(aDeck), p2hand);
    }
}

//----------------------------------------
// Helper functions
//----------------------------------------
/* 
 * Return 1 if the given hand contains one card of the given suit
 * @param hand - a pointer to a Hand
 * @param suit - an enum suit
 * @return 1 if the given hand contains one card of the given suit
 */
int IsSuitInHand(Hand* hand, Suit suit) {
    CardNode* temp = hand->first_card;
    while (temp) {
        if (temp->this_card->suit == suit) {
            return 1;
        }
        temp = temp->next_card;
    }
    return 0;
}

/*
 * Disconnect the given card node with the previous node and the next node.
 * @param card_node - a pointer to a Card Node
 */
void DisconnectCardNode(CardNode* card_node) {
    card_node->prev_card = NULL;
    card_node->this_card = NULL;
    card_node->next_card = NULL;
    free(card_node);
}

/*
 * Destroy all previous card nodes of the given card node.
 * @param card_node - a pointer to a Card Node
 */
void DestroyAllPreCard(CardNode* card_node) {
    if (card_node->prev_card) {
        DestroyAllPreCard(card_node->prev_card);
    } else {
        free(card_node);
    }
}

/*
 * Destroy all next card nodes of the given card node.
 * @param card_node - a pointer to a Card Node
 */
void DestroyAllNextCard(CardNode* card_node) {
    if (card_node->next_card) {
        DestroyAllNextCard(card_node->next_card);
    } else {
        free(card_node);
    }
}

/*
 * Return 1 if the given two cards have the same suit and name,
 * otherwise 0.
 * @param card1 - a pointer to a Card
 * @param card2 - a pointer to a Card
 * @return 1 if the given cards have the same suit and name
 */
int EqualTwoCards(Card* card1, Card* card2) {
    if (card1->name == card2->name &&
        card1->suit == card2->suit) {
        return 1;
    } else {
        return 0;
    }
}
