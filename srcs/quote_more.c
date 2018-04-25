#include "../includes/sh.h"

int            do_quotes(t_sh *sh, char quote)
{
    int            ret_stop[2];

    ret_stop[0] = 0;
    ret_stop[1] = 0;
    char buf2[2];

	(void)quote;
	del_quote(sh, quote);
	init_term();
	sh->buf = 0;
	sh->line->prompt_mode = 2;
	sh->line->cur_mod_pos = 6;
	while (!ret_stop[1])
	{
			reset_line_mode(sh);
			ft_prompt(3);
			while ((ret_stop[0] = read(0, &sh->buf, sizeof(int))))
			{
				buf2[0] = (char)sh->buf;
				buf2[1] = '\0';
				handle_key(sh);
				tputs(tgetstr("cd", NULL), 1, ft_pointchar);
				if (sh->buf == 10)
				{
					sh->line->cur_mod_pos++;
					sh->line->max_mod_size++;
					break ;
				}
				if (sh->buf == 3)
				{
					ft_putchar('\n');
					sh->line->prompt_mode = 0;
					return (0);
				}
				sh->buf = 0;
			}
			simple_quote_work(sh, &ret_stop[1], quote);
	}
	return (1);
}

int				quote_checker(char *input, t_sh *sh)
{
	size_t i;
	int sq;
	int dq;

  i = 0;
	sq = 0;
	dq = 0;
	while (i <= (ft_strlen(input)))
	{
		if (input[i] == '\'')
		{
			i++;
			sq++;
			while (input[i] && input[i] != '\'')
				i++;
			if (input[i] && input[i] != '\0')
				sq++;
		}
		if (input[i] && input[i] == '\"')
		{
			i++;
			dq++;
			while (input[i] && input[i] != '\"')
				i++;
		if (input[i] && input[i] != '\0')
			dq++;
		}
		i++;
	}
	if (sq % 2 != 0)
  		return (do_quotes(sh, '\''));
	if (dq % 2 != 0)
  		return (do_quotes(sh, '\"'));
	return (1);
}
