#include "../includes/sh.h"

void			ft_print_env(t_env *env)
{
	while (env)
	{
		ft_putendl(env->var);
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
