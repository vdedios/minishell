/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: migferna <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/12 10:58:41 by migferna          #+#    #+#             */
/*   Updated: 2021/02/18 22:19:14 by migferna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void		set_path(char *path, const char *key, t_shell *shell)
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
}

static void		dir_err(t_shell *shell, char *path, char *err)
{
	char		*msg;
	char		*tmp;

	path = ft_strjoin(" ", path);
	tmp = ft_strdup(path);
	free(path);
	msg = ft_strjoin(tmp, err);
	free(tmp);
	print_errors(shell, msg, shell->binary);
	free(msg);
}

static void		change_dir_error(t_shell *shell, char *path)
{
	struct stat	s;

	if (stat(path, &s) != -1)
	{
		if (s.st_mode & S_IFDIR)
			dir_err(shell, path, ": Permission denied");
		else
			print_errors(shell, "not a directory:", shell->binary);
	}
	else
		dir_err(shell, path, ": No such file or directory");
}

static void		update_olddir(t_shell *shell, char *oldpwd)
{
	char		*tmp;

	tmp = ft_strjoin("OLDPWD=", oldpwd);
	ft_export(shell, tmp);
	free(tmp);
}

int	is_symbolic_link(char *path)
{
    struct stat buf;
    int 		x;

    x = lstat(path, &buf);
    return (S_ISLNK(buf.st_mode));
}

static void		change_dir(char *path, t_shell *shell)
{
	char		*oldcwd;
	char		*cwd;
	char		*tmp;


	oldcwd = ft_calloc(1024, sizeof(oldcwd));
	cwd = ft_calloc(1024, sizeof(cwd));
	if (chdir(path) == 0)
	{
		getcwd(cwd, 1024);
		tmp = get_env(shell, "PWD");
		if (tmp)
			update_olddir(shell, tmp);
		else
			update_olddir(shell, "");
		free(tmp);
		if (is_symbolic_link(path))
			set_path(path, "PWD=", shell);
		else
			set_path(cwd, "PWD=", shell);
	}
	else
		change_dir_error(shell, path);
	free(oldcwd);
	free(cwd);
}

static short	home_not_exists(t_shell *shell, char *path)
{
	char	*tmp;

	free(path);
	path = NULL;
	tmp = ft_strdup(shell->binary);
	print_errors(shell, " HOME not set", tmp);
	free(tmp);
	return (1);
}

static short	many_arguments(t_shell *shell)
{
	print_errors(shell, "too many arguments", shell->binary);
	return (1);
}

int				ft_cd(t_shell *shell)
{
	char	*path;
	char	*target;

	target = shell->args[1];
	if (!target || !ft_strncmp(target, "--", 3) || !ft_strncmp(target, "~", 2))
	{
		path = get_env(shell, "HOME");
		if (ft_strcmp(path, ""))
			return (home_not_exists(shell, path));
	}
	else if (!ft_strncmp(target, ".", 2) || !ft_strncmp(target, "", 1))
		path = get_env(shell, "PWD");
	else if (!ft_strncmp(target, "-", 2))
		path = get_env(shell, "OLDPWD");
	else if (shell->args[2] && *shell->args[2])
	{
		path = ft_strdup(target);
		if (shell->args[3])
			return (many_arguments(shell));
	}
	else
		path = ft_strdup(target);
	change_dir(path, shell);
	free(path);
	return (1);
}
