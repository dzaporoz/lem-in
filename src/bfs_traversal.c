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

static void	build_route(t_data *data)
{
	t_room *prev_room;
	t_list *way;

	if (!((t_room*)data->end->content)->back_link)
		error(NULL, data);
	way = add_link((t_room*)data->end->content);
	prev_room = ((t_room*)data->end->content)->back_link->content;
	while (prev_room)
	{
		ft_lstadd(&way, add_link(prev_room));
		prev_room = (prev_room->back_link) ? prev_room->back_link->content
			: NULL;
	}
	data->routes = add_link(way);
	data->routes->content_size = ft_lstcount(way);
}

static int	check_dup_pipes(t_list *list, t_room *room)
{
	while (list)
	{
		if (list->content == room)
			return (1);
		list = list->next;
	}
	return (0);
}

void		breadth_first_traversal(t_data *data)
{
	t_list *queue;
	t_list *temp;
	t_list *link;

	queue = add_link(data->start->content);
	((t_room*)data->start->content)->level = 0;
	while (queue)
	{
		link = ((t_room*)queue->content)->links;
		while (link)
		{
			if (((t_room *)link->content)->level > ((t_room*)queue->content)->level)
			{
				if (link->content != data->end->content && !((t_room *)link->content)->back_link)
					((t_room*)link->content)->back_link = add_link(queue->content);
				else if (!check_dup_pipes(((t_room*)data->end->content)->back_link, queue->content) && link->content == data->end->content)
				{
					((t_room *) link->content)->back_link = add_link(queue->content);
					ft_lstdel(&queue, NULL);
					build_route(data);
					return ;
				}
				((t_room *)link->content)->level = ((t_room *)queue->content)->level + 1;
				temp = queue;
				while (temp->next)
					temp = temp->next;
				temp->next = add_link(link->content);
			}
			link = link->next;
		}
		temp = queue;
		queue = queue->next;
		ft_lstdelone(&temp, NULL);
	}
	build_route(data);
}
