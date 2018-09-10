/**
 * @file file_extra.h
 * @brief Provides ready-made function(s) for opt repeated file operations 
 *
 * @author Harish
 */

#ifndef __FILE_EXTRA_H
#define __FILE_EXTRA_H

#include <sys/stat.h> 	/* for stats for files */
#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>	/* for FILE */
#include <stdlib.h>	/* for malloc() */

/**
 * @brief Copies the entire file contents into a file
 * 
 * If the file is very big, this may fail due to lack of memory. Use only when
 * it is certain that the file size is small
 *
 * @param filename Filename of the file
 * @return Buffer containing contents of the file
 * 	NULL in case of failure
 */ 
char* get_file_contents(char* filename);


#endif
