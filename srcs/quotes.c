#include "../includes/sh.h"

void			do_simple_quotes(t_sh *sh)
{
	int			ret_stop[2];

	ret_stop[0] = 0;
	ret_stop[1] = 0;
	init_term();
	while (!ret_stop[1])
	{
		ft_prompt(3);
		while ((ret_stop[0] = read(0, &sh->buf, sizeof(int))))
		{
			handle_key(sh->buf, sh->line, 2);
			if (sh->buf == 39)
				ret_stop[1] = 1;
			if (sh->buf == '\n' || sh->buf == 3)
				break ;
			sh->buf = 0;
		}
		ft_putchar('\n');
	}
	set_term_back();
}

int				quote_checker(t_parsing *data, char *input, t_sh *sh)
{
	data->quote_checker = 0;
	while (input[data->quote_checker])
	{
		if (input[data->quote_checker] == '\'')
			data->simpleq++;
		if (input[data->quote_checker] == '\"')
			data->doubleq++;
		if (input[data->quote_checker + 1] == '\0')
		{
			if (data->simpleq % 2)
				do_simple_quotes(sh);
				// return (ft_errors(2, NULL, NULL));
			if (data->doubleq % 2)
				// do_double_quotes();
				return (ft_errors(3, NULL, NULL));
		}
		data->quote_checker++;
	}
	return (1);
}
