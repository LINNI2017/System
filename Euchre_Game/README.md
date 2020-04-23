## Two-Handed Euchre Game

### Rule:
- All the cards are the same as in normal Euchre: 9, 10, J, Q, K, A of each suit.
- Euchre is a trick-taking game. The non-dealer has the opportunity to call trump or pass. If they pass, the dealer is forced to choose (like in “screw the dealer” in normal Euchre).

  - Once trump is chosen, the non-dealer leads normal play. To reiterate, it doesn't matter who chose trump — the non-dealer always leads. Each player must follow suit, playing from the face-up cards in front of them on the table or in their hand. When a card on the table is played, the card below it (if there is one) is turned over once the trick is complete.

  - There are twelve tricks to be played. To win the hand, you must take 7 of the 12 tricks. Each player gets one point for each trick they took. If the trump-caller fails to take 7 tricks, they have been “Euchred”, and the other person gets all 12 points.

  - The game is over when one player reaches 31 points.

#### This program aims to implement two-handed euchre game, build up a dynamic deck of cards, allow a human user and a computer default user to play the game, allocate and free memory as needed. 

- Use `make test` to build test code, use `./test` to test
- Use `make run` to build run code, use `./run` to run
- Use `make clean` to clean directory after using `make` many times, 
  you might see some error like `make: Nothing to be done for 'all'.`

- No input needed for this program.

- Sample test output in the end of the page.

- The files in this directory
	- Makefile: build and compile code
	- euchre.h: header file for a4 program
	- euchre_helpers.c: helper program for a4 program
	- euchre_run.c: run program
	- euchre_test.c: test program
	- euchre.c: game program
	- deck.c: deck program
	- README.md: an intro about this program and directory  

- header files for `euchre_helpers.c` script include:
	- `stdio.h`
	- `stdlib.h`
	- `string.h`
	- `euchre.h`

- header files for `euchre_run.c` script include:
	- `stdio.h`
	- `stdlib.h`
	- `time.h`
	- `euchre.h`

- header files for `euchre_test.c` script include:
	- `stdio.h`
	- `stdlib.h`
	- `string.h`
	- `euchre.h`

- header files for `euchre.c` script include:
	- `stdio.h`
	- `stdlib.h`
	- `string.h`
	- `time.h`
	- `euchre.h`

- My assumption include: the deck is used in a valid way, the card is used in a valid way.
	- A deck has minimally 0 card, maximally 24 cards.  
	- Each card is valid, with appropriate suit and valid name.  
	- If deck is full, user cannot push card.
	- If deck top card points to some specific card, it must be valid within the range.
	- If deck top card points to some specific card, if push a new card, 
	  the new card is next to the pointed card.
	  Even though sometimes the next card has some name and some suit, 
	  next card will be replaced with new card, the deck top card will point to the next card.
	- For shuffle cards, I used random number generation, pair it with 4 suits, 
	  each suit has 6 name cards, sometimes during the shuffle, the current new
	  card is still the same as the original card at the same location, I will
	  swap it with the previous card, if it is the first card, I will swap it with
	  the next card.
	- For remove the card from the hand, I disconnect the removed card with
	  its previous and next card, modify previous card's next card, and next card's
	  previous card to make new connection.

- Valgrind report sample:

```
==7613== 
==7613== HEAP SUMMARY:
==7613==     in use at exit: 0 bytes in 0 blocks
==7613==   total heap usage: 237 allocs, 237 frees, 6,312 bytes allocated
==7613== 
==7613== All heap blocks were freed -- no leaks are possible
==7613== 
==7613== For counts of detected and suppressed errors, rerun with: -v
==7613== ERROR SUMMARY: 0 errors from 0 contexts (suppressed: 0 from 0)
```

- Test Output example:

```
Test #11: deal

got a match!!
got a match!!
got a match!!
got a match!!
got a match!!
Assertion 'num_matches == kNumCardsInHand' passed, file 'a4_test.c' line '473'.
Assertion 'ptr->this_card == expected_hand2[i]' passed, file 'a4_test.c' line '479'.
Assertion 'ptr->this_card == expected_hand2[i]' passed, file 'a4_test.c' line '479'.
Assertion 'ptr->this_card == expected_hand2[i]' passed, file 'a4_test.c' line '479'.
Assertion 'ptr->this_card == expected_hand2[i]' passed, file 'a4_test.c' line '479'.
Assertion 'ptr->this_card == expected_hand2[i]' passed, file 'a4_test.c' line '479'.
```

```
Test #12: is_legal_move

Assertion 'IsLegalMove(&hand, &ten_hearts, &queen_hearts)' passed, file 'a4_test.c' line '524'.
Assertion '!IsLegalMove(&hand, &ten_hearts, &king_spades)' passed, file 'a4_test.c' line '525'.
Assertion '!IsLegalMove(&hand, &ten_hearts, &nine_clubs)' passed, file 'a4_test.c' line '526'.
Assertion 'IsLegalMove(&hand, &ten_hearts, &nine_hearts)' passed, file 'a4_test.c' line '527'.
Assertion 'IsLegalMove(&hand, &led_jack_diamonds, &queen_hearts)' passed, file 'a4_test.c' line '531'.
Assertion 'IsLegalMove(&hand, &led_jack_diamonds, &king_spades)' passed, file 'a4_test.c' line '532'.
Assertion 'IsLegalMove(&hand, &led_jack_diamonds, &nine_clubs)' passed, file 'a4_test.c' line '533'.
Assertion 'IsLegalMove(&hand, &led_jack_diamonds, &nine_hearts)' passed, file 'a4_test.c' line '534'.
```

```
Test #14: return hand to deck

Assertion 'deck->cards[idx--] == expected_hand1[i]' passed, file 'a4_test.c' line '601'.
Assertion 'deck->cards[idx--] == expected_hand1[i]' passed, file 'a4_test.c' line '601'.
Assertion 'deck->cards[idx--] == expected_hand1[i]' passed, file 'a4_test.c' line '601'.
Assertion 'deck->cards[idx--] == expected_hand1[i]' passed, file 'a4_test.c' line '601'.
Assertion 'deck->cards[idx--] == expected_hand1[i]' passed, file 'a4_test.c' line '601'.
Assertion 'deck->cards[idx--] == expected_hand2[i]' passed, file 'a4_test.c' line '608'.
Assertion 'deck->cards[idx--] == expected_hand2[i]' passed, file 'a4_test.c' line '608'.
Assertion 'deck->cards[idx--] == expected_hand2[i]' passed, file 'a4_test.c' line '608'.
Assertion 'deck->cards[idx--] == expected_hand2[i]' passed, file 'a4_test.c' line '608'.
Assertion 'deck->cards[idx--] == expected_hand2[i]' passed, file 'a4_test.c' line '608'.
```

#### Difference between memory on the stack vs heap memory.

- Stack is used for static memory allocation.
	- variables on the stack are stored directly to the memory, and accessing to memory is fast.
	- order is always last in first out.
	- simple to keep track of the stack.
- Heap is used for dynamic memory allocation.
	- variables on the heap have memory allocated at run time, and accessing to memory is slower.
	- the heap size is limited by the size of virtual memory.
	- complex to keep track of the heap.
- Both stored in the computer's RAM.

#### Reference
- https://www.chellman.org/euchreForTwo.html
- http://net-informations.com/faq/net/stack-heap.htm
