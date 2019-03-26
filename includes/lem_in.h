/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsprigga <bsprigga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/01 17:05:02 by bsprigga          #+#    #+#             */
/*   Updated: 2019/03/18 13:54:02 by bsprigga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEM_IN_H
# define LEM_IN_H

# include "../libft/includes/libft.h"
# include <stdio.h> // delete after

typedef struct s_neighbour	t_neighbour;
typedef struct s_room		t_room;

struct						s_neighbour
{
	t_room					*room;
	t_neighbour				*next;
};

struct						s_room
{
	char					*name;
	int						coord_x;
	int						coord_y;
	t_room					*next; // needed for reading input
	t_room					*next_elem; // needed for the algorithm
	t_room					*prev_path; // needed for the algorithm
	t_room					*prev_elem; // for current iteration tracking prev element for relinking
	int						path_nr;
	int						in_paths;
	t_neighbour				*neighbours;
	int						ant_nr;
};

typedef struct				s_path
{
	int						len_seq;
	t_neighbour				*seq;
	struct s_path			*next;
}							t_path;

typedef struct				s_params
{
	int						nr_rooms;
	int						nr_ants;
	t_room					*start;
	t_room					*end;
	t_room					*start_of_list;
	t_path					*start_of_list_of_paths;
	t_room					**arr; // sorted array of nodes
}							t_params;

typedef struct				s_queue
{
	struct s_queue			*next;
	struct s_queue			*prev;
	t_room					*room;
}							t_queue;

typedef struct				s_stack
{
	int						value;
	struct s_stack			*prev;
	struct s_stack			*next;
}							t_stack;

t_params					*g_params;
enum						e_start_end	{e_start, e_end};

void						read_input(int fd);
int							get_next_line_or_exit(char **line);
void						free_2d_array(char **line);
void						error_exit(void);
size_t						ft_arrlen(char **str);
void						get_nr_ants(char **line, int fd);
t_room						*room_writing(char **ln_split);
void						start_end_writing(char **line, int fd);
t_room						*find_leaf(char *name);
char						*ft_strjoin_for_arr(char **lines, int max_len);
void						link_writing(char **line);
void						free_g_params(void);
t_room						*new_room(char *name, int x, int y);
int							ft_min(int a, int b, int c);
int							algorithm(int flows, t_path **paths);
int							num_of_nghbrs(t_neighbour *neighbour);
void						add_path(t_path **paths_prev_iter, t_room **room);
void						print_paths_(void);
void						print_paths_double(void);
void						free_and_relocate_start_of_list_of_paths(t_path *paths_curr_iter);

#endif
