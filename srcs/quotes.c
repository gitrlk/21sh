#include "../includes/sh.h"

void del_after_quote(t_sh * sh)
{
    int i;
    char *tmp;

    i = 0;
    while (sh->line->q_str[i])
        i++;
    i--;
    while (sh->line->q_str[i] && (sh->line->q_str[i] != '\''))
        i--;
    tmp = ft_strsub(sh->line->q_str, 0 , (i));
    ft_strdel(&sh->line->q_str);
    sh->line->q_str = tmp;
}

void simple_quote_work(t_sh *sh, int ret_stop[2])
{
    // if (sh->buf == '\n')
    //     reset_line_mode(sh);
    if (ft_strchr(sh->line->q_str, '\''))
    {
            ret_stop[1] = 1;
            set_term_back();
            del_after_quote(sh);
            sh->line->quote_complete = 1;
            ft_putstr(sh->line->q_str);
    }
}

void del_quote(t_sh *sh)
{
    int i;
    int j;
    char new[1024 + 1];
    i = 0;
    j =    0;
    while (sh->line->line[i] && sh->line->line[i] != '\'')
        i++;
    while (sh->line->line[i])
    {
        if (sh->line->line[i] != '\'')
        {
                new[j] = sh->line->line[i];
                j++;
        }
        // else
        // {
        //     sh->line->max_size =-1;
        //     sh->line->cursor_pos =-1;
        // }

        i++;
    }
    new[j] = '\n';
    new[j + 1] = '\0';
    sh->line->q_str = ft_strdup(new);
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

void            do_simple_quotes(t_sh *sh, t_parsing *data)
{
    int            ret_stop[2];

    ret_stop[0] = 0;
    ret_stop[1] = 0;
    del_quote(sh);
    init_term();
	 sh->line->prompt_mode = 2;
    while (!ret_stop[1])
    {
        // reset_line_mode(sh);
        ft_prompt(3);
        while ((ret_stop[0] = read(0, &sh->buf, sizeof(int))))
        {
            handle_key(sh);
            tputs(tgetstr("cd", NULL), 1, ft_pointchar);
            if (sh->buf == '\n')
                break ;
            if (ft_isprint(sh->buf) || sh->buf == 10)
                sh->line->q_str = ft_freejoinstr(sh->line->q_str, ascii_to_char(sh->buf));
            if (sh->buf == 3)
            {
                data->quote_checker = 1;
                sh->line->quote_complete = 0;
                set_term_back();
                ret_stop[1] = 1;
            }
            sh->buf = 0;
        }
        simple_quote_work(sh, ret_stop);
    }
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
				do_simple_quotes(sh, data);
				// return (ft_errors(2, NULL, NULL));
			if (data->doubleq % 2)
				// do_double_quotes();
				return (ft_errors(3, NULL, NULL));
		}
		data->quote_checker++;
	}
	return (1);
}
