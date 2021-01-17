#include "minishell.h"

static short	check_special_char(char c, short parse_mode)
{
	if (parse_mode == 0 && (c == '\'' || c == '\"'))
		return (1);
	else if (parse_mode == 1
			&& (c == ' ' || c == '|' || c == ';' ||
			c == '$' || c == '\\' || is_alpha(c) ||
			c == '&'))
		return (1);
	else if (parse_mode == 2 &&  c == '\\')
		return (1);
	return (0);
}

static char		*remove_backslash(char *buff, char *backslash)
{
	char	*tmp;
	char	*tmp2;
	int		len;
	int		len_left;

	len = ft_strlen(buff);
	len_left = ft_strlen(backslash);
	backslash++;
	if (!(tmp = malloc((len - len_left + 1) * sizeof(char))))
		return (NULL);
	ft_strlcpy(tmp, buff, len - len_left + 1);
	tmp2 = ft_strjoin(tmp, backslash);
	free(buff);
	free(tmp);
	return (tmp2);
}

/*
static short	end_open_backslashes(char *str)
{
	int n;

	n = 0;
	while (*str)
	{
		if (*str != '\\')
			return (0);
		str++;
		n++;
	}
	return (n % 2);
}

** parse_mode determines which chars should be escaped.
*/

char			*parse_backslash(char *str, short parse_mode)
{
	char	*buff;
	char	*backslash;

	buff = ft_strdup(str);
	if (*str == '\\' && !*(str + 1))
	{
		*buff = '\0';
		str++;
	}
	while (*str)
	{
		if (!(backslash = ft_strchr(str, '\\')))
			break;
		/*
		if (!parse_mode && end_open_backslashes(backslash))
		{
			free(buff);
			return(ft_strdup("error"));
		}
		*/
		if (check_special_char(*(backslash + 1), parse_mode))
			buff = remove_backslash(buff, backslash);
		str = backslash + 1;
		if (*str == '\\')
			str++;
	}
	return (buff);
}