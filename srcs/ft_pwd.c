#include "minishell.h"

int		ft_pwd()
{
	char	cwd[1024];

	if (getcwd(cwd, sizeof(cwd)))
		ft_putendl_fd(cwd, 1);
	return (1);	
}
