#include "../includes/sh.h"

int				ignore_first_semi(t_sh *sh)
{
	char		*tmp;
	int			i;
	int			start;
	int			go;

	tmp = ft_strdup(sh->line->line);
	start = 0;
	go = 0;
	i = 0;
	while (sh->line->line[i] && ft_isspace(sh->line->line[i]))
		i++;
	if (sh->line->line[i] == ';')
	{
		start = i + 1;
		if (!look_for_op(sh, (i + 1)))
			return (ft_errors(1, ";", NULL));
		while (sh->line->line[i])
		{
			i++;
			go++;
		}
		ft_strdel(&sh->line->line);
		sh->line->line = ft_strsub(tmp, start, go);
	}
	return (1);
}

int				setup_parsing(t_parsing *data, t_env *env, t_sh *sh)
{
	data->env = env;
	data->empty_input = ft_strtrim(sh->line->line);
	if (data->empty_input[0] == '\0')
		data->empty = 1;
	ft_strdel(&data->empty_input);
	if (ignore_first_semi(sh))
	{
		data->len = ft_strlen(sh->line->line);
		return (1);
	}
	return (0);
}

void			ignore_quotes(char *s, t_parsing *data)
{
	if (s[data->index] == '\'')
	{
		data->index++;
		while (s[data->index] != '\'')
			data->index++;
	}
	if (s[data->index] == '\"')
	{
		data->index++;
		while (s[data->index] != '\"')
			data->index++;
	}
}
