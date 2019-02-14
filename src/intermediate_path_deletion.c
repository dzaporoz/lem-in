/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intermediate_path_deletion.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dzaporoz <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/12 22:20:44 by dzaporoz          #+#    #+#             */
/*   Updated: 2019/02/14 20:07:27 by dzaporoz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../project.h"

static void		del_adjacency_links(t_list *this_path, t_list *path)
{
	t_list *another_path;
	t_list *temp;

	another_path = ((t_list*)this_path->content)->content;
	while (another_path->next->content != path)
		another_path = another_path->next;
	temp = another_path->next;
	another_path->next = temp->next;
	ft_lstdelone(&temp, NULL);
}

void			delete_path(t_list *path, t_data *data)
{
	t_list *this_path;
	t_list *temp;

	this_path = ((t_list*)path->content)->next;
	while (this_path)
	{
		del_adjacency_links(this_path, path);
		this_path = this_path->next;
	}
	if (path == data->path_adjacency)
	{
		temp = data->path_adjacency;
		data->path_adjacency = data->path_adjacency->next;
	}
	else
	{
		this_path = data->path_adjacency;
		while (this_path->next != path)
			this_path = this_path->next;
		temp = this_path->next;
		this_path->next = temp->next;
	}
	ft_lstdel((t_list**)&temp->content, NULL);
	ft_lstdelone(&temp, NULL);
}

void			del_excess_path(t_data *data)
{
	t_list *path;

	path = data->path_adjacency;
	while (path)
	{
		if ((int)((t_list*)path->content)->content_size <
				data->current_efficiency)
			path = path->next;
		else
		{
			delete_path(path, data);
			path = data->path_adjacency;
		}
	}
}

void			delete_long_paths(t_data *data)
{
	t_list *paths;
	t_list *list;

	paths = data->path_adjacency;
	while (paths)
	{
		if (paths->content_size)
		{
			list = paths->content;
			while ((list = list->next))
				((t_list*)list->content)->content_size = 0;
		}
		paths = paths->next;
	}
	count_efficiency(data, data->path_adjacency);
	if (ft_lstcount(data->all_paths) > 85)
		del_excess_path(data);
	ft_lstdel(&data->unique_paths, NULL);
	paths = data->path_adjacency;
	while ((paths = paths->next))
		if (paths->content_size == 0)
			paths->content_size = ft_lstcount(paths->content);
	data->current_efficiency = INT_MAX;
}
