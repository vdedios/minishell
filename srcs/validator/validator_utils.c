/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: migferna <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/12 10:18:23 by migferna          #+#    #+#             */
/*   Updated: 2021/02/22 16:15:45 by migferna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char		*post_to_token(t_shell *shell, char *line, int it, char token)
{
	char	*key;
	char	*value;
	char	*tmp;

	if (token == '>')
		while (line[it++])
			if (line[it] == '}' && line[it - 1] != ' ')
			{
				key = get_var_key(line, it);
				value = expand_var(key, shell);
				if (contain_spaces(value))
				{
					free(value);
					tmp = ft_strjoin("$", key);
					free(key);
					return (tmp);
				}
				free(key);
				free(value);
			}
	return (NULL);
}

short	prior_to_token(char *line, int it, char token)
{
	int aux_it;

	aux_it = it;
	while (aux_it > 0 && line[aux_it] == ' ')
		aux_it--;
	if (token == '>' || token == '<')
		return (aux_it > 0 && aux_it != it &&
				(line[aux_it] == '>' ||
				line[aux_it] == '<'));
	else
	{
		return (aux_it < 1 ||
				line[aux_it] == ';' ||
				line[aux_it] == '>' ||
				line[aux_it] == '<' ||
				line[aux_it] == '|');
	}
	return (0);
}

short	nothing_after_pipe(char *line, int it)
{
	if ((it - 2) >= 0 && *(line - 2) == '\\')
		return (0);
	while (*line && *line == ' ')
		line++;
	if (!*line)
		return (1);
	return (0);
}

int		get_validator_err(t_shell *shell,
		char *line, char separator, int it)
{
	if (separator == ';')
		print_errors(shell, "syntax error near unexpected token `;'", NULL);
	else if (separator == '|')
		print_errors(shell, "syntax error near unexpected token `|'", NULL);
	else if (separator == '>' && line[it + 1] == '>')
		print_errors(shell, "syntax error near unexpected token `>>'", NULL);
	else if (separator == '>')
		print_errors(shell, "syntax error near unexpected token `>'", NULL);
	else if (separator == '<' && line[it + 1] == '<')
		print_errors(shell, "syntax error near unexpected token `<<'", NULL);
	else if (separator == '<')
		print_errors(shell, "syntax error near unexpected token `<'", NULL);
	shell->stat_loc = 2;
	return (1);
}

void		safe_print_err(t_shell *shell, char *key)
{
	char	*tmp;

	tmp = ft_strjoin(key, ": ambiguous redirect");
	print_errors(shell, tmp, NULL);
	free(tmp);
	free(key);
}
