/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   search.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: migferna <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/12 10:08:20 by migferna          #+#    #+#             */
/*   Updated: 2021/01/14 23:09:42 by migferna         ###   ########.fr       */
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
	//char			cwd[1024];
	struct stat		s;
	struct dirent	*direntp;
	DIR				*pdir;

//	if (getcwd(cwd, sizeof(cwd)))
//	{
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
//	}
	return (NULL);
}

char	*search_binary(t_shell *shell, char **paths, int *binary)
{
	size_t			it;
	struct stat		s;
	struct dirent	*direntp;
	DIR				*pdir;
	char			*bin_name;

	it = -1;
	//hay que liberarlo, se pasa a lower solo para buscarlo
	bin_name = strdup(shell->args[0]);
	to_lower(bin_name);
	while (paths[++it])
	{
		if (stat(paths[it], &s) != -1 &&
			s.st_mode & S_IFDIR)
		{
			if (!(pdir = opendir(paths[it])))
				return (NULL);
			while ((direntp = readdir(pdir)))
			{
				if (ft_strcmp(direntp->d_name, bin_name))
				{
					if (binary)
						*binary = 1;
					closedir(pdir);
					return (absolute_bin_path(paths[it], shell->binary));
				}
				direntp++;
			}
			closedir(pdir);
		}
	}
	if (stat(bin_name, &s) != -1)
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
		return (shell->binary);
	}
	if (lstat(bin_name, &s) != -1 || !ft_strncmp(bin_name, "./", 2))
	{
		shell->stat_loc = 127;
		print_errors(shell, " No such file or directory", shell->binary);
		exit(shell->stat_loc);
	}
	return (NULL);
}