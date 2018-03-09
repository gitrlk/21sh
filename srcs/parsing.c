#include "../includes/sh.h"


int 				ft_pre_parser(t_edit *line)
{
	int i;

	i = 0;
	while (line->line[i])
	{
		if (ft_strchr(OPERATOR, line->line[i]))
		{
			if (line->line[i] == '>')
			{
				if (line->line[i+1] == '<')
					return (1);
				if (line->line[i+1] == ';')
					return (6);
			}
			if (line->line[i] == '<')
			{
				if (line->line[i+1] == '>')
					return (2);
				if (line->line[i+1] == ';')
					return (6);
			}
			if (line->line[i] == ';')
			{
				if (line->line[i+1] == ';')
					return (3);
				if (line->line[i+1] == '|')
					return (5);
			}
		}
		i++;
	}
	line->line_split = ft_prep_input(line->line);
	return (0);
}

// int 				parse_list(t_lexit *list)
// {
// 	t_lexit *tmp;
//
// 	tmp = list;
// 	while (tmp)
// 	{
// 		if (tmp->prio == AND_OR || tmp->prio == PIPE)
// 			if (tmp->prev->prio != COMMAND && tmp->next->prio != COMMAND)
// 			 	return ()
// 		tmp = tmp->next;
// 	}
// }
