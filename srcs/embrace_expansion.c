#include "minishell.h"

static int      count_chars(char *str, char character)
{
    int l;
    
    l = 0;
    while (*str)
    {
        if (*str == character)
            l++;
        str++;
    }
    return (l);
}

static short    is_limit_character(char character)
{
    if ( character == '\'' ||
            character == '\"' ||
            character == '\\' ||
            character == ',' ||
            character == '[' ||
            character == ']' ||
            character == '$' ||
            character == ' ' ||
            character == '\0')
        return (1);
    return (0);
}

static char		*set_opening_braces(char *str)
{
	char	*buff;
	int     i;
	int     j;

	i = 0;
	j = 0;
	if (!(buff = malloc((ft_strlen(str) + count_chars(str, '$') + 1) * sizeof(char))))
		return (NULL);
	while(str[j])
	{
		if (str[j] &&
        (j - 1 >= 0 && str[j - 1] == '$') &&
        ((j - 2 < 0) || ((j - 2 >= 0) && str[j - 2] != '\\')))
			buff[i++] = '{';
		buff[i++] = str[j++];
	}
    buff[i] = '\0';
    return (buff);
}

static char		*set_closing_braces(char *str)
{
    short   is_open_brace;
	char	*buff;
	int     i;

	i = 0;
    is_open_brace = 0;
	if (!(buff = malloc((ft_strlen(str) + count_chars(str, '{') + 2) * sizeof(char))))
		return (NULL);
	while(*str)
	{
		if (*str == '{')
            is_open_brace = 1;
		buff[i++] = *str;
        if (is_open_brace && is_limit_character(*(str + 1)))
        {
			buff[i++] = '}';
            is_open_brace = 0;
        }
		str++;
	}
    buff[i] = '\0';
    return (buff);
}

char			*embrace_expansion(char *str)
{
	char	*buff;
    char    *tmp;

	tmp = set_opening_braces(str);
	buff = set_closing_braces(tmp);
    free(tmp);
	return (buff);
}