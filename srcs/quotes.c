#include "../includes/sh.h"

void reset_line_mode(t_sh *sh)
{
	sh->line->cur_mod_pos = 6;
	sh->line->max_mod_size = 6;
}

void del_after_quote(t_sh * sh)
{
    int i;
    char *tmp;

    i = 0;
    while (sh->line->q_str[i])
        i++;
    i--;
    // ft_putchar(sh->line->q_str[i]);
    while (sh->line->q_str[i] && (sh->line->q_str[i] != '\''))
        i--;
    // ft_putchar(sh->line->q_str[i]);
    tmp = ft_strsub(sh->line->q_str, 0 , (i));
    // ft_putstr("RESULT:");
    // ft_strdel(&sh->line->q_str);
    sh->line->q_str = tmp;

}

void simple_quote_work(t_sh *sh, int *ret_stop)
{
    // ft_putstr("input:");
    // ft_putendl(sh->line->q_str);
    if (sh->buf == 3)
    {
        *ret_stop = 1;
        // ft_strdel(&sh->line->q_str);
        sh->line->quote_complete = 0;
        sh->line->prompt_mode = 0;
        set_term_back();
    }
    if (ft_strchr(sh->line->q_str, '\''))
    {
        *ret_stop = 1;
        set_term_back();
        del_after_quote(sh);
        sh->line->quote_complete = 1;
        sh->line->prompt_mode = 0;
        ft_putchar('\n');
    }
    else if (sh->buf == 10)
    {
      reset_line_mode(sh);
      ft_putchar('\n');
      sh->line->q_str = ft_freejoinstr(sh->line->q_str, "\n");
    }
}

int del_quote(t_sh *sh)
{
    int i;
    int j;
    char new[1024 + 1];
		int start;

    i = 0;
    j = 0;
    while (sh->line->line[i] && sh->line->line[i] != '\'')
        i++;
		start = i + 1;
    while (sh->line->line[i + 1])
    {
        new[j] = sh->line->line[i + 1];
        j++;
        i++;
				if (sh->line->line[i + 1] == '\'')
        {
					// ft_putnbr(i);
				sh->line->quote_complete = 1;
				new[j] = '\0';
				sh->line->q_str = ft_strsub(sh->line->line, start, j);
				return (0);

			}
    }
    new[j] = '\n';
    new[j + 1] = '\0';
    sh->line->q_str = ft_strdup(new);
		return (1);
}



char *ascii_to_char(int c)
{
    char *ret;
    char tmp[2];

    tmp[0] = (char)c;
    tmp[1] = '\0';
    ret = ft_strdup(&tmp[1]);
    return(ret);
}

void            do_simple_quotes(t_sh *sh)
{
    int            ret_stop[2];

    ret_stop[0] = 0;
    ret_stop[1] = 0;
    char buf2[2];

    if (del_quote(sh))
		{
			init_term();
			sh->line->prompt_mode = 2;
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
						if (sh->buf == 10 || sh->buf == 3)
								break ;
						if (ft_isprint(sh->buf) || sh->buf == 10)
							sh->line->q_str = ft_freejoinstr(sh->line->q_str, buf2);
							// ft_putendl(sh->line->q_str);
						sh->buf = 0;
					}
					simple_quote_work(sh, &ret_stop[1]);
			}
		}
}

int				quote_checker(char *input, t_sh *sh)
{
	int i;

  i = 0;
	while (input[i])
	{
		if (input[i] == '\'')
    {
      do_simple_quotes(sh);
      break;
    }
		if (input[i] == '\"')
		{
      ;
    }
		i++;
	}
	return (1);
}
