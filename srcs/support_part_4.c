/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   support_part_4.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsprigga <bsprigga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/28 22:42:34 by tsimonis          #+#    #+#             */
/*   Updated: 2019/04/02 00:09:42 by bsprigga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

int			num_of_nghbrs(t_neighbour *neighbour)
{
	int		i;

	i = 0;
	while (neighbour)
	{
		neighbour = neighbour->next;
		i++;
	}
	return (i);
}

/*
**	recursion called BEFORE ft_printf because
**	lstadd() adds new list element to the left of current value
*/

void		recursive_print_and_free(t_list **input)
{
	if (!(*input))
		return ;
	recursive_print_and_free(&((*input)->next));
	if (ft_strlen((*input)->content))
		ft_printf("%s\n", (*input)->content);
	free((*input)->content);
	free(*input);
}

static void	error_exit_additional_errors2(int value)
{
	if (value == e_invalid_end_node)
		ft_fprintf(2, "ERROR at line №%d: end node is invalid\n",
		g_params->read_lines);
	else if (value == e_room_starts_with_L)
		ft_fprintf(2, "ERROR at line №%d: room starts with \"L\"\n",
		g_params->read_lines);
	else if (value == e_invalid_coordinates)
		ft_fprintf(2, "ERROR at line №%d: a node has invalid coordinates\n",
		g_params->read_lines);
	else if (value == e_invalid_link)
		ft_fprintf(2,
"ERROR at line №%d: no or invalid first link in input file\n",
		g_params->read_lines);
	else if (value == e_invalid_node)
		ft_fprintf(2, "ERROR at line №%d: invalid or no nodes in input file\n",
		g_params->read_lines);
	else if (value == e_no_possible_flow)
		ft_fprintf(2, "ERROR: No possible flow exists\n");
	else if (value == e_duplicate_node)
		ft_fprintf(2, "ERROR at line №%d: duplicate node in file\n",
		g_params->read_lines);
	else
		ft_fprintf(2, "ERROR at line №%d\n", g_params->read_lines);
	free_g_params();
	exit(0);
}

static void	error_exit_additional_errors1(int value)
{
	if (value == e_no_end_node)
		ft_fprintf(2, "ERROR at line №%d: no end node\n", g_params->read_lines);
	else if (value == e_cannot_read_file)
		ft_fprintf(2, "ERROR at line №%d: cannot read from file\n",
		g_params->read_lines);
	else if (value == e_two_nodes_have_the_same_coordinates)
		ft_fprintf(2,
"ERROR at line №%d: two nodes have the same coordinates\n",
		g_params->read_lines);
	else if (value == e_repeating_start_node)
		ft_fprintf(2,
"ERROR at line №%d: ##start command is repeated at least twice/follows end\n",
g_params->read_lines);
	else if (value == e_repeating_end_node)
		ft_fprintf(2,
"ERROR at line №%d: ##end command is repeated at least twice/follows start\n",
g_params->read_lines);
	else if (value == e_invalid_start_node)
		ft_fprintf(2, "ERROR at line №%d: start node is invalid\n",
		g_params->read_lines);
	else
		error_exit_additional_errors2(value);
	free_g_params();
	exit(0);
}

void		error_exit(int value)
{
	char	*line;

	line = NULL;
	if (value != e_no_possible_flow && get_next_line(0, &line) > 0)
		ft_fprintf(2, "WARNING: File wasn't read completely!\n");
	if (value == e_no_ants_value)
		ft_fprintf(2,
"ERROR at line №%d: no ants value\n", g_params->read_lines);
	else if (value == e_incorrect_ants_value)
		ft_fprintf(2, "ERROR at line №%d: ants' value is incorrect\n",
		g_params->read_lines);
	else if (value == e_ants_value_less_or_equal_than_zero)
		ft_fprintf(2,
"ERROR at line №%d: ants' value less than or equal to zero\n",
		g_params->read_lines);
	else if (value == e_ants_value_bigger_int)
		ft_fprintf(2, "ERROR at line №%d: ants' value bigger than int\n",
		g_params->read_lines);
	else if (value == e_no_start_node)
		ft_fprintf(2,
"ERROR at line №%d: no start node\n", g_params->read_lines);
	else
		error_exit_additional_errors1(value);
	free_g_params();
	exit(0);
}
