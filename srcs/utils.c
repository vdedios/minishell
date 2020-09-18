#include "minishell.h"

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
		tmp_envp[i] = *envp;
		envp++;
		i++;
	}
	tmp_envp[i] = NULL;
	return (tmp_envp);
}

char	*abs_bin_path(char *path, char *bin)
{
	char *tmp;

	tmp = ft_strjoin(path, "/");
	path = ft_strjoin(tmp, bin);
	free(tmp);
	return (path);
}
