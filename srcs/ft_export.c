#include "minishell.h"

char	**add_new_env(char *variable, char **envp)
{
	char	**tmp_envp;
	int		i;

	i = 0;
	tmp_envp = realloc_one(envp);
	while (*envp)
	{
		tmp_envp[i] = *envp;
		envp++;
		i++;
	}
	tmp_envp[i] = variable;
	tmp_envp[i + 1] = NULL;
	return (tmp_envp);
}

size_t	is_bigger(char *s1, char *s2)
{
	int ret;

	ret = 0;
	if (*s1 == *s2)
		ret = is_bigger(s1 + 1, s2 + 1);
	else if (*s1 > *s2)
		ret = 1;
	return (ret);
}

char	**sort_alfa(char **envp)
{
	char	*tmp;
	size_t	len;
	size_t	i;
	size_t	j;

	len = 0;
	i = 0;
	while (envp[len + 1])
		len++;
	while (i < len)
	{
		j = 0;
		while (j < len - i)
		{
			if (is_bigger(envp[j], envp[j + 1]))
			{
				tmp = envp[j];
				envp[j] = envp[j + 1];
				envp[j + 1] = tmp;
			}
			j++;
		}
		i++;
	}
	return (envp);
}

void	print_sorted_env(t_shell *shell)
{
	char **tmp_envp;

	tmp_envp = ft_strdup_matrix(shell->env);
	ft_env(shell->args + 1, sort_alfa(tmp_envp));
	free(tmp_envp);
}

int		ft_export(char **command, t_shell *shell)
{
	int  i;
	char *var;
	char *tmp;

	if (!*command)
		print_sorted_env(shell);
	while (*command)
	{
		i = 0;
		if ((tmp = ft_strchr(*command, '=')))
		{
			var = ft_strdup(*command);
			*tmp = '\0';
			while (shell->env[i] && ft_strncmp(shell->env[i], *command, ft_strlen(*command)))
				i++;
			if (shell->env[i])
				shell->env[i] = var;
			else
				shell->env = add_new_env(var, shell->env);
		}
		command++;
	}
	return (1);
}
