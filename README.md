# Robot Vacuum (HW5 ALT)

This C++ program simulates a robot vacuum that cleans a grid containing garbage and obstacles. The robot moves around the grid, cleaning up garbage while avoiding obstacles.

## Grid Initialization

- The grid is represented as a 2D array of characters.
- The grid size is defined by `numrows` and `numcols`, with default values of 20 each.
- Garbage is represented by the character `'.'`, and obstacles are represented by the character `'*'`.
- The grid is initialized randomly, with 25% of cells containing obstacles and the rest containing garbage.

## Robot Movement

- The robot's initial position is at `(0, 0)` (top-left corner).
- The robot can move one step in any direction (up, down, left, right) as long as it does not move out of bounds or more than one step at a time.
- The robot cleans up garbage by moving to a cell containing garbage and changing it to an empty cell.

## Functions Implemented

- **initGrid()**: Initializes the grid with garbage and obstacles.
- **printGrid()**: Prints the current state of the grid.
- **moveTo(int r, int c)**: Moves the robot to the specified row and column position and cleans up any garbage at that location.
- **printScore()**: Calculates and prints the final score based on the number of moves made, garbage collected, and obstacles avoided.
- **sweepGrid()**: Implements the robot's cleaning algorithm by iteratively moving to neighboring cells and cleaning up garbage.

## Main Function

- The `main()` function initializes the grid, simulates the robot's cleaning process, prints the cleaned grid, and calculates the final score.

## Testing and Scoring

- The program keeps track of the number of moves made, garbage collected, and obstacles avoided.
- The final score is calculated based on the efficiency of cleaning and obstacles avoided.
- Scores are normalized and provided as a percentage out of 100.

Feel free to explore and modify the code as needed.
