// Cursor Control
// CS 452 - Operating Systems
// Professor Wolffe
// Program 1
// Author: Troy Veldhuizen
// Date: 09/13/17
//
#include <ncurses.h>

/*******************************************************************
 * Function: fit_terminal
 * ensures that user coordinates are within the window
 * int *usrx : pointer to the user entered x coordinate
 * int *usry : pointer to the user entered y coordinate
 * int * mx : pointer to maximum x value in the window
 * int * my : pointer to the maximum y value in the window
 *
 * returns: void
 ******************************************************************/
void fit_terminal(int *usrx, int *usry, int *mx, int *my){
	
	// allow space for two lines of output to screen
	if(*usry > *my -2)
		*usry = *my -2;

	// allow space for output
	if(*usrx > *mx - 41)
		*usrx = *mx - 41;
	
	// change negative values in x direction to 0
	if(*usrx < 0)
		*usrx = 0;
	
	// change negative values in y direction to 0
	if(*usry < 0)
		*usry = 0;
}



/*******************************************************************
 * Function: main
 * CLI to get user input and move curser in terminal
 *
 * returns: int, the termination status
 ******************************************************************/
int main(){
	
	char resp; // users response to exit prompt
	int loop = 1; // continue looping, 1 == yes, 0 == no
	int mx=0, my=0, usrx=0, usry=0; // rows and columns
	
	initscr(); // creates stdscr
	cbreak(); // allows exit using ctr-c
	
	getmaxyx(stdscr, my, mx);  // get window size
	
	printw("Window size is %d rows by %d columns.", my, mx);
	
	halfdelay(50); // delay for n tenths of a second. 
	getch();			 // waits for n tenths and moves on if no input
	cbreak();			 // turn cbreak mode back on

	clear();	// clear screen and home the cursor

	// max adjusted to fit prompt
	printw("Enter row and column (max %d %d)?  ", my - 2, mx - 41);
	scanw("%d %d", &usry, &usrx);
	fit_terminal(&usrx, &usry, &mx, &my);  // adjust user input if needed
	
	// loop to continue using the program
	while(loop){
		
		// move and prompt user if they want to quit
		mvprintw(usry, usrx, "Enter 'q' to exit, else press any key");
		resp = getch();

		// break out of loop if user entered 'q'
		if(resp == 'q'){
			loop = 0;
		} else {
			// enter the coordinates for next movement	
			mvprintw(usry + 1, usrx, "Enter row and column (max %d %d)?  ", my -1, mx);
			scanw("%d %d", &usry, &usrx);
			fit_terminal(&usrx, &usry, &mx, &my);  // adjust user input if needed
		}
	}

	endwin(); // clean up memory
	return 0;
}
