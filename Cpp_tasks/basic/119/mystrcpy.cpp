/**
 * mystrcpy
 */
#include <stdio.h>

char *mystrcpy(char *s1, const char *s2);

int main()
{
	char a[30], b[30], c[30];
	gets(c);
	mystrcpy(a, mystrcpy(b, c));
	puts(a);
	return 0;
}
char *mystrcpy(char *s1, const char *s2)
{
	for (int i = 0; *(s2+i); ++i)
	{
		*(s1+i) = *(s2+i) ;
	}
	return s1;
}