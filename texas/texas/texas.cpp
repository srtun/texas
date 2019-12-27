// texas.cpp : 此檔案包含 'main' 函式。程式會於該處開始執行及結束執行。
//

// suit: spade, heart, dimond, club

#include <iostream>
#include <vector>
#include <random>
#include <functional>
#include "function.h"

using namespace std;

int main()
{
    
    int rounds = 10000;
    int r = rounds;
    int times = 0;
    vector<string> rank_type = { "Royal flush", "straight flush", "four of a kind", "full house",
                                "flush", "staight", "three of a kind", "two pairs", "pair", "high card" };
    vector<int> stat (10, 0);
    while (r--) {
        // decide the player number
        cout << ++times << endl;
        int p = 5, hands = 2;
        vector<bool> card_pool (13 * 4 + 1, true);
        vector<vector<Poker>> player;
        player.resize(p);
        for (int i = 0; i < p; ++i) {
            player[i].resize(hands);
        }
        // deal the hand card
        for (int i = 0; i < p; ++i) {
            deal(player[i], card_pool);
        }
        //deal(player);
        // deal the board card
        vector<Poker> board;
        board.resize(5);
        deal(board, card_pool);

        // set the card by human
        /*
        int input_fig = 0;
        int input_suit = 0;
        for (int i = 0; i < p; ++i) {
            for (int j = 0; j < hands; ++j) {
                cin >> input_fig >> input_suit;
                player[i][j].set_figure(input_fig);
                player[i][j].set_suit(input_suit);
            }
        }
        cin.get();
        */

        // print the hand cards
        
        for (int ix = 0; ix < p; ++ix) {
            vector<Poker> ::iterator iter = player[ix].begin();
            for (int iy = 0; iter != player[ix].end(); ++iter, ++iy) {
                cout << (*iter).figure_str();
                cout << (*iter).suit()[0] << " ";
            }
            cout << endl;
        }
        cout << endl;
        
        // print the board cards
        
        cout << "board card: " << endl;
        for (int i = 0; i < board.size(); ++i) {
            cout << board[i].figure_str();
            cout << board[i].suit()[0] << " ";
        }
        cout << endl << endl;
        
        vector<int> winner = compare(player, board);


        //stat
        for (int i = 0; i < p; ++i) {
            ++stat[player[i][0].rank()];
            if (player[i][0].rank() == 1 || player[i][0].rank() == 2) {
                //cin.get();
            }
        }
        
        // print the result
        
        if (winner.size() == p) {
            cout << "tie!!" << endl;
        }
        else {
            cout << "player ";
            for (auto i : winner) {
                cout << i << " ";
            }
            cout << "win(s)" << endl;
        }
        
        //if(winner.size() > 1) cin.get();
        cin.get();
        system("CLS");
        
    }
    for (int i = 1; i < 10; ++i) {
        double prob = stat[i];
        prob = 100 * prob / (rounds * 5);
        cout << rank_type[i] << ": " << stat[i]<<"("<<prob << "%)" << endl;
    }

    return 0;
}

// 執行程式: Ctrl + F5 或 [偵錯] > [啟動但不偵錯] 功能表
// 偵錯程式: F5 或 [偵錯] > [啟動偵錯] 功能表

// 開始使用的提示: 
//   1. 使用 [方案總管] 視窗，新增/管理檔案
//   2. 使用 [Team Explorer] 視窗，連線到原始檔控制
//   3. 使用 [輸出] 視窗，參閱組建輸出與其他訊息
//   4. 使用 [錯誤清單] 視窗，檢視錯誤
//   5. 前往 [專案] > [新增項目]，建立新的程式碼檔案，或是前往 [專案] > [新增現有項目]，將現有程式碼檔案新增至專案
//   6. 之後要再次開啟此專案時，請前往 [檔案] > [開啟] > [專案]，然後選取 .sln 檔案
