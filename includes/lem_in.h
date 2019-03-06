/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsprigga <bsprigga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/01 17:05:02 by bsprigga          #+#    #+#             */
/*   Updated: 2019/03/06 20:39:33 by tsimonis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEM_IN_H
# define LEM_IN_H

# include "../libft/includes/libft.h"
# include <stdio.h>

typedef struct			s_neighbour t_neighbour;
typedef struct			s_room t_room;

struct					s_neighbour
{
	t_room				*room;
	t_neighbour			*next;
};

struct					s_room
{
	char				*name;
	int					coord_x;
	int					coord_y;
	t_room				*next;
	t_neighbour			*neighbours;
	int					visited;
};

typedef struct			s_path
{
	int					len_seq;
	t_neighbour			*seq;
	struct s_path		*next;
}						t_path;

typedef struct			s_params
{
	int					nr_rooms;
	int					nr_ants;
	t_room				*start;
	t_room				*end;
	t_room				*start_of_list;
	t_path				*start_of_list_of_path;
	t_room				**arr; // sorted array of nodes
}						t_params;

t_params				*g_params; //extern 
enum					e_start_end	{e_start, e_end};

void					read_input(t_params *g_params);
int						get_next_line_or_exit(char **line, t_params *g_params);
void					free_2d_array(char **line);
void					error_exit(void); //t_params *g_params
size_t					ft_arrlen(char **str);
void					get_nr_ants(char **line, t_params *g_params);
t_room					*room_writing(char **ln_split, t_params *g_params);
void					start_end_writing(char **line, t_params *g_params);
t_room					*find_leaf(char *name, t_params *g_params);
char					*ft_strjoin_for_arr(char **lines, int max_len);
void					link_writing(char **line, t_params *g_params);
void					free_g_params(t_params *g_params);
t_room					*new_room(char *name, int x, int y);
t_room					**build_level_graph(t_room **graph);

#endif
