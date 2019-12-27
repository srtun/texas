// figure: 1 ~ 13
// suit: spade(0), heart(1), diamond(2), club(3)

#include <string>
#include <vector>
#include "poker.h"

using namespace std;

Poker::Poker() {
	_figure = 0;
	_figure_str = "";
	_suit = "";
	_suit_int = -1;
}

Poker::Poker(int figure, int suit) {
	_figure = figure;
	_figure_str = figure_name[figure];
	_suit = suit_type[suit];
	_suit_int = suit;
}

int Poker::figure() {
	return _figure;
}

string Poker::figure_str() {
	return _figure_str;
}

string Poker::suit() {
	return _suit;
}

int Poker::suit_int() {
	return _suit_int;
}

int Poker::rank() {
	return _rank;
}

void Poker::set_figure(int figure) {
	_figure = figure;
	_figure_str = figure_name[figure];
}

void Poker::set_suit(int suit) {
	_suit = suit_type[suit];
	_suit_int = suit;
}

void Poker::set_rank(int rank) {
	_rank = rank;
}

