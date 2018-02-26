/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jecarol <jecarol@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/26 20:15:05 by jecarol           #+#    #+#             */
/*   Updated: 2018/02/26 20:16:19 by jecarol          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/sh.h"

int 				ft_what_op_value_to_know_how_to_execute(char *str, int *i)
{
	if (str[*i] == ';')
		return (SEMICOLON);
	else if (str[*i] == '|')
	{
		if (str[*i+1] == '|')
		{
			*i += 1;
			return (DOUBLEPIPE);
		}
		return (PIPE);
	}
	else if (str[*i] == '>')
	{
		if (str[*i+1] == '>')
		{
			*i += 1;
			return(DOUBLECHEVRONRIGHT);
		}
		return (CHEVRONRIGHT);
	}
	else if (str[*i] == '<')
	{
		if (str[*i+1] == '<')
		{
			*i += 1;
			return(DOUBLECHEVRONLEFT);
		}
		return (CHEVRONLEFT);
	}
	else if (str[*i] == '&' && str[*i+1] == '&')
	{
		*i += 1;
		return (DOUBLESPER);
	}
	else
		return (-1);
}

int 				ft_isstrprint(char *str)
{
	int i;

	i = -1;
	while (str[++i])
		return (ft_isprint(str[i]));
	return (0);
}


char				**ft_prep_input(char *str)
{
	char **tmp;
	char *tmp1;
	int i;

	i = 0;
	tmp = ft_strsplit(str, ' ');
	while (tmp[i])
	{
		tmp1 = ft_strtrim(tmp[i]);
		ft_strdel(&tmp[i]);
		tmp[i] = tmp1;
		i++;
	}
	return (tmp);
}

t_lexit 			*ft_add_token(t_edit *line, int *i, int *j)
{
	t_lexit *tmp;

	if (!(tmp = ft_memalloc(sizeof(t_edit))))
		return (NULL);
	tmp->next = NULL;
	tmp->input = ft_strsub(line->line, *j, *i - *j);
	if (!ft_isstrprint(tmp->input))
	{
		ft_strdel(&tmp->input);
		tmp->input = NULL;
		tmp->to_exec = NULL;
	}
	else
	{
		tmp->to_exec = ft_prep_input(tmp->input);
		ft_strdel(&tmp->input);
	}
	tmp->lexem = ft_what_op_value_to_know_how_to_execute(line->line, i);
	return (tmp);
}



void 				ft_tokenize_it(t_edit *line, t_lexit **lexdat)
{
	int i;
	int j;
	t_lexit *tmp;

	i = 0;
	j = 0;
	tmp = *lexdat;
	while (line->line[i])
	{
		if (ft_strchr(OPERATOR, line->line[i]))
		{
			if (!tmp)
			{
				*lexdat = ft_add_token(line, &i, &j);
				tmp = *lexdat;
			}
			else
			{
				while (tmp->next)
					tmp = tmp->next;
				tmp->next = ft_add_token(line, &i, &j);
			}
			j = i + 1;
		}
		i++;
		if (line->line[i] == '\0')
		{
			if (!tmp)
			{
				*lexdat = ft_add_token(line, &i, &j);
				tmp = *lexdat;
			}
			else
			{
				while (tmp->next)
					tmp = tmp->next;
				tmp->next = ft_add_token(line, &i, &j);
			}
		}
		while (ft_isspace(line->line[i]))
			i++;
	}
}
