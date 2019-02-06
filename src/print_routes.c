/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_routes.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dzaporoz <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/05 16:51:24 by dzaporoz          #+#    #+#             */
/*   Updated: 2019/02/06 13:12:12 by dzaporoz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../project.h"

static int	put_route(t_data *data, t_list *route, int route_index)
{
	t_list *room;

	if (!((t_list*)route->content)->content_size)
		return (0);
	ft_putstr("\n");
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
		n += put_route(data, route, n);
		route = route->next;
	}
	ft_printf(FT_PRINTF_COLOR_BOLD_GREEN "Number of effective routes: %d\n"
			FT_PRINTF_COLOR_RESET, routes_count);
	ft_printf(FT_PRINTF_COLOR_BOLD_GREEN "Number of nodes: %d\n"
			FT_PRINTF_COLOR_RESET, ft_lstcount(data->rooms));
}

void		put_stat_data(t_data *data)
{
	t_list	*route;
	int		used_paths;

	used_paths = 0;
	route = data->routes;
	while (route)
	{
		used_paths += (((t_list*)route->content)->content_size) ? 1 : 0;
		route = route->next;
	}
	ft_printf(FT_PRINTF_COLOR_BOLD_GREEN "\nSTATISTIC:\n");
	ft_printf("%-39s %d\n", "1. Number of ants:", data->ants);
	ft_printf("%-39s %d\n", "2. Number of rooms (nodes):", data->s_nodes);
	ft_printf("%-39s %d\n", "3. Number of transitions (edges):",
			data->s_edges);
	ft_printf("%-39s %d\n", "4. Number of found paths:",
			ft_lstcount(data->routes));
	ft_printf("%-39s %d\n", "5. Number of used paths:", used_paths);
	ft_printf("%-39s %d / %.d%s ", "6. Number of lines (taked / required):",
			data->s_lines, data->s_req_lines, (data->s_req_lines) ? "" : "-");
	if (data->s_lines <= data->s_req_lines)
		ft_printf("\u2713\n");
	else if (data->s_req_lines != 0)
		ft_printf(FT_PRINTF_COLOR_BOLD_RED "\u274C\n" FT_PRINTF_COLOR_RESET);
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

	while (rooms)
	{
		link = ((t_room*)rooms->content)->links;
		while (link)
		{
			ft_printf("%s-%s\n", ((t_room*)rooms->content)->name,
					((t_room*)link->content)->name);
			delete_link_from_room(&((t_room*)link->content)->links,
					rooms->content);
			link = link->next;
		}
		rooms = rooms->next;
	}
	ft_putstr("\n");
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
