#include "minishell.h"

char	**realloc_one(char **envp)
{
	char	**tmp_envp;
	int		l;

	l = 0;
	while (envp[l])
		l++;
	if (!(tmp_envp = malloc((l + 2) * sizeof(char *))))
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
