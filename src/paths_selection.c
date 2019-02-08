#include "../project.h"

static int count_efficiency(t_data *data, t_list *path_adjacency)
{
	int current_efficiency;
	int n;
	int c;
	t_list *list;

	n = 0;
	list = path_adjacency;
	current_efficiency = ((t_list*)list->content)->content_size;
	c = ((t_list*)list->content)->content_size;
	while (n < data->ants)
	{
		if (list->content_size && ((t_list*)list->content)->content_size <= c)
			n++;
		list = list->next;
		if (!list || ((t_list*)list->content)->content_size > c)
		{
			list = path_adjacency;
			c++;
			current_efficiency += (n == data->ants) ? 0 : 1;
			if (current_efficiency >= data->current_efficiency)
				return (0);
		}
	}
	data->current_efficiency = current_efficiency;
	return (1);
}

void save_paths(t_data *data, t_list *path_adjacency, t_list **unique_paths)
{
	t_list *temp;

	ft_lstdel(unique_paths, NULL);
	while (path_adjacency)
	{
		if (path_adjacency->content_size)
		{
			if (*unique_paths == NULL)
			{
				*unique_paths = add_link(((t_list*)path_adjacency->content)->content);
				temp = *unique_paths;
			}
			else
			{
				temp->next = add_link(((t_list*)path_adjacency->content)->content);
				temp = temp->next;
			}
			temp->content_size = ft_lstcount(temp->content) - 1;
		}
		path_adjacency = path_adjacency->next;
	}
}

int check_path_uniqueness(t_list *path_adjacency)
{
	while (path_adjacency)
	{
		if (path_adjacency->content_size && ((t_list*)path_adjacency->content)->next)
			return (0);
		path_adjacency = path_adjacency->next;
	}
	return (1);
}

void path_selection(t_data *data, t_list *path)
{
	t_list *seized_lists;
	t_list *p;

	seized_lists = NULL;
	if (path->content_size)
	{
		p = path->content;
		seized_lists = p->next;
		while ((p = p->next))
			if (((t_list*)p->content)->content_size)
			{
				((t_list*)p->content)->content_size = 0;
				p->content_size = 0;
			}
		((t_list*)path->content)->next = NULL;
	}
	if (path->next && seized_lists)
		path_selection(data, path->next);
	if (!path->next && check_path_uniqueness(data->path_adjacency) && count_efficiency(data, data->path_adjacency))
		save_paths(data, data->path_adjacency, &data->unique_paths);
	if (seized_lists)
		((t_list*)(path->content))->next = seized_lists;
	while (seized_lists)
	{
		if (!seized_lists->content_size)
		{
			((t_list *) seized_lists->content)->content_size = 1;
			seized_lists->content_size = 1;
		}
		seized_lists = seized_lists->next;
	}
	if (path->next)
		path_selection(data, path->next);
}
