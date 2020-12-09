#include "minishell.h"

static	int		count_args(char	*input)
{
	int		i;
	int		l;

	l = 0;
	i = -1;
	while(input[++i])
	{
		if (input[i] == ' ' && input[i - 1] != '\\')
		{
			l++;
			while (input[i] && input[i] != ' ')
				i++;
			if (!input[i])
				break;
		}
	}
	return (l);
}

static void		set_split_delimiter(char *input)
{
	while (*input)
	{
		if (*input == ' ' && *(input - 1) != '\\')
			*input = '\0';
		input++;
	}
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

static	void	delete_residual_backslash(char **args)
{
	while (*args)
	{
		*args = parse_backslash(*args, 1);
		args++;
	}
}

char	**ft_split_args(char *input)
{
	char	**args;
	int		len;

	if (!(args = malloc((count_args(input) + 2) * sizeof(char *))))
		return (NULL);
	len = strlen(input);
	set_split_delimiter(input);
	divide_arguments(args, input, len);
	delete_residual_backslash(args);
	return (args);
}
