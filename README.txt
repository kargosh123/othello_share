Team: Bozoteam
Team Members: Neymika Jain, Riana Karim

Describe how and what each group member contributed for the past two weeks.

For the past two weeks, we decided to split up the tasks or chunks of functionality and add to and build upon each other's initial implementations. An outline of the allotted tasks for each of us is below. We spent a lot of time debugging together, especially in office hours so we could ask the TAs for help if we were both stuck. We worked really well together in that we were able to work through first deciding on a general outline of what we wanted to do with pseudocode, and each implementing the code for our tasks first, and then working together to build upon our implementations and debug together. As discussed in the second question, sometimes a method we tried to code did not improve the performance of our bot, and we abandoned it to pursue other avenues to optimize our bot's peformance. We each tried different methods for optimization that were covered in the recitation slides, and tested them out to see if they were effective or not.

(Riana)
- DoMove function Part 1 implementation
- Minimax implementation
- AB Pruning
- Helper functions like possible moves possMoves
- Memory cleanup and deallocation
- Heuristic optimizations (mobility and frontier square)

(Neymika)
- Cornell heuristic implementation
- AB Pruning
- Weight calculations and considerations
- Helper functions like doCorner
- Memory cleanup and deallocation

Document the improvements that your group made to your AI to make it tournament-worthy. Explain why you think your strategy(s) will work. Feel free to discuss any ideas that were tried but didn't work out.

Our current strategies optimize in terms of time-efficiency by using alpha-beta pruning, and also free memory allocutions in such a manner that we can run our AI to 6-Depth (or more). However, after running several games (n = 20) on each side at a variety of depth, we found a higher success rate at depth = 4. Our minimax implementation would be subpar in comparison to the negamax, so it was not tested. In addition, we tried a variety of heuristics, including mobility, corners, adjacents, and edges, at several different weights and at the depth = 0 level of possible moves and at the depth = 0 level board. We noticed that when the heuristics were only run on the possible moves, the success rate increased, so we stopped trying it at the board. Overall, our intensive testing, heuristic implementations (and failures), and AI tree with AB pruning has made our AI tournament-worthy. As such we hope our strategy will work for at least 50% of the matches.
Below is our "Score Tally" demonstrating our testing.

- Changed weights for corners in heuristic
- Implemented Minimax
- Implemented AB Pruning
- Played with alpha and beta values to optimize our performance againts various other bots
- We tried adding heuristic optimizers such as mobility and frontier square but due to lower success rates, they were not used in the final AI
- We were also prudent with memory deallocation and freeing to prevent kills and speed up our performance overall


(From Score_Tally)
Neymika's Corner Version - Depth 3
(Weights: 10 - Corner, 5 - Edge)
 - bozoteam: Black
	Loss: 12
	Win: 8
	Rate: 40%
 - bozoteam: White
	Loss: 13
	Win: 7
	Rate: 35%
(Weights: 20 - Corner, 5 - Edge)
 - bozoteam: Black
	Loss: 13
	Win: 7
	Rate: 35%
 - bozoteam: White
	Loss: 15
	Win: 5
	Rate: 25%
(Switch calculations)
 - bozoteam: Black
	Loss: 20
	Win: 0
	Rate: 0%
 - bozoteam: White
	Loss: 18
	Win: 2
	Rate: 10%
(Weights: 10 - Corner, 5 - Edge, 20 - Possible Corner)
 - bozoteam: Black
	Loss: 12
	Win: 8
	Rate: 40%
 - bozoteam: White
	Loss: 15
	Win: 5
	Rate: 20%
(Weights: 10 - Corner, 5 - Edge, 20 - Possible Corner, Always Take Corner)
 - bozoteam: Black
	Loss: 7
	Win: 13
	Rate: 65%
 - bozoteam: White
	Loss: 8
	Win: 12
	Rate: 60%

Neymika's Corner Version - Depth 4
(Weights: 10 - Corner, 5 - Edge, 20 - Possible Corner, Always Take Corner)
 - bozoteam: Black
	Loss: 9
	Win: 11
	Rate: 55%
 - bozoteam: White
	Loss: 12
	Win: 8
	Rate: 40%
(Weights: 10 - Corner, 7 - Edge, 20 - Possible Corner, Always Take Corner
Take into Account Adjacent Tiles, 1 - Adjacent on Edge, 5 - Middle Adjacent, 7 - Total Adj Weight)
 - bozoteam: Black
	Loss: 11
	Win: 9
	Rate: 45% (changed to 7 in the middle)
 - bozoteam: White
	Loss: 13
	Win: 7
	Rate: 35%

(Screw everything)
 - bozoteam: Black
	Loss: 9
	Win: 11
	Rate: 55%
 - bozoteam: White
	Loss: 6
	Win: 14
	Rate: 70%

(Screw everything vs. BetterPlayer)
 - bozoteam: Black
	Loss: 2 
	Win: 
	Rate: 
 - bozoteam: White
	Loss: 
	Win: 2
	Rate: 

Riana's Mobility Version
(Screw everything + Weight: 5 - Mobility Heuristic)
 - bozoteam: Black
	Loss: 15
	Win: 5
	Rate: 25%
 - bozoteam: White
	Loss: 11
	Win: 9
	Rate: 45%
(Screw everything + Weight: 5 - Mobility Heuristic vs. BetterPlayer)
 - bozoteam: Black
	Loss: 2
	Win: 
	Rate: 
 - bozoteam: White
	Loss: 2
	Win: 
	Rate: 
(Screw everything + Weight: 2 - Mobility Heuristic)
 - bozoteam: Black
	Loss: 14
	Win: 6
	Rate: 30%
 - bozoteam: White
	Loss: 13
	Win: 7
	Rate: 35%

Final Version
(Screw everything)
 - bozoteam: Black
	Loss: 15
	Win: 5
	Rate: 25%
 - bozoteam: White
	Loss: 9
	Win: 11
	Rate: 55%
(Screw everything vs. BetterPlayer)
 - bozoteam: Black
	Loss: 2 
	Win: 
	Rate: 
 - bozoteam: White
	Loss: 
	Win: 2
	Rate:

(Screw everything - Corner = 15)
 - bozoteam: Black
	Loss: 6
	Win: 4
	Rate: 40%
 - bozoteam: White
	Loss: 4
	Win: 6
	Rate: 60%

(Screw everything - Corner = 15 vs. BetterPlayer)
 - bozoteam: Black
	Loss: 2 
	Win: 
	Rate: 
 - bozoteam: White
	Loss: 
	Win: 2
	Rate:



