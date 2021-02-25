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
	char		**commands;
	char		**args;
	char		**env;
	char		*binary;
	char		*prompt;
	int			stat_loc;
	int			previous_stat;
	int			is_binary;
}				t_shell;


/*
** Cleaning functions
*/

void	clean_matrix(char **matrix);
void	clean_instructions(t_shell *shell);
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
void	to_lower_in(char *input);

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
** Expansion-utils functions
*/

int		count_keys_to_scape(char *str, char key);
char	*escape_char(char *str, char key);
char	*append_expanded(char *buff, char *env);
void	escape_char_safe(char **value, char c);

/*
** Quotes-utils functions
*/

char	*alloc_in_quotes(char *str, char quote, int opening, int closing);
void	handle_quote_error(char quote);
char	*get_string_between_quotes(char *str, int opening,
										int closing, char quote);
char	*find_closing_quote(char *str, char quote
								, int opening, int *closing);

/*
** Split_non_escaped-utils functions
*/

short	is_whitespace(char c);
short	is_delimiter(char input, char delimiter);
int		count_args(char *input, char delimiter);

/*
** Redirections-utils functions
*/

int		redirections_append(t_shell *shell, size_t it);
int		redirections_output(t_shell *shell, size_t it);
short	redirection_exists(t_shell *shell, size_t it);

/*
** Builtin functions
*/

int		ft_env(t_shell *shell, char **args);
int		ft_cd(t_shell *shell);
int		ft_echo(char **args);
int		ft_pwd(t_shell *shell);
int		ft_unset(t_shell *shell);
void	ft_exit(t_shell *shell);
int 	ft_export(t_shell *shell, char *last_arg);

/*
** Builtin-cd utils functions
*/

void	set_path(char *path, const char *key, t_shell *shell);
void	dir_err(t_shell *shell, char *path, char *err);
void	change_dir(char *path, t_shell *shell);
void	change_dir_error(t_shell *shell, char *path);
short	home_not_exists(t_shell *shell, char *path);
void	update_olddir(t_shell *shell, char *oldpwd);
short	many_arguments(t_shell *shell);
int		is_symbolic_link(char *path);

/*
** Builtin-export utils functions
*/

size_t  is_bigger(char *s1, char *s2);
char	**sort_alpha(char **envp);
short	is_escapable_char_export(char c);
int		count_special_chars(char *str);
char	*add_quotes_and_backslash(char *str);
int     ft_strncmp_equal(char *str1, char *str2, int len);
short	is_num(char c);
short	is_forbidden_char(char *str, int i);
short	has_valid_name(char *str);
short	not_valid_keyname(t_shell *shell, char *var, char *command);
char	**process_envs(char **env);
size_t	print_sorted_env(t_shell *shell);
void	export_values(t_shell *shell, char *last_arg, int j);

/*
** Signal functions
*/

void	signal_handler_waiting(int signal);
void	signal_handler_running(int signal);

/*
** Shell functions
*/

void	minishell(char *line, t_shell *shell);
char	*last_arg(char *arg);
char	*update_last_arg(char **args);
char	*append_pwd(char *value);
char	*to_lower(char *input);
int		exec_export(t_shell *shell);
int		exec_env(t_shell *shell);
char	*get_var_key(char *line, int it);
short	contain_spaces(char *value);
char	*add_space(char *line, char *output, size_t *it, char redir);
size_t	additional_spaces(char *line);
char	*inject_spaces(char *line);
char	*safe_allocate(char *line, char *(*f)(char *));

/*
** Validator functions
*/

int		validate_input(t_shell *shell, char *line);
char	*post_to_token(t_shell *shell, char *line, int it, char token);
short	prior_to_token(char *line, int it, char token);
short	nothing_after_pipe(char *line, int it);
int		get_validator_err(t_shell *shell,
							char *line, char separator, int it);
void	safe_print_err(t_shell *shell, char *key);

#endif