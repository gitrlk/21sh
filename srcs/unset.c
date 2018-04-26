#include "../includes/sh.h"

void		ft_lst_add_tenv(t_env **alst, t_env *new)
{
	t_env	*lst;

	lst = *alst;
	if (lst == NULL)
	{
		*alst = new;
	}
	else
	{
		while (lst->next != NULL)
			lst = lst->next;
		lst->next = new;
	}
}

int			find_t_env_array(char *env, char *search)
{
	int		len;

	len = ft_strlen(search);
	if (!ft_strncmp(env, search, len))
		if (!ft_strncmp((env + len), "=", 1))
			return (1);
	return (0);
}

int			look_for_env(t_env **venv, char *commands)
{
	t_env	*tmp;

	tmp = *venv;
	while (tmp)
	{
		if (find_t_env_array(tmp->var, commands))
			return (1);
		tmp = tmp->next;
	}
	return (0);
}

void		remove_one_t_env(t_env **venv, char *commands)
{
	t_env	*free_this;

	while (*venv)
	{
		if (find_t_env_array((*venv)->var, commands))
		{
			free_this = *venv;
			*venv = free_this->next;
			free(free_this->var);
			free(free_this);
			break ;
		}
		venv = &(*venv)->next;
	}
}

void		exec_unsetenv(char **commands, t_env **venv)
{
	int		i;

	i = -1;
	while (commands[++i])
  {
    if (look_for_env(venv, commands[i]))
  		remove_one_t_env(venv, commands[i]);
    else
    {
		ft_putstr_fd("unset: ", 2);
      ft_putstr_fd(commands[i], 2);
      ft_putendl_fd(" variable not found", 2);
    }
  }
	if (i == 0)
		ft_putendl_fd("usage : unset <environment variable>", 2);
}
