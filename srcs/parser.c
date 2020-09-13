/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: migferna <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/12 11:18:25 by migferna          #+#    #+#             */
/*   Updated: 2020/09/13 19:06:10 by migferna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**get_args(char *input)
{
	char **args;

	if (!input)
		return (NULL);
	args = ft_split(input, ' ');
	return (args);
}

char	*first_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t i;

	i = 0;
	while (i < len && needle[i])
	{
		if (haystack[i] != needle[i])
			return (0);
		i++;
	}
	return ((char *)haystack);
}

char	*post_string_expand(char *command)
{
	while (*command && *command != '}')
		command++;
	*command = '\0';
	command++;
	return (command);
}

void	set_expansion_boundaries(char **command, char **post)
{
	**command = '\0';
	*command = *command + 1;
	if (**command == '{')
	{
		*command = *command + 1;
		*post = post_string_expand(*command);
	}
}

size_t	last_proc_status(char *env, t_shell *shell, int j)
{
	if (*(env + 1) == '?' && *(env + 2) == '\0')
	{
		shell->args[j] = ft_itoa(shell->stat_loc);
		return (1);
	}
	return (0);
}

/*
** In case var expansion is in the middle of a string we consider:
** [pre]${VAR}[post]
*/
void	expand_var(t_shell *shell)
{
	int			i;
	int			j;
	t_expand	expnd;

	j = 1;
	expnd.post = NULL;
	while (shell->args[j])
	{
		i = 0;
		expnd.pre = shell->args[j];
		if ((expnd.env = ft_strchr(shell->args[j], '$'))
				&& !last_proc_status(expnd.env, shell, j))
		{
			set_expansion_boundaries(&expnd.env, &expnd.post);
			while (shell->env[i] && !first_strnstr(shell->env[i], expnd.env, ft_strlen(shell->env[i])))
				i++;
			if (shell->env[i])
				shell->args[j] = ft_strjoin(expnd.pre, shell->env[i] + ft_strlen(expnd.env) + 1);
			else
				shell->args[j] = ft_strjoin(expnd.pre, "");
			if (expnd.post)
				shell->args[j] = ft_strjoin(shell->args[j], expnd.post);
		}
		j++;
	}
}
