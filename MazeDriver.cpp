/*
	Sahir Boghani
	COP 3503
	Section 6776
	Due 3/17/2014

*/
#include "maze.h"
#include "maze.cpp"
#include <iostream>

#define MAZE_FILE "maze.txt"

/*
	@ Parameters:
	Maze &M: 			Maze that is being solved
	int current_r: 		Current row position in the maze
	int current_c: 		Current column position in the maze
	int visited[][100]: 100 by 100 matrix (max possible size of maze) to keep track of visited location.
						If visited, location is '1' 
						Every other location is '0'
*/


void DFS(Maze &M, int current_r, int current_c, int visited[][100]) {
		
	// if maze is solved, we're done so return
	if (M.isFinish())
		return;
	
	// hit enter to see the move. Visually pleasing to the eye.
	cin.ignore();
	
	// print the maze
	cout << M << endl;

	// print the visited matrix. I am only printing the first 25 rows and columns 
	// because that is how big the ones we're working with are. 
	// i and j can be increased up to 100 depending on the size of the maze
	
	/*for(int i = 0; i < 25; i++) {
		for(int j = 0; j < 25; j++) {
			cout << visited[i][j];
		}	
		cout << endl;
	}*/

	// if the position "north" (in the visited matrix) has not been visited AND north is 
	// visitable (M.north() evaluates to true)
	if(visited[current_r-1][current_c] == 0 && M.north()) {
			
			// mark current location to be visited 
			visited[current_r][current_c] = 1;
			
			// call DFS with same maze M, decremented value of current row (since you went
			// "up" a "coordinate" in the visited matrix, and the updated visited matrix
			DFS(M, current_r-1, current_c, visited);
			
			// mark current location to be visited since you just came out of the recursive step
			visited[current_r][current_c] = 1;
			
			// if finished, return, else go the opposite way since there are no more possible moves
			// on the current attempted path
			if(M.isFinish())
				return;
			M.south();
	}

	// do the same process as earlier, except current column will be incremented 
	// since you went "right" a "coordinate" in the visited maxtrix
	if(visited[current_r][current_c+1] == 0 && M.east()) {
			visited[current_r][current_c] = 1;
			DFS(M, current_r, current_c+1, visited);
			visited[current_r][current_c] = 1;
			if(M.isFinish())
				return;
			M.west();
	}
	
	// do the same process as earlier, except current row will be incremented 
	// since you went "down" a "coordinate" in the visited maxtrix
	if(visited[current_r+1][current_c] == 0 && M.south()) {
			visited[current_r][current_c] = 1;
			DFS(M, current_r+1, current_c, visited);
			visited[current_r][current_c] = 1;
			if(M.isFinish())
				return;
			M.north();
	}	
	
	// do the same process as earlier, except current column will be decremented 
	// since you went "left" a "coordinate" in the visited maxtrix
	if(visited[current_r][current_c-1] == 0 && M.west()) {
			visited[current_r][current_c] = 1;
			DFS(M, current_r, current_c-1, visited);
			visited[current_r][current_c] = 1;
			if(M.isFinish())
				return;
			M.east();
	}
}

int main() {

	// make M and read in the file
	Maze M;
	M.ReadMaze(MAZE_FILE);

	// print maze M
	cout << "This is the maze" << endl;
	cout << M;
	
	// declare current row and column ints
	int current_r, current_c;
	
	// declare visited matrix and initialize all values to '0'
	int visited[100][100] = { 0 };

	// start the maze and assign start positions to current_r and current_c
	M.getStart();
	M.getCurrentLocation(current_c, current_r);

	// solve the maze recursively
	DFS(M, current_r, current_c, visited);

	// set the current row and column positions the final values (the finish coordinates)
	M.getCurrentLocation(current_c, current_r);
	
	// print whether or not the maze was solved
	if (M.isFinish()) {
		cout << M << endl;
		cout << "Solved the maze" << endl;
	}
	else
		cout << "Did not solve the maze" << endl;
	return 0;
}

