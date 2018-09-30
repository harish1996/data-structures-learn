#include "include/input.h"

char *readline(FILE *fp)
{
	char *str;
	int ch;
	size_t len = 0;
	size_t size = 10;

	str = malloc(sizeof(char) * size);
	if (!str)
		return str;
	while (EOF != (ch = fgetc(fp)) && ch != '\n') {
		str[len++] = ch;
		if (len == size) {
			str = realloc(str, sizeof(char) * (size += 16));
			if (!str)
				return str;
		}
	}
	str[len++] = '\0';

	return realloc(str, sizeof(char) * len);
}

enum types{
	INT10=0,
	INT16,
	UINT10,
	UINT16,
	LONG10,
	LONG16,
	ULONG10,
	ULONG16,
	LONGLONG10,
	LONGLONG16,
	ULONGLONG10,
	ULONGLONG16,
	CHAR,
	FLOAT
};

#define STRTOX(lhs,argv,end,base,errno,fn) \
	lhs = fn(argv,end,base);	   \
	if( errno ){ \
		ret = -7; \
		goto conv_fail; \
	} \
	if( *end != '\0' ){ \
		ret = -8;   \
		goto conv_fail; \
	}

void *get_array_commandline( int argc, char *argv[], int size, int type, int start, int end )
{
	void *array;
	int element_size;
	int sizes[FLOAT + 1]={sizeof(int),sizeof(int),sizeof(int),sizeof(int),sizeof(long),sizeof(long),sizeof(long),sizeof(long),sizeof(long long),sizeof(long long),sizoef(long long),sizeof(long long),sizeof(char),sizeof(float)};
	int base=0;
	char *end;
	
	
	if( !argc )
		return -1;
	if( !argv )
		return -2;
	if( !size )
		return 1;
	if( type < INT || type > FLOAT )
		return -3;
	if( start < 0 || start > argc )
		return -4;
	if( end < 0 || end > argc )
		return -5;
	if( ( end - start ) + 1 != size )
		return -6;

	array = malloc( size * sizes[type] );
	
	switch(type){
	case INT10:
		base = 10;
	case INT16:
		if( !base ) base = 16;
		for( int i=0; i<size; i++){
			STRTOX(array[i],argv[start+i],&end,base,errno,strtoq);
		}
		break;
	case UINT10:
		base = 10;
	case UINT16:
		if( !base ) base = 16;
		for( int i=0; i<size; i++){
			STRTOX(array[i],argv[start+i],&end,base,errno,strtouq);
		}
		break;
	case LONG10:
		base = 10;
	case LONG16:
		if( !base ) base = 16;
		for( int i=0; i<size; i++){
			STRTOX(array[i],argv[start+i],&end,base,errno,strtol);
		}
		break;
	case ULONG10:
		base=10;
	case ULONG16:
		if( !base ) base = 16;
		for( int i=0; i<size; i++){
			STRTOX(array[i],argv[start+i],&end,base,errno,strtoul);
		}
		break;
	case LONGLONG10:
		base = 10;
	case LONGLONG16:
		if( !base ) base = 16;
		for( int i=0; i<size; i++){
			STRTOX(array[i],argv[start+i],&end,base,errno,strtoll);
		}
		break;
	case ULONGLONG10:
		base = 10;
	case ULONGLONG16:
		if( !base ) base = 16;
		for( int i=0; i<size; i++){
			STRTOX(array[i],argv[start+i],&end,base,errno,strtoull);
		}
		break;
	case CHAR:
			
			
		      
		
	}

 conv_fail:
	free(array);
	return ret;
	
