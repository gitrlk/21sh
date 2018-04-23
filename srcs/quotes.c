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
		sh->line->prompt_mode = 0;
        set_term_back();
        del_after_quote(sh);
        ft_putchar('\n');
    }
    else if (sh->buf == 10)
    {
      reset_line_mode(sh);
      sh->line->q_str = ft_freejoinstr(sh->line->q_str, "\n");
	  sh->buf = 0;
	  ft_putchar('\n');
    }
}


void 	del_quote(t_sh *sh)
{
    int i;
    int j;

    i = 0;
    j = 0;
	sh->line->q_str = ft_strnew(0);
    while (sh->line->line[i])
        i++;
	i--;
	while (sh->line->line[i] && (sh->line->line[i] != '\'' || sh->line->line[i] == '\"'))
		i--;
	if (sh->line->line[i] == '\'' || sh->line->line[i] == '\"')
    {
		i++;
		sh->line->q_str = ft_freejoinstr(sh->line->q_str, &sh->line->line[i]);
	}
    sh->line->q_str = ft_freejoinstr(sh->line->q_str, "\n");
	// ft_putstr("output qstr:   \n");
	// ft_putendl(sh->line->q_str);
	// ft_putstr("-------\n");
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

int            do_quotes(t_sh *sh, char quote)
{
    int            ret_stop[2];

    ret_stop[0] = 0;
    ret_stop[1] = 0;
    char buf2[2];

	(void)quote;
	del_quote(sh);
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
			simple_quote_work(sh, &ret_stop[1]);
	}
	return (1);
}

int				quote_checker(char *input, t_sh *sh)
{
	int i;
	int sq;
	int dq;

  	i = 0;
	sq = 0;
	dq = 0;
	while (input[i])
	{
		if (input[i] == '\'')
		{
			i++;
			sq++;
			while (input[i] && input[i] != '\'')
				i++;
			if (input[i] != '\0')
				sq++;
		}
		if (input[i] == '\"')
		{
			i++;
			dq++;
			while (input[i] && input[i] != '\"')
				i++;
		if (input[i] != '\0')
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
