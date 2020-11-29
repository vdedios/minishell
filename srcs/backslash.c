#include "minishell.h"

static short	check_special_char(char c)
{
	if (c == '\''|| c == '\"')
		return (1);
	return (0);
}

static short	check_special_char_pre(char c)
{
	if (c == '\\')
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
	if (*(backslash + 1) == '\\' && *(backslash + 2))
		backslash += 2;
	else
		backslash++;
	if (!(tmp = malloc((len - len_left + 1) * sizeof(char))))
		return (NULL);
	ft_strlcpy(tmp, buff, len - len_left + 1);
	tmp2 = ft_strjoin(tmp, backslash);
	free(buff);
	free(tmp);
	return (tmp2);
}

char			*parse_backslash(char *str, short previous)
{
	char	*buff;
	char	*backslash;

	buff = ft_strdup(str);
	while (*str)
	{
		if (!(backslash = ft_strchr(str, '\\')))
			break;
		if (previous)
		{
			if (check_special_char_pre(*(backslash + 1)))
				buff = remove_backslash(buff, backslash);
		}
		else
		{
			if (check_special_char(*(backslash + 1)))
				buff = remove_backslash(buff, backslash);
		}
		str = backslash + 1;
	}
	return (buff);
}
