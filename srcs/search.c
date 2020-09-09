#include "minishell.h"

static char *in_path(char *binary, char *path, size_t len)
{
	DIR				*pdir;
	struct dirent 	*direntp;
	char 			*directory;

	directory = ft_calloc(len + 2, sizeof(directory));
	ft_strlcpy(directory, path, len + 2);
	directory[len] = '/';
	directory[len + 1] = '\0';
	if (!(pdir = opendir(directory)))	
		return (NULL);
	while ((direntp = readdir(pdir)))
	{
		if (ft_strncmp(direntp->d_name, binary, ft_strlen(binary) + 1) == 0)
		{
			closedir(pdir);
			return (ft_strdup(directory));
		}
		direntp++;
	}
	closedir(pdir);
	return (NULL);
}

static char *check_binary(char *binary, char **paths)
{
	char 		*path;
	size_t 		it;
	struct stat s;
	
	it = 0;
	while (paths[it])
	{
		if ((path = in_path(binary, paths[it], ft_strlen(paths[it]))))
		{
			if (lstat(path, &s) == -1)
				free(path);
			else
				return (path);
		}
		it++;
	}
	return (NULL);
}

static char *split_path(char *binary, char *env)
{
	char *path;
	char **paths;

	path = ft_strchr(env, '=');
	if (path)
	{
		paths = ft_split(path + 1, ':');		
		return (check_binary(binary, paths));
	}
	return (NULL);
}

static char *environments(char *binary, char **env)
{
	size_t it;
	size_t len;
	
	len = ft_strlen("PATH");
	it = 0;
	while (env[it])
	{
		if (ft_strncmp(env[it], "PATH", len) == 0)
			return (split_path(binary, env[it]));
		it++;
	}
	return (NULL);
}

char 	*get_path(char *binary, char **env)
{
	if (!env)
		return (NULL);
	return (environments(binary, env));	
}
