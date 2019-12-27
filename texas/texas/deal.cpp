/* 
function deal
deal the cards to the players
*/
#include <iostream>
#include <vector>
#include <functional>
#include <random>
#include "poker.h"

using namespace std;

void deal(vector<Poker> &player, vector<bool>& card_pool) {
//void deal(vector<vector<Poker>> &player){
    // rand function : generator and distribution
    // random figure
    random_device rd;
    default_random_engine gen = default_random_engine(rd());
    uniform_int_distribution<int> dis(1, 13);
    auto rand_figure = bind(dis, gen);
    // random suit
    random_device rd1;
    default_random_engine gen1 = default_random_engine(rd1());
    uniform_int_distribution<int> dis1(0, 3);
    auto rand_suit = bind(dis1, gen1);

    //vector<bool> card_pool (13*4 + 1, true);

    // deal the card
    /*
    int num_players = player.size(), hands = player[0].size();
    for (int p = 0; p < num_players; ++p) {
        for (int h = 0; h < hands; ++h) {
            int s = rand_suit();
            int fig = rand_figure();
            while (!card_pool[s * 13 + fig]) {
                s = rand_suit();
                fig = rand_figure();
            }
            player[p][h].set_figure(fig);
            player[p][h].set_suit(s);
            card_pool[s * 13 + fig] = false;
        }
    }*/
    int hands = player.size();
    for (int h = 0; h < hands; ++h) {
        int s = rand_suit();
        int fig = rand_figure();
        while (!card_pool[s * 13 + fig]) {
            s = rand_suit();
            fig = rand_figure();
        }
        player[h].set_figure(fig);
        player[h].set_suit(s);
        card_pool[s * 13 + fig] = false;
    }
    return;
}