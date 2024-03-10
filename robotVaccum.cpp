#include <iostream>
#include <vector>
#include <random>


using namespace std;


 const int numcols = 20;  // number of columns in our grid (width)
 const int numrows = 20;  // number of rows in our grid (height)
 char grid[numrows][numcols]; // declare our grid
 char original[numrows][numcols]; // declare our a duplicate of our grid for reference
 int trials=700;
 int currentRow = 0;      // starting row location of robot
 int currentCol = 0;      // starting col location of robot
 int totalMoves = 0;      // total count of moves made by the robot


 //
 // INIT THE GRID
 //
 void initGrid(){
   for(int r=0; r<numrows; r++){
     for(int c=0; c<numcols; c++){
       if(rand()%100 < 25){
         grid[r][c] = '*'; // this is an obstacle
       }
       else {
         grid[r][c] = '.';   // this is garbage
       }
       original[r][c] = grid[r][c]; // put in our original array for final scoring
     }
   }
 }


 //
 // PRINT THE GRID
 //


 void printGrid(){
  
   cout << "-";
   for(int c=0; c<numcols; c++) // print top border
     cout << "---";
   cout << "-" << endl;


   for (int i = 0; i < numrows; i++) { // print all rows
     cout << "|";
       for (int j = 0; j < numcols; j++) { // print a row
         cout << " " << grid[i][j] << " ";
       }
       cout << "|" << endl;
   }
   cout << "-";
   for(int c=0; c<numcols; c++) // print bottom border
     cout << "---";
   cout << "-" << endl;
 }


 //
 // GET ROW
 //


 int getRow(){   // return the current row location of the robot
     return currentRow;
 }


 int getCol(){
     return currentCol;  // return the current row location of the robot
 }


 //
 // MOVE TO
 //


 bool moveTo(int r, int c){ // move the robot to this location and sweep up what is there
   if (r<0 || r >= numrows) {
     cout << "moveT0() ignoring requested move to " << r << ", " << c << " because it is out of room" << endl;
     return false; // cannot move out of the room
   }


   if (c<0 || c >= numcols) {
     cout << "moveT0() ignoring requested move to " << r << ", " << c << " because it is out of room" << endl;
     return false; // cannot mvoe out of the room
   }


   if (abs(r-currentRow) > 1 || (abs(c-currentCol) >1)){
     cout << "moveT0() ignoring requested move to " << r << ", " << c << " because it is > 1 in either direction" << endl;
     return false; // cannot move by more than 1 in each direction
   }


   currentRow = r;
   currentCol = c;
   grid[r][c] = ' '; // clean what was there even if it it was an obstacle.
   totalMoves++; // increment the number of total moves taken so far
   return true;
 }










//
// PRINT SCORE
//


 void printScore(){
   int obstaclesMissing = 0;
   int obstaclesTotal = 0;
   int garbageTotal = 0;
   int garbageMissed = 0;




   for(int r=0; r<numrows;  r++){
     for(int c=0; c<numcols; c++){
       if (grid[r][c] == '.') garbageMissed++; // found leftover garbage,
       if (original[r][c] == '*') obstaclesTotal++; // total original obstacles
       if (original[r][c] == '.') garbageTotal++;   // total original garbage
       if (original[r][c] == '*' && grid[r][c] != '*') obstaclesMissing++; // someone removed an obstacle - that's bad
     }
   }


   int garbageSweptUp = (garbageTotal - garbageMissed);


   int score = numrows*numcols - garbageMissed - obstaclesMissing; // reduce score from total possible by garbage that was not picked up and obstacles that were removed
   score = (100*score)/(numrows*numcols); // normalized based on total possible squares in grid


   cout << "SCORE:" << endl;
   cout << "----------------------" << endl;
   cout << "Total squares in grid = " << numrows*numcols << endl;
   cout << "Garbage total (original): " << garbageTotal << endl;
   cout << "Obstacles total (original): " << obstaclesTotal << endl;
   cout << "Garbage swept up: " << garbageSweptUp << endl;
   cout << "Garbage Missed = " << garbageMissed << " (minus " << garbageMissed << " points)" << endl;
   cout << "Obstacles Missing = " << obstaclesMissing << " out of " << obstaclesTotal << " (minus " << obstaclesMissing << " points)"<< endl;
   cout << "Total Moves taken = " << totalMoves << endl;
   if (totalMoves > 0)
     cout << "Cleaning efficiency = garbage swept up/totalMoves = %" << ((100*garbageSweptUp)/totalMoves) << endl;
   cout << "Final normalized score out of 100 possible = " << score << endl;
  
   if (score > 90) cout << "Well done!" << endl;
   else if (score > 80) cout << "Not bad - your robot is a bit sloppy though" << endl;
   else if (score > 70) cout << "So So - your robot might need a tune up" << endl;
   else if (score > 60) cout << "Not so great - your robot seems to be having a bad day" << endl;
   else  cout << "Hmmm - might want to call in some iRobot back-up for help.  Let me know if you have questions!" << endl;
 }




 int blocked_garbage(){
   int blocked=0;
  
   for(int r=0; r<numrows;  r++){
     for(int c=0; c<numcols; c++){
       int neighbour=0;
       for(int i=r-1;i<=r+1;i++){
         for(int j=c-1;j<=c+1;j++){
           if(i>=0 && i<numrows && j>=0 && j<numcols){
             if (i==r and j==c) continue;
             else if(original[i][j] == '.') neighbour++;


           }
         }
       }
       if (neighbour==0) blocked++;
     }
   }
   return blocked;
 }
int total_garbage(){
   int total=0;
  
   for(int r=0; r<numrows;  r++){
     for(int c=0; c<numcols; c++){
       if(original[r][c] == '.') total++;
     }
   }
   return total;
 }
 //
 // SWEEP GRID TODO - you need to write this function so that it cleans grid[][] without sweeping up obstacles
 //


 void sweepGrid(){
   int cleared=0;
   int total=total_garbage();
   int blocked=blocked_garbage();
   //cout<<"Blocked pieces: "<<blocked<<"\n";
  
   vector<pair<int,int>> options;
   vector<pair<int,int>> neutral;
  while(cleared<(total-int(0.03*total)))
   {
   //  NOTE - you must use getRow() and getCol() to find the current location of the robot
  
   int myRow = getRow(); // get current row location of the robot
   int myCol = getCol(); // get current row location of the robot
  
   for(int i=myRow-1;i<=myRow+1;i++){
         for(int j=myCol-1;j<=myCol+1;j++){
           if(i>=0 && i<numrows && j>=0 && j<numcols){
             if (i==myRow and j==myCol) continue;
             else if(grid[i][j] == '.') options.push_back( make_pair(i,j) );
             else if(grid[i][j] == ' ') neutral.push_back( make_pair(i,j) );
           }
         }
       }
   int n_choices=int(options.size());
   int n_neutral=int(neutral.size());
   if(n_choices>0) {
     int choice=rand()%n_choices;
     cleared++;
     moveTo(options[choice].first,options[choice].second);
   }
   else {
     int rnd=rand()%n_neutral;
     //cout<<"\nFrom "<<myRow<<" "<<myCol<<" To "<<options[rnd].first<<" "<<options[rnd].second<<" ";
     moveTo(neutral[rnd].first,neutral[rnd].second);
   }
   options.clear();
   neutral.clear();
 }
 }




int main() {
 std::cout << "HW5 ALT - Robot Vacuum (starter) \n";


 initGrid();   // init the grid with garbage and obstacles
 cout << "Dirty Room before sweeping: " << endl;
 printGrid();


 sweepGrid();  // TODO Your routine!


 cout << "Clean Room after sweeping: " << endl;
 printGrid();


 printScore(); // your score


}



