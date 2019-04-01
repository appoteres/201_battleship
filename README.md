201_connect4
CS201 2019 spring, Semester Portfolio Submission

Poteres, Andrew

For my portfolio project I created the game connect 4 in C, and utilized the curses library.

For the program to run, the user must have the ncurses library installed, as well as being able to use the make command.
To install curses on Debian/Ubuntu, user can run "sudo apt-get install libncurses5-dev"

Once downloaded/cloned and navigated to, the user must use the command 'make build'.
After that the game can be run by running the 'game' or './game' command.

Here we are brought to the main menu with 5 options.
The first 2 will let you play connect4 either versus another person, or solo versus the algorithm.
Upon choosing either of these, the user must first input the 
amount of rows they want, and then the amount of columns.
	NOTE: While you  technically can make an extremely large board (ex. 100000 x 1000), it is reccommended to stick to realistic numbers, as the display will not work properly beyond about 50x50 sizes. 
Then follow the on screen instructions to play the game. Invalid column inputs are handled by the game

In scores, one can check how player 'X' fares against player 'O'. Scores can also be reset by the 'Erase Scores' option

Exit, quits the program.

For more information about the features or about running the program, check out the tutorial video included in the .zip or by going to the link:
https://alabama.box.com/s/uudkql4y94m75tuwf864fzehc4qqnru1

Below is a summary of the code:

In this zip you will find:
	.gitignore
	README.md
	Connect4Tutorial.webm
	makefile
	boardgen.c
	boardgen.h
	main.c

.gitignore -
	Ignores all files specified from being pushed to the github repository
	Ignores .txt, .bin, and .o files

README.md -
	The file you are reading now, contains information about the program

Connect4Tutorial.webm -
	Video tutorial on how to run the program and how to play the game

makefile - 
	Allows user to build the runnable file with 'make build', also supports 'make clean' to clean out files created as a result of making
	'make build' is necessary to get the file 'game'. 'game' is run to access the program

boardgen.c -
	This file handles all operations directly related to generating the board class, and appending pieces to it.
	It also houses functions for checking the winning state of the game, and for the algorithm to decide where to move

boardgen.h - 
	Header file for boardgen.c, contains a few getters used by main to access private features of the board

main.c - 
	This is the main part of the program. This contains the logic needed for the menu, scoring, and board size selection (which is then sent to boardgen.c).
	This file also contains all the ncurses stuff, and makes the program beautiful!
	Part of the logic used for creating my menu was created by github user: cmsun in their ConnectFour repository. No logic was borrowed, only some of the curses work needed for drawing the initial menu was used. That code can be found in my main.c and their game.c.


Here are the Project Requirements put in place by the professor:

Connect-Four with arbitrary board size-one player against computer and player against
player-uses a function to determine wining state and must use a graph to determine the
“next best” move

Consist of ascii or curses-based interfaces
• Players should be able to choose game mode (single, double or playing against
computer).
• A series of matches can be played between the same opponents. The program should
keep score.