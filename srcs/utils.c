#include "minishell.h"

int		ft_isspace(int c)
{
	c = (unsigned char)c;
	if (c == '\t' || c == '\n' || c == '\v'
		|| c == '\f' || c == '\r' || c == ' ')
		return (1);
	return (0);
}

char	**ft_strdup_matrix(char **envp)
{
	char	**tmp_envp;
	int		l;
	int		i;

	i = 0;
	l = 0;
	while (envp[l])
		l++;
	if (!(tmp_envp = malloc((l + 1) * sizeof(char *))))
		return (NULL);
	while (*envp)
	{
		tmp_envp[i] = ft_strdup(*envp);
		envp++;
		i++;
	}
	tmp_envp[i] = NULL;
	return (tmp_envp);
}

char	*absolute_bin_path(char *path, char *bin)
{
	char *tmp;

	tmp = ft_strjoin(path, "/");
	path = ft_strjoin(tmp, bin);
	free(tmp);
	return (path);
}

char	**realloc_matrix(char **envp, int additional)
{
	char	**tmp_envp;
	int		l;

	l = 0;
	while (envp[l])
		l++;
	if (!(tmp_envp = malloc((l + additional + 1) * sizeof(char *))))
		return (NULL);
	return (tmp_envp);
}

char	**add_env(char **variable, char **env, int n)
{
	char	**tmp_envp;
	int		i;

	i = 0;
	if (env[n])
		tmp_envp = realloc_matrix(env, 0);
	else
		tmp_envp = realloc_matrix(env, 1);
	tmp_envp[n] = ft_strdup(*variable);
	while (*env)
	{
		if (i != n)
			tmp_envp[i] = ft_strdup(*env);
		env++;
		i++;
	}
	if (i != n)
		tmp_envp[i] = NULL;
	else
		tmp_envp[i + 1] = NULL;
	return (tmp_envp);
}
