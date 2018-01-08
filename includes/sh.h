# ifndef SH_H
# define SH_H

# define BUILTIN "exit echo cd env setenv unsetenv"

# include "../libft/libft.h"
# include <sys/wait.h>
# include <sys/stat.h>
# include <signal.h>
# include <termios.h>
# include <sys/ioctl.h>
# include <curses.h>
# include <term.h>


int					ft_pointchar(int c);


typedef	struct		s_edit
{
	struct winsize 	sz;
	int             	cursor_pos;
	int             	line_number;
	int					max_size;
	char 					*line;
}							t_edit;

void ft_isarrow(char *buf, t_edit *line);

#endif
