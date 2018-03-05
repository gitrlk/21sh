/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jecarol <jecarol@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/26 20:14:55 by jecarol           #+#    #+#             */
/*   Updated: 2018/03/05 18:43:14 by rfabre           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

void					ft_print_lexdat(t_lexit *lexdat)
{
	t_lexit			*tmp;
	int				i;

	i = 0;
	tmp = lexdat;
	while (tmp)
	{
		if (tmp->to_exec)
		{
			while (tmp->to_exec[i])
			{
				ft_putstr("commands-> ");
				ft_putstr(tmp->to_exec[i]);
				ft_putchar('\n');
				i++;
			}
			i = 0;
		}
		ft_putstr("LEXEM TO COME HAS VALUE : ");
		ft_putnbr(tmp->lexem);
		ft_putchar('\n');
		tmp = tmp->next;
	}
}

void					ft_setvalues(t_edit *line, t_norm *values)
{
	line->hstr = NULL;
	ft_line_reset(line);
	values->buf = 0;
	values->i = 0;
	values->ret = 0;
	line->select_mode = 0;
	line->start_select = 0;
	line->end_select = 0;
	line->is_highlight = ft_strnew(0);
}



t_ast build_leaf(char **input, int index_input)
{
	leaf = ft_memalloc(sizeof(t_ast));
	leaf->content = input[index_input];
	leaf->to_exec = *input;
	leaf->
}

int search_input(char **input, int prio)
{
  int i;
  char *search;
  i = 0;

  if (prio == 1)
    search = ft_strdup(";");
  if (prio == 2)
    search = ft_strdup("&&");
  if (prio == 3)
    search = ft_strdup("|");
  while (input[i])
  {

    if (ft_strequ(input[i], search))
		{
			return (i);
		}

    i++;
  }
  return (-1);
}

int					main(int ac, char **av, char **envp)
{
	t_edit			*line;
	t_lexit			*lexdat;
	t_env				*env;
	t_norm			*values;

	(void)ac;
	(void)av;
	env = NULL;
	lexdat = NULL;
	g_data = ft_memalloc(sizeof(t_data));
	line = ft_memalloc(sizeof(t_edit));
	values = ft_memalloc(sizeof(t_norm));
	ft_setvalues(line, values);
	ft_init();
	ft_signal();
	tputs(tgetstr("cl", NULL), 1, ft_pointchar);
	while (envp[values->i])
		ft_push_env(&env, envp[values->i++]);
	while (42)
	{
		ft_prompt();
		while ((values->ret = read(0, &values->buf, sizeof(int))) &&
		values->buf != 10)
		{
			handle_key(values->buf, line);
			values->buf = 0;
		}
		if (ft_errors(ft_pre_parser(line), NULL, NULL))
		{
			ft_tokenize_it(line, &lexdat);
			if (ft_errors(ft_parser(lexdat), NULL, NULL))
			{
				ft_putchar('\n');
				ft_execs(lexdat, env, line);
				// ft_putchar('\n');
				// ft_putchar('\n');
				// ft_print_lexdat(lexdat);
			}
		}
		ft_add_history(line); //add line to history
		ft_free_lexdat(lexdat);
		lexdat = NULL;
		if (ft_strequ(line->line, "clear"))
			tputs(tgetstr("cl", NULL), 1, ft_pointchar);
		ft_line_reset(line);
	}
	return (0);
}
