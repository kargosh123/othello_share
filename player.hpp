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
    double doCorner();
    void setBoard();
    Move *doMove(Move *opponentsMove, int msLeft);
    vector<Move*> possMoves(Board *board, Side side);
    int minimax(Board *board, int depth, Side oppcolor);

    // Flag to tell if the player is running within the test_minimax context
    bool testingMinimax;
};

#endif