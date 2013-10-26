/*
 * Louis Croce
 * Rummy Project for Grandma
 *
 * rummy.h
 * A header file for rummy.cpp that contains
 * structs used and function declarations.
 */

#ifndef __RUMMY_H__
#define __RUMMY_H__

using namespace std;


/*
 * A structure to represent a state in the game.
 */
struct State {
	vector<int> deck;
	vector<int> agentHand;
	vector<int> userHand;
	list<int> remaining;
	int turnCard;
};

/*
 * swap the cards at positions pos1 and pos2.
 */
void swap(vector<int> &cards, int pos1, int pos2);

/*
 * A function that shuffles a deck of cards.
 */
void shuffle(vector<int> &deck);

/*
 * A function that returns a newly shuffled deck
 */
vector<int> getNewDeck();

/*
 * A function that initializes a state's remaining
 * cards
 */
list<int> initializeRemaining();

/*
 * A function that deals hands to the user and agent
 */
void dealCards(vector<int> &deck, vector<int> &userHand, vector<int> &agentHand);


/*
 * A function that adjusts the remaining cards
 */
void adjustRemaining(list<int> &remaining, vector<int> hand);

/*
 * A function that initializes a new game (fresh state)
 */
State initializeState();


/*
 * Determines the suit of the corresponding integer
 */
char getSuit(int i);

/*
 * Determines the rank of the corresponding integer
 */
char getRank(int i);

/*
 * Prints the opponent's hand and deck.
 */
void printOpponentHandandDeck();

/*
 * Prints the turn card with corresponding value
 */
void printTurnCard(int v);

/*
 * Prints the users hand to the screen.
 */
void printHand(vector<int> hand);

/*
 * A function that prints the game's current state.
 */
void printState(State state);


/*
 * A function that merges the elements of a vector
 * starting at points a1 and b1 into the output vector
 */
void merge(vector<int> integers, int a1, int a2, int b1, int b2, vector<int> &output);

/*
 * Uses mergesort to sort a vector of ints
 */
void mergeSort(vector<int> &integers, int start, int finish);

/*
 * Determines if the given hand is a winner.
 * Returns true if it is, returns false otherwise.
 */
bool isWinner(vector<int> hand);

/*
 * Returns true if the game is over.
 * Returns false otherwise.
 */
bool gameOver(State state);

/*
 * A function that plays a user's turn in the game rummy
 */
void playUserTurn(State &state);

/*
 * A function that evaluates a given hand.
 * If the hand is a winner, the maximum value (100) is returned.
 * +15 is given for 4 of a kind or 4 in a row.
 * +11 is given for 3 in a row with 2 remaining cards that can make 4 in a row.
 * +10 is given 3 in a row or 3 of a kind with 1 remaining.
 * +9 is given for 3 in a row or 3 of a kind with 0 remaining.
 * +4 is given for 2 in a row with 4 remaining.
 * +3 is given for 2 in a row with 3 remaining.
 * +2 is given for 2 in a row or a pair with 2 remaining.
 * +1 is given for 2 in a row or a pair with 1 remaining.
 */
int evaluate(State state);

/*
 * A function that determines whether the agent
 * should pick up the turn card or not.
 * If the turn card is a winner, return true.
 * If the turn card results in a 3 of a kind
 * or 3 in a row that wasn't there before, return true.
 * Else, return false.
 */
bool takeTurnCard(State state);


/*
 * A function that removes the worst card from the agent's
 * hand.  IE, the card that produces the highest evaluation
 * score when removed.
 */
int removeWorstCard(State &state);

/*
 * A function that plays a computer agent's turn in rummy.
 */
void playAgentTurn(State &state);

#endif