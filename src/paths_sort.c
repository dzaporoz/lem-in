/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routes_optimization.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dzaporoz <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/05 16:50:33 by dzaporoz          #+#    #+#             */
/*   Updated: 2019/02/05 16:50:35 by dzaporoz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../project.h"

static void	paste_sort(t_list **dst, t_list *src)
{
	t_list *temp;
	t_list *new;

	if (*dst == NULL)
	{
		*dst = add_link(src->content);
		(*dst)->content_size = src->content_size;
	}
	else if (src->content_size < (*dst)->content_size)
	{
		temp = *dst;
		*dst = add_link(src->content);
		(*dst)->content_size = src->content_size;
		(*dst)->next = temp;
	}
	else
	{
		temp = *dst;
		while (temp->next && temp->next->content_size < src->content_size)
			temp = temp->next;
		new = add_link(src->content);
		new->content_size = src->content_size;
		new->next = temp->next;
		temp->next = new;
	}
}

void		sort_paths(t_data *data)
{
	t_list	*routes;
	t_list	*new_routes;
	int		min;

	min = INT_MAX;
	routes = data->all_paths;
	while (routes)
	{
		routes->content_size = ft_lstcount(routes->content) - 1;
		if (min > routes->content_size)
			min = routes->content_size;
		routes = routes->next;
	}
	routes = data->all_paths;
	new_routes = NULL;
	while (routes)
	{
		if (routes->content_size - min > data->ants)
			ft_lstdel(&routes->content, NULL);
		else
			paste_sort(&new_routes, routes);
		routes = routes->next;
	}
	ft_lstdel(&data->all_paths, NULL);
	data->all_paths = new_routes;
}