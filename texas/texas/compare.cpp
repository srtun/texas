/*
function compare:
compare which player won
0.Royal flush > 
1.straight flush > 2.four of a kind > 3.full house > 4.flush > 5.straight > 6.three of a kind > 7.two pair > 8.one pair > 9.high card
TODO: find the winner with exactly 5 cards instead of 7
*/

#include <iostream>
#include <vector>
#include "poker.h"
#include <algorithm>
#include <math.h>

#define POKER_FIGURE 13

using namespace std;
vector<int> compare(vector<vector<Poker>>& player, vector<Poker>& board) {
    vector<string> rank_type = {"Royal flush", "straight flush", "four of a kind", "full house", 
                                "flush", "straight", "three of a kind", "two pairs", "pair", "high card"};
    int poker_size = POKER_FIGURE;

    int p = player.size();

    for (int i = 0; i < p; ++i) {
        player[i].insert(player[i].end(), board.begin(), board.end());
    }

    vector<int> rank(p, 9);     // which rank type
    vector<double> val(p, 0.0); // rank is tie -> compare val
	vector<vector<int>> num (p, vector<int>(poker_size + 2, 0)); //num[i, 0] = 0, num[i, 1] = num[i, 14] -> A
    vector<vector<vector<int>>> suit_num;
    suit_num.resize(p);
    for (int i = 0; i < p; ++i) {
        suit_num[i].resize(4);
    }

    // build the tables
    for (int ix = 0; ix < p; ++ix) {
        vector<Poker> ::iterator iter = player[ix].begin();
        for (int iy = 0; iter != player[ix].end(); ++iter, ++iy) {
            int fig = (*iter).figure();
            ++num[ix][fig];
            int color = (*iter).suit_int();
            //cout << color << endl;
            if (fig == 1) fig = 14;
            suit_num[ix][color].push_back(fig);
        }
    }
    for (int i = 0; i < p; ++i) {
        num[i][14] = num[i][1];
    }

    // print the table
    /*r (int i = 0; i < num.size(); ++i) {
        for (int j = 2; j < num[i].size(); ++j) { // 2 ~ K
            cout << num[i][j] << " ";
        }
        cout << num[i][1] << " "; // A
        cout << endl;
    }*/

    // pair ~ four of a kind (fok)
    vector<vector<int>> pair;
    pair.resize(p);
    //vector<int> two_pair(p, 0);     // two pair
    vector<vector<int>> tok;        // three of a kind
    tok.resize(p);
    vector<int> fok(p, 0);          // four of a kind

    for (int i = 0; i < p; ++i) {
        int cnt = 0;
        for (int j = 2; j <= poker_size + 1; ++j) { 
            if (num[i][j] == 2) {
                //if (pair[i]) two_pair[i] = j;
                //else pair[i] = j;
                pair[i].insert(pair[i].begin(), j);
            }
            else if (num[i][j] == 3) {
                if (!tok[i].empty()) {
                    int len = pair[i].size();
                    int loc = 0;
                    for (int n = 0; n < len; ++n) {
                        if (tok[i][0] > pair[i][n]){
                            //pair[i].insert(pair[i].begin() + n, tok[i][0]);
                            loc = n;
                            break;
                        }
                    }
                    pair[i].insert(pair[i].begin() + loc, tok[i][0]);
                }
                tok[i].insert(tok[i].begin(), j);
            }
            else if (num[i][j] == 4) {
                fok[i] = j;
                rank[i] = 2;                    // fok
                val[i] = j;
            }
            cnt += num[i][j];
            if (cnt >= 6) break;
        }
        sort(pair[i].begin(), pair[i].end(), greater<int>());
    }

    vector<bool> fh (p, false);
    for (int i = 0; i < p; ++i) {
        fh[i] = !tok[i].empty() & !pair[i].empty();
        if (fh[i]) {
            rank[i] = 3;                        // full house
            val[i] = pair[i][0];
            val[i] = val[i] / 15 + tok[i][0];
        }
        else if (!tok[i].empty()) {
            rank[i] = 6;                        // three of a kind
            val[i] = tok[i][0];
        }
        else if (pair[i].size() >= 2) {
            rank[i] = 7;                        // two pairs
            val[i] = pair[i][1];
            val[i] = val[i] / 15 + pair[i][0];
        }
        else if (pair[i].size()) {
            rank[i] = 8;                        // pair
            val[i] = pair[i][0];
        }
    }


    // flush 
    vector<int> flush (p, 0);
    for (int ix = 0; ix < p; ++ix) {
        for (int iy = 0; iy < 4; ++iy) {
            if (suit_num[ix][iy].size() >= 5) {
                flush[ix] = iy + 4;
                break;
            }
        }
    }
    // straight
    vector<int> straight (p, 0);
    for (int i = 0; i < p; ++i) {
        for (int front = 1; front <= 10; ++front) { // A2345 ~ 10JQKA 
            bool is_straight = true;
            for (int cnt = 0; cnt < 5; ++cnt) {
                if (!num[i][front + cnt]) {
                    is_straight = false;
                    break;
                }
            }
            if (is_straight) straight[i] = front + 4;
        }
    }

    for (int i = 0; i < p; ++i) {
        if (flush[i]) {
            sort(suit_num[i][flush[i] - 4].begin(), suit_num[i][flush[i] - 4].end(), greater<int>());
            // flush
            if (rank[i] > 4) {
                rank[i] = 4;
                //sort(suit_num[i][flush[i] - 4].begin(), suit_num[i][flush[i] - 4].end(), greater<int>());
                val[i] = suit_num[i][flush[i] - 4][0];
            }
            // straight flush
            int list_size = suit_num[i][flush[i] - 4].size();
            if (suit_num[i][flush[i] - 4][0] == 14 && suit_num[i][flush[i] - 4][list_size - 4] == 5) { // A2345
                rank[i] = 1;
                val[i] = 5;
            }
            for (int j = 4; j < suit_num[i][flush[i] - 4].size(); ++j) {
                if (suit_num[i][flush[i] - 4][j - 4] - suit_num[i][flush[i] - 4][j] == 4) {
                    rank[i] = 1;
                    val[i] = suit_num[i][flush[i] - 4][j - 4];
                    if (val[i] == 14) rank[i] = 0; // royal
                    break;
                }
            }
        }
        else if (straight[i] && rank[i] > 5) { //straight
            rank[i] = 5;
            val[i] = straight[i];
        }
    }
    // high card
    for (int i = 0; i < p; ++i) {
        
        if (rank[i] == 9) {
            for (int j = 14; j > 1; --j) {
                if (num[i][j]) {
                    val[i] = j;
                    break;
                }
            }
        }
    }
    // find the winner
    vector<int> win;
    win.push_back(0);
    int winner = 0;
    int value;

    for (int i = 0; i < p; ++i) {
        if (i == 0) {

        }
        else if (rank[i] < rank[winner]) {
            winner = i;
            win.clear();
            win.push_back(i);
        }
        else if (rank[i] == rank[winner]) {
            if (val[i] > val[winner]) {
                winner = i;
                win.clear();
                win.push_back(i);
            }
            else if (val[i] == val[winner]) {
                if (rank[i] == 0 || rank[i] == 1 || rank[i] == 3 || rank[i] == 5) { // tie
                    win.push_back(i);
                }
                else if (rank[i] == 4) { // flush
                    bool tie = true;
                    for (int j = 0; j < 5; ++j) {
                        if (suit_num[i][flush[i] - 4][j] > suit_num[winner][flush[winner] - 4][j]) {
                            winner = i;
                            win.clear();
                            win.push_back(i);
                            tie = false;
                            break;
                        }
                        else if (suit_num[i][flush[i] - 4][j] < suit_num[winner][flush[winner] - 4][j]) {
                            tie = false;
                            break;
                        }
                    }
                    if (tie) {
                        win.push_back(i);
                    }
                }
                else {
                    bool tie = true;
                    for (int j = poker_size + 1; j > 1; --j) {
                        if (num[i][j] > num[winner][j]) {
                            winner = i;
                            win.clear();
                            win.push_back(i);
                            tie = false;
                            break;
                        }
                        else if (num[i][j] < num[winner][j]) {
                            tie = false;
                            break;
                        }
                    }
                    if (tie) {
                        win.push_back(i);
                    }
                }
            }
        }
        player[i][0].set_rank(rank[i]);
        value = (int) val[i];
        if (value == 14) value = 1;
        Poker temp(value, 1);
        cout << "player " << i << ": " << rank_type[rank[i]] << " " << temp.figure_str() << endl;
        cout << "val: " << val[i] << endl;
    }
	return win;
}

