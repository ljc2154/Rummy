Rummy
=====

A command line version of the card game Rummy with competitive Computer Agent written in C++.

# Preface #
Rummy is my Grandma's favorite card game to play.
However, it takes at least two to play Rummy.
Since my Grandpa passed, she has not been playing very much Rummy.

Last Summer, I wrote this game in my spare time.
The game has a computer agent, so a player can play it alone.
I would argue that the agent is competitive.
Although I have won games here and there, I have never won a best of 7 series.

On 4th Of July, I showed the game to Grandma.
She was able to bring out a few bugs in the game which I have since fixed.

In the rest of this document, I will explain:
* The rules of rummy and how Grandma's rules and my game's rules differ.
* How the flow of the game works in my implementation.
* My implementation choices and description of AI behind Computer Agent.

# Rules of Rummy #
The rules in the **Basic Rummy** section were taken from http://www.pagat.com/rummy/rummy.html

## Basic Rummy ##

The game is best played with two to four players, but up to six can take part. Either a fixed number of deals are played, or the game is played to a target score. The number of deals or the target score needs to be agreed before beginning to play.

### The Deck ###

One standard deck of 52 cards is used. Cards in each suit rank, from low to high:

Ace 2 3 4 5 6 7 8 9 10 Jack Queen King

### The Deal ###

The first dealer is chosen randomly, and the turn to deal alternates if there are two players, and rotates clockwise if there are more than two. In a two player game, each player is dealt a hand of ten cards. Seven cards each are dealt if there are three or four players, and when five or six play each player gets six cards. The cards are dealt one at a time, and after the deal, the next card is placed face up on the table to start the discard pile, and the remainder of the deck is placed face down beside it to form the stock. The players look at and sort their cards.

### Object of the Game ###

The object of the game is to dispose of all the cards in your hand. There are three ways to get rid of cards: melding, laying off, and discarding.

**Melding** is taking a combination of cards from your hand, and placing it face up in front of you on the table, where it stays. There are two kinds of combination which can be melded: sequences (also known as runs) and groups (also known as sets or books).
a sequence or run consists of three or more cards of the same suit in consecutive order, such as club4, club5, club6 or heart8, heart9, heart10, heartJ.
a group, set or book is three or four cards of the same rank, such as diamond7, heart7, spade7.

**Laying off** is adding a card or cards from your hand to a meld already on the table. The cards added to a meld must make another valid meld. For example to the club4, club5, club6 you could add the club3 or the club7. You are not permitted to rearrange the melds in the process. For example, club2, heart2, diamond2, spade2 and spade3, spade4, spade5 have been melded, you are not permitted to move the spade2 from the group to the sequence, so as to lay off the spadeA.

**Discarding** is playing a card from your hand on top of the discard pile. You get rid of one card this way at the end of each turn.

### Play ###

If there are two players, they take alternate turns starting with the non dealer. If there are more than two players, they take turns in clockwise rotation, beginning with the player to dealer's left.

Each turn consists of the following parts:

**The Draw**. You must begin by taking one card from either the top of the Stock pile or the top card on the discard pile, and adding it to your hand. The discard pile is face up, so you can see in advance what you are getting. The stock is face down, so if you choose to draw from the stock you do not see the card until after you have committed yourself to take it. If you draw from the stock, you add the card to your hand without showing it to the other players.

**Melding**. If you have a valid group or sequence in your hand, you may lay one such combination face up on the table in front of you. You cannot meld more than one combination in a turn (but see House Rules). Melding is optional; you are not obliged to meld just because you can.

**Laying off**. This is also optional. If you wish, you may add cards to groups or sequences previously melded by yourself or others. There is no limit to the number of cards a player may lay off in one turn.

**The Discard**. At the end of your turn, one card must be discarded from your hand and placed on top of the discard pile face up. If you began your turn by picking up the top card of the discard pile you are not allowed to end that turn by discarding the same card, leaving the pile unchanged - you must discard a different card. You may however pick up the discard on one turn and discard that same card at a later turn. If you draw a card from the stock, it can be discarded on the same turn if you wish.

If the stock pile has run out and the next player does not want to take the discard, the discard pile is turned over, without shuffling, to form a new stock, and play continues - but see the variations section for a discussion of alternatives and problems that can arise.
A player wins an individual hand by either melding, laying off, or discarding all of his or her cards. Getting rid of your last card in one of these ways is called going out. As soon as someone goes out, play ceases. There can be no further melding or laying off, even if the other players have valid combinations in their hands.

### Scoring ###
When a player goes out, the other players add up the value of all the cards still remaining in their hands, as follows:

* Face cards (K,Q,J) are worth 10 points each
* Aces are worth 1 point each.
* Number Cards are worth their face value - for example a six is worth 6 points, a four is 4 points, and so on.
* The total value of all the cards in the hands of the other players is added to the winner's cumulative score.

The game continues with further deals until a player reaches the points target that was decided before the game began, or until the agreed number of deals has been played.

## Variations in my Version ##

### Grandma's Rules ###

### Additional Notes ###

# Game Flow #

## Initial Set Up ##

## User Turn ##

## Agent Turn ##

# Implementation #

## C++ ##

## Computer Agent AI ##

### Determine Best Hand ###

### Drop Worst Card ###
