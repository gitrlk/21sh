#include "../includes/sh.h"

char **ft_replace_quote(char **array, t_sh *sh, char **ret)
{
	char  **start;
	char  **end;
	int		i;
	int  	nbr;
	char  *trimed;

	i = -1;
  nbr = 0;
	if (sh->line->array_size == 1)
		return (array);
	if (sh->line->array_size > 1)
	{
		trimed = ft_strtrim(array[0]);
    ft_putstr("trimed1:");
    ft_putendl(trimed);
		if (trimed)
		{
			start = ft_strsplit(trimed, ' ');
			while (start[++i])
				nbr++;
			ft_strdel(&trimed);
		}
	}
	if (sh->line->array_size > 2)
	{
		i = -1;
		trimed = ft_strtrim(array[2]);
    ft_putstr("trimed2:");
    ft_putendl(trimed);
		if (trimed)
		{
			end = ft_strsplit(trimed, ' ');
			while (end[++i])
				nbr++;
			ft_strdel(&trimed);
		}
	}
	ret = (char **)malloc(sizeof(*ret) * (nbr + 2));
	i = -1;
	nbr = -1;
	if (sh->line->array_size > 1)
	{
		while(start[++i])
			ret[++nbr] = ft_strdup(start[i]);
		ret[++nbr] = ft_strdup(array[1]);
	}
	if (sh->line->array_size > 2)
	{
		i = -1;
		while(end[++i])
			ret[++nbr] = ft_strdup(end[i]);
	}
	ret[++nbr] = NULL;
  i = 0;
	return (ret);
}
