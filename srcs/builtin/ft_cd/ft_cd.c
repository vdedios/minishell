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

int		ft_cd(t_shell *shell)
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

int		is_symbolic_link(char *path)
{
    struct stat buf;
    int 		x;

    x = lstat(path, &buf);
    return (S_ISLNK(buf.st_mode));
}

void	change_dir(char *path, t_shell *shell)
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

short	home_not_exists(t_shell *shell, char *path)
{
	char	*tmp;

	free(path);
	path = NULL;
	tmp = ft_strdup(shell->binary);
	print_errors(shell, " HOME not set", tmp);
	free(tmp);
	return (1);
}

short	many_arguments(t_shell *shell)
{
	print_errors(shell, "too many arguments", shell->binary);
	return (1);
}
