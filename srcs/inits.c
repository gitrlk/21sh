#include "../includes/sh.h"

void init_line_edit(t_edit *line)
{
	ioctl(STDERR_FILENO, TIOCGWINSZ, &line->sz);
	line->select_mode = 0;
	line->start_select = 0;
	line->end_select = 0;
	line->prompt_mode = 0;
	line->q_str = NULL;
	line->quote_complete = 0;
	line->array_size = 0;
	line->is_highlight = ft_strnew(0);
}

void					init_structs(t_edit *line, t_fday *fd)
{
	line->hstr = NULL;
	ft_line_reset(line);
	init_line_edit(line);
	fd->saved_in = STDIN_FILENO;
	fd->saved_out = STDOUT_FILENO;
	fd->saved_err = STDERR_FILENO;
	fd->in = 0;
	fd->out = 1;
	fd->saved_fd = 0;
}

t_parsing		*init_data(void)
{
	t_parsing *data;

	data = ft_memalloc(sizeof(t_parsing));
	data->env = NULL;
	data->index = -1;
	data->anex = 0;
	data->len = 0;
	data->last = 0;
	data->simpleq = 0;
	data->doubleq = 0;
	data->checker = 0;
	data->latest = 0;
	data->subber = 0;
	data->breaker = 1;
	data->empty = 0;
	data->to_node = NULL;
	data->to_node_op[0] = '\0';
	data->to_node_op[1] = '\0';
	data->to_node_op[2] = '\0';
	return (data);
}

t_execs			*init_igo(t_sh *sh)
{
	t_execs		*igo;

	igo = ft_memalloc(sizeof(t_execs));
	igo->tmp = sh->list;
	igo->start = NULL;
	igo->copy = NULL;
	igo->head = NULL;
	igo->tmp2 = NULL;
	igo->exec_number = get_number(sh);
	sh->execs = NULL;
	return (igo);
}
