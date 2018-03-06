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
// lol we should sort this out huehue

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
    if (board->hasMoves(ourcolor))
    {
        if (testingMinimax)
        {
            // access with helper function

        }
        else
        {
            // Based on heuristics from: Cornell Othello
            double c, dc, maxhc;
            int m, maxx, maxxy, opp, multiplier;
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

            if (maxx == -1)
            {
                return nullptr;
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
std::vector<*Move> Player::possMoves(Board board, Side side)
{
    std::vector<*Move> moves;

    for (int a = 0; a < 8; a++)
    {
        for (int b = 0; b < 8; b++)
        {
            Move *play = new Move(a, b);
            if(board.checkMove(play, side))
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
int *Player::minimax(Board *board, int depth, Side oppcolor)
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

    std::vector<*Move> possible_moves = Player::possMoves(board, color);
    std::vector<int> scores;

    int temp;
    int alpha = -1e9;
    int cx = -1, cy = -1;

    if (possible_moves.size() == 0)
    {
        // shouldn't this return null or nullptr or something cuz there are no possible moves left?
        return board->count(ourcolor)-board->count(oppcolor);
    }
    else
    {
        for (int i = 0; i < possible_moves.size(); i++)
        {
            board->copy()->doMove(possible_moves[i], oppcolor);

            // calls heuristic to generate score for possible move
            scores.push_back(Player::doMove(possible_moves[i], 30));

            // I think I already did this above though
            temp = Player::minimax(board->copy(), depth-1, my_side);

            // delete copy of board?

                if (alpha < temp)
                {
                    cx = i;
                    cy = j;
                    alpha = temp;
                }
        }

        // find index of highest score
        int highest_score = scores[0];
        int high_index = 0;
        for (int j = 0; j < possible_moves.size())
        {
            if (scores[j] > highest_score)
            {
                highest_score = scores[j];
                high_index = j;
            }
        }

        if (cx != -1)
        {
            board->doMove(cx, cy);
        }

        // return alpha;
        return high_index;
    }
}