/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rfabre <rfabre@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/25 01:35:08 by rfabre            #+#    #+#             */
/*   Updated: 2018/04/05 19:02:11 by jecarol          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# ifndef SH_H
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

typedef enum 				e_priorities
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
	// CHEVRONLEFT,
	// CHEVRONRIGHT,
	// DOUBLECHEVRONLEFT,
	// DOUBLECHEVRONRIGHT
}								t_priorities;

typedef struct				s_norm
{
	int						buf;
	int						ret;
	int						i;
}								t_norm;

typedef	struct			s_edit
{
	struct winsize 		sz;
	int						cursor_pos;
	int						max_size;
	char 						*line;
	// char					**line_split;
int 							select_mode;
	int       			    start_select;
	int	    	       	end_select;
	char 						*is_highlight;
	char						*left;
	char						*right;
	struct s_hstr			*hstr; //pointer to the last element added
	struct s_hstr			*curr; //pointer to current element of the history
}								t_edit;

typedef struct 	s_hstr
{
	char 					*cmd;
	struct s_hstr		*up;
	struct s_hstr		*down;
} 							t_hstr;

void ft_add_history(t_edit *line);
void ft_arrow_up(t_edit *line);
void ft_arrow_down(t_edit *line);

typedef struct			s_env
{
	char					*var;
	struct s_env		*next;
}							t_env;

typedef struct			s_lexit
{
	char					*input;
	char					**args;
	char					*command;
	int					prio;
	struct s_redir		*redirs;
	struct s_lexit		*left;
	struct s_lexit		*right;
	struct s_lexit		*next;
	struct s_lexit		*prev;
}							t_lexit;

typedef struct			s_redir
{
	int					redir_right;
	char					*right_target;
	int					redir_left;
	char					*left_target;
	struct s_redir		*next;
}							t_redir;

typedef struct			s_parsing
{
	int					index;
	int					anex;
	int					quote_checker;
	int					simpleq;
	int					doubleq;
	int					checker;
	int					redir_c;
	int					latest;
	int					subber;
	int					breaker;
	int					empty;
	char					*to_node;
	char					*to_node2;
	char					to_node_op[2];
	char					*ptr;
	char					*ptr2;
}							t_parsing;

typedef struct			s_fday
{
	int					in;
	int					out;
	int					saved_file;
	int					saved_in;
	int					saved_out;
	int					saved_err;
}							t_fday;

typedef struct			s_sh
{
	t_env					*env;
	t_lexit				*list;
	t_lexit				*lexdat;
	t_lexit				**execs;
	t_edit				*line;
	t_norm				*values;
	t_fday				fd;
}							t_sh;






struct winsize		ft_init(t_edit *line);
int					ft_pointchar(int c);
void ft_left_arrow(t_edit *line);
void ft_right_arrow(t_edit *line);
void ft_homekey(t_edit *line);
void ft_endkey(t_edit *line);
void ft_delete(t_edit *line);
void ft_insert(int buf, t_edit *line);
void ft_move_it(t_edit *line, int check);
void ft_line_reset(t_edit *line);
void ft_go_start(t_edit *line);
void ft_highlight(t_edit *line);
void ft_go_start(t_edit *line);
void ft_cut(t_edit *line);
void select_copy_cut(t_edit *line, int buf);
void ft_prompt(void);
void add_to_line(t_edit *line, int buf);
void handle_key(int buf, t_edit *line);
void ft_tokenize_it(t_edit *line, t_lexit **lexdat);
int 				ft_pre_parser(t_edit *line);
int 				parse_list(t_lexit *list);
void			ft_freetab(char **table);
void 				ft_free_lexdat(t_lexit *lexdat);
void				ft_env(char **cmd, t_env *env);
void				ft_execs(t_lexit *lexdat, t_env *env, t_edit *line);
char				**ft_set_paths(t_env *env);
int 			ft_errors(int code, char *cmd, char *arg);
char				**ft_prep_input(char *str);
char			**ft_fill_envp(t_env *env);

void			ft_print_env(t_env *env);
t_env			*add_env(char *var);
void			ft_push_env(t_env **lst, char *var);
t_lexit 			*ft_tree_it(t_lexit *lexdat, t_lexit *list, int prio);
int 				ft_isstrprint(char *str);
char				*find_cmd(char **apaths, char *cmd);
int				parsing_listing(t_lexit **list, char *input, t_env *env);
t_lexit			*add_node(char *input, t_env *env);
t_parsing		*init_data(void);
int				quote_checker(t_parsing *data, char *input);
int				check_first_node(t_parsing *data, char *input);
void				get_full_op(t_parsing *data, char *input);
void				execs_deep(t_lexit *list, t_env *env, t_sh *sh);



#endif
