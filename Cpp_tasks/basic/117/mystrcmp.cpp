#include <stdio.h>

int mystrcmp(const char *s1, const char *s2)
{
    for(;*s1==*s2;++s1,++s2)
        if(*s1=='\0')
            return(0);
    return((*s1<*s2)?-1:+1);
}

int main()
{
	char s1[30], s2[30];
	scanf("%s", s1);
	scanf("%s", s2);
	if (mystrcmp(s1, s2) > 0)
	{
		printf("%s > %s\n", s1, s2);
	}
	if (mystrcmp(s1, s2) == 0)
	{
		printf("%s == %s\n", s1, s2);
	}
	if (mystrcmp(s1, s2) < 0)
	{
		printf("%s < %s\n", s1, s2);
	}
	return 0;
}
