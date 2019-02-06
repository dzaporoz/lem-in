/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   auxilliary.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dzaporoz <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/05 17:06:50 by dzaporoz          #+#    #+#             */
/*   Updated: 2019/02/06 13:10:06 by dzaporoz         ###   ########.fr       */
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

t_list	*add_link(void *p)
{
	t_list	*new;

	new = (t_list*)malloc(sizeof(t_list));
	new->content = p;
	new->content_size = sizeof(void*);
	new->next = NULL;
	return (new);
}

void	free_room_data(void *data, size_t size)
{
	t_room *room_data;

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
	t_list	*temp;

	ft_lstdel(&data->rooms, free_room_data);
	if (data->routes)
	{
		temp = data->routes;
		while (temp)
		{
			ft_lstdel(&temp->content, NULL);
			temp = temp->next;
		}
		ft_lstdel(&data->routes, NULL);
	}
	ft_bzero(data, sizeof(t_data));
}

void	error(char *string, t_data *data)
{
	if (string)
		free(string);
	free_data(data);
	write(1, "ERROR\n", 6);
	exit(EXIT_SUCCESS);
}
