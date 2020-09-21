/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: migferna <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/12 10:58:41 by migferna          #+#    #+#             */
/*   Updated: 2020/09/21 10:18:08 by vde-dios         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	set_path(char *path, const char *key, t_shell *shell)
{
	size_t	len;
	size_t	it;
	char	*variable;
	char	**tmp;

	len = ft_strlen(key) + 1;
	it = 0;
	while (shell->env[it])
	{
		if (ft_strnstr(shell->env[it], key, len))
		{
			variable = ft_strjoin(key, path);
			tmp = add_env(&variable, shell->env, it);
			clean_env(shell);
			shell->env = tmp;
		}
		it++;
	}
	free(path);
}

static void	change_dir(char *path, t_shell *shell)
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
		set_path(cwd, "PWD=", shell);
		set_path(oldcwd, "OLDPWD=", shell);
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

int			ft_cd(t_shell *shell)
{
	char	*path;

	if (!shell->args[1] || !ft_strncmp(shell->args[1], "--", 3) ||
		!ft_strncmp(shell->args[1], "~", 2))
		path = get_env(shell->env, "HOME");
	else if (!ft_strncmp(shell->args[1], "-", 2))
		path = get_env(shell->env, "OLDPWD");
	else if (shell->args[2])
	{
		path = NULL;
		if (shell->args[3])
		{
			ft_putendl_fd("cd: too many arguments", 1);
			return (1);
		}
	}
	else
		path = shell->args[1];
	change_dir(path, shell);
	return (1);
}
