/*!
  \file minesweeper.c
  \author L.Draescher <draescherl@eisti.eu>
  \date 15/12/2020
  \version 0.1 - first draft
  \brief Minesweeper
  \remarks None

  File to store all the methods to implement
  a game of minesweeper.

*/

#include "minesweeper.h"



/*!
  \fn int cellHasMine(cell** minefield, dimensions dim_dimensions, int int_x, int int_y)
  \author L.Draescher <draescherl@eisti.eu>
  \date 17/12/2020
  \version 0.1 - first draft
  \param minefield The minefield
  \param dim_dimensions The dimensions of the minefield
  \param int_x x coordinate
  \param int_y y coordinate
  \return 1 if there is a mine in the cell, 0 otherwise
  \brief Checks if there is a mine in a given cell
  \remarks None
*/
int cellHasMine(cell** minefield, dimensions dim_dimensions, int int_x, int int_y)
{
  /* If x coordinate is invalid */
  if ( (int_x < 0) || (int_x > dim_dimensions.width-1) ) {
    return(0);
  }

  /* If y coordinate is invalid */
  if ( (int_y < 0) || (int_y > dim_dimensions.width-1) ) {
    return(0);
  }

  return(minefield[int_x][int_y].hasMine);
}

/*!
  \fn int surroundingMines(cell** minefield, dimensions dim_dimensions, int int_x, int int_y)
  \author L.Draescher <draescherl@eisti.eu>
  \date 17/12/2020
  \version 0.1 - first draft
  \param minefield The minefield
  \param dim_dimensions The dimensions of the minefield
  \param int_x x coordinate
  \param int_y y coordinate
  \return Amount of surrounding mines
  \brief Counts the amount of surrounding mines
  \remarks None
*/
int surroundingMines(cell** minefield, dimensions dim_dimensions, int int_x, int int_y)
{
  /* Variables */
  int north;
  int northEast;
  int east;
  int southEast;
  int south;
  int southWest;
  int west;
  int northWest;
  int mines;

  /* Count the amount of surrounding mines */
  north     = cellHasMine(minefield, dim_dimensions, int_x,   int_y-1);
  northEast = cellHasMine(minefield, dim_dimensions, int_x+1, int_y-1);
  east      = cellHasMine(minefield, dim_dimensions, int_x+1, int_y);
  southEast = cellHasMine(minefield, dim_dimensions, int_x+1, int_y+1);
  south     = cellHasMine(minefield, dim_dimensions, int_x,   int_y+1);
  southWest = cellHasMine(minefield, dim_dimensions, int_x-1, int_y+1);
  west      = cellHasMine(minefield, dim_dimensions, int_x-1, int_y);
  northWest = cellHasMine(minefield, dim_dimensions, int_x-1, int_y-1);
  mines =   north
          + northEast
          + east
          + southEast
          + south
          + southWest
          + west
          + northWest;

  return(mines);
}

void placeMines(cell** minefield, dimensions dim_dimensions, int int_numOfMines)
{
  /* Variables */
  int i;
  int int_randX;
  int int_randY;

  for (i = 0; i < int_numOfMines; i++) {
    /* Prevent two mines from being placed in the same cell */
    do {
      int_randX = rand() % dim_dimensions.width;
      int_randY = rand() % dim_dimensions.height;
    } while (minefield[int_randX][int_randY].hasMine);

    /* Place mine */
    minefield[int_randX][int_randY].hasMine = true;

    // For debug purposes :
    // minefield[int_randX][int_randY].toDisplay = 'X';
  }
}

void initSurroundingMines(cell** minefield, dimensions dim_dimensions)
{
  /* Variables */
  int i;
  int j;
  int int_mines;

  for (i = 0; i < dim_dimensions.width; i++) {
    for (j = 0; j < dim_dimensions.height; j++) {
      int_mines = surroundingMines(minefield, dim_dimensions, i, j);
      if (int_mines > 0) {
        minefield[i][j].surroundingMines = int_mines;

        // For debug purposes :
        // if (minefield[i][j].hasMine == false) minefield[i][j].toDisplay = int_mines + '0';
      }
    }
  }
}

void reveal(cell** minefield, dimensions dim_dimensions, int int_x, int int_y)
{
  /* Variables */
  int int_surroundingMines;
  int i;
  int j;
  int int_newX;
  int int_newY;

  /* Stop if a cell has a mine on it (theoretically
  this should never happen) */
  if (minefield[int_x][int_y].hasMine == false) {
    /* Save the number of surrounding mines */
    int_surroundingMines = minefield[int_x][int_y].surroundingMines;

    /* Remove the hidden attribute of the cell */
    minefield[int_x][int_y].isHidden = false;

    /* Remove the flag if there is one */
    minefield[int_x][int_y].hasFlag = false;

    /* Update display */
    minefield[int_x][int_y].toDisplay = (int_surroundingMines == 0) ? 'd' : int_surroundingMines + '0';
        
    /* Stop the recursion if the cell has at least one mine around it */
    if (int_surroundingMines == 0) {
      /* The two for loops are to test all directions around the current cell */
      for (i = -1; i <= 1; i++) {
        for (j = -1; j <= 1; j++) {
          /* Save new coordinates in variables */
          int_newX = int_x + i;
          int_newY = int_y + j;

          /* First line : prevent unnecessary computation 
          (i and j = 0 means we are on the original cell) 
          Second and third lines : ignore outside of the minefield */
          if ( 
            ((i != 0) || (j != 0)) &&
            (int_newX >= 0) && (int_newX < dim_dimensions.width) && 
            (int_newY >= 0) && (int_newY < dim_dimensions.height)
          ) {
            /* If the new cell is hidden, recursively call
            the function */
            if (minefield[int_newX][int_newY].isHidden) {
              reveal(minefield, dim_dimensions, int_newX, int_newY);
            }
          }
        }
      }
    }
  }
}

int click(cell** minefield, dimensions dim_dimensions, int int_x, int int_y, int int_action)
{
  /* Cell is already revealed */
  if (minefield[int_x][int_y].isHidden == false) return(-1);

  /* If user marks the cell */
  if (int_action == 2) {
    /* Create a toggle for unmarking/marking a cell */
    if (minefield[int_x][int_y].hasFlag) {
      minefield[int_x][int_y].hasFlag   = false;
      minefield[int_x][int_y].toDisplay = 'h';
    } else {
      minefield[int_x][int_y].hasFlag   = true;
      minefield[int_x][int_y].toDisplay = 'f';
    }
    return(1);
  }

  /* If we arrive here, it means the coordinates are valid and the user wants
  to reveal the clicked cell */
  
  if (minefield[int_x][int_y].hasMine) {
    /* User clicked on a mine */
    minefield[int_x][int_y].toDisplay = 'b';
    return(0);
  } else {
    /* User didn't click on a mine */
    reveal(minefield, dim_dimensions, int_x, int_y);
    return(1);
  }
}

int userHasWon(cell** minefield, dimensions dim_dimensions)
{
  /* Variables */
  int i;
  int j;
  int int_res;
  int int_allMinesHaveFlags;
  int int_thereAreOnlyMinesLeft;
  int int_nMines;
  int int_nFlags;
  int int_nValidFlags;
  cell cell_c;

  int int_nHiddenCellsWithMines;
  int int_nHiddenCellsWithoutMines;


  /* Init values */
  i = 0;
  j = 0;
  int_nFlags = 0;
  int_nMines = 0;
  int_nValidFlags = 0;
  int_nHiddenCellsWithMines = 0;
  int_nHiddenCellsWithoutMines = 0;

  /* Go through array and count */
  for (i = 0; i < dim_dimensions.width; i++) {
    for (j = 0; j < dim_dimensions.height; j++) {
      cell_c = minefield[i][j];

      if (cell_c.isHidden && cell_c.hasMine && (cell_c.hasFlag == false)) {
        int_nHiddenCellsWithMines++;
      }

      if (cell_c.isHidden && (cell_c.hasMine == false)) {
        int_nHiddenCellsWithoutMines++;
      }

      if (cell_c.hasFlag) int_nFlags++;
      if (cell_c.hasMine) int_nMines++;
      if (cell_c.hasFlag && cell_c.hasMine) int_nValidFlags++;
    }
  }

  /* This checks if all the cells still hidden have mines underneath them 
  AND all the flags are correctly placed. If so, the user has won */
  int_thereAreOnlyMinesLeft = (
    ((int_nHiddenCellsWithMines + int_nValidFlags) == int_nMines) &&
    (int_nHiddenCellsWithoutMines == 0) &&
    (int_nValidFlags == int_nFlags)
  ) ? 1:0;
  
  /* User has won if all the mines have flags on top AND 
  the amount of flags is equal to the amount of mines */
  int_allMinesHaveFlags = (
    (int_nFlags == int_nMines) && 
    (int_nValidFlags == int_nFlags)
  ) ? 1:0;

  /* Check if user has won by either method */
  int_res = (
    (int_allMinesHaveFlags == 1) ||
    (int_thereAreOnlyMinesLeft == 1)
  ) ? 1:0;

  return(int_res);
}