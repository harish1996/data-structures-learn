/********************************
 *
 *	HELPER FOR FILE RELATED 
 *	FUNCTIONS
 *
 ********************************/
#include "include/file_extra.h"

char* get_file_contents( char *filename )
{
	FILE *fp = fopen(filename,"r");
	struct stat file_info;
	char *contents;

	if( !fp ){
		return NULL;
	}
	if( stat( filename , &file_info ) ){
		return NULL;
	}

	contents = (char*)malloc((file_info.st_size+1)*sizeof(char));
	
	if( fread( contents , 1 , file_info.st_size , fp ) != file_info.st_size ){
		printf(" Couldnt read contents\n");
		return NULL;
	}
	contents[file_info.st_size] = 0;

	return contents;
}

