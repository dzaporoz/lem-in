/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unique_path_saving.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dzaporoz <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/13 15:38:21 by dzaporoz          #+#    #+#             */
/*   Updated: 2019/02/14 19:32:55 by dzaporoz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../project.h"

static int	count_one_turn(t_data *data, int *cur_efficiency, size_t *c, int *n)
{
	t_list			*lst;
	static size_t	paths_num;

	if (!(*n))
		paths_num = 0;
	lst = data->path_adjacency;
	while (lst)
	{
		if (lst->content_size)
			paths_num += (((t_list*)lst->content)->content_size == *c) ? 1 : 0;
		lst = lst->next;
	}
	*n += paths_num;
	(*c)++;
	*cur_efficiency += (*n >= data->ants) ? 0 : 1;
	if (*cur_efficiency >= data->current_efficiency)
		return (0);
	else
		return (1);
}

int			count_efficiency(t_data *data, t_list *path_adjacency)
{
	int		current_efficiency;
	int		n;
	size_t	c;
	t_list	*list;

	n = 0;
	list = path_adjacency;
	c = (list->content_size) ? ((t_list*)list->content)->content_size : INT_MAX;
	while ((list = list->next))
		if (list->content_size && ((t_list*)list->content)->content_size < c)
			c = ((t_list*)list->content)->content_size;
	current_efficiency = c - 1;
	while (n < data->ants)
		if (!count_one_turn(data, &current_efficiency, &c, &n))
			return (0);
	data->current_efficiency = current_efficiency;
	return (1);
}

static void	save_paths(t_list *path_adjacency, t_list **unique_paths)
{
	t_list *temp;

	ft_lstdel(unique_paths, NULL);
	while (path_adjacency)
	{
		if (path_adjacency->content_size)
		{
			if (*unique_paths == NULL)
			{
				*unique_paths =
						add_link(((t_list*)path_adjacency->content)->content);
				temp = *unique_paths;
			}
			else
			{
				temp->next =
						add_link(((t_list*)path_adjacency->content)->content);
				temp = temp->next;
			}
			temp->content_size = ft_lstcount(temp->content) - 1;
		}
		path_adjacency = path_adjacency->next;
	}
}

int			check_path_uniqueness(t_list *path_adjacency)
{
	while (path_adjacency)
	{
		if (path_adjacency->content_size &&
			((t_list*)path_adjacency->content)->next)
			return (0);
		path_adjacency = path_adjacency->next;
	}
	return (1);
}

void		check_and_safe_paths(t_data *data)
{
	if (check_path_uniqueness(data->path_adjacency) &&
			count_efficiency(data, data->path_adjacency))
		save_paths(data->path_adjacency, &data->unique_paths);
}
