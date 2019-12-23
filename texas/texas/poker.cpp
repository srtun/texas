// figure: 1 ~ 13
// suit: spade(0), heart(1), diamond(2), club(3)

#include <string>
#include <vector>
#include "poker.h"

using namespace std;

Poker::Poker() {
	_figure = 0;
	_suit = "";
}

Poker::Poker(int figure, int suit) {
	_figure = figure;
	_suit = suit_type[suit];
}

int Poker::figure() {
	return _figure;
}

string Poker::suit() {
	return _suit;
}

int Poker::rank() {
	return _rank;
}

void Poker::set_figure(int figure) {
	_figure = figure;
}

void Poker::set_suit(int suit) {
	_suit = suit_type[suit];
}

void Poker::set_rank(int rank) {
	_rank = rank;
}

