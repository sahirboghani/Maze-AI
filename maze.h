#ifndef MAZE_H
#define MAZE_H

#include <iostream>
#include <fstream>
using namespace std;

#define MAXSIZE 100

class Maze
{
 public:
   // Constructor
   Maze();
   Maze(const Maze& old);
   ~Maze();

   // Methods
   void ReadMaze(string name);
   string PrintMaze();
   bool isFinish();
   bool west();
   bool east();
   bool north();
   bool south();
   void getStart();
   void getCurrentLocation(int& x, int& y);

   friend ostream& operator<<(ostream& out, const Maze& maze);

 private:
   int num_rows, num_cols;
   int start_row, start_col;
   int end_row, end_col;
   int current_row, current_col;

   char** maze;
};

#endif // MAZE_H