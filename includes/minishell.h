#ifndef MINISHELL_H
# define MINISHELL_H

# include <string.h>
# include <errno.h>
# include <dirent.h>
# include <signal.h>
# include "get_next_line_bonus.h"

char	**get_args(char *input);
char	*get_path(char *arg, char **env);
int		ft_env(char **env);
int		ft_cd(char *arg);
void	signal_handler(int signal);

#endif
