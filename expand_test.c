#include <stdio.h>
#include <stdlib.h>

#define SINGLE_Q 1
#define DOUBLE_Q 2
#define DOLLARS 4
/*UN DEBUT PREMOETTEUR, A CHECKER AVEC LUC*/

// char	*__is_expandable(char *str)
// {
// 	static int quote_flag1 = 0;
// 	static int quote_flag2 = 0;

// 	if (*str == '\0')
// 		return (NULL);


// 	quote_flag1 ^= (((*str == '\'') * 1) + ((*str == '"') * -1));
// 	printf("quote_flag1 = %d and *str = %c\n", quote_flag1, *str);
// 	//quote_flag2 = (quote_flag1 == 1 && quote_flag1 == -2);
// 	if (*str == '$' && *(str + 1) != ' ' && !quote_flag2)
// 	{
// 		return (str);
// 	}
// 	return (__is_expandable(str + 1));
// }

char	*__is_expandable(char *str)
{
	static char quote_flag1 = 0;

	if (*str == '\0')
		return (NULL);
	if (quote_flag1 == 0 || quote_flag1 == '\'')
		quote_flag1 ^= (*str == '\'') * '\'';
	if (quote_flag1 == 0 || quote_flag1 == '\"')
		quote_flag1 ^= (*str == '\"') * '\"';
	if (*str == '$' && *(str + 1) != ' ' && *(str + 1) && quote_flag1 != '\'')
		return (str);
	return (__is_expandable(str + 1));
}

int main(void)
{
	// char *str = "kldsjglkd\"esn\'ffld$ft\'d\"fj\'$vb\'jdkdgfdgheriokg$";
	// while ((str = __is_expandable(str)))
	// {
	// 	printf("%s\n", str);
	// 	str++;
	// }
	char *str = "\'\" ;";
	printf("%s\n", str);
	return (0);
}


// single = 0100;
// double = 1000;

// quoteflag = 0000;

// if !quoteflag
// 	quoteflag |= single

