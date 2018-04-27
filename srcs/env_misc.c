#include "../includes/sh.h"

void			ft_print_env(t_env *env)
{
	while (env)
	{
		ft_putendl_fd(env->var, STDOUT_FILENO);
		env = env->next;
	}
}

t_env			*add_env(char *var)
{
	t_env		*tmp;

	if (!(tmp = (t_env *)malloc(sizeof(t_env))))
		return (NULL);
	tmp->next = NULL;
	if (!var)
		tmp->var = NULL;
	else
		tmp->var = ft_strdup(var);
	return (tmp);
}

void			ft_push_env(t_env **lst, char *var)
{
	t_env		*tmp;

	tmp = *lst;
	if (!tmp)
		*lst = add_env(var);
	else
	{
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = add_env(var);
	}
}

int				ft_get_egal_pos(char *vartoadd)
{
	int			i;
	int			result;

	i = 0;
	result = 0;
	if (ft_strchr(vartoadd, '='))
	{
		while (vartoadd[i] != '=')
		{
			i++;
			result++;
		}
		return (result);
	}
	return (0);
}

void			ft_refresh_link(t_env **tmp, char *vartoadd)
{
	t_env		*tmp2;

	tmp2 = *tmp;
	ft_strdel(&tmp2->var);
	tmp2->var = ft_strdup(vartoadd);
}
