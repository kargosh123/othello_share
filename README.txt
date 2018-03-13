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

(Why our strategies worked) neymikaaaaaaa

- Changed weights for corners in heuristic
- Implemented Minimax
- Implemented AB Pruning
- Played with alpha and beta values to optimize our performance againts various other bots
- We tried adding heuristic optimizers such as mobility and frontier square but with the 
- We were also prudent with memory deallocation and freeing to prevent kills and speed up our performance overall