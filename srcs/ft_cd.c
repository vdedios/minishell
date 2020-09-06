#include "minishell.h"

int		ft_cd(char *arg)
{
	char *oldcwd;
	char *newcwd;
	
	oldcwd = ft_calloc(1024, sizeof(oldcwd));
	newcwd = ft_calloc(1024, sizeof(newcwd));
	getcwd(oldcwd, 1024);
	chdir(arg);
	getcwd(newcwd, 1024);
	return (1);
}
