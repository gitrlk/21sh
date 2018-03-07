/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jecarol <jecarol@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/26 20:15:05 by jecarol           #+#    #+#             */
/*   Updated: 2018/03/07 22:59:42 by jecarol          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/sh.h"
//
// int 				ft_what_op_value_to_know_how_to_execute(char *str, int *i)
// {
// 	if (str[*i] == ';')
// 		return (SEMICOLON);
// 	else if (str[*i] == '|')
// 	{
// 		if (str[*i+1] == '|')
// 		{
// 			*i += 1;
// 			return (DOUBLEPIPE);
// 		}
// 		return (PIPE);
// 	}
// 	else if (str[*i] == '>')
// 	{
// 		if (str[*i+1] == '>')
// 		{
// 			*i += 1;
// 			return(DOUBLECHEVRONRIGHT);
// 		}
// 		return (CHEVRONRIGHT);
// 	}
// 	else if (str[*i] == '<')
// 	{
// 		if (str[*i+1] == '<')
// 		{
// 			*i += 1;
// 			return(DOUBLECHEVRONLEFT);
// 		}
// 		return (CHEVRONLEFT);
// 	}
// 	else if (str[*i] == '&' && str[*i+1] == '&')
// 	{
// 		*i += 1;
// 		return (DOUBLESPER);
// 	}
// 	else
// 		return (-1);
// }

int 				ft_isstrprint(char *str)
{
	int i;

	i = -1;
	while (str[++i])
		return (ft_isprint(str[i]));
	return (0);
}

char				**ft_prep_input(char *str)
{
	char			**tmp;
	char			*tmp1;
	int			i;

	i = 0;
	tmp = ft_strsplit(str, ' ');
	while (tmp[i])
	{
		tmp1 = ft_strtrim(tmp[i]);
		ft_strdel(&tmp[i]);
		tmp[i] = tmp1;
		i++;
	}
	return (tmp);
}

// t_lexit 			*ft_add_token(t_edit *line, int *i, int *j)
// {
// 	t_lexit *tmp;
//
// 	if (!(tmp = ft_memalloc(sizeof(t_edit))))
// 		return (NULL);
// 	tmp->next = NULL;
// 	tmp->input = ft_strsub(line->line, *j, *i - *j);
// 	if (!ft_isstrprint(tmp->input))
// 	{
// 		ft_strdel(&tmp->input);
// 		tmp->input = NULL;
// 		tmp->to_exec = NULL;
// 	}
// 	else
// 	{
// 		tmp->to_exec = ft_prep_input(tmp->input);
// 		ft_strdel(&tmp->input);
// 	}
// 	tmp->lexem = ft_what_op_value_to_know_how_to_execute(line->line, i);
// 	return (tmp);
// }
//
//
//
//
// input = ["ls", "|", "cat", "&&", "echo"]
//
// prio = [1 = ';', 2 = '&& ou ||' 3 = '|' ...]
//
// t_btree cut_input_and_build_leaf(t_btree *tree, t_input *input, int prio)
// {
//     int index_input;
//     index_input = search_input(input, prio);
//     if (index_input)
//         tree = insert_tree(tree, build_leaf(input, index_input))
//
//         cut_input(input, &input_left, &input_right)
//         tree->left = cut_input_and_build_leaf(tree->left, input_left, prio + 1);
//         tree->right = cut_input_and_build_leaf(tree->right, input_right, prio);
// }




// char 				*find_input(char **input, int prio)
// {
// 	char *input;
// 	int i;
// 	static char *operators[8];
// 	operators[0] = ";";
// 	operators[1] = "||";
// 	operators[2] = "&&";
// 	operators[3] = "|";
// 	operators[4] = ">";
// 	operators[5] = "<";
// 	operators[6] = ">>";
// 	operators[7] = "<<";
//
// 	i = 0;
// 	ft_putstr("PRIO IS : ");
// 	ft_putnbr(prio);
// 	ft_putchar('\n');
// 	if (input)
// 	{
// 		while (input[i])
// 		{
// 			// ft_putstr(input[i]);
// 			if (!(ft_strcmp(input[i], operators[prio])))
// 				return (i);
// 			i++;
// 		}
// 	}
// 	return (0);
// }


t_lexit			*insert_tree(t_lexit *lexdat, char *leaf)
{
	t_lexit *node;

	node = NULL;
	if (!lexdat)
	{
		if (!(node = malloc(sizeof(t_lexit))))
			return (NULL);
		node->left = NULL;
		node->right = NULL;
		node->input = ft_strdup(leaf);
		ft_putstr(leaf);
	}
	else
	{
		if (!(node = malloc(sizeof(t_lexit))))
			return (NULL);
		node->input = ft_strdup(leaf);
	}
	return (node);
}

char				**cut_input(char **origin, int index)
{
	int i;
	int j;
	char **left;

	i = 0;
	j = 0;
	// while (origin[j])
	// 	j++;
	if(!(left = (char **)malloc(sizeof(*left) * index + 1)))
		return (NULL);
	while (i < index)
	{
		left[i] = ft_strdup(origin[i]);
		i++;
	}
	return (left);
	// i = 0;
	// if(!(right = (char **)malloc(sizeof(*right) * (j - index) + 1)))
	// 	return ;
	// while (i < index)
	// {
	// 	left[i] = ft_strdup(origin[i]);
	// 	i++;
	// }

}

char				**cut_input_right(char **origin, int index)
{
	int i;
	int j;
	int k;
	char **right;

	i = 0;
	j = 0;
	while (origin[j])
		j++;
	k = j - index;
	// ft_putnbr(k);
	// ft_putchar('\n');
	if(!(right = (char **)malloc(sizeof(*right) * k + 1)))
		return (NULL);
	while (i < k)
	{
		right[i] = ft_strdup(origin[index]);
		index++;
		i++;
	}
	return (right);
}


	t_lexit 			*ft_tree_it(t_lexit *list, t_lexit *compare, int prio)
	{
		t_lexit	*keep;
		t_lexit	*tmp;


		// if (checker)
		// {
		// 	ft_putstr("BAWEEee");
		// 	ft_putchar('\n');
		// }
		keep = NULL;
		tmp = list;
		if (prio == REDIR || !list)
			return (NULL);
		while (tmp != compare)
		{
			if (tmp->prio == prio)
				keep = tmp;
			tmp = tmp->next;
		}
		if (keep)
		{
			keep->left = ft_tree_it(list, keep, prio);
			keep->right = ft_tree_it(keep->next, compare, prio + 1);
			return (keep);
			// ft_putstr("I'M IN BAWS");
			// ft_putchar('\n');
			// lexdat = insert_tree(lexdat, line[index_input]);
			// input_left = cut_input(line, index_input);
			// input_right = cut_input_right(line, index_input + 1);
			// while (input_left[i])
			// {
			// 	ft_putstr("left : ");
			// 	ft_putstr(input_left[i]);
			// 	ft_putchar('\n');
			// 	i++;
			// }
			// i = 0;
			// while (input_right[i])
			// {
			// 	ft_putstr("right : ");
			// 	ft_putstr(input_right[i]);
			// 	ft_putchar('\n');
			// 	i++;
			// }
			// lexdat->left = ft_tree_it(lexdat->left, input_left, prio + 1);
			// lexdat->right = ft_tree_it(lexdat->right, input_right, prio);
			// return (lexdat);
		}
		// ft_putstr("okok");
		// ft_putchar('\n');
		else
			return(ft_tree_it(list, compare, prio + 1));
		}


// t_lexit 			*ft_tree_it(t_lexit *lexdat, char **line, int prio)
// {
// 	int index_input;
// 	char **input_left;
// 	char **input_right;
// 	int i;
//
//
// 	// if (checker)
// 	// {
// 	// 	ft_putstr("BAWEEee");
// 	// 	ft_putchar('\n');
// 	// }
// 	i = 0;
// 	input_left = NULL;
// 	input_right = NULL;
// 	if (prio == 8 || !line)
// 		return (NULL);
// 	index_input = find_input(line, prio);
// 	if (index_input)
// 	{
// 		// ft_putstr("I'M IN BAWS");
// 		// ft_putchar('\n');
// 		lexdat = insert_tree(lexdat, line[index_input]);
// 		input_left = cut_input(line, index_input);
// 		input_right = cut_input_right(line, index_input + 1);
// 		// while (input_left[i])
// 		// {
// 		// 	ft_putstr("left : ");
// 		// 	ft_putstr(input_left[i]);
// 		// 	ft_putchar('\n');
// 		// 	i++;
// 		// }
// 		// i = 0;
// 		// while (input_right[i])
// 		// {
// 		// 	ft_putstr("right : ");
// 		// 	ft_putstr(input_right[i]);
// 		// 	ft_putchar('\n');
// 		// 	i++;
// 		// }
// 		lexdat->left = ft_tree_it(lexdat->left, input_left, prio + 1);
// 		lexdat->right = ft_tree_it(lexdat->right, input_right, prio);
// 		return (lexdat);
// 	}
// 	// ft_putstr("okok");
// 	// ft_putchar('\n');
// 	else
// 		return(ft_tree_it(lexdat, line, prio + 1));
// 	}
// //
// //
// //
// //
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
// 	// int			i;
// 	// int			j;
// 	// t_lexit		*tmp;
//    //
// 	// i = 0;
// 	// j = 0;
// 	// tmp = *lexdat;
// 	// while (line->line[i])
// 	// {
// 	// 	if (ft_strchr(OPERATOR, line->line[i]))
// 	// 	{
// 	// 		if (!tmp)
// 	// 		{
// 	// 			*lexdat = ft_add_token(line, &i, &j);
// 	// 			tmp = *lexdat;
// 	// 		}
// 	// 		else
// 	// 		{
// 	// 			while (tmp->next)
// 	// 				tmp = tmp->next;
// 	// 			tmp->next = ft_add_token(line, &i, &j);
// 	// 		}
// 	// 		j = i + 1;
// 	// 	}
// 	// 	i++;
// 	// 	if (line->line[i] == '\0')
// 	// 	{
// 	// 		if (!tmp)
// 	// 		{
// 	// 			*lexdat = ft_add_token(line, &i, &j);
// 	// 			tmp = *lexdat;
// 	// 		}
// 	// 		else
// 	// 		{
// 	// 			while (tmp->next)
// 	// 				tmp = tmp->next;
// 	// 			tmp->next = ft_add_token(line, &i, &j);
// 	// 		}
// 	// 	}
// 	// 	while (ft_isspace(line->line[i]))
// 	// 		i++;
// 	// }
// }
