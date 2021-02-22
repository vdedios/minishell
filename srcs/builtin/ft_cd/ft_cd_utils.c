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

void		set_path(char *path, const char *key, t_shell *shell)
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

void		dir_err(t_shell *shell, char *path, char *err)
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

void		change_dir_error(t_shell *shell, char *path)
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

void		update_olddir(t_shell *shell, char *oldpwd)
{
	char		*tmp;

	tmp = ft_strjoin("OLDPWD=", oldpwd);
	ft_export(shell, tmp);
	free(tmp);
}
