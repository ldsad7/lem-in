/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsprigga <bsprigga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/01 17:05:02 by bsprigga          #+#    #+#             */
/*   Updated: 2019/03/29 20:33:53 by bsprigga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEM_IN_H
# define LEM_IN_H

# include "libft.h"

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
	t_room					*next;
	t_room					*next_elem;
	t_room					*prev_path;
	t_room					*prev_elem;
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
	t_room					**arr;
	int						read_lines;
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

typedef struct				s_cost_params
{
	int						path_nr;
	int						num_paths_in_resulting_group;
	int						num_paths_in_curr_group;
	int						min_cost;
}							t_cost_params;

t_params					*g_params;
enum						e_start_end {e_start, e_end};
enum						e_errors
{
	e_no_ants_value,
	e_incorrect_ants_value,
	e_ants_value_less_or_equal_than_zero,
	e_ants_value_bigger_int,
	e_room_starts_with_L,
	e_invalid_coordinates,
	e_invalid_node,
	e_invalid_link,
	e_cannot_read_file,
	e_invalid_start_node,
	e_invalid_end_node,
	e_two_nodes_have_the_same_coordinates,
	e_repeating_start_node,
	e_repeating_end_node,
	e_no_start_node,
	e_no_end_node,
	e_no_possible_flow,
	e_duplicate_node
};

void						read_input(t_list **input);
int							get_next_line_or_exit(char **line);
void						free_2d_array(char **line);
void						error_exit(int value);
size_t						ft_arrlen(char **str);
void						get_nr_ants(char **line, t_list **input);
t_room						*room_writing(char **ln_split);
void						start_end_writing(char **line, t_list **input);
t_room						*find_leaf(char *name);
char						*ft_strjoin_for_arr(char **lines, int max_len);
void						free_g_params(void);
t_room						*new_room(char *name, int x, int y);
t_cost_params				*algorithm(int flows);
void						print_paths_(void);
void						print_paths_double(void);
void						free_and_relocate_start_of_list_of_paths(t_path
														*paths_curr_iter);
void						sort_list_to_arr(void);
void						g_params_init(int (*fls)[3], char **line);
void						print_paths(int nr_steps);
t_stack						*ft_stacknew(int value, t_stack *prev,
													t_stack *next);
void						ft_stackdelone(t_stack **top);
int							ft_stackdel(t_stack **top);
void						push_stack(t_stack **stack, int value);
void						rotate_forward_stack(t_stack **top);
void						rotate_forward_queue(t_queue **queue);
t_queue						*queue_new(t_room **room, t_queue **prev,
													t_queue **next);
void						queue_delone(t_queue **queue);
void						queue_free(t_queue **queue);
void						push_queue(t_queue **queue, t_room **room);
void						rotate_forward_queue(t_queue **queue);
t_cost_params				*cost_params_setup(void);
void						flag_path(t_room **paths_ends, int path_nr,
										t_path **paths);
void						add_path(t_path **paths, t_room **room);
int							bfs(int path_nr, t_room ***paths_ends,
								t_path **paths);
int							compare(t_cost_params *cost_params,
									t_path **paths_bfs);
void						add_path(t_path **paths, t_room **room);
void						recursive_print_and_free(t_list **input);
int							ft_min(int a, int b, int c);
int							num_of_nghbrs(t_neighbour *neighbour);
void						check_data_sufficiency(void);
void						check_coordinates_and_name(t_room *room);

#endif
