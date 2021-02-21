/*!
  \file minesweeper.h
  \author L.Draescher <draescherl@eisti.eu>
  \date 15/12/2020
  \version 0.1 - first draft
  \brief Header file for minesweeper.c
  \remarks None
*/

#ifndef _MINESWEEPER_H_
#define _MINESWEEPER_H_

/* Additional librairies */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "utils.h"

/* Global variables */


/* Function prototypes */
/*!
  \fn void placeMines(cell** minefield, dimensions dim_dimensions, int int_numOfMines)
  \author L.Draescher <draescherl@eisti.eu>
  \date 17/12/2020
  \version 0.1 - first draft
  \param minefield The minefield
  \param dim_dimensions The dimensions of the minefield
  \param int_numOfMines Number of mines to place
  \brief Randomly places a given amount of mines 
  \remarks None
*/
void placeMines(cell** minefield, dimensions dim_dimensions, int int_numOfMines);

/*!
  \fn void initSurroundingMines(cell** minefield, dimensions dim_dimensions)
  \author L.Draescher <draescherl@eisti.eu>
  \date 17/12/2020
  \version 0.1 - first draft
  \param minefield The minefield
  \param dim_dimensions The dimensions of the minefield
  \brief Counts the amount of surrounding mines of each cell
  \remarks None
*/
void initSurroundingMines(cell** minefield, dimensions dim_dimensions);

/*!
  \fn void reveal(cell** minefield, dimensions dim_dimensions, int int_x, int int_y)
  \author L.Draescher <draescherl@eisti.eu>
  \date 18/12/2020
  \version 0.1 - first draft
  \param minefield The minefield
  \param dim_dimensions The dimensions of the minefield
  \param int_x x coordinate
  \param int_y y coordinate
  \brief Reveal necessary cells
  \remarks None
*/
void reveal(cell** minefield, dimensions dim_dimensions, int int_x, int int_y);

/*!
  \fn int click(cell** minefield, dimensions dim_dimensions, int int_x, int int_y, int int_action)
  \author L.Draescher <draescherl@eisti.eu>
  \date 18/12/2020
  \version 0.1 - first draft
  \param minefield The minefield
  \param dim_dimensions The dimensions of the minefield
  \param int_x x coordinate to click
  \param int_y y coordinate to click
  \param int_action reveal or mark cell
  \return 0 if the user clicks on a mine, -1 if the cell is not clickable, 1 otherwise
  \brief Perform a user 'click'
  \remarks action = 1 => reveal, action = 2 => mark
*/
int click(cell** minefield, dimensions dim_dimensions, int int_x, int int_y, int int_action);

/*!
  \fn int userHasWon(cell** minefield, dimensions dim_dimensions)
  \author L.Draescher <draescherl@eisti.eu>
  \date 18/12/2020
  \version 0.1 - first draft
  \param minefield The minefield
  \param dim_dimensions The dimensions of the minefield
  \return 1 if the user has won, 0 otherwise
  \brief Checks if the user has won
  \remarks None
*/
int userHasWon(cell** minefield, dimensions dim_dimensions);


#endif