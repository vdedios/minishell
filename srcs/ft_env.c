#include "minishell.h"

int	ft_env(char **env)
{
	size_t it;
	
	it = 0;
	while (env[it])
	{
		ft_putendl_fd(env[it], 0);
		it++;
	}
	return (1);
}
