#include "minishell.h"

static	int		count_args(char	*input, char delimiter)
{
	int		i;
	int		l;

	l = 0;
	i = -1;
	while(input[++i])
	{
		if (input[i] == delimiter && input[i - 1] != '\\')
		{
			l++;
			while (input[i] && input[i] != delimiter)
				i++;
			if (!input[i])
				break;
		}
	}
	return (l);
}

static short	is_whitespace(char c)
{
	if (c == ' ' || c == '\t')
		return (1);
	return (0);
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

static	char	*set_split_delimiter_whitespace(char *input)
{
	int	i;

	i = 0;
	while (is_whitespace(input[i]))
		input++;
	while (input[i])
	{
		if (is_whitespace(input[i]) && not_escaped(input, i))
			input[i] = '\0';
		i++;
	}
	return (input);
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
		if (input[i] == delimiter && not_escaped(input, i))
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
		args[j] = strdup(&input[i]);
		if (!ft_strncmp(args[j], "\"\"", 3))
		{
			tmp = ft_strdup("");
			free(args[j]);
			args[j] = tmp;
			i += 2;
		}
		else
			i += strlen(args[j]);
		j++;
		while (i < len && !input[i])
			i++;
		if (i >= len)
			break;
	}
	args[j] = NULL;
}

char	**ft_split_non_escaped(char *input, char delimiter)
{
	char	**args;
	int		len;

	if (!(args = malloc((count_args(input, delimiter) + 2) * sizeof(char *))))
		return (NULL);
	len = strlen(input);
	if (delimiter == ' ')
		input = set_split_delimiter_whitespace(input);
	else
		input = set_split_delimiter(input, delimiter);
	divide_arguments(args, input, len);
	return (args);
}