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

t_list	*add_link(void *p)
{
	t_list	*new;

	new = (t_list*)malloc(sizeof(t_list));
	new->content = p;
	new->content_size = sizeof(void*);
	new->next = NULL;
	return (new);
}

void	del_room_backlinks(t_list *room)
{
	((t_room*)room->content)->level = INT_MAX;
	ft_lstdel(&((t_room*)room->content)->back_link, NULL);
}

void	close_rooms(t_list *room)
{
	((t_room*)room->content)->level = 0;
}

int		isnt_dupl(t_list *list, void *content)
{
	while (list)
	{
		if (list->content == content)
			return (0);
		list = list->next;
	}
	return (1);
}

void	error(char *string, t_data *data)
{
	if (string)
		free(string);
	free_data(data);
	write(1, "ERROR\n", 6);
	exit(EXIT_SUCCESS);
}
