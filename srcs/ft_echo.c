#include "minishell.h"

int		ft_echo(char **args)
{
	char	*end;
	size_t 	len;
	size_t	it;
	
	end = ft_strdup("\n");
	args++;
	it = 0;
	if (*args && (*args)[it++] == '-' && (*args++)[it] == 'n')
		end = NULL;
	while (*args)
	{
		len = ft_strlen(*args);
		write(1, *args++, len);
		if (*args)
			write(1, " ", 1);
	}
	if (end)
	{
		write(1, end, 1);
		free(end);
	}
	return (1);
}
