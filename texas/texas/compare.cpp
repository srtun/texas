/*
function compare:
compare which player won
0.Royal flush > 
1.straight flush > 2.four of a kind > 3.full house > 4.flush > 5.staight > 6.three of a kind > 7.two pair > 8.one pair > 9.high card
*/

#include <iostream>
#include <vector>
#include "poker.h"
#include <algorithm>
#include <math.h>

using namespace std;
vector<int> compare(vector<vector<Poker>>& player) {
//int compare(vector<vector<Poker>> &player) {
    vector<string> rank_type = {"Royal flush", "straight flush", "four of a kind", "full house", 
                                "flush", "staight", "three of a kind", "two pairs", "pair", "high card"};
    int poker_size = 13;
    
    int p = player.size();
    vector<int> rank(p, 9);     // which rank type
    vector<double> val(p, 0.0); // rank is tie -> compare val
	vector<vector<int>> num (p, vector<int>(poker_size + 2, 0)); //num[i, 0] = 0, num[i, 1] = num[i, 14] -> A
    
    // build the table
    for (int ix = 0; ix < p; ++ix) {
        vector<Poker> ::iterator iter = player[ix].begin();
        for (int iy = 0; iter != player[ix].end(); ++iter, ++iy) {
            int fig = (*iter).figure();
            ++num[ix][fig];
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
    vector<int> pair(p, 0);         // pair
    vector<int> two_pair(p, 0);     // two pair
    vector<int> tok(p, 0);          // three of a kind
    vector<int> fok(p, 0);          // four of a kind

    for (int i = 0; i < num.size(); ++i) {
        int cnt = 0;
        for (int j = 2; j <= poker_size + 1; ++j) { 
            if (num[i][j] == 2) {
                if (pair[i]) two_pair[i] = j;
                else pair[i] = j;
            }
            else if (num[i][j] == 3) {
                tok[i] = j;
            }
            else if (num[i][j] == 4) {
                fok[i] = j;
                rank[i] = 2;                    // fok
                val[i] = j;
            }
            cnt += num[i][j];
            if (cnt >= 4) break;
        }
    }

    vector<bool> fh (p, false);
    for (int i = 0; i < p; ++i) {
        fh[i] = tok[i] * pair[i];
        if (fh[i]) {
            rank[i] = 3;                        // full house
            val[i] = pair[i];
            val[i] = val[i] / 15 + tok[i];
        }
        else if (tok[i]) {
            rank[i] = 6;                        // three of a kind
            val[i] = tok[i];
        }
        else if (two_pair[i]) {
            rank[i] = 7;                        // two pairs
            val[i] = pair[i];
            val[i] = val[i] / 15 + two_pair[i];
        }
        else if (pair[i]) {
            rank[i] = 8;                        // pair
            val[i] = pair[i];
        }
    }


    // flush
    vector<int> flush (p, 0);
    for (int ix = 0; ix < p; ++ix) {
        if (rank[ix] != 9) continue;
        vector<Poker> ::iterator iter = player[ix].begin();
        flush[ix] = (*iter).figure();
        if (flush[ix] == 1) flush[ix] = 14;
        string suit = (*iter).suit();
        ++iter;
        for (int iy = 1; iter != player[ix].end(); ++iter, ++iy) {
            if ((*iter).suit() != suit) {
                flush[ix] = 0;
                break;
            }
            else if ((*iter).figure() == 1) flush[ix] = 14;
            else flush[ix] = max(flush[ix], (*iter).figure());
        }
    }
    // straight
    vector<int> straight (p, 0);
    for (int i = 0; i < num.size(); ++i) {
        if (rank[i] != 9) continue;
        int cnt = 0;
        
        // case: 10JQKA
        bool royal = num[i][1]; 
        for (int j = 10; j < num[i].size(); ++j) {
            royal = royal & num[i][j];
        }
        if (royal) {
            straight[i] = 14; // A
            continue;
        }
        
        // normal case
        for (int j = 1; j <= poker_size; ++j) { // 1 ~ K
            if (!straight[i]) {
                if (num[i][j]) {
                    ++cnt;
                    straight[i] = j;
                }
            }
            else if(straight[i]) {
                if (num[i][j]) {
                    ++cnt;
                    straight[i] = j;
                }
                else {
                    straight[i] = 0;
                    break;
                }
            }
            if (cnt == 5) {
                break;
            }
        }
    }

    for (int i = 0; i < p; ++i) {
        if (flush[i] && straight[i]) {
            rank[i] = 1;
            val[i] = straight[i];
        }
        else if (flush[i]) {
            rank[i] = 4;
            val[i] = flush[i];
        }
        else if (straight[i]) {
            rank[i] = 5;
            val[i] = straight[i];
        }
    }
    // high card
    for (int i = 0; i < p; ++i) {
        if (rank[i] != 9) continue;
        for (int j = 14; j > 1; --j) {
            if (num[i][j]) {
                val[i] = j;
                break;
            }
        }
    }
    // find the winner
    // TODO need to handle more than one players win
    vector<int> win;
    //vector<int> *res = &win;
    win.push_back(0);
    int winner = 0;
    int value;
    //int value = (int) val[0];
    //cout <<"player 0: "<< rank_type[rank[0]] << " " << value << endl;
    //cout << "val: " << val[0] << endl;
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
        //cout << "player " << i << ": " << rank_type[rank[i]] << " " << value << endl;
        //cout << "val: " << val[i] << endl;
    }
    //cout << endl;
	return win;
}

