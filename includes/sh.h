/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rfabre <rfabre@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/25 01:35:08 by rfabre            #+#    #+#             */
/*   Updated: 2018/01/25 20:44:12 by rfabre           ###   ########.fr       */
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

enum
{
	SEMICOLON,
	PIPE,
	DOUBLEPIPE,
	CHEVRONLEFT,
	CHEVRONRIGHT,
	DOUBLECHEVRONLEFT,
	DOUBLECHEVRONRIGHT,
	ESPER,
	DOUBLESPER
};

typedef	struct		s_edit
{
	struct winsize 	sz;
	int					cursor_pos;
	int					max_size;
	char 					*line;
	int 					select_mode;
	int           		start_select;
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
	char					*var;
	struct s_env		*next;
}							t_env;




typedef struct			s_lexit
{
	char					*input;
	int					lexem;			//0 = input / 1 = operator
	struct s_lexit		*next;
}							t_lexit;




struct winsize		ft_init(t_edit *line);
int					ft_pointchar(int c);
void ft_isarrow(char *buf, t_edit *line);
void ft_left_arrow(char *buf, t_edit *line);
void ft_right_arrow(char *buf, t_edit *line);
void ft_homekey(char *buf, t_edit *line);
void ft_endkey(char *buf, t_edit *line);
void ft_delete(char *buf, t_edit *line);
void ft_insert(char *buf, t_edit *line);
void ft_move_it(t_edit *line, char *buf, int check);
void ft_line_reset(t_edit *line);
void ft_go_start(t_edit *line, char *buf);
void ft_highlight(t_edit *line, char *buf);
void ft_go_start(t_edit *line, char *buf);
void ft_cut(t_edit *line, char *buf);
void select_copy_cut(t_edit *line, char *buf);
void ft_prompt(void);
void add_to_line(t_edit *line,char *buf);
void handle_key(char *buf, t_edit *line);

void			ft_print_env(t_env *env);
t_env			*add_env(char *var);
void			ft_push_env(t_env **lst, char *var);

#endif
