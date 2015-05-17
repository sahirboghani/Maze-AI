#include"maze.h"
#include <sstream>

Maze::Maze(){
   num_rows = 0;
   num_cols = 0;
   start_row = 0;
   start_col = 0;
   end_row = 0;
   end_col = 0;
   current_row = 0;
   current_col = 0;
}

Maze::Maze(const Maze& old)
{
	num_rows = old.num_rows;
	num_cols = old.num_cols;
	start_row = old.start_row;
	start_col = old.start_col;
	end_row = old.end_row;
	end_col = old.end_col;
	current_row = old.current_row;
	current_col = old.current_col;

	maze = new char*[num_rows];

	for(int y=0; y < num_rows; y++)
	{
		maze[y] = new char[num_cols];

		for(int x=0; x < num_cols; x++)
		{
			maze[y][x] = old.maze[y][x];
		}
	}
}

Maze::~Maze()
{
	for(int y=0; y < num_rows; y++)
	{
		delete[] maze[y];
	}

	delete[] maze;
}

void Maze::ReadMaze(string name){
   // Read maze parameter from txt file
   ifstream din;
   din.open(name.c_str());
   din >> num_rows >> num_cols;

	maze = new char*[num_rows];

	for(int y=0; y < num_rows; y++)
	{
		maze[y] = new char[num_cols];
	}

   din >> start_row >> start_col;
   din >> end_row >> end_col;
   current_row = start_row;
   current_col = start_col;

	// Read maze body from txt file
	string line;
	getline(din, line);
	for (int r = 0; r < num_rows; r++)
	{
		getline(din, line);
		for (int c = 0; c < num_cols; c++)
			if (c < int(line.length()))
				maze[r][c] = line[c];
	}
	din.close();
}


string Maze::PrintMaze()
{
	ostringstream out;

	// Print maze
	out<<*this;

	return out.str();
}

ostream& operator<<(ostream &out, const Maze& maze)
{
	// Print maze
	for (int r = 0; r < maze.num_rows; r++)
	{
		for (int c = 0; c < maze.num_cols; c++)
			out << maze.maze[r][c];
		out << endl;
	}

	out<<endl<<"---------------------------------------------"<<endl<<endl;

	return out;
}


bool Maze::isFinish(){
	return (current_row==end_row)&&(current_col==end_col);
}


bool Maze::west(){
	int t = current_col-1;
	if((t<0)||(t>=num_cols))
		return false;
	else if(maze[current_row][t]!=' ')
		return false;
	else
	{
		maze[current_row][current_col]=' ';
		current_col=t;
		maze[current_row][current_col]='@';
		return true;
	}
}

bool Maze::east(){
	int t = current_col+1;
	if((t<0)||(t>=num_cols))
		return false;
	else if(maze[current_row][t]!=' ')
		return false;
	else
	{
		maze[current_row][current_col]=' ';
		current_col=t;
		maze[current_row][current_col]='@';
		return true;
	}
}

bool Maze::north(){
	int t = current_row-1;
	if((t<0)||(t>=num_rows))
		return false;
	else if(maze[t][current_col]!=' ')
		return false;
	else
	{
		maze[current_row][current_col]=' ';
		current_row=t;
		maze[current_row][current_col]='@';
		return true;
	}
}

bool Maze::south(){
	int t = current_row+1;
	if((t<0)||(t>=num_rows))
		return false;
	else if(maze[t][current_col]!=' ')
		return false;
	else
	{
		maze[current_row][current_col]=' ';
		current_row=t;
		maze[current_row][current_col]='@';
		return true;
	}
}


void Maze::getStart(){
	current_row = start_row;
	current_col = start_col;
	maze[current_row][current_col]='@';
}


void Maze::getCurrentLocation(int& x, int& y){
	x = current_col;
	y = current_row;
}
