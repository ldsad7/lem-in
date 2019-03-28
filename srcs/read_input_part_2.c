/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_input_part_2.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsimonis <tsimonis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/02 10:41:48 by bsprigga          #+#    #+#             */
/*   Updated: 2019/03/29 02:54:40 by tsimonis         ###   ########.fr       */
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

char		*ft_strjoin_for_arr(char **lines, int max_len)
{
	int		i;
	int		j;
	int		len;
	char	*res;

	len = 0;
	i = 0;
	while (lines[i] && lines[i + max_len])
	{
		len += ft_strlen(lines[i]);
		i++;
	}
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

static void	sort_list_to_arr_main_loop(int i, t_room *start_of_list)
{
	int		j;
	int		tmp;

	while (start_of_list)
	{
		j = 0;
		while (j < i)
		{
			if (ft_strcmp(g_params->arr[j]->name, start_of_list->name) > 0)
				break ;
			j++;
		}
		tmp = i;
		while (tmp > j)
		{
			g_params->arr[tmp] = g_params->arr[tmp - 1];
			tmp--;
		}
		g_params->arr[tmp] = start_of_list;
		start_of_list = start_of_list->next;
		i++;
	}
}

void		sort_list_to_arr(void)
{
	int		i;

	if (!(g_params->arr = (t_room **)malloc(sizeof(t_room *) *
										(g_params->nr_rooms))))
		exit(0);
	i = 0;
	sort_list_to_arr_main_loop(i, g_params->start_of_list);
}

void		g_params_init(int (*fls)[3], char **line)
{
	if (!(g_params = (t_params *)malloc(sizeof(t_params))))
		exit(0);
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
