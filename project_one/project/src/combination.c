#include "header.h"

char *str_combination(char *dest)
{
	const char *s1 = "hello";
	const char *s2 = "akaedu";
	int i, j, k;

	i = j = k = 0;

	while(s1[i] && s2[j]){
		if(s1[i] < s2[j])
			dest[k++] = s1[i++];
		else
			dest[k++] = s2[j++];
	}

	while(s1[i])
		dest[k++] = s1[i++];
	while(s2[j])
		dest[k++] = s2[j++];

	dest[k] = '\0';
	return dest;
}
