#include <stdio.h>

char *mystrcat(char *s1, const char *s2);

int main()
{
	char a[100] = "abcd", b[60], c[30];
	scanf("%s", b);
	scanf("%s", c);
	mystrcat(a, mystrcat(b, c));
	puts(a);
	return 0;
}

char *mystrcat(char *s1, const char *s2){
	char *p1=s1;
	while (*p1) *p1++;
	while (*p1++ = *s2++ );
	return s1;
}