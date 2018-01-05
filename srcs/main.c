#include "../libft/libft.h"
#include <unistd.h>
#include <termios.h>

void			ft_prompt(void)
{
	char		cwd[1024];

	getcwd(cwd, sizeof(cwd));
	ft_putstr(TURQUOISE);
	ft_putstr(cwd);
	ft_putstr("$>");
	ft_putstr(DEFAULT);
}

void			ft_init()
{
	struct termios attributes;

	tcgetattr(0, &attributes);
	attributes.c_lflag &= ~ICANON;
	attributes.c_lflag &= ~ECHO;
	tcsetattr(0, TCSADRAIN, &attributes);
}

int				main(int ac, char **av, char **envp)
{
	int buf;
	(void)ac;
	(void)av;
	(void)envp;

	buf = 0;
	ft_init();
	while (42)
	{
		ft_prompt();
		read(0, &buf, 8);
		ft_putchar(buf);
		// ft_putchar('\n');
		buf = 0;
	}
	return 0;
}
