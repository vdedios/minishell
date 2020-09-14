/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: migferna <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/12 10:58:41 by migferna          #+#    #+#             */
/*   Updated: 2020/09/14 10:07:51 by migferna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	set_path(char *path, const char *key, char **env)
{
	size_t len;
	size_t it;

	len = ft_strlen(key) + 1;
	it = 0;
	while (env[it])
	{
		if (ft_strnstr(env[it], key, len))
			env[it] = ft_strjoin(key, path);
		it++;
	}
}

static void	change_dir(char *path, char **env)
{
	char		*oldcwd;
	char		*cwd;
	struct stat	s;

	oldcwd = ft_calloc(1024, sizeof(oldcwd));
	cwd = ft_calloc(1024, sizeof(cwd));
	getcwd(oldcwd, 1024);
	if (chdir(path) == 0)
	{
		getcwd(cwd, 1024);
		set_path(cwd, "PWD=", env);
		set_path(oldcwd, "OLDPWD=", env);
	}
	else
	{
		ft_putstr_fd("cd: ", 1);
		if (lstat(path, &s) != -1)
			if (s.st_mode & S_IFDIR)
				ft_putstr_fd("permission denied: ", 1);
			else
				ft_putstr_fd("not a directory: ", 1);
		else
			ft_putstr_fd("no such file or directory: ", 1);
		ft_putendl_fd(path, 1);
	}
}

int			ft_cd(char **args, char **env)
{
	char	*path;

	if (!args[0] || !ft_strncmp(args[0], "--", 3) ||
		!ft_strncmp(args[0], "~", 2))
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
	change_dir(path, env);
	return (1);
}
