/*
 * Louis Croce
 * Rummy Project for Grandma
 *
 * rummy.cpp
 */

#include <iostream>
#include <cstdlib>
#include <vector>
#include <list>
#include <ctime>
#include "rummy.h"


using namespace std;

/*
 * Main function for my program.
 */
int main(int argc, char **argv)
{
	State state = initializeState();
	printState(state);
	while (gameOver(state) == false)
	{
		playUserTurn(state);
		if (gameOver(state))
			break;
		playAgentTurn(state);
		printState(state);
	}
	return 0;
}

/*
 * swap the cards at positions pos1 and pos2.
 */
void swap(vector<int> &cards, int pos1, int pos2)
{
	int temp = cards[pos1];
	cards[pos1] = cards[pos2];
	cards[pos2] = temp;
}

/*
 * A function that shuffles a deck of cards.
 */
void shuffle(vector<int> &deck)
{
	srand(time(NULL));
	int size = deck.size();
	for (int i = size-1; i >0; i--)
	{
		int swapPos = rand() % i;
		swap(deck, i, swapPos);
	}
}

/*
 * A function that returns a newly shuffled deck
 */
vector<int> getNewDeck()
{
	vector<int> deck;
	for (int i = 0; i < 52; i++)
	{
		deck.push_back(i);
	}
	shuffle(deck);
	return deck;
}

/*
 * A function that initializes a state's remaining
 * cards
 */
list<int> initializeRemaining()
{
	list<int> remaining;
	for (int i = 0; i < 52; i++)
		remaining.push_back(i);
	return remaining;
}

/*
 * A function that deals hands to the user and agent
 */
void dealCards(vector<int> &deck, vector<int> &userHand, vector<int> &agentHand)
{
	for (int i = 0; i < 14; i ++)
	{
		int topCard = deck.back();
		deck.pop_back();
		if (i%2 == 0)
			userHand.push_back(topCard);
		else
			agentHand.push_back(topCard);
	}
}

/*
 * A function that adjusts the remaining cards.
 * The remaining cards are all the cards that the agent
 * does not have, but are still in play.
 * I use the remaining cards in my heuristic for the agent.
 */
void adjustRemaining(list<int> &remaining, vector<int> hand)
{
	for (int i = 0; i < hand.size(); i++)
		remaining.remove(hand[i]);
}

/*
 * A function that initializes a new game (fresh state)
 */
State initializeState()
{
	State state;
	state.deck = getNewDeck();
	state.remaining = initializeRemaining();
	dealCards(state.deck, state.userHand, state.agentHand);
	adjustRemaining(state.remaining, state.agentHand);
	mergeSort(state.userHand, 0, state.userHand.size());
	state.turnCard = 52;
	return state;
}

/*
 * Determines the suit of the corresponding integer
 */
char getSuit(int i)
{
	if (i < 13)
		return '&';
	else if (i < 26)
		return '%';
	else if (i < 39)
		return '$';
	else
		return '@';
}

/*
 * Determines the rank of the corresponding integer
 */
char getRank(int i)
{
	int rank = i % 13;
	if (rank == 0)
		return 'A';
	if (rank == 1)
		return '2';
	if (rank == 2)
		return '3';
	if (rank == 3)
		return '4';
	if (rank == 4)
		return '5';
	if (rank == 5)
		return '6';
	if (rank == 6)
		return '7';
	if (rank == 7)
		return '8';
	if (rank == 8)
		return '9';
	if (rank == 9)
		return 'T';
	if (rank == 10)
		return 'J';
	if (rank == 11)
		return 'Q';
	return 'K';
}

/*
 * Prints the opponent's hand and deck.
 */
void printOpponentHandandDeck()
{
	/* Printing out what looks like opponent's hand */
	for (int i = 0; i < 10; i++)
	{
		for (int j = 0; j < 56; j++)
		{
			int k = j % 8;
			if (k == 7)
				cout << "* ";
			else if (i == 0 || i == 9 || k == 0)
				cout << "*";
			else
				cout << "?";
		}
		cout << endl;
	}
	cout << endl;

	/* Printing out what looks like a deck */
	for (int i = 0; i < 10; i++)
	{
		for (int j = 0; j < 8; j++)
		{
			if (i == 0 || i == 9 || j == 0 || j == 7)
				cout << "*";
			else
				cout << "?";
		}
		cout << endl;
	}
	cout << endl;
}

/*
 * Prints the turn card with corresponding value.
 */
void printTurnCard(int v)
{
	char suit = getSuit(v);
	char rank = getRank(v);
	for (int i = 0; i < 10; i++)
	{
		for (int j = 0; j < 8; j++)
		{
			if (i == 0 || i == 9 || j == 0 || j == 7)
				cout << "*";
			else if ((j == 1 && i == 1) || (j == 6 && i == 8) || (j == 3 && i == 4))
				cout << rank;
			else if ((j == 6 && i == 1) || (j == 1 && i == 8) || (j == 4 && i == 5))
				cout << suit;
			else
				cout << " ";
		}
		cout << endl;
	}
	cout << endl;
}

/*
 * Prints the users hand to the screen.
 */
void printHand(vector<int> hand)
{
	int size = hand.size();
	for (int i = 0; i < 10; i++)
	{
		for (int j = 0; j < size; j++)
		{
			char rank = getRank((hand[j]));
			char suit = getSuit((hand[j]));
			for (int k = 0; k < 8; k++)
			{
				if (k == 7)
					cout << "* ";
				else if (i == 0 || i == 9 || k == 0)
					cout << "*";
				else if ((k == 1 && i == 1) || (k == 6 && i == 8) || (k == 3 && i == 4))
					cout << rank;
				else if ((k == 6 && i == 1) || (k == 1 && i == 8) || (k == 4 && i == 5))
					cout << suit;
				else
					cout << " ";
			}
		}
		cout << endl;
	}
	cout << endl;
}

/*
 * A function that prints the game's current state.
 */
void printState(State state)
{
	//printHand(state.agentHand);
	printOpponentHandandDeck();
	if (state.turnCard < 52)
		printTurnCard(state.turnCard);
	printHand(state.userHand);
}

/*
 * A function that merges the elements of a vector
 * starting at points a1 and b1 into the output vector
 */
void merge(vector<int> integers, int a1, int m, int b2, vector<int> &output)
{
	int a2, b1;
	a2 = b1 = m;
	while (a1 < a2 && b1 < b2)
	{
		if (integers[a1] <= integers[b1])
			output.push_back(integers[a1++]);
		else
			output.push_back(integers[b1++]);
	}

	while (a1 < a2)
		output.push_back(integers[a1++]);
	while (b1 < b2)
		output.push_back(integers[b1++]);
}

/*
 * Uses mergesort to sort a vector of ints
 */
void mergeSort(vector<int> &integers, int start, int finish)
{
	if ((finish - start) <= 1)
		return;
	int m = (finish - start) / 2;
	mergeSort(integers, start, start+m);
	mergeSort(integers, start+m, finish);

	vector<int> temp;
	merge(integers, start, start+m, finish, temp);
	int tempIndex = 0;
	for (int i = start; i < finish; i++)
		integers[i] = temp[tempIndex++];
}

/*
 * Determines if the given hand is a winner.
 * Returns true if it is, returns false otherwise.
 */
bool isWinner(vector<int> hand)
{
	mergeSort(hand, 0, hand.size());		// sort hand first

	/* Check if first 4 are in a row */
	if (hand[0] % 13 < 10 && hand[1] == hand[0] + 1 && hand[2] == hand[0] + 2
				&& hand[3] == hand[0] + 3)
	{
		/* Check if last 3 are in a row */
		if (hand[4] % 13 < 11 && hand[5] == hand[4] + 1 && hand[6] == hand[4] + 1)
			return true;
		/* check if last 3 are the same rank */
		if (hand[4] % 13 == hand[5] % 13 && hand[4] % 13 == hand[6] % 13)
			return true;
	}

	/* Check if first 3 are in a row */
	if (hand[0] % 13 < 11 && hand[1] == hand[0] + 1 && hand[2] == hand[0] + 2)
	{
		/* Check if last 4 are in a row */
		if (hand[3] % 13 < 10 && hand[4] == hand[3] + 1 && hand[5] == hand[3] + 2
					&& hand[6] == hand[3] + 3)
			return true;
		/* Check if last 4 are the same rank */
		if (hand[3] % 13 == hand[4] % 13 && hand[3] % 13 == hand[5] % 13
					&& hand[3] % 13 == hand[6] % 13)
			return true;
	}

	/* Add cards not of same rank as first to a list */
	vector<int> nonMatches;
	for (int i = 0; i < hand.size(); i++)
	{
		if (hand[i] % 13 != hand[0] % 13)
			nonMatches.push_back(hand[i]);
	}

	/* Check for a legitimate number of nonmatches (3 or 4) */
	if (nonMatches.size() != 3 && nonMatches.size() != 4)
		return false;

	/* Check if nonmatches are not in a row */
	bool areInARow = true;
	for (int i = 0; i < nonMatches.size(); i++)
	{
		if (nonMatches[i] != nonMatches[0] + i)
			areInARow = false;
	}
	if (areInARow)
		return true;

	/* Check if nonmatches are not the same */
	for (int i = 0; i < nonMatches.size(); i++)
	{
		if (nonMatches[i] % 13 != nonMatches[0] % 13)
			return false;
	}
	return true;
}

/*
 * Returns true if the game is over.
 * Returns false otherwise.
 */
bool gameOver(State state)
{
	/* Check if user won */
	if (isWinner(state.userHand))
	{
		cout << "You won the game!" << endl;
		printHand(state.userHand);
		return true;
	}

	/* Check if agent won */
	if (isWinner(state.agentHand))
	{
		cout << "Read 'em and weep!" << endl;
		printHand(state.agentHand);
		cout << "You lost the game :(" << endl;
		return true;
	}

	/* No player has won */
	return false;
}

/*
 * A function that plays a user's turn in the game rummy.
 */
void playUserTurn(State &state)
{
	/* Give user options for drawing */
	if (state.turnCard < 52)
		cout << "Enter \"t\" to take the turn card." << endl;
	cout << "Enter \"d\" to draw a card from the deck." << endl;
	char choice;
	cin >> choice;
	while (choice != 'd' && (choice != 't' || state.turnCard == 52))
	{
		if (state.turnCard < 52)
			cout << "Enter \"t\" to take the turn card." << endl;
		cout << "Enter \"d\" to draw a card from the deck." << endl;
		cin >> choice;
	}
	/* handle user wants the turn card */
	if (choice == 't')
		state.userHand.push_back(state.turnCard);
	/* handle user wants to draw a new card from the deck */
	else
	{
		state.userHand.push_back(state.deck.back());
		state.deck.pop_back();
	}
	printHand(state.userHand);

	/* Give user options for tossing */
	cout << "Enter \"g\" to give back a card or \"r\" to rearrange your hand.";
	cout << endl;
	cin >> choice;
	while (choice != 'g' && choice != 'r')
	{
		cout << "Enter \"g\" to give back a card or \"r\" to rearrange your hand.";
		cout << endl;
		cin >> choice;
	}
	while (choice != 'g')
	{
		/* Handle user wants to rearrange hand */
		if (choice == 'r')
		{
			char pos1, pos2;
			cout << "Enter the position of first card to swap [1-8]." << endl;
			cin >> pos1;
			while (pos1 < '1' || pos1 > '8')
			{
				cout << "Enter the position of first card to swap [1-8]." << endl;
				cin >> pos1;
			}
			cout << "Enter the position of second card to swap [1-8]." << endl;
			cin >> pos2;
			while (pos2 < '1' || pos2 > '8')
			{
				cout << "Enter the position of second card to swap [1-8]." << endl;
				cin >> pos2;
			}
			/* swap cards */
			swap(state.userHand, pos1-49, pos2-49);		// subtract 48 for ASCII, subtract 1 more for 0 indexing
			printHand(state.userHand);					// print user's hand
		}
		/* Give user options for tossing */
		cout << "Enter \"g\" to give back a card or \"r\" to rearrange your hand.";
		cout << endl;
		cin >> choice;
		while (choice != 'g' && choice != 'r')
		{
			cout << "Enter \"g\" to give back a card or \"r\" to rearrange your hand.";
			cout << endl;
			cin >> choice;
		}
	}
	/* handle user wants to give back a card */
	if (choice == 'g')
	{
		cout << "Enter the position of the card you would like to give back [1-8].";
		cout << endl;
		char pos;
		cin >> pos;
		while (pos < '1' || pos > '8')
		{
			cout << "Enter the position of the card you would like to give back [1-8].";
			cout << endl;
			cin >> pos;
		}
		state.turnCard = state.userHand[pos-49];					// set turn card
		state.remaining.remove(state.turnCard);						// remove from remaining cards
		state.userHand.erase(state.userHand.begin()+pos-49);		// remove from user hand
	}
}

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
int evaluate(State state)
{
	mergeSort(state.agentHand, 0, state.agentHand.size());
	vector<int> hand = state.agentHand;
	list<int> remaining = state.remaining;
	int score = 0;					// score of hand
	int rank;								// rank of card
	int val;								// stored value of card

	/* Check if hand is a winner */
	if (isWinner(hand))
		return 100;

	/* Check for 4 of a kind or 4 in a row */
	for (int i = 0; i < hand.size() - 3; i++)
	{
		val = hand[i];
		rank = val % 13;
		/* Check for 4 of a kind */
		int matchCount = 0;
		for (int j = i + 1; j < hand.size(); j++)
		{
			if (rank == hand[j] % 13)
				matchCount++;
		}
		if (matchCount == 3)
		{
			score += 15;
			matchCount = 0;
		}

		/* Check for 4 in a row */
		if (val < 10 && val+1 == hand[i+1] && val+2 == hand[i+2]
				&& val+3 == hand[i+3])
			score += 15;
	}

	/* Check for 3 of a kind or 3 in a row */
	for (int i = 0; i < hand.size() - 2; i++)
	{
		val = hand[i];
		rank = val % 13;

		/* Check for 3 of a kind */
		int matchCount = 0;
		for (int j = i + 1; j < hand.size(); j++)
		{
			if (rank == hand[j] % 13)
				matchCount++;
		}
		if (matchCount == 2)
		{
			score += 9;
			/* Check for 1 of the same kind in remaining cards */
			for (list<int>::iterator it = remaining.begin();
						it != remaining.end(); it++)
				if (*it % 13 == rank)
					score ++;
			matchCount = 0;
		}	

		/* Check for 3 in a row */
		if (rank < 11 && val+1 == hand[i+1] && val+2 == hand[i+2])
		{
			score += 9;
			/* Check for 1 before and 1 after in remaining cards */
			for (list<int>::iterator it = remaining.begin();
						it != remaining.end(); it++)
			{
				if (rank > 0 && *it == val - 1)
					score++;
				if (rank < 10 && *it == val + 3)
					score++;
			}
		}
	}

	/* Check for 2 of a kind or 2 in a row */
	for (int i = 0; i < hand.size() - 1; i++)
	{
		val = hand[i];
		rank = val % 13;

		/* Check for 2 of a kind */
		int matchCount = 0;
		for (int j = i + 1; j < hand.size(); j++)
		{
			if (rank == hand[j] % 13)
				matchCount++;
		}
		if (matchCount == 1)
		{
			/* Check to see if any remain */
			for (list<int>::iterator it = remaining.begin();
						it != remaining.end(); it++)
				if (*it % 13 == rank)
					score++;
			matchCount = 0;
		}

		/* Check for 2 in a row */
		if (rank < 12 && val+1 == hand[i+1])
		{
			/* Check for 1 or 2 before and 1 or 2 after in remaining cards */
			for (list<int>::iterator it = remaining.begin();
						it != remaining.end(); it++)
			{
				if (rank > 0 && *it == val - 1)
				{
					score++;
					for (list<int>::iterator jt = remaining.begin();
						jt != remaining.end(); jt++)
						if (rank > 1 && *jt == val - 2)
							score++;
				}
				if (rank < 11 && *it == val + 2)
				{
					score++;
					for (list<int>::iterator jt = remaining.begin();
						jt != remaining.end(); jt++)
						if (rank < 10 && *jt == val + 3)
							score++;
				}
			}
		}			
	}

	return score;
}


/*
 * A function that determines whether the agent
 * should pick up the turn card or not.
 * If the turn card is a winner, return true.
 * If the turn card results in a 3 of a kind
 * or 3 in a row that wasn't there before, return true.
 * Else, return false.
 */
bool takeTurnCard(State state)
{
	State originalState = state;
	vector<int> testHand = state.agentHand;
	testHand.push_back(state.turnCard);	// add turn card to hand to test

	/* Empty agent hand */
	while (state.agentHand.empty() == false)
		state.agentHand.pop_back();

	/* Check all possible new hands */
	for (int i = 0; i < testHand.size(); i++)
	{
		for (int j = 0; j < testHand.size(); j++)
		{
			if (i != j)
				state.agentHand.push_back(testHand[j]);
		}

		/* Check if new hand is a winner */
		if (isWinner(state.agentHand))
			return true;

		/* Check if new hand is better than old */
		if (evaluate(state) > evaluate(originalState))
			return true;

		while (state.agentHand.empty() == false)
			state.agentHand.pop_back();
	}
	return false;
}

/*
 * A function that removes the worst card from the agent's
 * hand.  IE, the card that produces the highest evaluation
 * score when removed.
 */
int removeWorstCard(State &state)
{
	State testState = state;

	/* Empty agent hand of testState */
	while (testState.agentHand.empty() == false)
		testState.agentHand.pop_back();

	int maxEval = 0;
	int maxEvalIndex = 0;
	int eval = 0;

	/* Find the card that when removed produces the highest score */
	for (int i = 0; i < state.agentHand.size(); i++)
	{
		for (int j = 0; j < state.agentHand.size(); j++)
		{
			if (i != j)
				testState.agentHand.push_back(state.agentHand[j]);
		}

		eval = evaluate(testState);
		if (eval > maxEval)
		{
			maxEval = eval;
			maxEvalIndex = i;
		}

		/* Empty agent hand of testState */
		while (testState.agentHand.empty() == false)
			testState.agentHand.pop_back();
	}

	int returnVal = state.agentHand[maxEvalIndex];

	/* Remove worst card */
	state.agentHand.erase(state.agentHand.begin() + maxEvalIndex);

	return returnVal;
}

/*
 * A function that plays a computer agent's turn in rummy.
 */
void playAgentTurn(State &state)
{
	/* Must be rewritten with dropCard function */
	if (takeTurnCard(state))
	{
		cout << "The computer took the turn card!" << endl;
		int turnCard = state.turnCard;
		state.agentHand.push_back(turnCard);
		state.turnCard = removeWorstCard(state);
	}
	else
	{
		cout << "The computer drew from the deck." << endl;
		state.agentHand.push_back(state.deck.back());
		state.remaining.remove(state.deck.back());
		state.deck.pop_back();
		state.turnCard = removeWorstCard(state);
	}
}
