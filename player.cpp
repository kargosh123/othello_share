#include "player.hpp"
#define EDGE_WEIGHT     25
#define CORNER_WEIGHT   100
#define ADJ_C_WEIGHT    -100
#define ADJ_C_MID_WT    -200
#define OTHERS          1

/*
 * Constructor for the player; initialize everything here. The side your AI is
 * on (BLACK or WHITE) is passed in as "side". The constructor must finish
 * within 30 seconds.
 */

Board *board;
Side ourcolor;
bool color;
double scores[8][8];

Player::Player(Side side) {
    // Will be set to true in test_minimax.cpp.
    testingMinimax = false;
    
    // Added some global variables
    ourcolor = side; // can we make this a boolean to check sides?
    color = (side == WHITE);
    board = new Board();
    for (int x = 0; x < 8; x++)
    {
        for (int y = 0; y < 8; y++)
        {
            scores[x][y] = 0.;
        }
    }

    /*
     * TODO: Do any initialization you need to do here (setting up the board,
     * precalculating things, etc.) However, remember that you will only have
     * 30 seconds.
     */
}

/*
 * Destructor for the player.
 */
Player::~Player() {
    delete[] board;
}

double Player::doDC(Side oppcolor)
{
    int m = 0, opp = 0;
    m = board->count(ourcolor);
    opp = board->count(oppcolor);
    return (100)*(m-opp)/(m+opp);
}

double Player::doCorner()
{
    int m = 0, opp = 0;
    if (board->checkMove(new Move(0, 0), ourcolor))
    {
        m++;
    }
    else
    {
        opp++;
    }
    if (board->checkMove(new Move(7, 0), ourcolor))
    {
        m++;
    }
    else
    {
        opp++;
    }
    if (board->checkMove(new Move(0, 7), ourcolor))
    {
        m++;
    }
    else
    {
        opp++;
    }
    if (board->checkMove(new Move(7, 7), ourcolor))
    {
        m++;
    }
    else
    {
        opp++;
    }
    return 100* (m-opp)/(m+opp);
}
/*
 * Compute the next move given the opponent's last move. Your AI is
 * expected to keep track of the board on its own. If this is the first move,
 * or if the opponent passed on the last move, then opponentsMove will be
 * nullptr.
 *
 * msLeft represents the time your AI has left for the total game, in
 * milliseconds. doMove() must take no longer than msLeft, or your AI will
 * be disqualified! An msLeft value of -1 indicates no time limit.
 *
 * The move returned must be legal; if there are no valid moves for your side,
 * return nullptr.
 */
Move *Player::doMove(Move *opponentsMove, int msLeft) {
    /*
     * TODO: Implement how moves your AI should play here. You should first
     * process the opponent's move before calculating your own move
     */

    // Process opponent's move and consider current state of board
    Side oppcolor;
    if (ourcolor == WHITE)
    {
        oppcolor = BLACK;
    }
    else
    {
        oppcolor = WHITE;
    }
    if (opponentsMove != nullptr)
    {
        board->doMove(new Move(opponentsMove->getX(), opponentsMove->getY()), oppcolor);
    }
    if (board->hasMoves(ourcolor))
    {
        if (testingMinimax)
        {
            //RIRI Code
        }
        else
        {
            // Based on heuristics from: Cornell Othello
            double c, dc, maxhc;
            int m, maxx, maxxy, opp, multiplier;

            // corners
            c = doCorner();

            //disc count
            dc = doDC(oppcolor);

            //get best move
            maxhc = scores[0][0];
            maxx = -1;
            maxxy = -1;
            multiplier = OTHERS;
            for (int x = 0; x < 8; x++)
            {
                for (int y = 0; y < 8; y++)
                {
                    if (y == 0 || y == 7)
                    {
                        if (x == 0 || x == 7)
                        {
                            multiplier = CORNER_WEIGHT;
                        }
                        else if (x != 1 && x != 6)
                        {
                            multiplier = EDGE_WEIGHT;
                        }
                        else
                        {
                            multiplier = ADJ_C_WEIGHT;
                        }
                    }
                    if (multiplier != CORNER_WEIGHT && (x == 0 || x == 7))
                    {
                        if (y != 1 && y != 6)
                        {
                            multiplier = EDGE_WEIGHT;
                        }
                        else
                        {
                            multiplier = ADJ_C_WEIGHT;
                        }
                    }
                    if ((x == 1 && y == 1) || (x == 6 && y == 6) || 
                        (x == 1 && y == 6) || (x == 6 && y == 1))
                    {
                        multiplier = ADJ_C_MID_WT;
                    }

                    if (board->checkMove(new Move(x, y), ourcolor))
                    {
                        if (maxx == -1)
                        {
                            maxhc = scores[x][y];
                            maxx = x;
                            maxxy = y;
                        }
                        scores[x][y] = multiplier*(10*c+5*dc);
                        if (maxhc < scores[x][y])
                        {
                            maxhc = scores[x][y];
                            maxx = x;
                            maxxy = y;
                        }
                    }
                }
            }

            board->doMove(new Move(maxx, maxxy), ourcolor);
            return new Move(maxx, maxxy);
        }
    }

    return nullptr;
}