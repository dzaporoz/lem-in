/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data_release.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dzaporoz <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/12 21:43:50 by dzaporoz          #+#    #+#             */
/*   Updated: 2019/02/14 19:25:09 by dzaporoz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../project.h"

void	delete_link_from_room(t_list **links, void *content)
{
	t_list *temp;
	t_list *p;

	if ((*links)->content == content)
	{
		temp = (*links)->next;
		free(*links);
		*links = temp;
	}
	else
	{
		p = *links;
		while (p && p->next->content != content)
			p = p->next;
		if (p)
		{
			temp = p->next;
			p->next = temp->next;
			free(temp);
		}
	}
}

void	ft_lstpathdel(void *p, size_t size)
{
	t_list *temp;

	if (!p)
		return ;
	temp = p;
	ft_lstdel(&temp, NULL);
	size = sizeof(void*);
	ft_bzero(&p, size);
}

void	free_room_data(void *data, size_t size)
{
	t_room *room_data;

	size = sizeof(t_room);
	room_data = (t_room*)data;
	if (room_data->back_link)
		ft_lstdel(&room_data->back_link, NULL);
	if (room_data->links)
		ft_lstdel(&room_data->links, NULL);
	ft_strdel(&room_data->name);
	ft_bzero(room_data, size);
	free(room_data);
}

void	free_data(t_data *data)
{
	ft_lstdel(&data->rooms, free_room_data);
	if (data->all_paths)
		ft_lstdel(&data->all_paths, ft_lstpathdel);
	if (data->path_adjacency)
		ft_lstdel(&data->path_adjacency, ft_lstpathdel);
	if (data->unique_paths)
		ft_lstdel(&data->unique_paths, NULL);
	ft_bzero(data, sizeof(t_data));
}
