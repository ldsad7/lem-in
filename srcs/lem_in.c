/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem-in.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsprigga <bsprigga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/01 17:40:41 by bsprigga          #+#    #+#             */
/*   Updated: 2019/03/06 20:19:44 by tsimonis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lem_in.h"

void	free_g_params(t_params *g_params)
{
	t_room		*start_of_list;
	t_room		*tmp;
	t_neighbour	*neighb;
	t_neighbour	*pmt;

	if (!g_params)
		return ;
	start_of_list = g_params->start_of_list;
	while (start_of_list)
	{
		free(start_of_list->name);
		neighb = start_of_list->neighbours;
		while (neighb)
		{
			pmt = neighb;
			neighb = neighb->next;
			free(pmt);
		}
		tmp = start_of_list;
		start_of_list = start_of_list->next;
		free(tmp);
	}
	free(g_params->arr);
	free(g_params);
}

void	check_coordinates(t_params *g_params)
{
	t_room		*start_of_list;
	t_room		*tmp;

	if (!g_params)
		return ;
	start_of_list = g_params->start_of_list;
	while (start_of_list)
	{
		tmp = start_of_list->next;
		while (tmp)
		{
			if (tmp->coord_x == start_of_list->coord_x &&
				tmp->coord_y == start_of_list->coord_y)
				error_exit();
			tmp = tmp->next;
		}
		start_of_list = start_of_list->next;
	}
}

int		num_of_nghbrs(t_neighbour *neighbour)
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

int		sum_of_paths(t_path **paths, int flows)
{
	int		sum;
	int		i;

	i = 0;
	sum = 0;
	while (i < flows)
	{
		sum += paths[i]->len_seq;
		i++;
	}
	return (sum);
}

void	copy(t_path ***dest, t_path **src, int flows)
{
	int			i;

	*dest = (t_path **)malloc(sizeof(t_path *) * flows);
	i = 0;
	while (i < flows)
	{
		(*dest)[i] = (t_path *)malloc(sizeof(t_path));
		i++;
	}
	i = 0;
	while (i < flows)
	{
		(*dest)[i]->len_seq = src[i]->len_seq;
		(*dest)[i]->seq = src[i]->seq;
		i++;
	}
}

/*
int		recursion(t_room **nghbrs, int num_nghbrs, int flows, int start,
	t_path ***paths, int ind, int num_path, t_params *g_params, int *min,
	t_path ***short_paths)
{
	int			i;
	int			j;
	int			fl;
	int			sum;
	t_neighbour	*tmp;
	t_neighbour	*new_neighbour;

	i = start;
	fl = 0;
	printf("ind=%d,flows=%d,num_nghbrs=%d,i=%d,num_path=%d,start=%d,min=%d\n", ind, flows, num_nghbrs, i, num_path, start, *min);
	if (ind < flows)
	{
		//printf("1:\n");
		while (i < num_nghbrs - flows + ind + 1)
		{
			if (!((*paths)[ind]->seq = (t_neighbour *)malloc(sizeof(t_neighbour))))
				exit(0);
			(*paths)[ind]->seq->room = nghbrs[i];
			(*paths)[ind]->seq->room->visited = 1;
			(*paths)[ind]->seq->next = NULL;
			(*paths)[ind]->len_seq = 1;
			if (recursion(nghbrs, num_nghbrs, flows, i + 1, paths, ind + 1, 0, g_params, min, short_paths))
				fl = 1;
			(*paths)[ind]->seq->room->visited = 0;
			i++;
		}
	}
	else if (ind == flows && num_path < flows)
	{
		//printf("2:\n");
		if ((*paths)[num_path]->seq->room == g_params->start)
			return (recursion(nghbrs, num_nghbrs, flows, start, paths, ind, num_path + 1, g_params, min, short_paths));
		tmp = (*paths)[num_path]->seq->room->neighbours;
		while (tmp)
		{
			if (!(tmp->room->visited))
			{
				//printf("%s,%s,%d\n", (*paths)[num_path]->seq->room->name, tmp->room->name, (*paths)[num_path]->len_seq);
				if (tmp->room != g_params->start)
					tmp->room->visited = 1;
				if (!(new_neighbour = (t_neighbour *)malloc(sizeof(t_neighbour))))
					exit(0);
				new_neighbour->room = tmp->room;
				new_neighbour->next = (*paths)[num_path]->seq;
				(*paths)[num_path]->seq = new_neighbour;
				(*paths)[num_path]->len_seq++;
				if (recursion(nghbrs, num_nghbrs, flows, start, paths,
								ind, num_path + 1, g_params, min, short_paths))
					fl = 1;
				(*paths)[num_path]->seq = (*paths)[num_path]->seq->next;
				if (!fl)
					free(new_neighbour);
				(*paths)[num_path]->len_seq--;
				tmp->room->visited = 0;
			}
			tmp = tmp->next;
		}
	}
	else if (num_path == flows)
	{
		//printf("3:\n");
		j = 0;
		while (j < flows)
		{
			if ((*paths)[j]->seq->room != g_params->start)
			{
				fl = 1;
				break ;
			}
			j++;
		}
		if (fl)
			return (recursion(nghbrs, num_nghbrs, flows, start, paths, ind, 0, g_params, min, short_paths));
		if ((sum = sum_of_paths(*paths, flows)) < *min)
		{
			copy(short_paths, *paths, flows);
			*min = sum;
		}
		return (1);
	}
	if (fl)
		return (1);
	return (0);
}
*/

int		ft_min(int a, int b, int c)
{
	if (a <= b && a <= c)
		return (a);
	if (b <= a && b <= c)
		return (b);
	return (c);
}

t_room	**lst_to_array(t_neighbour *nghbr, int len)
{
	int		i;
	t_room	**res;

	res = (t_room **)malloc(sizeof(*res) * len);
	i = 0;
	while (nghbr)
	{
		res[i] = nghbr->room;
		nghbr = nghbr->next;
		i++;
	}
	return (res);
}

int		bfs(void)
{
	return (1);
}

/*
void	print_paths(t_path **short_paths, int flows)
{
	int	i;
	int	j;

	i = 0;
	while (i < flows)
	{
		printf("len: %d\n", short_paths[i]->len_seq);
		j = 0;
		while (j < short_paths[i]->len_seq)
		{
			printf("%s\n", short_paths[i]->seq->room->name);
			short_paths[i]->seq = short_paths[i]->seq->next;
			j++;
		}
		printf("end\n");
		printf("-----------------\n");
		i++;
	}
	return ;
}
*/

/*
void	walk_paths(t_path *short_paths, t_params *g_params)
{
	return ;
}
*/

/*
void	algorithm(t_params *g_params)
{
	int				num_nghbrs;
	int				flows;
	int				fl;
	int				i;
	int				min;
	t_path			**paths;
	t_room			**nghbrs;
	t_path			**short_paths;

	short_paths = NULL;
	min = 2147483647;
	num_nghbrs = num_of_nghbrs(g_params->end->neighbours);
	nghbrs = lst_to_array(g_params->end->neighbours, num_nghbrs);
	flows = ft_min(num_nghbrs, num_of_nghbrs(g_params->start->neighbours),
														g_params->nr_ants);
	g_params->end->visited = 1;
	if (!(paths = (t_path **)malloc(sizeof(*paths) * flows)))
		exit(0);
	i = 0;
	while (i < flows)
	{
		if (!(paths[i] = (t_path *)malloc(sizeof(**paths))))
			exit(0);
		i++;
	}
	while (flows > 1)
	{
		if (recursion(nghbrs, num_nghbrs, flows, 0, &paths, 0, 0, g_params, &min, &short_paths))
			break ;
		flows--;
	}
	fl = 0;
	if (flows == 1 && bfs())
		fl = 1;
	if (flows > 1 || fl)
	{
		print_paths(short_paths, flows);
		walk_paths(short_paths, flows, g_params);
	}
	else
		error_exit(g_params);
}
*/


int		main(int argc, char **argv)
{
	t_params	*g_params;
	t_path		*short_paths;

	argc = 0;
	argv = NULL;
	if (!(g_params = (t_params *)malloc(sizeof(t_params))))
		error_exit();
	read_input(g_params);
	check_coordinates(g_params);
	//algorithm(g_params);

	//walk_paths(short_paths, g_params);

	free_g_params(g_params);
	return (0);
}
