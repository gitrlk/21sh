#include "../includes/sh.h"

int			isnumber(char *s)
{
	int		i;

	i = -1;
	while (s[++i])
	{
		if (!(s[i] >= '0' && s[i] <= '9'))
			return (0);
	}
	return (1);
}

int				get_segment_number(t_sh *sh)
{
	char		**tmp;
	int			i;

	i = 0;
	tmp = ft_strsplit(sh->line->line, ';');
	while (tmp[i])
		i++;
	ft_freetab(tmp);
	return (i);
}

char			**copypasta(char **src, int i)
{
	int			size;
	int			j;
	char		**ret;

	size = 0;
	j = 0;
	while (src[size])
		size++;
	if (!(ret = (char **)malloc(sizeof(char *) * (size + 1))))
		return (NULL);
	while (src[i])
	{
		ret[j] = ft_strdup(src[i]);
		i++;
		j++;
	}
	ret[j] = NULL;
	return (ret);
}

int 				ft_isstrprint(char *str)
{
	int i;

	i = 0;
	while (str[i] && ft_isprint(str[i]))
		i++;
	return (i);
}
