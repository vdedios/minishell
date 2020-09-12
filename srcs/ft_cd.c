/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: migferna <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/12 10:58:41 by migferna          #+#    #+#             */
/*   Updated: 2020/09/12 10:58:43 by migferna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	change_dir(char *path)
{
	char		*oldcwd;
	struct stat	s;

	oldcwd = ft_calloc(1024, sizeof(oldcwd));
	getcwd(oldcwd, 1024);
	if (chdir(path) == 0)
		return ;
	else
	{
		write(1, "cd: ", 4);
		if (lstat(path, &s) != -1)
			if (s.st_mode & S_IFDIR)
				write(1, "permission denied: ", 19);
			else
				write(1, "not a directory: ", 17);
		else
			write(1, "no such file or directory: ", 27);
		ft_putendl_fd(path, 1);
	}
}

int		ft_cd(char **args, char **env)
{
	char	*path;

	if (!args[0] || !ft_strncmp(args[0], "--", 3))
		path = get_env(env, "HOME");
	else if (!ft_strncmp(args[0], "-", 2))
		path = get_env(env, "OLDPWD");
	else if (args[1])
	{
		path = NULL;
		if (args[2])
		{
			ft_putendl_fd("cd: too many arguments", 1);
			return (1);
		}
	}
	else
		path = args[0];
	change_dir(path);
	return (1);
}
