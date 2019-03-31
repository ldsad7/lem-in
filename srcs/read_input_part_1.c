/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_input_part_1.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsprigga <bsprigga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/02 10:41:48 by bsprigga          #+#    #+#             */
/*   Updated: 2019/03/31 13:41:49 by bsprigga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

/*
**	first while is for skipping comments before ants_nr value
*/

void			get_nr_ants(char **line, t_list **input)
{
	long long num;

	while (get_next_line_or_exit(line) > 0 && (*line)[0] == '#'
			&& !ft_strequ(*line, "##start") && !ft_strequ(*line, "##end"))
	{
		g_params->read_lines++;
		ft_lstadd(input, ft_lstnew(*line, 0));
	}
	if (ft_isnumeric(*line))
	{
		if ((num = ft_atoi_long(*line)) <= 2147483647 && num > 0)
			g_params->nr_ants = num;
		else if (num <= 0)
			error_exit(e_ants_value_less_or_equal_than_zero);
		else
			error_exit(e_ants_value_bigger_int);
	}
	else if (!ft_strlen(*line))
		error_exit(e_no_ants_value);
	else
		error_exit(e_incorrect_ants_value);
	ft_lstadd(input, ft_lstnew(*line, 0));
}

static t_room	*tmp_room_setup(t_room *tmp, int num1, int num2)
{
	tmp->coord_x = num1;
	tmp->coord_y = num2;
	tmp->next = NULL;
	tmp->next_elem = NULL;
	tmp->prev_path = NULL;
	tmp->prev_elem = NULL;
	tmp->path_nr = 0;
	tmp->in_paths = 0;
	tmp->neighbours = NULL;
	tmp->ant_nr = 0;
	return (tmp);
}

t_room			*room_writing(char **ln_split)
{
	t_room			*tmp;
	long long int	num1;
	long long int	num2;

	num1 = 0;
	num2 = 0;
	if (!(tmp = (t_room *)malloc(sizeof(t_room))))
		perror_exit("malloc");
	if (!(tmp->name = ft_strdup(ln_split[0])))
		perror_exit("malloc");
	if (tmp->name[0] == 'L')
		error_exit(e_room_starts_with_L);
	if (!ft_isnumeric(ln_split[1]) || !ft_isnumeric(ln_split[2])
	|| (num1 = ft_atoi_long(ln_split[1])) > 2147483647 || num1 < -2147483648
	|| (num2 = ft_atoi_long(ln_split[2])) > 2147483647 || num2 < -2147483648)
		error_exit(e_invalid_coordinates);
	g_params->nr_rooms++;
	tmp = tmp_room_setup(tmp, num1, num2);
	if (g_params->start_of_list)
		tmp->next = g_params->start_of_list;
	g_params->start_of_list = tmp;
	return (tmp);
}

static void		start_end_writing_input_saving(char **line, t_list **input)
{
	while (get_next_line_or_exit(line) && (*line)[0] == '#' &&
			!ft_strequ(*line, "##start") && !ft_strequ(*line, "##end"))
	{
		ft_lstadd(input, ft_lstnew(*line, 0));
		g_params->read_lines++;
	}
}

void			start_end_writing(char **line, t_list **input)
{
	int		start_or_end;
	char	**line_split;

	start_or_end = ft_strequ(*line, "##start") ? e_start : e_end;
	if (!start_or_end && g_params->start)
		error_exit(e_repeating_start_node);
	if (start_or_end && g_params->end)
		error_exit(e_repeating_end_node);
	start_end_writing_input_saving(line, input);
	ft_lstadd(input, ft_lstnew(*line, 0));
	g_params->read_lines++;
	if (ft_strequ(*line, "##start"))
		error_exit(e_repeating_start_node);
	if (ft_strequ(*line, "##end"))
		error_exit(e_repeating_end_node);
	line_split = ft_strsplit(*line, ' ');
	if (ft_arrlen(line_split) != 3)
		error_exit((start_or_end == 0) * e_invalid_start_node
					+ (start_or_end == 1) * e_invalid_end_node);
	if (start_or_end == e_start)
		check_coordinates_and_name((g_params->start =
									room_writing(line_split)));
	else
		check_coordinates_and_name((g_params->end = room_writing(line_split)));
	free_2d_array(line_split);
}
