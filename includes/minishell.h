#ifndef MINISHELL_H
# define MINISHELL_H

# include <string.h>
# include <stdint.h>
# include <errno.h>
# include <dirent.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <signal.h>
# include <fcntl.h>
# include <limits.h>
# include "libft.h"

/*
** Basic structures
*/

typedef struct	s_shell{
	char		**instructions;
	char		*binary;
	char		**commands;
	char		**args;
	char		**env;
	int			stat_loc;
	int			previous_stat;
	int			is_binary;
}				t_shell;


/*
** Cleaning functions
*/

void	clean_matrix(char **matrix);
void	clean_commands(t_shell *shell);
void	clean_env(t_shell *shell);
void	clean_shell(t_shell *shell);


/*
** Error functions
*/

void	print_errors(t_shell *shell, char *msg, char *bin);


/*
** Utils functions
*/

int		ft_isspace(int c);
char	**ft_strdup_matrix(char **envp);
char	*absolute_bin_path(char *path, char *bin);
char	**add_env(char **variable, char **env, int n);
char	**realloc_matrix(char **envp, int additional);
char	**get_args(char *input);
char	*get_env(t_shell *env, char *arg);
char	*search_binary(t_shell *shell, char **paths);
char	*search_binary_in_pwd(t_shell *shell);
int		get_next_line(char **line);
int		find_redirections(t_shell *shell);
void	find_pipes(t_shell *shell);
int		check_builtin(t_shell *shell);
int		run_command(t_shell *shell);
int		check_permissions(t_shell *shell, char *path);
void	handle_shlvl(t_shell *shell);
char	*get_path(t_shell *shell);

/*
** Parsing functions
*/

char	*expansion(t_shell *shell, char *str);
char	*embrace_expansion(char *str);
char	*expand_var(char *env, t_shell *shell);
char    *mantain_expansion_spaces(char *str);
char	*parse_quotes(char *str);
char	*parse_backslash(char *str, short residual);
char	*parse_input(char *input);
short	is_special_char(char c);
short	is_space(char c);
short	is_alpha(char c);
short	check_prev_backslashes(char *str, int i);
int		n_special_chars(char *str, int opening, int closing, char quote);
char	**ft_split_non_escaped(char *input, char delimiter);
void	delete_environment(t_shell *shell, char *key, char **env);
char	*set_opening_braces(char *str);
char	*set_closing_braces(char *str);

/*
** Builtin functions
*/

int		ft_env(t_shell *shell, char **args);
int		ft_cd(t_shell *shell);
int		ft_echo(char **args);
int		ft_pwd();
int		ft_unset(t_shell *shell);
void	ft_exit(t_shell *shell);
int 	ft_export(t_shell *shell, char *last_arg);

/*
** Signal functions
*/

void	signal_handler_waiting(int signal);
void	signal_handler_running(int signal);

#endif
