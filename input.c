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


