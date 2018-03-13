#ifndef __PLAYER_H__
#define __PLAYER_H__

#include <iostream>
#include "common.hpp"
#include "board.hpp"
#include <vector>
using namespace std;

class Player {

public:
    Player(Side side);
    ~Player();

    double doDC(Side oppcolor);
    int doCorner(Board *cboard, Side current);
    int doAdjacent(Board *cboard, Side current);
    int mobility(Board *cboard, Side current, Side oppcolor);
    void setBoard();
    void freeMoves(vector<Move*> possible_moves);
    Move *doMove(Move *opponentsMove, int msLeft);
    vector<Move*> possMoves(Board *board, Side side);
    int minimax(Board *cboard, int depth, Side oppcolor);
    int ab(Board *cboard, int depth, Side current, Side oppcolor, int alpha, int beta);

    // Flag to tell if the player is running within the test_minimax context
    bool testingMinimax;
};

#endif