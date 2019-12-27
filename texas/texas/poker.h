// figure: 1 ~ 13
// suit: spade(0), heart(1), diamond(2), club(3)

#include <string>
#include <vector>

using namespace std;

class Poker {
public:
	Poker();
	Poker(int, int);

	int figure();
	string figure_str();
	string suit();
	int suit_int();
	int rank();

	void set_figure(int);
	void set_suit(int);
	void set_rank(int);

private:
	int _figure;
	string _figure_str;
	int _suit_int;
	string _suit;
	int _rank;
	vector<string> suit_type = {"spade", "heart", "diamond", "club"};
	vector<string> figure_name = {"", "A", "2", "3", "4", "5", "6", "7", "8", "9", "T", "J", "Q", "K"};
};
