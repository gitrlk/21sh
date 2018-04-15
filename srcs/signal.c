#include "../includes/sh.h"

void			sig_int(int i)
{
	i = 0;
}

void			listen_signal(void)
{
	signal(SIGINT, sig_int);
}

void				init_term(void)
{
	const char			*name;
	struct termios		term;

	if (!(name = getenv("TERM")))
		ft_errors(8, "terminal can't be set : specify \"TERM\" variable", NULL);
  if (tgetent(NULL, name) == ERR)
		ft_errors(8, "terminal can't be set : term unknow", NULL);
	if (tcgetattr(0, &term) == -1)
		ft_errors(8, "tcgetattr", NULL);
	term.c_lflag &= ~(ICANON | ECHO);
	term.c_cc[VMIN] = 1;
	term.c_cc[VEOF] = 4;
	term.c_cc[VINTR] = 2;
	if (tcsetattr(0, TCSADRAIN, &term) == -1)
		ft_errors(8, "tcgetattr", NULL);
}

void				set_term_back(void)
{
	const char			*name;
	struct termios		term;

	if (!(name = getenv("TERM")))
		ft_errors(8, "terminal can't be set : specify \"TERM\" variable", NULL);
	if (tgetent(NULL, name) <= 0)
		ft_errors(8, "terminal can't be set : term unknow", NULL);
	if (tcgetattr(0, &term) == -1)
		ft_errors(8, "tcgetattr", NULL);
	term.c_lflag |= (ECHO);
	term.c_lflag |= (ICANON);
	term.c_lflag &= ~(ECHOCTL);
	term.c_cc[VMIN] = 1;
	term.c_cc[VEOF] = 4;
	term.c_cc[VINTR] = 3;
	if (tcsetattr(0, TCSADRAIN, &term) == -1)
		ft_errors(8, "tcgetattr", NULL);
}
