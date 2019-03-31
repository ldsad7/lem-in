/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_input_part_2.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsprigga <bsprigga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/02 10:41:48 by bsprigga          #+#    #+#             */
/*   Updated: 2019/03/31 13:42:08 by bsprigga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

t_room		*find_leaf(char *name)
{
	int		start;
	int		end;
	int		i;
	t_room	**arr;

	if (!g_params)
		return (NULL);
	start = 0;
	end = g_params->nr_rooms - 1;
	arr = g_params->arr;
	i = start + (end - start) / 2;
	while (start <= end)
	{
		if (ft_strcmp(arr[i]->name, name) > 0)
			end = i - 1;
		else if (ft_strcmp(arr[i]->name, name) < 0)
			start = i + 1;
		else
			return (arr[i]);
		i = start + (end - start) / 2;
	}
	return (NULL);
}

static int	arr_len_calc(char **lines, int max_len, int *i)
{
	int len;

	len = 0;
	while (lines[*i] && lines[*i + max_len])
	{
		len += ft_strlen(lines[*i]);
		(*i)++;
	}
	return (len);
}

char		*ft_strjoin_for_arr(char **lines, int max_len)
{
	int		i;
	int		j;
	int		len;
	char	*res;

	i = 0;
	len = arr_len_calc(lines, max_len, &i);
	len += i - 1;
	if (!(res = (char *)malloc(sizeof(*res) * (len + 1))))
		return (NULL);
	len = 0;
	i = 0;
	while (lines[i] && lines[i + max_len])
	{
		j = 0;
		while (lines[i][j])
			res[len++] = lines[i][j++];
		i++;
		if (lines[i] && lines[i + max_len])
			res[len++] = '-';
	}
	res[len] = '\0';
	return (res);
}

void		g_params_init(int (*fls)[3], char **line)
{
	if (!(g_params = (t_params *)malloc(sizeof(t_params))))
		perror_exit("malloc");
	g_params->nr_rooms = 0;
	g_params->nr_ants = 0;
	g_params->start = NULL;
	g_params->end = NULL;
	g_params->start_of_list = NULL;
	g_params->start_of_list_of_paths = NULL;
	g_params->arr = NULL;
	g_params->read_lines = 1;
	(*fls)[0] = 0;
	(*fls)[1] = 0;
	(*fls)[2] = 0;
	*line = NULL;
}

/*
**	we take tmp as g_params->start_of_list->next because in loop we don't
**	want to compare this same node with itself. Nodes are added to the left,
**	so we skip node that we're comparing to others.
*/

void		check_coordinates_and_name(t_room *current_room)
{
	t_room		*tmp;

	tmp = g_params->start_of_list->next;
	while (tmp)
	{
		if (!(ft_strcmp(tmp->name, current_room->name)))
			error_exit(e_duplicate_node);
		else if (tmp->coord_x == current_room->coord_x &&
		tmp->coord_y == current_room->coord_y)
			error_exit(e_two_nodes_have_the_same_coordinates);
		tmp = tmp->next;
	}
}
