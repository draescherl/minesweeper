/*!
  \file utils.c
  \author L.Draescher <draescherl@eisti.eu>
  \date 15/12/2020
  \version 0.1 - first draft
  \brief Utilities
  \remarks None

  This file stores general utility methods
  as well as custom types for the project.

*/

#include "utils.h"



/*!
  \fn void display(char char_c)
  \author L.Draescher <draescherl@eisti.eu>
  \date 19/12/2020
  \version 0.1 - first draft
  \param char_c The character in the toDisplay property of a cell
  \brief Apply fancy display to character using unicode
  \remarks None
*/
void display(char char_c)
{
  switch (char_c) {
  case 'f' : /* Cell has a flag */
    printf(RED " \u2690 " reset "|");
    break;

  case 'h' : /* Cell is hidden */
    printf(" \u23F9 |");
    break;

  case 'b' : /* Cell has a bomb */
    printf(RED " X " reset "|");
    break;

  case 'd' : /* Cell is displayed and has no adjacent mines */
    printf("   |");
    break;

  case '1' :
    printf(GREEN " %c " reset "|", char_c);
    break;

  case '2' :
    printf(CYAN " %c " reset "|", char_c);
    break;

  case '3' :
    printf(BLUE " %c " reset "|", char_c);
    break;

  case '4' :
    printf(YELLOW " %c " reset "|", char_c);
    break;

  case '5' :
  case '6' :
  case '7' :
  case '8' :
    printf(RED " %c " reset "|", char_c);
    break;
  
  default: /* Failsafe */
    printf(" %c |", char_c);
    break;
  }
}

void printMinefield(cell** minefield, dimensions dim_dimensions)
{
  /* Variables */
  int i;
  int j;
  int k;

  /* Line of numbers */
  printf("    ");
  for (i = 0; i < dim_dimensions.width; i++) {
    if (i < 10) printf(" ");
    printf(" %d ", i);
  }

  /* Arrow after x axis */
  printf("   \u2190 x \n");

  /* Separation line */
  printf("    ");
  for (i = 0; i < dim_dimensions.width; i++) printf("+---");
  printf("+\n");

  /* Display minefield */
  for (i = 0; i < dim_dimensions.height; i++) {
    /* Numbers */
    if (i < 10) printf(" ");
    printf(" %d |", i);

    /* Values */
    for (j = 0; j < dim_dimensions.width; j++) display(minefield[j][i].toDisplay);
    printf("\n");

    /* Separation line */
    printf("    ");
    for (k = 0; k < dim_dimensions.width; k++) printf("+---");
    printf("+\n");
  }

  /* Arrow below y axis */
  printf("  \u2191 \n  y \n\n");
}

void initMinefield(cell** minefield, dimensions dim_dimensions)
{
  /* Variables */
  int i;
  int j;

  for (i = 0; i < dim_dimensions.width; i++) {
    /* Create second dimension */
    minefield[i] = malloc(dim_dimensions.height * sizeof(cell));

    /* Kill the program if allocation error */
    if (minefield[i] == NULL) {
      fprintf(stderr, "Memory allocation error.\n");
      exit(MEMORY_ALLOCATION_ERROR);
    }

    /* Init all attributes of all cells */
    for (j = 0; j < dim_dimensions.height; j++) {
      minefield[i][j].hasMine  = false;
      minefield[i][j].isHidden = true;
      minefield[i][j].hasFlag  = false;
      minefield[i][j].surroundingMines = 0;
      minefield[i][j].toDisplay = 'h';
    }
  }
}

int intInput(void)
{
  /* Variables */
  int int_input;
  int int_correct;
  int int_c;

  int_correct = scanf("%d", &int_input);
  if (int_correct == 0) {
    fprintf(stderr, "The value is not an int.\n");
    exit(INT_INPUT_ERROR);
  }

  /* Empty buffer */
  while ( ((int_c = getchar()) != '\n') && (int_c != EOF) ) { }

  return (int_input);
}

int countFlags(cell** minefield, dimensions dim_dimensions)
{
  /* Variables */
  int i;
  int j;
  int int_nFlags;

  int_nFlags = 0;
  for (i = 0; i < dim_dimensions.width; i++) {
    for (j = 0; j < dim_dimensions.height; j++) {
      if (minefield[i][j].hasFlag) int_nFlags++;
    }
  }

  return(int_nFlags);
}