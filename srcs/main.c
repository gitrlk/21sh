#include "../libft/libft.h"
#include <unistd.h>
#include <termios.h>


int main(int argc, char const *argv[] char **envp)
{
	int buf;
	struct termios attributes;
	(void)argc;
	(void)argv;

	buf = 0;
	tcgetattr(0, &attributes);
	attributes.c_lflag &= ~ICANON;
	attributes.c_lflag &= ~ECHO;
	tcsetattr(0, TCSADRAIN, &attributes);
	while (42)
	{
		read(0, &buf, 8);
		ft_putnbr(buf);
		ft_putchar('\n');
		buf = 0;
	}
	return 0;
}
