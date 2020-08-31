#include "minishell.h"

char	**get_args(char *input)
{
	char **args;
	
	if (!input)
		return (NULL);
	args = ft_split(input, ' ');
	return args;
}
