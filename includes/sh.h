/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rfabre <rfabre@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/25 01:35:08 by rfabre            #+#    #+#             */
/*   Updated: 2018/05/03 15:38:01 by jecarol          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SH_H
# define SH_H

# define BUILTIN "exit echo cd env setenv unsetenv"
# define OPERATOR ">&;|<"

# include "../libft/libft.h"
# include <sys/wait.h>
# include <sys/stat.h>
# include <signal.h>
# include <termios.h>
# include <sys/ioctl.h>
# include <curses.h>
# include <term.h>
# include <fcntl.h>

typedef enum		e_priorities
{
	SEMICOLON,
	AND_OR,
	PIPE,
	REDIR_R,
	REDIR_RR,
	REDIR_L,
	HEREDOC,
	COMMAND,
	ARG,
	ERROR
}					t_priorities;

typedef	struct		s_edit
{
	struct winsize	sz;
	int				cursor_pos;
	int				cur_mod_pos;
	int				max_size;
	int				max_mod_size;
	int				select_mode;
	int				start_select;
	int				end_select;
	int				prompt_mode;
	int				quote_complete;
	int				array_size;
	char			*quote;
	char			*line;
	char			*heredoc;
	char			*is_highlight;
	char			*left;
	char			*right;
	char			*q_str;
	struct s_hstr	*hstr;
	struct s_hstr	*curr;
}					t_edit;

typedef struct		s_hstr
{
	char			*cmd;
	struct s_hstr	*up;
	struct s_hstr	*down;
}					t_hstr;

void				ft_add_history(t_edit *line);
void				ft_arrow_up(t_edit *line);
void				ft_arrow_down(t_edit *line);

typedef struct		s_env
{
	char			*var;
	struct s_env	*next;
}					t_env;

typedef struct		s_lexit
{
	char			*input;
	char			**args;
	char			*command;
	int				is_pipe;
	int				prio;
	int				first;
	int				agr;
	int				checker;
	int				fdsrc;
	int				fddst;
	int				fdclose;
	int				quote;
	struct s_redir	*redirs;
	struct s_lexit	*left;
	struct s_lexit	*right;
	struct s_lexit	*next;
	struct s_lexit	*prev;
}					t_lexit;

typedef struct		s_redir
{
	int				redir_right;
	char			*right_target;
	int				redir_left;
	char			*left_target;
	char			*endoff;
	struct s_redir	*next;
}					t_redir;

typedef struct		s_hdc
{
	int				ret_stop[2];
	int				hd;
	char			*tmp;
}					t_hdc;

typedef struct		s_heredoc
{
	int				fd;
	char			*path;
	int				random;
	char			*tmp;
}					t_heredoc;

typedef struct		s_parsing
{
	int				index;
	int				anex;
	int				check;
	int				len;
	int				last;
	int				wordsize;
	int				anex2;
	int				quote_checker;
	int				simpleq;
	int				doubleq;
	int				checker;
	int				redir_c;
	int				latest;
	int				subber;
	int				breaker;
	int				empty;
	t_env			*env;
	char			*to_node;
	char			to_node_op[3];
	char			*ptr;
	char			*ptr2;
	char			*content;
	char			*tmpn;
	char			*empty_input;
}					t_parsing;

typedef struct		s_fday
{
	int				in;
	int				out;
	int				saved_fd;
	int				saved_file;
	int				saved_in;
	int				saved_out;
	int				saved_err;
}					t_fday;

typedef struct		s_sh
{
	t_env			*env;
	t_lexit			*list;
	t_lexit			*lexdat;
	t_lexit			*execs;
	t_edit			*line;
	t_fday			fd;
	char			*hd_state;
	int				buf;
	int				buf2;
}					t_sh;

typedef struct		s_execs
{
	t_lexit			*tmp;
	t_lexit			*start;
	t_lexit			*copy;
	t_lexit			*head;
	t_lexit			*tmp2;
	int				exec_number;
}					t_execs;

typedef struct		s_cd
{
	char			tmp[1024 + 1];
	char			*cwd;
	char			*oldpwd;
}					t_cd;

typedef struct		s_insert
{
	char			*tmp;
	char			*tmp2;
	char			*tmp3;
	char			buf2[2];
	int				i;
}					t_insert;

typedef struct		s_split
{
	int				cnt;
	int				in_substring;
	int				i;
	int				nb_word;
	int				index;
	char			**t;
}					t_split;

int					ft_pointchar(int c);
void				ft_left_arrow(t_edit *line);
void				ft_right_arrow(t_edit *line);
void				ft_homekey(t_edit *line);
void				ft_endkey(t_edit *line);
void				ft_delete(t_edit *line);
void				ft_insert(int buf, t_edit *line);
void				ft_move_it(t_edit *line, int check);
void				ft_line_reset(t_edit *line);
void				ft_go_start(t_edit *line);
void				ft_highlight(t_edit *line);
void				ft_go_start(t_edit *line);
void				ft_cut(t_edit *line);
void				select_copy_cut(t_edit *line, int buf);
void				ft_prompt(int prompt);
void				add_to_line(t_edit *line, int buf);
void				handle_key(t_sh *sh);
void				ft_tokenize_it(t_edit *line, t_lexit **lexdat);
int					ft_pre_parser(t_edit *line);
int					parse_list(t_lexit *list);
void				ft_freetab(char **table);
void				ft_free_lexdat(t_lexit *lexdat);
void				ft_env(t_lexit *list, t_env **env, t_sh *sh);
char				**ft_set_paths(t_env *env);
int					ft_errors(int code, char *cmd, char *arg);
char				**ft_prep_input(char *str);
char				**ft_fill_envp(t_env *env);
void				ft_print_env(t_env *env);
t_env				*add_env(char *var);
void				ft_push_env(t_env **lst, char *var);
t_lexit				*ft_tree_it(t_lexit *lexdat, t_lexit *list, int prio);
int					ft_isstrprint(char *str);
char				*find_cmd(char **apaths, char *cmd);
int					parsing_listing(t_lexit **list, t_env *env, t_sh *sh);
t_lexit				*add_node(char *input, t_sh *sh);
t_parsing			*init_data(void);
int					quote_checker(char *input, t_sh *sh);
int					check_first_node(t_parsing *data, char *input);
void				get_full_op(t_parsing *data, char *input);
void				execs_deep(t_lexit *list, t_env **env, t_sh *sh);
void				free_list(t_lexit *list);
char				**copypasta(char **src, int i);
void				execs(t_lexit *list, t_env **env, t_sh *sh);
int					get_prio(char *str, char **command, char **apaths);
void				ft_echo(t_lexit *list, t_env **env);
void				ft_cd(char **args, t_env **env);
void				exec_unsetenv(char **commands, t_env **venv);
void				exec_setenv(char **cmd, t_env **env);
int					ft_modify_tenv(t_env **venv, char *new, char *contents);
int					find_t_env(t_env **venv, char *commands);
void				ft_lst_add_tenv(t_env **alst, t_env *new);
int					find_t_env_array(char *env, char *search);
void				ft_lst_add_tenv(t_env **alst, t_env *new);
void				exec_no_fork(t_lexit *list, t_env **env, t_sh *sh);
int					check_if_builtin(t_lexit *list);
void				listen_signal(void);
void				init_term(void);
void				set_term_back(void);
int					switch_fd(t_lexit *list, t_sh *sh, int *mod);
void				reset_fd(t_sh *sh, int mod);
void				do_pipes(t_lexit *list, t_env **env, t_sh *sh);
int					get_segment_number(t_sh *sh);
int					double_check(t_lexit *lst);
t_lexit				*copy_segment(t_lexit *src);
int					check_semi(t_sh *sh, t_lexit *lst);
void				execute(t_sh *sh);
void				execute_builtin(t_lexit *list, t_env **env, t_sh *sh);
void				execute_binary(t_lexit *list, t_env **env, t_sh *sh);
void				assign_redir(t_lexit *list, t_sh *sh);
void				do_heredoc(t_lexit *list, t_sh *sh);
void				init_valhd(t_hdc *valhd);
void				heredoc_work(t_sh *sh, t_lexit *list, t_hdc *valhd);
t_execs				*init_igo(t_sh *sh);
void				init_structs(t_edit *line, t_fday *fd);
int					get_execs(t_sh *sh);
void				cut_list(t_execs *igo);
void				exec_segment(t_sh *sh, t_execs *igo);
void				exec_last_segment(t_sh *sh, t_execs *igo);
int					free_igo(t_execs *igo, int mod);
void				trim_redir(t_lexit *list);
void				swap_quote(t_execs *igo, t_sh *sh);
char				**ft_replace_quote(char **array, t_sh *sh, char **input);
char				**ft_strsplit_21(char const *s, char c, char d, char e);
void				clean_list(t_lexit *tmp);
void				del_quote(t_sh *sh, char quote);
void				reset_line_mode(t_sh *sh);
void				simple_quote_work(t_sh *sh, int *ret_stop, char quote);
int					exec_cd_env(t_env **env, char *search,
					int mode, char **args);
int					find_t_env_str(char *venv, char *str);
void				do_cd(char *path, t_env **venv, int mode);
int					ft_get_egal_pos(char *vartoadd);
void				ft_refresh_link(t_env **tmp, char *vartoadd);
void				ft_refresh_link_cd(t_env **tmp, char *vartoadd);
void				update_list(t_lexit *list, int i, t_env *env);
t_env				*ft_copy_list(t_env *env);
void				ft_env_with_var(t_env **env, char *vartoadd);
void				exec_env(t_lexit *list, int i, t_env *new_env, t_sh *sh);
int					isnumber(char *s);
void				free_env(t_env *lst);
char				*get_quote_str(char *line);
void				ft_wordleft(t_edit *line);
void				ft_wordright(t_edit *line);
void				print_cpy(int buf, t_edit *line);
int					check_copy(int buf);
int					ft_isstrprint(char *str);
void				init_redirs(t_lexit *node);
void				init_valhd(t_hdc *valhd);
void				get_eof(t_lexit *node, t_sh *sh);
void				do_heredoc(t_lexit *list, t_sh *sh);
int					open_heredoc(t_sh *sh);
void				hd_sig(t_hdc *valhd, t_lexit *list, t_sh *sh);
int					test_l_r(t_parsing *data, char *input,
					t_lexit **list, t_sh *sh);
int					its_over(t_insert *vals, t_parsing *data, char *input);
int					node_lro(char *input, t_lexit **list,
					t_parsing *data, t_sh *sh);
int					check_left_right(char *input, t_parsing *data);
void				get_redir(t_lexit *node, t_sh *sh);
t_split				init_split(char const *s, char c, char d, char e);
int					ft_cnt_parts(const char *s, char c, char d, char e);
void				init_node(t_lexit *tmp);
int					is_quote_closed(char const *s, char quote);
int					ft_wlen(const char *s, char c);
void				match_quotes(t_split *vals, const char *s, char d, char e);
void				lol(t_sh *sh, t_execs *igo);
int					setup_parsing(t_parsing *data, t_env *env, t_sh *sh);
void				ignore_quotes(char *s, t_parsing *data, int mod);
int					look_for_op(t_sh *sh, int pos);
int					ignore_first_semi(t_sh *sh);
int					parsing_error(t_parsing **data);
void				kick_semi(t_lexit *list);
void				ft_left_arrow_q(t_edit *line);
void				ft_right_arrow_q(t_edit *line);
void				ft_left_arrow_select_mode(t_edit *line);
void				go_down(t_edit *line);
void				replace_quote(t_lexit *node, t_sh *sh);
t_lexit				*add_node_proxy(char *input, t_sh *sh);
void				ignore_quotes_more(char *s, t_parsing *data);
int					return_free(char *tmp, char *tmp1);

#endif
