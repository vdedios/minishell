#include "minishell.h"

short	is_special_char(char c)
{
	if (c == '$')
		return (1);
	return (0);
}

short	is_space(char c)
{
	if (c == ' ')
		return (1);
	return (0);
}

int		n_special_chars(char *str, int opening, int closing, char quote)
{
	int	i;
	int	n;

	i = opening + 1;
	n = 0;
	while (i < closing)
	{
		if (quote != '\'' && is_special_char(str[i]))
			n++;
		else if (is_space(str[i]))
			n++;
		i++;
	}
	return (n);
}

