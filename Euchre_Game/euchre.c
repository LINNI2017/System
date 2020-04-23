#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include "euchre.h"


#define kPrintDebug 1

//----------------------------------------
// Card functions
//----------------------------------------

// Creates a card, initializing the suit and name to that specified.
// Returns a pointer to the new card, which has beel allocated on the heap.
// It is the responsibility of the caller to call destroyCard()
// when it is done with the Card.
Card* CreateCard(Suit suit, Name name) {
    Card* new_card = (Card*)malloc(sizeof(Card));
    new_card->name = name;
    new_card->suit = suit;
    new_card->value = -1;
    return new_card;
}

// Destroys the card, freeing any memory allocated for the card.
void DestroyCard(Card* card) {
    free(card);
}

// ----------------------------------------
// Hand functions
// ----------------------------------------

// Creates a Hand struct and initializes any necessary fields.
// Returns a pointer to the new Hand, which has been allocated on the heap.
Hand* CreateHand() {
    Hand* new_hand = (Hand*)malloc(sizeof(Hand));
    new_hand->first_card = NULL;
    new_hand->num_cards_in_hand = 0;
    return new_hand;
}

// Adds a card to the hand.
void AddCardToHand(Card *card, Hand *hand) {
    CardNode* new_card_node = (CardNode*)malloc(sizeof(CardNode));
    new_card_node->prev_card = NULL;
    new_card_node->this_card = card;
    if (!hand->first_card) {
        new_card_node->next_card = NULL;
    } else {
        hand->first_card->prev_card = new_card_node;
        new_card_node->next_card = hand->first_card;
    }
    hand->num_cards_in_hand++;
    hand->first_card = new_card_node;
}

// Removes a card from the hand.
// Does not free the card; it is the responsibility
// of the caller to free the card at the appropriate
// time.
// Returns a pointer to the card that is no longer in the hand.
Card* RemoveCardFromHand(Card *card, Hand *hand) {
    if (!hand || hand->num_cards_in_hand <= 0) {
        return NULL;
    } else {
        CardNode* temp = hand->first_card;
        if (EqualTwoCards(temp->this_card, card)) {  // the first card matches
            Card* result = temp->this_card;
            hand->num_cards_in_hand--;
            hand->first_card = temp->next_card;
            return result;
        }
        if (hand->num_cards_in_hand == 1) {
            return NULL;
        } else {  // hand->num_cards_in_hand > 1
            while (temp->next_card) {
                temp = temp->next_card;
                if (EqualTwoCards(temp->this_card, card)) {
                    Card* result = temp->this_card;
                    if (temp->prev_card) {
                        temp->prev_card->next_card = temp->next_card;
                    }
                    if (temp->next_card) {
                        temp->next_card->prev_card = temp->prev_card;
                    }
                    hand->num_cards_in_hand--;
                    DisconnectCardNode(temp);
                    hand->first_card->prev_card = temp;
                    return result;
                }
            }
        }
    }



    // if (hand->num_cards_in_hand == 1) {
    //     CardNode* temp = hand->first_card;
    //     if (EqualTwoCards(temp->this_card, card)) {
    //         Card* result = temp->this_card;
    //         hand->num_cards_in_hand--;
    //         hand->first_card = NULL;
    //         return result;
    //     } else {
    //         return NULL;
    //     }
    // } else {  // hand->num_cards_in_hand > 1
        
    //     while (temp->next_card) {
    //         temp = temp->next_card;
    //         if (EqualTwoCards(temp->this_card, card)) {
    //             Card* result = temp->this_card;
    //             if (temp->prev_card) {
    //                 temp->prev_card->next_card = temp->next_card;
    //             }
    //             if (temp->next_card) {
    //                 temp->next_card->prev_card = temp->prev_card;
    //             }
    //             hand->num_cards_in_hand--;
    //             DisconnectCardNode(temp);
    //             return result;
    //         }
    //     }
    // }
    return NULL;
}

// Determines if there are any cards in the hand.
// Return 1 if the hand is empty; 0 otherwise.
int IsHandEmpty(Hand* hand) {
    if (hand->num_cards_in_hand == 0) {
        return 1;
    } else {
        return 0;
    }
}

// Destroys the hand, freeing any memory allocated for it.
void DestroyHand(Hand* hand) {
    CardNode* temp = hand->first_card;
    if (temp) {
        if (temp->next_card) {
            DestroyAllNextCard(temp->next_card);
        }
        if (temp->prev_card) {
            DestroyAllPreCard(temp->prev_card);
        }
        free(temp->this_card);
    }
    free(hand);
}

// ----------------------------------------
// Game functions
// ----------------------------------------

// Shuffle the deck.
// Put them in a random order.
void Shuffle(Deck *deck) {
    unsigned int seed = time(0);
    int j = 0;
    int rand_list[kNumCardsInDeck];
    int rand_cnt = 0;
    int existed[kNumCardsInDeck];
    for (int i = 0; i < kNumCardsInDeck; i++) {
        existed[i] = 0;
    }
    while (rand_cnt < kNumCardsInDeck) {
        int val = rand_r(&seed) % kNumCardsInDeck;
        if (existed[val] == 0) {
          rand_list[rand_cnt++] = val;
          existed[val] = 1;
        }
    }
    int cnt = 0;
    for (int cur_suit = HEARTS; cur_suit <= DIAMONDS; cur_suit++) {
        for (int cur_name = NINE; cur_name <= ACE; cur_name++) {
            Card* new_card = CreateCard(cur_suit, cur_name);
            Card* record_card = deck->cards[rand_list[cnt]];
            if (EqualTwoCards(new_card, record_card)) {
                if (cnt == 0) {
                    // first card swap with second card
                    deck->cards[rand_list[cnt]] =
                        deck->cards[rand_list[cnt + 1]];
                    deck->cards[rand_list[cnt + 1]] = new_card;
                } else {
                    // cnt > 0, current card swap with previous card
                    deck->cards[rand_list[cnt]] =
                        deck->cards[rand_list[cnt - 1]];
                    deck->cards[rand_list[cnt - 1]] = new_card;
                }
            } else {
                deck->cards[rand_list[cnt]] = new_card;
            }
            cnt++;
            DestroyCard(record_card);
        }
    }
    deck->top_card = kNumCardsInDeck - 1;
}

// Create a Deck for this game, and add any
// needed cards to the deck.
// Return a pointer to the deck to be used for the game
Deck* PopulateDeck() {
    Deck* deck = CreateDeck();
    for (int cur_suit = HEARTS; cur_suit <= DIAMONDS; cur_suit++) {
        for (int cur_name = NINE; cur_name <= ACE; cur_name++) {
            PushCardToDeck(CreateCard(cur_suit, cur_name), deck);
        }
    }
    return deck;
}

// Given a lead card, a players hand, and the card the player wants
// to play, is it legal?
// If the player has a card of the same suit as the lead card, they
// must play a card of the same suit.
// If the player does not have a card of the same suit, they can
// play any card.
// Returns 1 if the move is legal; 0 otherwise.
int IsLegalMove(Hand *hand, Card *lead_card, Card *played_card) {
    if (IsSuitInHand(hand, lead_card->suit)) {
        if (played_card->suit == lead_card->suit) {
            return 1;
        } else {
            return 0;
        }
    } else {
        return 1;
    }
}

// Given two cards that are played in a hand, which one wins?
// If the suits are the same, the higher card name wins.
// If the suits are not the same, player 1 wins, unless player 2 played trump.
// Returns 1 if the person who led won, 0 if the person who followed won.
int WhoWon(Card *lead_card, Card *followed_card, Suit trump) {
    if (lead_card->suit == followed_card->suit) {
        if (lead_card->name > followed_card->name) {
            return 1;
        } else {
            return 0;
        }
    } else if (followed_card->suit == trump) {
        return 0;
    }
    return 1;
}

// Take all the cards out of a given hand, and put them
// back into the deck.
void ReturnHandToDeck(Hand *hand, Deck *deck) {
    while (hand->num_cards_in_hand > 0) {
        Card* hand_card = RemoveCardFromHand(hand->first_card->this_card, hand);
        PushCardToDeck(hand_card, deck);
    }
}

// ----------------------------------------
// Challenge functions
// ----------------------------------------

// Considering this for a challenge problem.
Card* GetBestMove(Hand *my_hand, Card *led_card, Suit trump) {
    return NULL;
}

// Sort the given hand in descending order of power.
//
// The sort order should be: all cards of the given trump should
// be the "highest", and A high down to 9;
// The other suits can be in random order, but the card values must go
// from high to low.
void SortHand(Hand *hand, Suit trump) {
}

void ShuffleHand(Hand* hand) {
}
