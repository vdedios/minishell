/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: migferna <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/18 18:20:56 by migferna          #+#    #+#             */
/*   Updated: 2021/02/18 18:20:59 by migferna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	clean_matrix(char **matrix)
{
	if (matrix)
	{
		while (*matrix)
		{
			free(*matrix);
			matrix++;
		}
	}
}

void	clean_env(t_shell *shell)
{
	clean_matrix(shell->env);
	free(shell->env);
	shell->env = NULL;
}

void	clean_commands(t_shell *shell)
{
	clean_matrix(shell->commands);
	free(shell->commands);
	shell->commands = NULL;
	clean_matrix(shell->args);
	free(shell->args);
	shell->args = NULL;
}

void	clean_shell(t_shell *shell)
{
	clean_commands(shell);
	clean_env(shell);
}
