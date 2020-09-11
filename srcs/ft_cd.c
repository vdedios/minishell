#include "minishell.h"

int		ft_cd(char *arg, char **env)
{
	char *oldcwd;
	char *newcwd;
	
	if (!arg)
		arg = get_env(env, "HOME");
	else if (!ft_strncmp(arg, "-", 2))
		arg = get_env(env, "OLDPWD");
	oldcwd = ft_calloc(1024, sizeof(oldcwd));
	newcwd = ft_calloc(1024, sizeof(newcwd));
	getcwd(oldcwd, 1024);
	chdir(arg);
	getcwd(newcwd, 1024);
	return (1);
}
