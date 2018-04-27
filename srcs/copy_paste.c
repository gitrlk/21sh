/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   copy_paste.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jecarol <jecarol@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/26 20:15:27 by jecarol           #+#    #+#             */
/*   Updated: 2018/04/27 02:20:07 by rlkcmptr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/sh.h"

void		ft_highlight(t_edit *line)
{
	int		i;
	char	*tmp;
	char	*tmp2;

	i = 0;
	tmp = ft_strndup(line->line, line->start_select);
	ft_putstr_fd(tmp, STDOUT_FILENO);
	ft_putstr_fd(tgetstr("mr", NULL), STDOUT_FILENO);
	tmp2 = ft_strsub(line->line, line->start_select ,
	(line->end_select - line->start_select));
	ft_putstr_fd(tmp2, STDOUT_FILENO);
	free(tmp);
	ft_putstr_fd(tgetstr("me", NULL), STDOUT_FILENO);
	tmp = ft_strsub(line->line, line->end_select ,
	((line->max_size - 2) - line->end_select));
	ft_putstr_fd(tmp, STDOUT_FILENO);
	line->cursor_pos = line->max_size;
	while ((size_t)++i <= ft_strlen(tmp))
		ft_left_arrow(line);
	free(tmp);
	free(line->is_highlight);
	line->is_highlight = tmp2;
}

void		ft_go_start(t_edit *line)
{
	int		i;

	i = 0;
	while (i < line->max_size)
	{
		ft_left_arrow(line);
		i++;
	}
	tputs(tgetstr("cd", NULL), 1, ft_pointchar);
}

void		ft_paste(t_edit *line)
 {
   char		*tmp;
   char		*tmp2;
   int		i;

   i = 0;
   tmp = ft_strndup(line->line, line->cursor_pos - 2);
   tmp2 = ft_freejoinstr(tmp, line->is_highlight);
   free (line->line);
   tmp = ft_strsub(line->line, line->cursor_pos - 2 , ((line->max_size) -line->cursor_pos));
   line->line = ft_freejoinstr(tmp2, tmp);
   ft_go_start(line);
 	 ft_putstr_fd(line->line, STDOUT_FILENO);
   line->max_size += ft_strlen(line->is_highlight);
   line->cursor_pos = ft_strlen(line->line) + 2;
   while ((size_t)i < ft_strlen(tmp))
   {
 	  ft_left_arrow(line);
 	  i++;
   }
   free(tmp);
}

void		ft_cut(t_edit *line)
{
	int		i;
	char	*tmp;
    char	*tmp2;

    i = 0;
    tmp = ft_strndup(line->line, line->start_select);
    ft_putstr_fd(tmp, STDOUT_FILENO);
    tmp2 = ft_strsub(line->line, line->end_select , ((line->max_size - 2) - line->end_select));
    ft_putstr_fd(tmp2, STDOUT_FILENO);
    free(line->line);
    line->max_size -= ft_strlen(line->is_highlight);
    line->line = ft_freejoinstr(tmp, tmp2);
    free(tmp2);
    line->cursor_pos = (ft_strlen(line->line) + 2);
}

void		select_copy_cut(t_edit *line, int buf)
{
	if (!line->select_mode && buf == PRESS_ALT_K)
	{
		line->select_mode = 1;
		line->start_select = ((line->cursor_pos) - 2);
	}
	else if ((line->select_mode) && ((buf == PRESS_ALT_K)  || (buf == PRESS_ALT_C)))
	{
		line->select_mode = 0;
    ft_go_start(line);
    ft_putstr_fd(line->line, STDOUT_FILENO);
    line->cursor_pos = (ft_strlen(line->line) + 2);
	}
	else if (line->select_mode && buf == PRESS_ALT_X)
  {
    line->select_mode = 0;
    ft_go_start(line);
    ft_cut(line);
  }
  else if (buf == PRESS_ALT_V && !line->select_mode)
  {
    line->select_mode = 0;
    ft_paste(line);
  }
}
