/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   project.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dzaporoz <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/14 19:03:13 by dzaporoz          #+#    #+#             */
/*   Updated: 2019/02/14 19:08:23 by dzaporoz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEM_IN_PROJECT_H
# define LEM_IN_PROJECT_H

# include "libft/libft.h"
# include "ftprintf/ft.h"
# include <limits.h>

# define START_ROOM 0
# define END_ROOM 1
# define REG_ROOM 2

# define START data->start->content
# define END data->end->content

typedef struct		s_room
{
	char			*name;
	int				x;
	int				y;
	t_list			*links;
	unsigned int	ant;
	int				level;
	t_list			*back_link;
}					t_room;

typedef struct		s_data
{
	int				ants;
	t_list			*rooms;
	t_list			*start;
	t_list			*end;
	t_list			*closed_rooms;
	t_list			*all_paths;
	t_list			*path_adjacency;
	t_list			*unique_paths;
	int				s_nodes;
	int				s_edges;
	int				s_lines;
	int				s_req_lines;
	int				current_efficiency;
	unsigned int	flag_put_routes:1;
	unsigned int	flag_put_stat:1;
	unsigned int	flag_colorize:1;
}					t_data;

void				read_data(t_data *data);
void				check_map(t_data *data);
void				error(char *string, t_data *data);
t_list				*add_link(void *p);
void				free_data(t_data *data);
void				print_moves(t_data *data);
void				print_routes(t_data *data);
void				put_stat_data(t_data *data);
void				print_main_data(t_data *data);
void				delete_link_from_room(t_list **links, void *content);
void				find_paths(t_data *data);
int					check_path_uniqueness(t_list *path_adjacency);
void				bfs_traversal(t_room *start, t_room *end);
void				prepare_paths_data(t_data *data);
void				path_selection(t_data *data, t_list *path);
void				paths_sort(t_list **list, int direction);
void				ft_lstpathdel(void *p, size_t size);
void				del_excess_path(t_data *data);
void				delete_path(t_list *path, t_data *data);
void				check_and_safe_paths(t_data *data);
void				del_room_backlinks(t_list *room);
void				close_rooms(t_list *room);
int					isnt_dupl(t_list *list, void *content);
int					count_efficiency(t_data *data, t_list *path_adjacency);
void				delete_long_paths(t_data *data);

#endif
