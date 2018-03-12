#include "player.hpp"
#include <vector>
#define EDGE_WEIGHT     5
#define CORNER_WEIGHT   10
#define ADJ_C_WEIGHT    -100
#define ADJ_C_MID_WT    -200
#define OTHERS          1
#define DLEVEL          3

/*
 * Constructor for the player; initialize everything here. The side your AI is
 * on (BLACK or WHITE) is passed in as "side". The constructor must finish
 * within 30 seconds.
 */

Board *board;
Side ourcolor;
double scores[8][8];
bool better;

Player::Player(Side side) {
    // Will be set to true in test_minimax.cpp.
    testingMinimax = false;
    better = true;
    
    // Added some global variables
    ourcolor = side;
    if (ourcolor == WHITE)
    {
        std::cerr << "WHITE" << std::endl;
    }
    else
    {
        std::cerr << "BLACK" << std::endl;
    }
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

/*
* doDC is based off of a Cornell heuristic to count discs for each
* team and result in a weighted score
* @param oppColor - opponent Side
*/
double Player::doDC(Side oppcolor)
{
    int m = 0, opp = 0;
    m = board->count(ourcolor);
    opp = board->count(oppcolor);
    return (100)*(m-opp)/(m+opp);
}

/*
* doCorner is based off of a Cornell heuristic to
* determine the number of corners each opponent has.
*/
int Player::doCorner(Board *cboard, Side ourcolor)
{
    int m = 0, opp = 0;
    Move* tcl = new Move(0, 0);
    Move* tcr = new Move(7, 0);
    Move* bcl = new Move(0, 7);
    Move* bcr = new Move(7, 7);

    if (cboard->checkMove(tcl, ourcolor))
    {
        m++;
    }

    if (cboard->checkMove(tcr, ourcolor))
    {
        m++;
    }

    if (cboard->checkMove(bcl, ourcolor))
    {
        m++;
    }

    if (cboard->checkMove(bcr, ourcolor))
    {
        m++;
    }

    delete tcl, tcr, bcl, bcr;
    return CORNER_WEIGHT* (m);
}

void Player::setBoard()
{
     char boardData[64] = {
        ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ',
        ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ',
        ' ', 'b', ' ', ' ', ' ', ' ', ' ', ' ',
        'b', 'w', 'b', 'b', 'b', 'b', ' ', ' ',
        ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ',
        ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ',
        ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ',
        ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '
    };
    board->setBoard(boardData);
}

void Player::freeMoves(vector<Move*> possible_moves)
{
    possible_moves.clear();
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
        board->doMove(opponentsMove, oppcolor);
    }
    if (board->hasMoves(ourcolor))
    {
        if (testingMinimax)
        {
            setBoard();
        }
        if (better)
        {
            vector<Move*> possible_moves = possMoves(board, ourcolor);
            int cx, cy, tscore, maxscore, alpha, beta;
            maxscore = -1e9;
            alpha = -1e9;
            beta = 1e9;
            tscore = 0;
            std::cerr << "Possible Moves: " << possible_moves.size() << std::endl;

            if (possible_moves.size() <= 0)
            {
                return nullptr;
            }
            for (int i = 0; i < possible_moves.size(); i++)
            {
                std::cerr << "Possible Move: (" << possible_moves[i]->getX() << ", " << possible_moves[i]->getY() << ")" << std::endl;
                Board *copied = board->copy();
                copied->doMove(possible_moves[i], ourcolor);
                tscore = ab(copied, DLEVEL, ourcolor, oppcolor, alpha, beta);
                if (tscore > maxscore)
                {
                    maxscore = tscore;
                    cx = possible_moves[i]->getX();
                    cy = possible_moves[i]->getY();
                }

                delete copied;
            }

            Move* myMove = new Move(cx, cy);
            board->doMove(myMove, ourcolor);

            freeMoves(possible_moves);
            return myMove;
        }
        else
        {
            // Based on heuristics from: Cornell Othello
            double dc, maxhc;
            int c, m, maxx, maxxy, opp, multiplier;

            // corners
            c = doCorner(board, ourcolor);

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
                delete play;
            }
            else
            {
                delete play;
            }
        }
    }
    return moves;
}

/*
 * Minimax helper function for minimax
 * @param board, depth, side for opposite player
 * @return alpha (score)
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
        freeMoves(possible_moves);
        return -cboard->count(oppcolor)+cboard->count(ourcolor);
    }
    else
    {
        for (int i = 0; i < possible_moves.size(); i++)
        {
            Board *copied = cboard->copy();
            copied->doMove(possible_moves[i], oppcolor);

            // calls heuristic to generate score for possible move
            temp = -minimax(copied, depth-1, oppcolor);

            // delete copy of board?

            if (alpha < temp)
            {
                // cx = possible_moves[i]->getX();
                // cy = possible_moves[i]->getY();
                alpha = temp;
            }
            delete copied;
        }

        // if (cx != -1)
        // {
        //     cboard->doMove(new Move(cx, cy), oppcolor);
        // }

        // return alpha;
        freeMoves(possible_moves);
        return alpha;
    }
}

int Player::ab(Board *cboard, int depth, Side current, Side oppcolor, int alpha, int beta)
{
    vector<Move*> possible_moves = possMoves(cboard, oppcolor);

    int temp, ccorners, ocorners;
    int cx = -1, cy = -1;

    if (possible_moves.size() == 0 || depth <= 0)
    {
        ccorners = doCorner(cboard, current);
        ocorners = doCorner(cboard, oppcolor);
        for (int i = 0; i < possible_moves.size(); i++)
        {
            if (possible_moves[i]->getX() == 0 || possible_moves[i]->getX() == 7)
            {
                if (possible_moves[i]->getY() == 0 || possible_moves[i]->getY() == 7)
                {
                    ocorners += 10;
                }
                else
                {
                    ocorners += 5;
                }
            }
            else if (possible_moves[i]->getY() == 0 || possible_moves[i]->getY() == 7)
            {
                ocorners += 5;
            }
        }
        vector<Move*> cpossible_moves = possMoves(cboard, current);
        for (int i = 0; i < cpossible_moves.size(); i++)
        {
            if (cpossible_moves[i]->getX() == 0 || cpossible_moves[i]->getX() == 7)
            {
                if (cpossible_moves[i]->getY() == 0 || cpossible_moves[i]->getY() == 7)
                {
                    ccorners += CORNER_WEIGHT;
                }
                else
                {
                    ccorners += EDGE_WEIGHT;
                }
            }
            else if (cpossible_moves[i]->getY() == 0 || cpossible_moves[i]->getY() == 7)
            {
                ccorners += EDGE_WEIGHT;
            }
        }
        freeMoves(possible_moves);
        freeMoves(cpossible_moves);
        return -cboard->count(oppcolor)+cboard->count(current)-ocorners+ccorners;
    }
    else
    {
        for (int i = 0; i < possible_moves.size(); i++)
        {
            Board *copied = cboard->copy();
            copied->doMove(possible_moves[i], oppcolor);

            // calls heuristic to generate score for possible move
            temp = -ab(copied, depth-1, oppcolor, current, -beta, -alpha);

            // delete copy of board?

            if (alpha < temp)
            {
                // cx = possible_moves[i]->getX();
                // cy = possible_moves[i]->getY();
                alpha = temp;
            }
            if (temp >= beta)
            {
                //std::cerr << "beta: " << beta << std::endl;
                freeMoves(possible_moves);
                delete copied;
                return beta;
            }
            delete copied;
        }

        // if (cx != -1)
        // {
        //     cboard->doMove(new Move(cx, cy), oppcolor);
        // }

        // return alpha;
        //std::cerr << "alpha: " << alpha << std::endl;
        freeMoves(possible_moves);
        return alpha;
    }
}