/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rfabre <rfabre@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/08 18:23:00 by rfabre            #+#    #+#             */
/*   Updated: 2017/06/30 16:19:07 by rfabre           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list				*ft_fd_checker(t_list **save, int fd)
{
	t_list			*tmp;

	tmp = *save;
	while (tmp)
	{
		if ((int)tmp->content_size == fd)
			return (tmp);
		tmp = tmp->next;
	}
	tmp = ft_lstnew("\0", 1);
	tmp->content_size = fd;
	if (*save)
		ft_lstaddend(save, tmp);
	else
		*save = tmp;
	return (tmp);
}

int					get_next_line(const int fd, char **line)
{
	t_list static	*save = NULL;
	t_list			*rd;
	char			*tmp;
	char			buff[BUFF_SIZE];
	int				ret;

	if (fd < 0 || !line || read(fd, buff, 0) < 0)
		return (-1);
	rd = ft_fd_checker(&save, fd);
	while (!ft_strchr(rd->content, '\n') && (ret = read(fd, buff, BUFF_SIZE)))
		if (ret == -1)
			return (-1);
		else
			rd->content = ft_strjoinnfree(rd->content, buff, ret, '1');
	ret = 0;
	while (((char*)rd->content)[ret] && ((char*)rd->content)[ret] != '\n')
		++ret;
	if (ret)
		*line = ft_strndup(rd->content, ret);
	else if (((char*)rd->content)[0] == '\n')
		*line = ft_strnew(0);
	(((char*)rd->content)[ret] == '\n') ? ++ret : 0;
	tmp = rd->content;
	rd->content = ft_strjoinnfree(tmp + ret, tmp, 0, '2');
	return (ret ? 1 : 0);
}
