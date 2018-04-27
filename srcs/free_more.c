#include "../includes/sh.h"

void			free_env(t_env *lst)
{
	t_env		*tmp;

	tmp = lst;
	while (lst)
	{
		tmp = lst;
		lst = lst->next;
		ft_strdel(&tmp->var);
		free(tmp);
	}
}
