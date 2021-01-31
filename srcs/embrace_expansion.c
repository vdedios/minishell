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
            character == '@' ||
            character == ';' ||
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
		if (j - 1 >= 0 && str[j - 1] == '$' &&
            (j - 2 < 0 || str[j - 2] != '\\') &&
            str[j] != '\\' && str[j] != '%')
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
    int     k;

	i = 0;
    k = 0;
    is_open_brace = 0;
	if (!(buff = malloc((ft_strlen(str) + count_chars(str, '{') + 3) * sizeof(char))))
		return (NULL);
	while(str[k])
	{
		if (str[k] == '{' && (k - 1) >= 0 && str[k - 1] == '$')
            is_open_brace = 1;
		buff[i++] = str[k];
        if (is_open_brace && is_limit_character(str[k + 1]))
        {
			buff[i++] = '}';
            is_open_brace = 0;
        }
        k++;
	}
    buff[i] = '\0';
    return (buff);
}

char            *mantain_expansion_spaces(char *str)
{
    int     i;
    short   var_opened;
    char    *buff;

    i = 0;
    var_opened = 0;
	if (!(buff = malloc((ft_strlen(str) + count_chars(str, '$') + 1) * sizeof(char))))
		return (NULL);
    while(*str)
    {
        if (*str == '$' && *(str - 1) != '\\' && !var_opened)
            var_opened = 1;
        buff[i++] = *str;
        if (var_opened && *(str + 1) == '}')
        {
            var_opened = 0;
            buff[i++] = ' ';
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