/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   paths_selection.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dzaporoz <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/12 20:21:35 by dzaporoz          #+#    #+#             */
/*   Updated: 2019/02/14 19:01:50 by dzaporoz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../project.h"

static void	put_from_seized_list(t_list *seized_lists, t_list *path)
{
	((t_list*)(path->content))->next = seized_lists;
	while (seized_lists)
	{
		if (!seized_lists->content_size)
		{
			((t_list*)seized_lists->content)->content_size = 1;
			seized_lists->content_size = 1;
		}
		seized_lists = seized_lists->next;
	}
}

static void	put_to_seized_list(t_list **seized_lists, t_list *path)
{
	t_list *p;

	p = path->content;
	*seized_lists = p->next;
	while ((p = p->next))
		if (((t_list*)p->content)->content_size)
		{
			((t_list*)p->content)->content_size = 0;
			p->content_size = 0;
		}
	((t_list*)path->content)->next = NULL;
}

void		path_selection(t_data *data, t_list *path)
{
	t_list *seized_lists;

	seized_lists = NULL;
	while (path->next && !path->content_size)
		path = path->next;
	if (path->content_size)
		put_to_seized_list(&seized_lists, path);
	if (seized_lists && path->next)
		path_selection(data, path->next);
	else if (!path->next)
		check_and_safe_paths(data);
	if (seized_lists)
		put_from_seized_list(seized_lists, path);
	if (path->next)
	{
		if (path == data->path_adjacency && ft_lstcount(path->content) > 1)
		{
			delete_path(path, data);
			del_excess_path(data);
			path = data->path_adjacency;
			path_selection(data, path);
		}
		else
			path_selection(data, path->next);
	}
}
