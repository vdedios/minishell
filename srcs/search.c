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

char	*search_binary(t_shell *shell, char **paths, int *binary)
{
	size_t			it;
	struct stat		s;
	struct dirent	*direntp;
	DIR				*pdir;

	it = -1;
	(void)binary;
	to_lower(shell->args[0]);
	while (paths[++it])
	{
		if (stat(paths[it], &s) != -1)
		{
			if(s.st_mode & S_IFDIR)
			{
				if (!(pdir = opendir(paths[it])))
					return (NULL);
				while ((direntp = readdir(pdir)))
				{
					if (ft_strcmp(direntp->d_name, shell->args[0]))
					{
						if (binary) *binary = 1;
						closedir(pdir);
						return (absolute_bin_path(paths[it], shell->binary));
					}
					direntp++;
				}
				closedir(pdir);
			}
		}
	}
	if (stat(shell->args[0], &s) != -1)
	{
		if (S_ISDIR(s.st_mode) || S_ISREG(s.st_mode))
		{
			//printf("Entra\n");
			if (ft_strncmp(shell->args[0], "/", 1) && ft_strncmp(shell->args[0], "./", 2) && !(shell->args[0][ft_strlen(shell->args[0]) - 1] == '/'))
			{
				shell->stat_loc = 127;
				print_errors(shell, " command not found", shell->binary);
				exit(shell->stat_loc);
			}
		}
		return (shell->binary);
	}
	if (lstat(shell->args[0], &s) != -1 || !ft_strncmp(shell->args[0], "./", 2))
	{
		shell->stat_loc = 127;
		print_errors(shell, " No such file or directory", shell->binary);
		exit(shell->stat_loc);
	}
	return (NULL);
}
