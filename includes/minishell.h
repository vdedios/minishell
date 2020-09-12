#ifndef MINISHELL_H
# define MINISHELL_H

# include <string.h>
# include <errno.h>
# include <dirent.h>
# include <sys/stat.h>
# include <signal.h>
# include "get_next_line_bonus.h"

typedef struct	s_shell{
	char		**commands;
	char		**args;
	char		**env;
}				t_shell;

char	**get_args(char *input);
char	*get_env(char **env, char *arg);
char	*search_binary(char *binary, char **paths);
int		ft_env(char **args, char **env);
int		ft_cd(char **arg, char **env);
int		ft_echo(char **args);
int		ft_pwd();
int		ft_unset(char *var, char **env);
int		ft_exit(char **exit);
void	signal_handler(int signal);

#endif
