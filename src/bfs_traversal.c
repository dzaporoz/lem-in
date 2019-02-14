/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bfs_traversal.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dzaporoz <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/13 20:39:15 by dzaporoz          #+#    #+#             */
/*   Updated: 2019/02/13 20:39:50 by dzaporoz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../project.h"

static void		add_backlink(t_list **queue, t_list *link, t_room *end)
{
	t_list *temp;

	if (link->content == end || !((t_room*)link->content)->back_link)
		ft_lstadd(&((t_room*)link->content)->back_link,
				add_link((*queue)->content));
	else
		((t_room*)link->content)->back_link->content = (*queue)->content;
	if (link->content == end)
		return ;
	((t_room*)link->content)->level =
			((t_room*)(*queue)->content)->level + 1;
	temp = *queue;
	while (temp->next)
		temp = temp->next;
	temp->next = add_link(link->content);
}

static void		add_room_links_to_queue(t_list **queue, t_room *end)
{
	t_list *link;

	link = ((t_room*)((*queue)->content))->links;
	while (link && link->content != end)
		link = link->next;
	if (!link)
		link = ((t_room*)((*queue)->content))->links;
	while (link)
	{
		if (((t_room*)link->content)->level >
				((t_room*)(*queue)->content)->level + 1)
		{
			add_backlink(queue, link, end);
			if (link->content == end)
				return ;
		}
		link = link->next;
	}
}

void			bfs_traversal(t_room *start, t_room *end)
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
