#include "sh.h"

void			ft_echo(t_lexit *list)
{
	int			i;

	if (!list->args[1])
		ft_putchar('\n');
	if (list->args[1])
	{
		i = (ft_strcmp(list->args[1], "-n") == 0 ? 2 : 1);
		while (list->args[i])
		{
			ft_putstr(list->args[i]);
			if (list->args[i + 1])
				write(1, " ", 1);
			i++;
		}
		if (ft_strcmp(list->args[1], "-n") != 0)
			write(1, "\n", 1);
	}
}
