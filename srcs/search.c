/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   search.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: migferna <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/12 10:08:20 by migferna          #+#    #+#             */
/*   Updated: 2021/02/15 22:57:51 by migferna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static	void	to_lower(char *input)
{
	size_t	it;

	it = -1;
	while (input[++it])
	{
		input[it] = ft_tolower(input[it]);
	}
}

char	*search_binary_in_pwd(t_shell *shell)
{
	struct stat		s;
	struct dirent	*direntp;
	DIR				*pdir;

	if (stat(".", &s) != -1 &&
		s.st_mode & S_IFDIR)
	{
		if (!(pdir = opendir(".")))
			return (NULL);
		while ((direntp = readdir(pdir)))
		{
			if (ft_strcmp(direntp->d_name, shell->args[0]))
			{
				closedir(pdir);
				return (absolute_bin_path(".", shell->binary));
			}
			direntp++;
		}
		closedir(pdir);
	}
	shell->stat_loc = 127;
	print_errors(shell, " No such file or directory", shell->binary);
	exit(shell->stat_loc);
	return (NULL);
}

static	void	command_exists(t_shell *shell, char *bin_name
								, struct stat s)
{
	if (S_ISDIR(s.st_mode) || S_ISREG(s.st_mode))
	{
		if (ft_strncmp(shell->args[0], "/", 1) &&
			ft_strncmp(shell->args[0], "./", 2) &&
			!(shell->args[0][ft_strlen(bin_name) - 1] == '/'))
		{
			shell->stat_loc = 127;
			print_errors(shell, " command not found", shell->binary);
			exit(shell->stat_loc);
		}
	}
}

static	short	binary_path_exists(char *path,char *bin_name,
									int *binary, struct stat *s)
{
	DIR				*pdir;
	struct dirent	*direntp;

	if (stat(path, s) != -1 &&
		s->st_mode & S_IFDIR)
	{
		if (!(pdir = opendir(path)))
			return (0);
		while ((direntp = readdir(pdir)))
		{
			if (ft_strcmp(direntp->d_name, bin_name))
			{
				if (binary)
					*binary = 1;
				closedir(pdir);
				free(bin_name);
				return (1);
			}
			direntp++;
		}
		closedir(pdir);
	}
	return (0);
}

char	*search_binary(t_shell *shell, char **paths, int *binary)
{
	size_t			it;
	struct stat		s;
	char			*bin_name;

	it = -1;
	bin_name = ft_strdup(shell->args[0]);
	to_lower(bin_name);
	while (paths[++it])
		if (binary_path_exists(paths[it], bin_name, binary, &s))
			return (absolute_bin_path(paths[it], shell->binary));
	if (stat(bin_name, &s) != -1)
	{
		command_exists(shell, bin_name, s);
		free(bin_name);
		return (ft_strdup(shell->binary));
	}
	if (lstat(bin_name, &s) != -1 || !ft_strncmp(bin_name, "./", 2) || ft_strchr(shell->args[0], '/'))
	{
		shell->stat_loc = 127;
		print_errors(shell, " No such file or directory", shell->binary);
		exit(shell->stat_loc);
	}
	free(bin_name);
	return (NULL);
}
