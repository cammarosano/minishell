#ifndef HEADER_H
# define HEADER_H

# include "libft.h"
# include <stdio.h>
# include <unistd.h>
# include <sys/wait.h>
# include <sys/errno.h>
# include <sys/stat.h>
# include <string.h>
# include <fcntl.h>
# include <signal.h>
# include <readline/readline.h>
# include <readline/history.h>

# define PROMPT "minishell$ "
# define HEREDOC_FILE ".temp_heredoc_file"

# define DOLLAR_SIGN -2
# define PIPE -3
# define SPACEBAR -4
# define LESS_THAN -5
# define GREATER_THAN -6

enum	e_states
{
	s_text,
	s_dquote,
	s_squote
};

typedef struct s_shell_env
{
	char			**envp;
	unsigned char	question_mark;
	t_list			*pipeline;
	t_list			*hd_files;
}				t_sh_env;

typedef struct s_command
{
	char	**argv;
	t_list	*redirections;
}				t_command;

typedef struct s_redirection
{
	int		n;
	int		op;
	char	*file;
}				t_redir;

enum	e_redirection_ops
{
	re_input,
	re_heredoc,
	re_output,
	re_output_append
};

// environment

int		setup_env(t_sh_env *shell_env, char **envp);
int		find_var_index(char **envp, char *var);
int		set_var(t_sh_env *shell_env, char *var_name, char *value);
char	*expand_var(char **envp, char *var);
void	remove_var(char *var_name, t_sh_env *shell_env);

// signal handling

void	setup_signal_handlers(void);

// parser

char	*pre_processor(char *line);
t_list	*parse_line(char *line);
t_list	*split_by_pipe(char *line);
int		parse_redirections(t_command *cmd);
void	remove_arg_from_argv(char **argv);
t_redir	*str2redir_struct(char **arg);

// expansion

int		make_var_expansions(t_command *command, t_sh_env *shenv);
char	*expand_str(char *str, t_sh_env *shell_env);
char	*parse_var_name(char **str);

// execution

int		execute_line(t_sh_env *shell_env);
int		get_here_docs(t_list *pipeline, t_list **hd_files);
char	*create_heredoc(char *word, t_list **hd_files);
int		run_pipeline(t_list *lst, t_sh_env *shell_env, int n);
int		resolve_path(char *command, char **path, char **envp);
int		process_redirections_list(t_list *lst);
int		is_builtin(char *command_name);
int		run_builtin(int builtin_index, t_command *command, t_sh_env *shenv);
void	exec_bin(t_command *command, t_sh_env *shenv);
int		exit_code_from_child(int status);

// builtins

int		builtin_env(char **argv, t_sh_env *shell_env);
int		builtin_echo(char **argv, t_sh_env *shell_env);
int		builtin_pwd(char **argv, t_sh_env *shell_env);
int		builtin_cd(char **argv, t_sh_env *shell_env);
int		builtin_export(char **argv, t_sh_env *shell_env);
int		builtin_exit(char **argv, t_sh_env *shell_env);
int		builtin_unset(char **argv, t_sh_env *shell_env);
int		is_valid_name(char *var);
void	print_error_msg_name(char *arg, char *builtin);

// clear memory

void	clear_memory(t_sh_env *shell_env);
int		clear_mem_exit(t_sh_env *shell_env, int exit_code);
void	clear_command(void *ptr);
void	clear_redirection(void *ptr);
void	delete_file(void *file_name);

// errors

void	ft_perror(char *func_name);
int		ft_perror_ret(char *func_name, int return_value);

#endif
