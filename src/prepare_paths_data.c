/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prepare_paths_data.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dzaporoz <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/05 16:56:21 by dzaporoz          #+#    #+#             */
/*   Updated: 2019/02/12 20:20:33 by dzaporoz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../project.h"

static void	add_links_to_path(t_data *data)
{
	t_list	*route;
	t_list	*room;

	room = data->rooms;
	while (room)
	{
		ft_lstdel(&((t_room*)room->content)->back_link, NULL);
		room = room->next;
	}
	route = data->all_paths;
	while (route)
	{
		room = route->content;
		while (room)
		{
			if ((t_room*)room->content != START &&
					(t_room*)room->content != END)
				ft_lstadd(&((t_room*)room->content)->back_link,
						add_link(route->content));
			room = room->next;
		}
		route = route->next;
	}
}

static void	create_paths_list(t_data *data)
{
	t_list	*new_list;
	t_list	*temp;
	t_list	*content;

	temp = data->all_paths;
	while (temp)
	{
		content = add_link(temp->content);
		content->content_size = temp->content_size;
		if (!data->path_adjacency)
		{
			data->path_adjacency = add_link(content);
			new_list = data->path_adjacency;
		}
		else
			new_list->next = add_link(content);
		if (new_list->next)
			new_list = new_list->next;
		temp = temp->next;
	}
}

static void	check_and_paste_link(t_list *path,
		t_list *another_path, t_list *paths_list)
{
	int		flag;
	t_list	*p;
	t_list	*temp;

	flag = 1;
	p = path;
	if (another_path == path->content)
		return ;
	while (flag)
	{
		if (p != path && ((t_list*)((t_list*)p->content)->content)->content ==
				another_path)
			return ;
		if (p->next)
			p = p->next;
		else
			flag = 0;
	}
	temp = paths_list;
	while (((t_list*)temp->content)->content != another_path)
		temp = temp->next;
	p->next = add_link(temp);
}

static void	fill_paths_list(t_data *data, t_list *paths, t_list *adjacency)
{
	t_list *room;
	t_list *links;

	while (paths)
	{
		room = paths->content;
		room = room->next;
		while (room->next)
		{
			links = ((t_room*)room->content)->back_link;
			while (links)
			{
				check_and_paste_link(adjacency->content, links->content,
						data->path_adjacency);
				links = links->next;
			}
			room = room->next;
		}
		adjacency->content_size = ft_lstcount(adjacency->content);
		paths = paths->next;
		adjacency = adjacency->next;
	}
}

void		prepare_paths_data(t_data *data)
{
	add_links_to_path(data);
	create_paths_list(data);
	fill_paths_list(data, data->all_paths, data->path_adjacency);
	delete_long_paths(data);
	paths_sort(&data->path_adjacency, -1);
	data->current_efficiency = INT_MAX;
	if (check_path_uniqueness(data->path_adjacency))
		check_and_safe_paths(data);
	else
	{
		path_selection(data, data->path_adjacency);
		paths_sort(&data->unique_paths, 1);
	}
}
