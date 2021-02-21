/*!
  \file utils.h
  \author L.Draescher <draescherl@eisti.eu>
  \date 15/12/2020
  \version 0.1 - first draft
  \brief Header file for utils.c
  \remarks None
*/

#ifndef _UTILS_H_
#define _UTILS_H_

/* Additional librairies */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

/* Global variables */
/*! Memory allocation error code */
#define MEMORY_ALLOCATION_ERROR -1
/*! Int input error code */
#define INT_INPUT_ERROR -2

/*! Clear screen macro */
#define clrscr() printf("\e[1;1H\e[2J")

/*! ANSI reset colour */
#define reset "\e[0m"
/*! ANSI red colour */
#define RED "\e[0;31m"
/*! ANSI green colour */
#define GREEN "\e[0;32m"
/*! ANSI yellow colour */
#define YELLOW "\e[0;33m"
/*! ANSI blue colour */
#define BLUE "\e[0;34m"
/*! ANSI cyan colour */
#define CYAN "\e[0;36m"


/* Custom types */
/*! Create a boolean type in C */
typedef enum{
  false = 0,   /*!< False is 0 */
  true = 1     /*!< True is 1 so I can do if(true) ... */
} boolean;

/*! Custom cell type for the game of minesweeper */
typedef struct{
  boolean hasMine;        /*!< true if cell has a mine on it */
  boolean isHidden;       /*!< true until user clicks on it */
  boolean hasFlag;        /*!< false until user puts a flag on it */
  int surroundingMines;   /*!< Contains the amount of surrounding mines */
  char toDisplay;         /*!< Contains the text to display on screen */
} cell;

/*! Type to store dimensions */
typedef struct {
  int width;    /*!< width of the minefield */
  int height;   /*!< height of the minefield */
} dimensions;


/* Function prototypes */
/*!
  \fn void printMinefield(cell** minefield, dimensions dim_dimensions)
  \author L.Draescher <draescherl@eisti.eu>
  \date 17/12/2020
  \version 0.1 - first draft
  \param minefield The minefield to print
  \param dim_dimensions The dimensions of the minefield
  \brief Prints the minefield to the terminal
  \remarks None
*/
void printMinefield(cell** minefield, dimensions dim_dimensions);

/*!
  \fn void initMinefield(cell** minefield, dimensions dim_dimensions)
  \author L.Draescher <draescherl@eisti.eu>
  \date 15/12/2020
  \version 0.1 - first draft
  \param minefield The minefield to init
  \param dim_dimensions The dimensions of the minefield
  \brief Creates a minefield and initializes all the values
  \remarks The minefield is square
*/
void initMinefield(cell** minefield, dimensions dim_dimensions);

/*!
  \fn int intInput(void)
  \author L.Draescher <draescherl@eisti.eu>
  \date 13/10/2020
  \version 0.1 - first draft
  \return The user's input
  \brief This function makes sure the user inputs an int
  \remarks None
*/
int intInput(void);

/*!
  \fn int countFlags(cell** minefield, dimensions dim_dimensions)
  \author L.Draescher <draescherl@eisti.eu>
  \date 19/12/2020
  \version 0.1 - first draft
  \param minefield The minefield
  \param dim_dimensions The dimensions of the minefield
  \return Number of flags the user has placed
  \brief Counts and returns the amount of flags the user has placed
  \remarks None
*/
int countFlags(cell** minefield, dimensions dim_dimensions);


#endif