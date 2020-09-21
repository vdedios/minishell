/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   search.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: migferna <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/12 10:08:20 by migferna          #+#    #+#             */
/*   Updated: 2020/09/18 12:57:53 by vde-dios         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*search_binary(char *binary, char **paths)
{
	size_t			it;
	struct stat		s;
	struct dirent	*direntp;
	DIR				*pdir;

	it = -1;
	while (paths[++it])
	{
		if (lstat(paths[it], &s) != -1 && (s.st_mode & S_IFDIR))
		{
			if (!(pdir = opendir(paths[it])))
				return (NULL);
			while ((direntp = readdir(pdir)))
			{
				if (ft_strcmp(direntp->d_name, binary))
				{
					closedir(pdir);
					return (paths[it]);
				}
				direntp++;
			}
			closedir(pdir);
		}
	}
	return (NULL);
}

char	*get_env(char **env, char *arg)
{
	size_t it;
	size_t len;

	len = ft_strlen(arg);
	it = 0;
	while (env[it])
	{
		if (ft_strncmp(env[it], arg, len) == 0)
			return (ft_strchr(env[it], '=') + 1);
		it++;
	}
	return (NULL);
}
