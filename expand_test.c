#include <stdio.h>
#include <stdlib.h>

#define SINGLE_Q 1
#define DOUBLE_Q 2
#define DOLLARS 4
/*UN DEBUT PREMOETTEUR, A CHECKER AVEC LUC*/

char	*__is_expandable(char *str)
{
	static int quote_flag1 = 0;
	static int quote_flag2 = 0;

	if (*str == '\0')
		return (NULL);
	quote_flag1 ^= (((*str == '\'') * 1) + ((*str == '"') * -1));
	quote_flag2 = (quote_flag1 == 1);
	if (*str == '&' && *(str + 1) != ' ' && !quote_flag2)
		return (str);
	return (__is_expandable(str + 1));
}
	//printf("quote_flag = %d and *str = %c\n", quote_flag, *str);

int main(void)
{
	char *str = "kldsjglkd\'test\'dfj&vbjdk";
	printf("%s\n", __is_expandable(str));
	return (0);
}