#include "minishell.h"

static short	is_escapable_char(char c, short parse_mode)
{
	if (parse_mode == 0 && (c == '\'' || c == '\"'))
		return (1);
	else if (parse_mode == 1
			&& (c == ' ' || c == '\t' || c == '|' || c == ';' ||
			c == '$' || c == '\\' || is_alpha(c) ||
			c == '&'))
		return (1);
	else if (parse_mode == 2 &&  c == '\\')
		return (1);
	return (0);
}

static short	is_between_delimiters(char *str, char *ref, int parse_mode)
{
	if (parse_mode && str != ref)
		if ((*(str - 1) == '[' && *(str + 1) == ']') ||
			(*(str - 1) == '{' && *(str + 1) == '}') ||
			(*(str - 1) == '.' && *(str + 1) == '.'))
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
	//free(buff); No se debe de liberar aqui
	free(tmp);
	return (tmp2);
}

char			*parse_backslash(char *str, short parse_mode)
{
	char	*buff;
	char	*ref;
	char	*backslash;

	buff = ft_strdup(str);
	ref = str;
	if (*str == '\\' && !*(str + 1))
	{
		*buff = '\0';
		str++;
	}
	while (*str)
	{
		if (!(backslash = ft_strchr(str, '\\')))
			break;
		if (is_escapable_char(*(backslash + 1), parse_mode) ||
			is_between_delimiters(backslash, ref, parse_mode))
			buff = remove_backslash(buff, backslash);
		str = backslash + 1;
		if (*str == '\\')
			str++;
	}
	return (buff);
}
