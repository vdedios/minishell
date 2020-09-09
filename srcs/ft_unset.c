#include "minishell.h"

int		ft_unset(char *var, char **env)
{
	size_t	it;
	size_t	len;
	
	len = ft_strlen(var);
	it = 0;
	while (env[it])
	{
		if (ft_strncmp(var, env[it], len + 1) == 0)
			break ;
		it++;
	}
	free(env[it]);
	env[it] = null;
	return (1);
}
