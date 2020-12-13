/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: migferna <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/12 10:58:41 by migferna          #+#    #+#             */
/*   Updated: 2020/12/13 13:25:31 by migferna         ###   ########.fr       */
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
	//free(path);
}

static char	*get_path(t_shell *shell, char *path)
{
	size_t 	it;
	size_t	len;

	it = -1;
	len = ft_strlen(path);
	while (shell->env[++it])
	{
		if (!ft_strncmp(shell->env[it], path, len))
			return (ft_strchr(shell->env[it], '=') + 1);
	}
	return (NULL);
}

static void	change_dir(char *path, t_shell *shell)
{
	char		*oldcwd;
	char		*cwd;
	struct stat	s;
	char		*msg;

	oldcwd = ft_calloc(1024, sizeof(oldcwd));
	cwd = ft_calloc(1024, sizeof(cwd));
	getcwd(oldcwd, 1024);
	//oldcwd = get_path(shell, "PWD=");
	//printf("Sale: %s\n", oldcwd);
	//set_path(oldcwd, "PWD=", shell);
	if (chdir(path) == 0)
	{
		getcwd(cwd, 1024);
		set_path(get_path(shell, "PWD="), "OLDPWD=", shell);
		set_path(cwd, "PWD=", shell);
	}
	else
	{
		if (stat(path, &s) != -1)
		{
			if (s.st_mode & S_IFDIR)
			{
				path = ft_strjoin(" ", path);
				msg = ft_strjoin(path, ": Permission denied");
				print_errors(shell, msg, shell->binary, 0);
			}
			else
				print_errors(shell, "not a directory:", shell->binary, 0);
		}
		else
		{
			path = ft_strjoin(" ", path);
			msg = ft_strjoin(path, ": No such file or directory");
			print_errors(shell, msg, shell->binary, 0);
		}
		//ft_putendl_fd(path, 1);
	}
}

int			ft_cd(t_shell *shell)
{
	char	*path;
	char	*target;

	target = shell->args[1];
	if (!target || !ft_strncmp(target, "--", 3) || !ft_strncmp(target, "~", 2))
		path = get_env(shell->env, "HOME", shell->binary);
	else if (!ft_strncmp(target, ".", 2) || !ft_strncmp(target, "", 1))
		path = get_env(shell->env, "PWD", shell->binary);
	else if (!ft_strncmp(target, "-", 2))
		path = get_env(shell->env, "OLDPWD", shell->binary);
	else if (shell->args[2] && *shell->args[2])
	{
		path = NULL;
		if (shell->args[3])
		{
			print_errors(shell, "too many arguments", shell->binary, 0);
			return (1);
		}
	}
	else
		path = target;
	if (!path) return (1);
	change_dir(path, shell);
	return (1);
}
