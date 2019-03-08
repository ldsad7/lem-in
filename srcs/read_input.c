/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_input.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsprigga <bsprigga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/02 10:41:48 by bsprigga          #+#    #+#             */
/*   Updated: 2019/03/08 03:35:52 by tsimonis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lem_in.h"

size_t	ft_arrlen(char **str)
{
	size_t	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

void	get_nr_ants(char **line)
{
	long long num;

	while (get_next_line_or_exit(line) && (*line)[0] == '#'
			&& !ft_strequ(*line, "##start") && !ft_strequ(*line, "##end"))
		free(*line);
	if (ft_isnumeric(*line))
	{
		if ((num = ft_atoi_long(*line)) <= 2147483647 && num >= -2147483648)
			g_params->nr_ants = num;
		else
			error_exit();
	}
	else
		error_exit();
	free(*line);
}

t_room	*room_writing(char **ln_split)
{
	t_room	*tmp;
	int		num1;
	int		num2;

	num1 = 0;
	num2 = 0;
	if (!(tmp = (t_room *)malloc(sizeof(t_room))))
		exit(0);
	if (!(tmp->name = ft_strdup(ln_split[0])))
		exit(0);
	if (tmp->name[0] == 'L')
		error_exit();
	if (!ft_isnumeric(ln_split[1]) || !ft_isnumeric(ln_split[2])
	|| (num1 = ft_atoi_long(ln_split[1])) > 2147483647 || num1 < -2147483648
	|| (num2 = ft_atoi_long(ln_split[2])) > 2147483647 || num2 < -2147483648)
		error_exit();
	g_params->nr_rooms++;
	tmp->coord_x = num1;
	tmp->coord_y = num2;
	tmp->neighbours = NULL;
	tmp->next = NULL;
	tmp->prev = NULL;
	tmp->num_path = 0;
	if (g_params->start_of_list)
		tmp->next = g_params->start_of_list;
	g_params->start_of_list = tmp;
	return (tmp);
}

void	start_end_writing(char **line)
{
	int		start_or_end;
	char	**line_split;

	start_or_end = ft_strequ(*line, "##start") ? e_start : e_end;
	if ((!start_or_end && g_params->start) || (start_or_end && g_params->end))
		error_exit();
	free(*line);
	while (get_next_line_or_exit(line) && (*line)[0] == '#' &&
			!ft_strequ(*line, "##start") && !ft_strequ(*line, "##end"))
		free(*line);
	if (ft_strequ(*line, "##start") || ft_strequ(*line, "##end"))
		error_exit();
	line_split = ft_strsplit(*line, ' ');
	if (ft_arrlen(line_split) != 3)
	{
		free_2d_array(line_split);
		error_exit();
	}
	if (start_or_end == e_start)
	{
		g_params->start = room_writing(line_split);
		g_params->start->num_path = -1;
	}
	else
	{
		g_params->end = room_writing(line_split);
		g_params->end->num_path = -2;
	}
	free_2d_array(line_split);
}

t_room	*find_leaf(char *name)
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

char	*ft_strjoin_for_arr(char **lines, int max_len)
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
	}
	res[len] = '\0';
	return (res);
}

void	add_to_lst(t_room *input, t_room *output)
{
	t_neighbour	*neighb;

	if (!(neighb = (t_neighbour *)malloc(sizeof(*neighb))))
		exit(0);
	neighb->room = input;
	if (output->neighbours)
		neighb->next = output->neighbours;
	else
		neighb->next = NULL;
	output->neighbours = neighb;
}

void	sort_list_to_arr(void)
{
	int		i;
	int		j;
	int		tmp;
	t_room	*start_of_list;

	start_of_list = g_params->start_of_list;
	g_params->arr = (t_room **)malloc(sizeof(t_room *) * (g_params->nr_rooms));
	i = 0;
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

void	link_writing(char **line)
{
	char		**line_split;
	char		*first_name;
	char		*second_name;
	t_room		*tmps[2];
	size_t		i;

	if (!(g_params->arr))
		sort_list_to_arr();
	line_split = ft_strsplit(*line, '-');
	if (!(i = 0) && ft_arrlen(line_split) < 2)
		error_exit();
	while (i < ft_arrlen(line_split) - 1)
	{
		if (!(first_name = ft_strjoin_for_arr(line_split, i + 1)) ||
			!(second_name = ft_strdup(*line + ft_strlen(first_name) + 1)))
			exit(0);
		if (++i && (tmps[0] = find_leaf(first_name))
				&& (tmps[1] = find_leaf(second_name)))
			break ;
		free(first_name);
		free(second_name);
	}
	if (!(tmps[0]) || !(tmps[1]) || !first_name || !second_name)
		error_exit();
	add_to_lst(tmps[1], tmps[0]);
	add_to_lst(tmps[0], tmps[1]);
	free_2d_array(line_split);
	free(first_name);
	free(second_name);
}

int		g_params_init(int (*fls)[3])
{
	if (!(g_params = (t_params *)malloc(sizeof(t_params))))
		exit(0);
	g_params->nr_rooms = 0;
	g_params->nr_ants = 0;
	g_params->start = NULL;
	g_params->end = NULL;
	g_params->start_of_list = NULL;
	g_params->start_of_list_of_path = NULL;
	g_params->arr = NULL;
	(*fls)[0] = 0;
	(*fls)[1] = 0;
	(*fls)[2] = 0;
	return (1);
}

/*
**	fls[0] -- was there a start?
**	fls[1] -- was there an end?
**	fls[2] -- was there a link?
*/

void	read_input(void)
{
	char	*line;
	int		nr_bytes_read;
	char	**line_split;
	int		fls[3];

	g_params_init(&fls);
	line = NULL;
	get_nr_ants(&line);
	while ((nr_bytes_read = get_next_line_or_exit(&line)))
	{
		line_split = ft_strsplit(line, ' ');
		if (line[0] == '#' && !ft_strequ(line, "##start")
				&& !ft_strequ(line, "##end"))
			;
		else if ((ft_strequ(line, "##start") && (fls[0] = 1))
				|| (ft_strequ(line, "##end") && (fls[1] = 1)))
			start_end_writing(&line);
		else if (ft_arrlen(line_split) == 3 && !fls[2])
			room_writing(line_split);
		else if (ft_arrlen(line_split) == 1 && (fls[2] = 1))
			link_writing(&line);
		else
			error_exit();
		free(line);
		free_2d_array(line_split);
	}
	free(line);
	if (!fls[0] || !fls[1] || !fls[2])
		error_exit();
}
