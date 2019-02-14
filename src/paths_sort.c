/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routes_optimization.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dzaporoz <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/05 16:50:33 by dzaporoz          #+#    #+#             */
/*   Updated: 2019/02/12 21:49:21 by dzaporoz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../project.h"

static void	paste_sort(t_list **dst, t_list *src, int direction)
{
	t_list *temp;
	t_list *new;

	temp = *dst;
	if (*dst == NULL || (direction < 0 && src->content_size >
		(*dst)->content_size) || (direction >= 0 && src->content_size
		<= (*dst)->content_size))
	{
		*dst = add_link(src);
		(*dst)->content_size = src->content_size;
		(*dst)->next = temp;
	}
	else
	{
		temp = *dst;
		while (temp->next && ((direction < 0 && temp->next->content_size >
				src->content_size) || (direction >= 0 &&
				temp->next->content_size <= src->content_size)))
			temp = temp->next;
		new = add_link(src);
		new->content_size = src->content_size;
		new->next = temp->next;
		temp->next = new;
	}
}

void		paths_sort(t_list **list, int direction)
{
	t_list	*routes;
	t_list	*sorted_routes;
	t_list	*temp;

	routes = *list;
	sorted_routes = NULL;
	while (routes)
	{
		paste_sort(&sorted_routes, routes, direction);
		routes = routes->next;
	}
	temp = sorted_routes;
	while (temp->next)
	{
		((t_list*)temp->content)->next = temp->next->content;
		temp = temp->next;
	}
	((t_list*)temp->content)->next = NULL;
	*list = sorted_routes->content;
	ft_lstdel(&sorted_routes, NULL);
}
