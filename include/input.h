/**
 * @file input.h 
 * @brief Provides function(s) for oft-repeated input
 * 	releated stuff
 *
 * @author Harish
 */
#ifndef _INPUT_H
#define _INPUT_H

#include <stdio.h>	/* for FILE */
#include <stdlib.h>	/* for malloc() */

/**
 * @brief Reads a line from the given FILE pointer and returns
 * the buffer
 *
 * This function dynamically allocates memory on getting new characters.
 * This function terminates only when it meets a NEXTLINE character.
 * For getting a line from stdin, set fp to `stdin`
 *
 * @param fp File pointer
 * @return Line buffer or NULL in case of allocation failures
 */
char *readline(FILE *fp);

#endif
