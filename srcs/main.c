/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jecarol <jecarol@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/26 20:14:55 by jecarol           #+#    #+#             */
/*   Updated: 2018/03/06 15:58:16 by jecarol          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

// void					ft_print_lexdat(t_lexit *lexdat)
// {
// 	t_lexit			*tmp;
// 	int				i;
//
// 	i = 0;
// 	tmp = lexdat;
// 	while (tmp)
// 	{
// 		if (tmp->to_exec)
// 		{
// 			while (tmp->to_exec[i])
// 			{
// 				ft_putstr(tmp->to_exec[i]);
// 				ft_putchar('\n');
// 				i++;
// 			}
// 			i = 0;
// 		}
// 		ft_putstr("LEXEM TO COME HAS VALUE : ");
// 		ft_putnbr(tmp->lexem);
// 		ft_putchar('\n');
// 		tmp = tmp->next;
// 	}
// }

void					ft_setvalues(t_edit *line, t_norm *values)
{
	line->hstr = NULL;
	ft_line_reset(line);
	line->sz = ft_init(line);
	values->buf = 0;
	values->i = 0;
	values->ret = 0;
}

void				ft_print_tree(t_lexit *lexdat)
{
	if (lexdat)
	{
		ft_putstr(lexdat->input);
		ft_putchar('\n');
		if (lexdat->left)
			ft_print_tree(lexdat->left);
		if (lexdat->right)
			ft_print_tree(lexdat->right);
	}
}

int					main(int ac, char **av, char **envp)
{
	t_edit			*line;
	t_lexit			*lexdat;
	t_env				*env;
	t_norm			*values;
	int				prio;

	(void)ac;
	(void)av;
	prio = 0;
	env = NULL;
	lexdat = NULL;
	line = ft_memalloc(sizeof(t_edit));
	values = ft_memalloc(sizeof(t_norm));
	ft_setvalues(line, values);
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
			ft_putchar('\n');
			lexdat = ft_tree_it(lexdat, line->line_split, prio);
			ft_print_tree(lexdat);
			// if (lexdat)
			// if (ft_errors(ft_parser(lexdat), NULL, NULL))
			// {
				// ft_putchar('\n');
				// ft_final_parsing(lexdat);
				// ft_execs(lexdat, env, line);
				ft_putchar('\n');
				ft_putchar('\n');
				// ft_print_lexdat(lexdat);
			// }
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
