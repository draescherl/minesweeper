/*!
  \file main.c
  \author L.Draescher <draescherl@eisti.eu>
  \date 15/12/2020
  \version 0.1 - first draft
  \brief Main project file
  \remarks None

  Main file for the creation of a game
  of minesweeper.

*/

/* Additional librairies */
#include <time.h>
#include "utils.h"
#include "minesweeper.h"

/*!
  \fn dimensions createMinefield(cell*** minefield)
  \author L.Draescher <draescherl@eisti.eu>
  \date 19/12/2020
  \version 0.1 - first draft
  \param minefield The minefield to create
  \return The dimensions of the minefield
  \brief Prompts the user for the dimensions of the minefield, allocates 
  the right amount of memory and returns the dimensions
  \remarks None
*/
dimensions createMinefield(cell*** minefield)
{
  /* Variables */
  dimensions dim_res;

  /* Prompt for width of the minefield */
  do {
    printf("Width of the minefield (>0)  : ");
    dim_res.width = intInput();
  } while (dim_res.width <= 0);
  
  *minefield = malloc(dim_res.width * sizeof(cell*));
  if (*minefield == NULL) {
    fprintf(stderr, "Memory allocation error.\n");
    exit(MEMORY_ALLOCATION_ERROR);
  }

  /* Prompt for height of the minefield */
  do {
    printf("Height of the minefield (>0) : ");
    dim_res.height = intInput();
  } while (dim_res.height <= 0);
  initMinefield(*minefield, dim_res);

  return(dim_res);
}



/*!
  \fn int initMines(cell** minefield, dimensions dim_dimensions)
  \author L.Draescher <draescherl@eisti.eu>
  \date 19/12/2020
  \version 0.1 - first draft
  \param minefield The minefield
  \param dim_dimensions The dimensions of the minefield
  \return The amount of mines the user wants
  \brief Prompts the user for the amount of mines, places
  them and returns the number
  \remarks None
*/
int initMines(cell** minefield, dimensions dim_dimensions)
{
  /* Variables */
  int int_mines;

  do {
    printf("Amount of mines (between 1 and %d) : ", dim_dimensions.height * dim_dimensions.width);
    int_mines = intInput();
  } while ( (int_mines <= 0) || (int_mines > dim_dimensions.height * dim_dimensions.width) );
  placeMines(minefield, dim_dimensions, int_mines);
  initSurroundingMines(minefield, dim_dimensions);

  return(int_mines);
}



/*!
  \fn void helpMessage(void)
  \author L.Draescher <draescherl@eisti.eu>
  \date 20/12/2020
  \version 0.1 - first draft
  \brief Prints a help message in the terminal
  \remarks None
*/
void helpMessage(void)
{
  /* Variables */
  int int_c;

  clrscr();
  printf("---------- Minesweeper ----------\n");
  printf("Goal : \n\n");

  printf("\tFind all the mines in the minefield.\n");

  printf("\nHow to play : \n\n");

  printf("\tAt the start of the game, you will be asked to enter the dimensions of the grid as well as the number of mines you want.\n");
  printf("\tMake sure to input correct values (the range will be given each time) otherwise the game will keep asking.\n");
  printf("\tEach round, you will be asked to enter coordinates.\n");
  printf("\t\tThe x coordinate is read on top of the minefield.\n");
  printf("\t\tThe y coordinate is read to the left of the minefield.\n");
  printf("\t\tBeware : once you have entered a coordinate, you can't go back, so be careful.\n");
  printf("\tOnce you have entered the coordinates, the game will ask you if you want to reveal or mark the selected cell.\n");
  printf("\t\tTo reveal, enter 1. Revealing will show you the amount of adjacent mines.\n");
  printf("\t\tTo mark, enter 2. Marking will put a flag on the cell.\n");
  printf("\t\t\tNote : marking is a toggle, this means that if you want to unmark a cell, all you need to do is \"mark\" it again.\n");
  
  printf("\nEnding : \n\n");

  printf("\tThe game ends if you click on a mine, or if you manage to find all the mines.\n");
  
  printf("\nGood luck !\n");
  
  printf("\nPress any key to start.");

  /* Empty buffer just in case */
  while ( ((int_c = getchar()) != '\n') && (int_c != EOF) ) { }
}



/*!
  \fn int playGameRound(cell** minefield, dimensions dim_dimensions, int int_mines)
  \author L.Draescher <draescherl@eisti.eu>
  \date 20/12/2020
  \version 0.1 - first draft
  \param minefield The minefield
  \param dim_dimensions The dimensions of the minefield
  \param int_mines The amount of mines in the minefield
  \return 1 if the user has won, 0 otherwise
  \brief Plays the game
  \remarks None
*/
int playGameRound(cell** minefield, dimensions dim_dimensions, int int_mines)
{
  /* Variables */
  int int_x;
  int int_y;
  int int_action;
  int int_hasNotClickedOnMine;
  int int_hasWon;
  int int_res;

  /* Keep playing until the game has ended */
  int_hasNotClickedOnMine = 1;
  do {
    printMinefield(minefield, dim_dimensions);
    printf("Flags : %d/%d\n", countFlags(minefield, dim_dimensions), int_mines);

    /* Prevent user from clicking on a cell that has already been revealed */
    do {
      /* Display error message */
      if (int_hasNotClickedOnMine == -1) printf("This cell can't be clicked.\n");

      /* Keep asking until x coordinate is in the minefield */
      do {
        printf("x coordinate (between 0 and %d) : ", dim_dimensions.width-1);
        int_x = intInput();
      } while ( (int_x < 0) || (int_x > dim_dimensions.width-1) );

      /* Keep asking until y coordinate is in the minefield */
      do {
        printf("y coordinate (between 0 and %d) : ", dim_dimensions.height-1);
        int_y = intInput();
      } while ( (int_y < 0) || (int_y > dim_dimensions.height-1) );

      /* Keep asking until user has entered a valid action */
      do {
        printf("Do you want to reveal (1) or mark (2) ? ");
        int_action = intInput();
      } while ( (int_action < 1) || (int_action > 2) );
      
      int_hasNotClickedOnMine = click(minefield, dim_dimensions, int_x, int_y, int_action);
    } while (int_hasNotClickedOnMine == -1);
    
    int_hasWon = userHasWon(minefield, dim_dimensions);
    clrscr();
  } while ( (int_hasNotClickedOnMine == 1) && (int_hasWon == 0) );

  int_res = (int_hasWon == 1) ? 1:0;
  return(int_res);
}



/*!
  \fn void winScreen(cell** minefield, dimensions dim_dimensions)
  \author L.Draescher <draescherl@eisti.eu>
  \date 20/12/2020
  \version 0.1 - first draft
  \param minefield The minefield
  \param dim_dimensions The dimensions of the minefield
  \brief Display win screen
  \remarks None
*/
void winScreen(cell** minefield, dimensions dim_dimensions)
{
  printMinefield(minefield, dim_dimensions);
  printf("Congratulations, you have found all the mines ! \n");
}



/*!
  \fn void loseScreen(cell** minefield, dimensions dim_dimensions)
  \author L.Draescher <draescherl@eisti.eu>
  \date 20/12/2020
  \version 0.1 - first draft
  \param minefield The minefield
  \param dim_dimensions The dimensions of the minefield
  \brief Display lose screen
  \remarks None
*/
void loseScreen(cell** minefield, dimensions dim_dimensions)
{
  /* Variables */
  int i;
  int j;

  /* Change toDisplay in order to show all the bomb locations */
  for (i = 0; i < dim_dimensions.width; i++) {
    for (j = 0; j < dim_dimensions.height; j++) {
      if (minefield[i][j].hasMine) minefield[i][j].toDisplay = 'b';
    }
  }

  printMinefield(minefield, dim_dimensions);
  printf("BOOM ! You just stepped on a mine.\n");
}



/*!
  \fn int main(int argc, char** argv)
  \author L.Draescher <draescherl@eisti.eu>
  \date 15/12/2020
  \version 0.1 - first draft
  \param argc Number of console arguments
  \param argv Console parameters
  \return 0 on success
  \brief Main program
  \remarks None
*/
int main(int argc, char** argv) {
  /* Generate seed */
  srand(time(NULL));

  /* Variables */
  cell** minefield;
  dimensions dim_dimensions;
  int int_mines;
  int i;
  int int_end;

  /* Help message */
  helpMessage();
  clrscr();

  /* Start game */
  dim_dimensions = createMinefield(&minefield);
  int_mines = initMines(minefield, dim_dimensions);
  clrscr();

  /* Play */
  int_end = playGameRound(minefield, dim_dimensions, int_mines);

  /* End screens */
  if (int_end == 1) {
    winScreen(minefield, dim_dimensions);
  } else {
    loseScreen(minefield, dim_dimensions);
  }

  /* Free memory */
  for (i = 0; i < dim_dimensions.width; i++) free(minefield[i]);
  free(minefield);

  return(0);
}