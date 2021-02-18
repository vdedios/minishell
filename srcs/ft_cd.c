/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: migferna <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/12 10:58:41 by migferna          #+#    #+#             */
/*   Updated: 2021/02/18 18:11:43 by migferna         ###   ########.fr       */
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
			free(variable);
			clean_env(shell);
			shell->env = tmp;
		}
		it++;
	}
	//if (variable)
	//	free(variable);Si se libera se pierde el env
	//free(path);
}

static void	change_dir(char *path, t_shell *shell)
{
	char		*oldcwd;
	char		*cwd;
	struct stat	s;
	char		*msg;
	char		*tmp;
	char		*tmp2;

	oldcwd = ft_calloc(1024, sizeof(oldcwd));
	cwd = ft_calloc(1024, sizeof(cwd));
	getcwd(oldcwd, 1024);
	//oldcwd = get_workdir(shell, "PWD=");
	//printf("Sale: %s\n", oldcwd);
	//set_path(oldcwd, "PWD=", shell);
	if (chdir(path) == 0)
	{
		getcwd(cwd, 1024);
		//set_path(get_workdir(shell, "PWD="), "OLDPWD=", shell);
		tmp = get_env(shell, "PWD");
		if (tmp)
		{
			tmp2 = ft_strjoin("OLDPWD=", tmp);
			ft_export(shell, tmp2);
			free(tmp2);
		}
		else
		{
			tmp2 = ft_strjoin("OLDPWD=", "");
			ft_export(shell, tmp2);
			free(tmp2);
		}
		free(tmp);
		set_path(cwd, "PWD=", shell);
		//ft_export(shell, ft_strjoin("OLDPWD=", oldcwd));
	}
	else
	{
		if (stat(path, &s) != -1)
		{
			if (s.st_mode & S_IFDIR)
			{
				path = ft_strjoin(" ", path);
				tmp = ft_strdup(path);
				free(path);
				msg = ft_strjoin(tmp, ": Permission denied");
				free(tmp);
				print_errors(shell, msg, shell->binary);
				free(msg);
			}
			else
				print_errors(shell, "not a directory:", shell->binary);
		}
		else
		{
			path = ft_strjoin(" ", path);
			tmp = ft_strdup(path);
			free(path);
			msg = ft_strjoin(tmp, ": No such file or directory");
			free(tmp);
			print_errors(shell, msg, shell->binary);
			free(msg);
		}
		//ft_putendl_fd(path, 1);
	}
	free(oldcwd);
	free(cwd);
}

int			ft_cd(t_shell *shell)
{
	char	*path;
	char	*target;
	char	*tmp;

	target = shell->args[1];
	if (!target || !ft_strncmp(target, "--", 3) || !ft_strncmp(target, "~", 2))
	{
		path = get_env(shell, "HOME");
		if (ft_strcmp(path, ""))
		{
			free(path);
			path = NULL;
			tmp = ft_strdup(shell->binary);
			print_errors(shell, " HOME not set", tmp);
			free(tmp);
		}
			
	}
	else if (!ft_strncmp(target, ".", 2) || !ft_strncmp(target, "", 1))
		path = get_env(shell, "PWD");
	else if (!ft_strncmp(target, "-", 2))
		path = get_env(shell, "OLDPWD");
	else if (shell->args[2] && *shell->args[2])
	{
		path = ft_strdup(target);
		if (shell->args[3])
		{
			print_errors(shell, "too many arguments", shell->binary);
			return (1);
		}
	}
	else
		path = ft_strdup(target);
	if (!path)
	{	
		free(path);
		return (1);
	}
	change_dir(path, shell);
	free(path);
	return (1);
}
