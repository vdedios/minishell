#include "minishell.h"

static short	is_whitespace(char c)
{
	if (c == ' ' || c == '\t')
		return (1);
	return (0);
}

static	short	is_delimiter(char input, char delimiter)
{
	if (delimiter == ' ' && is_whitespace(input))
		return (1);
	else if (input == delimiter)
		return (1);
	return (0);
}

static	int		count_args(char	*input, char delimiter)
{
	int		i;
	int		l;

	l = 0;
	i = 0;
	while(input[i])
	{
		if (is_delimiter(input[i], delimiter) && input[i - 1] != '\\')
		{
			l++;
			while (input[i] && !is_delimiter(input[i], delimiter))
				i++;
		}
		i++;
	}
	return (l);
}

static	short	not_escaped(char *str, int i)
{
	int		backslash;

	i--;
	backslash = 0;
	while (i >= 0 && str[i] == '\\')
	{
		i--;
		backslash++;
	}
	if (backslash > 1 && str[i] == ' ')
		backslash = 1;
	return ((backslash + 1) % 2);
}

static char		*set_split_delimiter(char *input, char delimiter)
{
	int	i;

	i = 0;
	while (*input == ' ')
		input++;
	while (*input == delimiter)
		input++;
	while (input[i])
	{
		if (is_delimiter(input[i], delimiter) && not_escaped(input, i))
			input[i] = '\0';
		i++;
	}
	return (input);
}

static	void	divide_arguments(char	**args, char *input, int len)
{
	int		i;
	int		j;
	char	*tmp;

	i = 0;
	j = 0;
	while(i < len)
	{
		args[j] = ft_strdup(&input[i]);
		if (!ft_strncmp(args[j], "\"\"", 3))
		{
			tmp = ft_strdup("");
			free(args[j]);
			args[j] = tmp;
			i += 2;
		}
		else
			i += ft_strlen(args[j]);
		j++;
		while (i < len && !input[i])
			i++;
		if (i >= len)
			break;
	}
	args[j] = NULL;
}

char			**ft_split_non_escaped(char *input, char delimiter)
{
	char	**args;
	int		len;

	if (!(args = malloc((count_args(input, delimiter) + 2) * sizeof(char *))))
		return (NULL);
	len = ft_strlen(input);
	input = set_split_delimiter(input, delimiter);
	divide_arguments(args, input, len);
	return (args);
}
