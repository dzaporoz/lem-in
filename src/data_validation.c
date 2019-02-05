/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data_validation.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dzaporoz <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/05 17:06:13 by dzaporoz          #+#    #+#             */
/*   Updated: 2019/02/05 17:06:20 by dzaporoz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../project.h"

void	check_map(t_data *data)
{
	t_list	*room_p1;
	t_list	*room_p2;
	t_room	*room1;
	t_room	*room2;

	if (!data->start || !data->end || !(((t_room*)data->start->content)->links)
			|| !(((t_room*)data->end->content)->links))
		error(NULL, data);
	room_p1 = data->rooms;
	while (room_p1)
	{
		room_p2 = room_p1->next;
		while (room_p2)
		{
			room1 = (t_room*)room_p1->content;
			room2 = (t_room*)room_p2->content;
			if ((room1->x == room2->x && room1->y == room2->y) ||
					!ft_strcmp(room1->name, room2->name))
				error(NULL, data);
			room_p2 = room_p2->next;
		}
		room_p1 = room_p1->next;
	}
}
