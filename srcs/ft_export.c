#include "minishell.h"

static size_t	is_bigger(char *s1, char *s2)
{
	int ret;

	ret = 0;
	if (*s1 == *s2)
		ret = is_bigger(s1 + 1, s2 + 1);
	else if (*s1 > *s2)
		ret = 1;
	return (ret);
}

static char		**sort_alpha(char **envp)
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

static short	is_escapable_char(char c) {
	if (c == '$' || c == '\\' || c == '\"')
		return (1);
	return (0);
}

static int		count_special_chars(char *str)
{
	int count;

	count = 0;
	while(*str)
	{
		if (is_escapable_char(*str))
			count++;
		str++;
	}
	return (count);
}

static char		*add_quotes_and_backslash(char *str)
{
	char	*buff;
	int		i;

	i = 0;
	if (!(buff = malloc((ft_strlen(str) + count_special_chars(str) + 3)
						* sizeof(char))))
		return (NULL);
	while(*str)
	{
		if (is_escapable_char(*str))
			buff[i++] = '\\';
		buff[i++] = *str;
		if (*str == '=')
			buff[i++] = '\"';
		str++;
	}
	buff[i++] = '\"';
	buff[i] = '\0';
	return (buff);
}

static  char	**process_envs(char **env)
{
	char **tmp_envp;
	char *tmp;
	char *tmp2;
	int	 i;

	i = 0;
	tmp_envp = ft_strdup_matrix(env);
	while (tmp_envp[i])
	{
		tmp = ft_strjoin("declare -x ", tmp_envp[i]);
		tmp2 = add_quotes_and_backslash(tmp);
		free(tmp_envp[i]);
		free(tmp);
		tmp_envp[i] = tmp2;
		i++;
	}
	return (tmp_envp);
}

static size_t	print_sorted_env(t_shell *shell)
{
	char **tmp_envp;

	tmp_envp = sort_alpha(shell->env);
	shell->env = process_envs(tmp_envp);
	ft_env(shell, NULL);
	clean_matrix(tmp_envp);
	free(tmp_envp);
	return (1);
}

static	void	export_values(t_shell *shell, char *last_arg, int j)
{
	int  	i;
	char 	*value;
	char	*tmp;
	char 	**tmp_env;

	i = 0;
	if (last_arg)
		value = last_arg;
	else
		value = ft_strdup(shell->args[j]);
	tmp = ft_strchr(value, '=');
	while (shell->env[i] && ft_strncmp(shell->env[i], value,
				ft_strlen(value) - ft_strlen(tmp)))
		i++;
	value = parse_backslash(value, 2);
	tmp_env = add_env(&value, shell->env, i);
	clean_env(shell);
	shell->env = tmp_env;
}

int				ft_export(t_shell *shell, char *last_arg)
{
	char	*tmp;
	int  	j;

	j = 1;
	if (last_arg)
		export_values(shell, last_arg, 0);
	else if(!shell->args[j])
		return(print_sorted_env(shell));
	else
	{
		while (shell->args[j])
		{
			if ((tmp = ft_strchr(shell->args[j], '=')) && *tmp != *shell->args[j])
				export_values(shell, last_arg, j);
			j++;
		}
	}
	return (1);
}