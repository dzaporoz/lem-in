/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_routes.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dzaporoz <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/05 16:51:24 by dzaporoz          #+#    #+#             */
/*   Updated: 2019/02/05 16:55:11 by dzaporoz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../project.h"

static int	put_route(t_data *data, t_list *route, int route_index)
{
	t_list *room;

	if (!((t_list*)route->content)->content_size)
		return (0);
	ft_printf(FT_PRINTF_COLOR_GREEN "Route #%d (%d nodes):\n"
			FT_PRINTF_COLOR_RESET, route_index, route->content_size);
	room = route->content;
	while (room)
	{
		if (room->content != START && room->content !=
				END && ((t_room*)room->content)->back_link->next)
			ft_printf(FT_PRINTF_COLOR_BOLD_YELLOW);
		ft_printf("%s" FT_PRINTF_COLOR_MAGENTA "%s" FT_PRINTF_COLOR_RESET,
				((t_room*)room->content)->name, (room->next) ? " -> " : "");
		room = room->next;
	}
	ft_printf(";\n%s", (route->next) ? "\n" : "");
	return (1);
}

void		put_stat_data(t_data *data)
{
	t_list	*route;
	int		used_routes;

	used_routes = 0;
	route = data->routes;
	while (route)
	{
		if (((t_list*)route->content)->content_size)
			used_routes++;
		route = route->next;
	}
	ft_printf(FT_PRINTF_COLOR_BOLD_GREEN "STATISTIC:\n");
	ft_printf("%-37s %d\n", "1. Number of ants:", data->ants);
	ft_printf("%-37s %d\n", "2. Number of rooms (nodes):", data->stat_nodes);
	ft_printf("%-37s %d\n", "3. Number of transitions (edges):",
			data->stat_edges);
	ft_printf("%-37s %d\n", "4. Number of found paths:",
			ft_lstcount(data->routes));
	ft_printf("%-37s %d\n", "5. Number of used paths:", used_routes);
	ft_printf("%-37s %d / %d ", "6. Number of lines (taked / minimum):",
			data->stat_lines, data->stat_min_lines);
	if (data->stat_lines <= data->stat_min_lines)
		ft_printf("\u2713\n");
	else
		ft_printf(FT_PRINTF_COLOR_BOLD_RED "\u274C\n" FT_PRINTF_COLOR_RESET);
}

void		print_routes(t_data *data)
{
	t_list	*route;
	int		routes_count;
	int		n;

	route = data->routes;
	routes_count = 0;
	while (route)
	{
		if (((t_list*)route->content)->content_size)
			routes_count++;
		route = route->next;
	}
	route = data->routes;
	n = 1;
	while (route)
	{
		n = put_route(data, route, n);
		route = route->next;
	}
	ft_printf(FT_PRINTF_COLOR_BOLD_GREEN "\nNumber of effective routes: %d\n"
			FT_PRINTF_COLOR_RESET, routes_count);
	ft_printf(FT_PRINTF_COLOR_BOLD_GREEN "Number of nodes: %d\n"
			FT_PRINTF_COLOR_RESET, ft_lstcount(data->rooms));
}

void		print_situation(t_data *data)
{
	t_list	*rooms;
	t_list	*route;
	int		route_index;

	sleep(1);
	system("clear");
	route_index = 0;
	route = data->routes;
	while (route)
	{
		if (((t_list*)route->content)->content_size)
		{
			ft_printf("%3d.", ++route_index);
			rooms = route->content;
			while (rooms)
			{
				(((t_room*)rooms->content)->ant) ?
					ft_putstr("\u2588") : ft_putstr(".");
				rooms = rooms->next;
			}
			ft_putstr("\n");
		}
		route = route->next;
	}
}

void		print_links(t_list *rooms)
{
	t_list *link;
	t_list *p;
	t_list *temp;

	while (rooms)
	{
		link = ((t_room*)rooms->content)->links;
		while (link)
		{
			ft_printf("%s-%s\n", ((t_room*)rooms->content)->name, ((t_room*)link->content)->name);
			p = ((t_room*)link->content)->links;
			if (p->content == rooms->content)
			{
				temp = p->next;
				free(p);
				((t_room*)link->content)->links = temp;
			}
			else
				while (p)
				{
					if (p->next->content == rooms->content)
					{
						temp = p->next->next;
						free(p->next);
						p->next = temp;
					}
					p = p->next;
				}
			link = link->next;
		}
		rooms = rooms->next;
	}
}

void		print_main_data(t_data *data)
{
	t_room	*room;
	t_list	*list;

	ft_printf("%d\n", data->ants);
	room = data->start->content;
	ft_printf("##start\n%s %d %d\n", room->name, room->x, room->y);
	list = data->rooms;
	while (list)
	{
		room = list->content;
		if (list->content != START && list->content != END)
			ft_printf("%s %d %d\n", room->name, room->x, room->y);
		list = list->next;
	}
	room = data->end->content;
	ft_printf("##end\n%s %d %d\n", room->name, room->x, room->y);
	print_links(data->rooms);

}