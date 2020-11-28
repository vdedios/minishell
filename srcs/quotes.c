#include "minishell.h"

static char	*get_string_between_quotes(char *str, int opening, int closing, char quote)
{
	char	*buff;
	int		i;
	int		j;

	j = 0;
	i = opening + 1;
	if (!(buff = malloc((closing - opening
		+ n_special_chars(str, opening, closing, quote) + 1) * sizeof(char))))
		return (NULL);
	while (i < closing)
	{
		if (quote != '\"' && is_special_char(str[i]))
			buff[j++] = '\\';
		else if (is_space(str[i]))
			buff[j++] = '\\';
		buff[j++] = str[i++];
	}
	buff[j] = '\0';
	return (buff);
}

static char	*find_closing_quote(char *str, char quote, int opening, int *closing)
{
	int 	i;

	i = opening + 1;
	*closing = 0;
	while (str[i])
	{
		if (str[i] == quote)
		{
			*closing += opening + 1;
			return (get_string_between_quotes(str, opening, *closing, quote));
		}
		*closing += 1;
		i++;
	}
	return (NULL);
}

/*
** char	*remove_quotes(char *str) attemps to find first string
** between quotes. If there is a valid quote couple it returns
** string between them (which is returned by find_closing_quote
** function) If there isn't couple quotes, it returns input str.
*/

static char	*remove_quotes(char *str, int *opening, int *closing) 
{
	char 	quote;

	*opening = 0;
	while (str[*opening])
	{
		if (str[*opening] == '\'' || str[*opening] == '\"')
		{
			quote = str[*opening];
			return(find_closing_quote(str, quote, *opening, closing));
		}
		*opening += 1;
	}
	*opening = -1;
	return (str);
}

static char	*join_parsed_str(char *str, char *str_in_quotes,
							char *buff, int opening)
{
	char 	*str_pre_quotes;
	char 	*tmp;
	char 	*tmp2;

	if (opening)
	{
		if (!(str_pre_quotes = malloc((opening + 1) * sizeof(char))))
			return (NULL);
		ft_strlcpy(str_pre_quotes, str, opening + 1);
		tmp = ft_strjoin(buff, str_pre_quotes);
		tmp2 = ft_strjoin(tmp, str_in_quotes);
		free(str_pre_quotes);
		free(tmp);
	}
	else
		tmp2 = ft_strjoin(buff, str_in_quotes);
	free(buff);
	return (tmp2);
}

char		*parse_quotes(char *str)
{
	char	*str_in_quotes;
	char	*buff;
	int		opening;
	int		closing;

	buff = strdup("");
	while(*str)
	{
		if (!(str_in_quotes = remove_quotes(str, &opening, &closing)))
		{
			free (buff);
			return (strdup("error"));
		}
		buff = join_parsed_str(str, str_in_quotes, buff, opening);
		if (str_in_quotes != str)
			free(str_in_quotes);
		if (opening != -1)
			str += (opening + (closing - opening) + 1);
		else
			break;
	}
	return (buff);
}
