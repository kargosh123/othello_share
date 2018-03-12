#include "player.hpp"
#include <vector>
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
double scores[8][8];

Player::Player(Side side) {
    // Will be set to true in test_minimax.cpp.
    testingMinimax = false;
    
    // Added some global variables
    ourcolor = side;
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
            // RIRI CODE
            vector<Move*> possible_moves = possMoves(board, ourcolor);
            int cx, cy, tscore, maxscore;
            maxscore = -1e9;
            tscore = 0;

            for (int i = 0; i < possible_moves.size(); i++)
            {
                Board *copied = board->copy();
                copied->doMove(new Move(possible_moves[i]->getX(), possible_moves[i]->getY()), ourcolor);
                tscore = minimax(copied, 3, oppcolor);
                if (tscore > maxscore)
                {
                    maxscore = tscore;
                    cx = possible_moves[i]->getX();
                    cy = possible_moves[i]->getY();
                }
            }

            return new Move(cx, cy);
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

/*
 * Helper function to generate vector of all possible moves for a player
 * @param board, side
 * @return vector with pointers for each move
 */
vector<Move*> Player::possMoves(Board *cboard, Side side)
{
    vector<Move*> moves;

    for (int a = 0; a < 8; a++)
    {
        for (int b = 0; b < 8; b++)
        {
            Move *play = new Move(a, b);
            if(cboard->checkMove(play, side))
            {
                moves.push_back(play);
            }
        }
    }
    return moves;
}

/*
 * Minimax helper function for minimax
 * Welp I hope this works
 */
int Player::minimax(Board *cboard, int depth, Side oppcolor)
{
    // create vector with all possible moves (done in above helper function)
    // create another vector with scores
    // loop through vector
        // check if current move is valid
        // copy board
        // make move
        // use heuristic to check score of move that was made
        // add score to score vector
        // delete copy of board
        // recursively call this function
    // loop through scores vector to find highest value which corresponds to index of best move

    vector<Move*> possible_moves = possMoves(cboard, oppcolor);

    int temp;
    int alpha = -1e9;
    int cx = -1, cy = -1;

    if (possible_moves.size() == 0 || depth <= 0)
    {
        return -cboard->count(oppcolor)+cboard->count(ourcolor);
    }
    else
    {
        for (int i = 0; i < possible_moves.size(); i++)
        {
            Board *copied = cboard->copy();
            copied->doMove(possible_moves[i], oppcolor);

            // calls heuristic to generate score for possible move
            temp = minimax(copied, depth-1, oppcolor);

            // delete copy of board?

            if (alpha < temp)
            {
                cx = possible_moves[i]->getX();
                cy = possible_moves[i]->getY();
                alpha = temp;
            }
        }

        if (cx != -1)
        {
            cboard->doMove(new Move(cx, cy), oppcolor);
        }

        // return alpha;
        return alpha;
    }
}

idk Player::ABPruner(Board *cboard, int depth, Side oppcolor)
{
    if (turn == BLACK) {
        g = -INF;
        //sort the moves by their estimated score
        sort(mvs, mvs+(n+1), pair_more);
        float alpha = a;
        for (int i = 0; i < n && alpha < b; i++) {
            BitBoard btmp = bd;
            btmp.do_move(rmvs[mvs[i].second], turn);

            float v = alpha_beta_search(btmp, alpha, b, d-1, OTHER_SIDE(turn));

            g = max(g, v);
            alpha = max(alpha, g);
        }
    } else {
        g = INF;
        //sort the moves by their estimated score
        sort(mvs, mvs+(n+1), pair_less);
        float beta = b;
        for (int i = 0; i < n && a < beta; i++) {
            BitBoard btmp = bd;
            btmp.do_move(rmvs[mvs[i].second], turn);

            float v = alpha_beta_search(btmp, a, beta, d-1, OTHER_SIDE(turn));

            g = min(g, v);
            beta = min(beta, g);
        }
    }

}