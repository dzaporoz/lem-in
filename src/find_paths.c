/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bfs_traversal.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dzaporoz <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/05 17:09:38 by dzaporoz          #+#    #+#             */
/*   Updated: 2019/02/14 19:27:44 by dzaporoz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../project.h"

int				check_dup_path(t_list *routes, t_list *path)
{
	t_list	*temp1;
	t_list	*temp2;
	int		same_flag;

	same_flag = 0;
	if (!routes)
		return (1);
	while (routes)
	{
		temp1 = routes->content;
		temp2 = path;
		while (temp1 && temp2 && temp1->content == temp2->content)
		{
			temp1 = temp1->next;
			temp2 = temp2->next;
		}
		if (temp1 == temp2)
			same_flag = 1;
		routes = routes->next;
	}
	return ((same_flag) ? 0 : 1);
}

static t_list	*test(t_list *link, t_room *room, int destination)
{
	t_room *temp;
	t_list *p;
	t_list *new_path;

	new_path = add_link(room);
	temp = ((t_room*)link->content);
	p = new_path;
	while (temp)
	{
		if (destination == END_ROOM)
		{
			p->next = add_link(temp);
			p = p->next;
		}
		else
			ft_lstadd(&new_path, add_link(temp));
		temp = (temp->back_link) ? temp->back_link->content : NULL;
	}
	return (new_path);
}

static void		build_routes(t_data *data, t_room *room, int destination)
{
	t_list *new_path;
	t_list *link;

	link = room->back_link;
	while (link)
	{
		new_path = test(link, room, destination);
		link = link->next;
		if (!check_dup_path(data->all_paths, new_path))
		{
			ft_lstdel(&new_path, NULL);
			continue ;
		}
		ft_lstadd(&data->all_paths, add_link(new_path));
		data->all_paths->content_size = ft_lstcount(new_path);
	}
}

void			del_pop_room(t_data *data)
{
	t_list	*room;
	t_list	*route;
	int		max;

	route = data->all_paths;
	while (route && !(max = 0))
	{
		room = route->content;
		while ((room = room->next) && room->next)
			ft_lstadd(&((t_room*)room->content)->back_link,
					add_link(route->content));
		route = route->next;
	}
	room = data->rooms;
	while (room)
	{
		room->content_size = ft_lstcount(((t_room*)room->content)->back_link);
		if ((int)room->content_size > max && isnt_dupl(data->closed_rooms,
					room->content) && (max = room->content_size))
			route = room->content;
		ft_lstdel(&((t_room*)room->content)->back_link, NULL);
		room = room->next;
	}
	if (route)
		ft_lstadd(&data->closed_rooms, add_link(route));
}

void			find_paths(t_data *data)
{
	del_pop_room(data);
	if (data->closed_rooms)
		ft_lstiter(data->closed_rooms, close_rooms);
	bfs_traversal(data->start->content, data->end->content);
	if (!((t_room*)END)->back_link && !data->all_paths)
		error(NULL, data);
	build_routes(data, data->end->content, START_ROOM);
	ft_lstiter(data->rooms, del_room_backlinks);
	if (data->closed_rooms)
		ft_lstiter(data->closed_rooms, close_rooms);
	bfs_traversal(data->end->content, data->start->content);
	build_routes(data, data->start->content, END_ROOM);
	ft_lstiter(data->rooms, del_room_backlinks);
}
