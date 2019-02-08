/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bfs_traversal.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dzaporoz <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/05 17:09:38 by dzaporoz          #+#    #+#             */
/*   Updated: 2019/02/05 17:11:25 by dzaporoz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../project.h"

static int 		check_dup_path(t_list *routes, t_list *path)
{
	t_list *temp1;
	t_list *temp2;
	int same_flag;

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

static void		add_room_links_to_queue(t_list **queue, t_room *end)
{
	t_list *link;
	t_list *temp;

	link = ((t_room*)((*queue)->content))->links;
	while (link && link->content != end)
		link = link->next;
	if (!link)
		link = ((t_room*)((*queue)->content))->links;
	while (link)
	{
		if (((t_room*)link->content)->level > ((t_room*)(*queue)->content)->level)
		{
			if (link->content == end || !((t_room*)link->content)->back_link)
				ft_lstadd(&((t_room*)link->content)->back_link, add_link((*queue)->content));
			else
				((t_room*)link->content)->back_link->content = (*queue)->content;
			if (link->content == end)
				return;
			((t_room*)link->content)->level = ((t_room*)(*queue)->content)->level + 1;
			temp = *queue;
			while (temp->next)
				temp = temp->next;
			temp->next = add_link(link->content);
		}
		link = link->next;
	}
}

static void		bfs_traversal(t_room *start, t_room *end)
{
	t_list *queue;
	t_list *temp;

	queue = add_link(start);
	((t_room*)queue->content)->level = 0;
	while (queue)
	{
		add_room_links_to_queue(&queue, end);
		temp = queue;
		queue = queue->next;
		ft_lstdelone(&temp, NULL);
	}
}

static void		build_routes(t_data *data, t_room *room, int destination)
{
	t_list *new_path;
	t_list *link;
	t_room *temp;
	t_list *p;

	link = room->back_link;
	while (link)
	{
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
		link = link->next;
		if (!check_dup_path(data->all_paths, new_path))
			continue ;
		ft_lstadd(&data->all_paths, add_link(new_path));
		data->all_paths->content_size = ft_lstcount(new_path);
	}
}

void		find_paths(t_data *data)
{
	t_list *room;

	bfs_traversal(data->start->content, data->end->content);
	if (!((t_room*)END)->back_link)
		error(NULL, data);
	build_routes(data, data->end->content, START_ROOM);
	room = data->rooms;
	while (room)
	{
		((t_room*)room->content)->level = INT_MAX;
		ft_lstdel(&((t_room*)room->content)->back_link, NULL);
		room = room->next;
	}
	bfs_traversal(data->end->content, data->start->content);
	build_routes(data, data->start->content, END_ROOM);
	room = data->rooms;
	while (room)
	{
		((t_room*)room->content)->level = INT_MAX;
		ft_lstdel(&((t_room*)room->content)->back_link, NULL);
		room = room->next;
	}
}
