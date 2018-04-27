#include "../includes/sh.h"

void			std_move_it(t_insert *vals, t_edit *line, int check)
{
	while (vals->i < line->max_size)
	{
		ft_left_arrow(line);
		vals->i++;
	}
	if (check == 0)
	{
		line->cursor_pos--;
		line->max_size--;
	}
	ft_putstr_fd(line->line, STDOUT_FILENO);
	line->cursor_pos = ft_strlen(line->line) + 2;
	tputs(tgetstr("cd", NULL), 1, ft_pointchar);
}

void			ft_move_it(t_edit *line, int check)
{
	t_insert	vals;

	vals.i = 0;
	vals.tmp = NULL;
	if (line->prompt_mode == 0 || line->prompt_mode == 1)
		std_move_it(&vals, line, check);
	else if (line->prompt_mode == 2)
	{
		while (vals.i < (line->max_mod_size - 6))
		{
			ft_left_arrow(line);
			vals.i++;
		}
		tputs(tgetstr("cd", NULL), 1, ft_pointchar);
		if (check == 0)
		{
			line->cur_mod_pos--;
			line->max_mod_size--;
		}
		vals.tmp = get_quote_str(line->q_str);
		ft_putstr_fd(vals.tmp, STDOUT_FILENO);
		line->cur_mod_pos = ft_strlen(vals.tmp) + 6;
		line->max_mod_size = ft_strlen(vals.tmp) + 6;
		ft_strdel(&vals.tmp);
	}
}

void		print_cpy(int buf, t_edit *line)
{
	char		str[5];
	char		tmp[2];
	int			i = 0;

	str[0] = buf % 128;
	str[1] = buf >> 8;
	str[2] = buf >> 16;
	str[3] = buf >> 24;
	str[4] = '\0';
	while (str[i])
	{
		tmp[0] = str[i];
		tmp[1] = '\0';
		add_to_line(line, (int)str[i]);
		i++;
	}
}

int		check_copy(int buf)
{
	char		check[4];
	int			i;

	i = 0;
	check[0] = buf % 128;
	check[1] = buf >> 8;
	check[2] = buf >> 16;
	check[3] = buf >> 24;
	while (i < 4)
	{
		if ((int)check[i] > 126 || (int)check[i] < 32)
			return (0);
		i++;
	}
	return (1);
}
