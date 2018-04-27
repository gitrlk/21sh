/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_more.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rfabre <rfabre@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/27 19:08:55 by rfabre            #+#    #+#             */
/*   Updated: 2018/04/27 19:09:44 by rfabre           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/sh.h"

void			init_valhd(t_hdc *valhd)
{
	valhd->ret_stop[0] = 0;
	valhd->hd = 0;
	valhd->ret_stop[1] = 0;
	valhd->tmp = NULL;
}

t_split			init_split(char const *s, char c, char d, char e)
{
	t_split		vals;

	vals.index = 0;
	vals.i = 0;
	vals.in_substring = 0;
	vals.cnt = 0;
	vals.nb_word = ft_cnt_parts((const char *)s, c, d, e);
	vals.t = (char **)malloc(sizeof(*vals.t) * (vals.nb_word + 1));
	vals.t[vals.nb_word] = NULL;
	return (vals);
}

void			init_node(t_lexit *tmp)
{
	tmp->next = NULL;
	tmp->left = 0;
	tmp->right = 0;
	tmp->redirs = NULL;
	tmp->checker = 0;
	tmp->agr = 0;
	tmp->is_pipe = 0;
	tmp->fdsrc = 1;
	tmp->fddst = -1;
	tmp->fdclose = 0;
	tmp->command = NULL;
}
