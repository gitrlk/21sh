/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rfabre <rfabre@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/25 01:35:08 by rfabre            #+#    #+#             */
/*   Updated: 2018/03/05 18:41:13 by rfabre           ###   ########.fr       */
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

enum
{
	SEMICOLON,
	PIPE,
	DOUBLEPIPE,
	CHEVRONLEFT,
	CHEVRONRIGHT,
	DOUBLECHEVRONLEFT,
	DOUBLECHEVRONRIGHT,
	DOUBLESPER
};

typedef struct			s_norm
{
	int					buf;
	int					ret;
	int					i;
}							t_norm;

typedef struct		s_data
{
	int							win_col;
	int							win_line;
	struct termios	term;
	struct termios	save_term;
	char						*name_term;
	char            *line;
}									t_data;

t_data						*g_data;

typedef	struct		s_edit
{
	struct winsize 	sz;
	int						cursor_pos;
	int						max_size;
	char 					*line;
	int 					select_mode;
	int           start_select;
	int	           	end_select;
	char 					*is_highlight;
	struct s_hstr *hstr; //pointer to the last element added
	struct s_hstr *curr; //pointer to current element of the history
}							t_edit;

typedef struct 	s_hstr
{
	char 					*cmd;
	struct s_hstr *up;
	struct s_hstr *down;
} 							t_hstr;

void ft_add_history(t_edit *line);
void ft_arrow_up(t_edit *line);
void ft_arrow_down(t_edit *line);

typedef struct			s_env
{
	char						*var;
	struct s_env		*next;
}							t_env;

typedef struct		s_lexit
{
	char					*input;
	char					**to_exec;
	char					**allpaths;
	int						lexem;
	struct s_lexit		*next;
}							t_lexit;




// REFLEXION FUTURE STRUCTURE POUR execution
//
// typedef struct			s_ast
// {
// 	char					*content;
// 	char					**to_exec;
// 	char					**env;
// 	int           exit_return;
// 	int           priorite_lexem;
// 	int						lexem;
// 	struct s_ast		*left;
// 	struct s_ast		*right;
// }							t_ast;



int search_input(char **input, int prio);
void ft_init();
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
int 				ft_parser(t_lexit *lexdat);
void			ft_freetab(char **table);
void 				ft_free_lexdat(t_lexit *lexdat);
void				ft_env(char **cmd, t_env *env);
void				ft_execs(t_lexit *lexdat, t_env *env, t_edit *line);
char				**ft_set_paths(t_env *env);
int 			ft_errors(int code, char *cmd, char *arg);


void			ft_print_env(t_env *env);
t_env			*add_env(char *var);
void			ft_push_env(t_env **lst, char *var);
void				ft_signal(void);
void				set_termm_back(int i);
void				set_termm_clear(int i);
void				set_termm_quit(int i);
void				ft_resize(int i);

#endif
