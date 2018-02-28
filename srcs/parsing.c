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
	return (0);
}

int 				ft_parser(t_lexit *lexdat)
{
	t_lexit *tmp;

	tmp = lexdat;
	while (tmp)
	{
		if (tmp->lexem == 3 || tmp->lexem == 4 || tmp->lexem == 1)
		{
			if (tmp->next)
			{
				if (!tmp->next->to_exec)
					return (4);
			}
			else
				return (4);
		}
		tmp = tmp->next;
	}
	return (0);
}
