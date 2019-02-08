/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_moves.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dzaporoz <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/05 16:43:44 by dzaporoz          #+#    #+#             */
/*   Updated: 2019/02/05 16:48:30 by dzaporoz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../project.h"

void	set_routes(t_data *data, t_list **ants)
{
	int		n;
	int		i;
	t_list	*route;

	route = data->unique_paths;
	while (route)
	{
		((t_list*)route->content)->content_size = 0;
		route = route->next;
	}
	n = 1;
	route = data->unique_paths;
	i = data->unique_paths->content_size;
	while (n <= data->ants)
	{
		if (route->content_size - 1 < i)
		{
			ants[n++] = route->content;
			((t_list*)route->content)->content_size = 1;
		}
		route = route->next;
		if (!route)
		{
			route = data->unique_paths;
			i++;
		}
	}
}

t_list	*get_alt_route(t_list *route, t_room *room)
{
	while (route)
	{
		if (route && route->content == room)
			return (route);
		route = route->next;
	}
	return (NULL);
}

int		set_alternative_route(t_data *data, t_list **ant)
{
	int		shortest_path;
	t_list	*routes_pointer;
	t_list	*shortest_pointer;
	t_list	*alt_route;

	if ((*ant)->content == data->start->content)
		return (0);
	shortest_path = 0;
	shortest_pointer = NULL;
	routes_pointer = ((t_room*)(*ant)->content)->back_link;
	while (routes_pointer)
	{
		alt_route = get_alt_route(routes_pointer->content, (*ant)->content);
		if (alt_route && !((t_room*)(alt_route->next->content))->ant)
			if (!shortest_path || ft_lstcount(routes_pointer->content) <
					shortest_path)
			{
				shortest_path = ft_lstcount(alt_route);
				shortest_pointer = alt_route;
			}
		routes_pointer = routes_pointer->next;
	}
	if (shortest_pointer)
	{
		*ant = shortest_pointer;
		return (1);
	}
	return (0);
}

void	put_one_move(t_data *data, t_list **ants, int counter, int *first_flag)
{
	if (ants[counter]->content == data->start->content && data->flag_colorize)
		ft_printf(FT_PRINTF_COLOR_GREEN);
	((t_room*)(ants[counter]->content))->ant -= 1;
	((t_room*)ants[counter]->next->content)->ant += 1;
	ants[counter] = ants[counter]->next;
	if (data->flag_vizualize == 1)
		print_situation(data);
	else if (data->flag_colorize && ants[counter]->content == data->end->content)
		ft_printf(FT_PRINTF_COLOR_RED);
	ft_printf("%sL%d-%s", (*first_flag) ? " " : "", counter,
			  ((t_room*)(ants[counter]->content))->name);
	if (data->flag_colorize)
		ft_printf(FT_PRINTF_COLOR_RESET);
	*first_flag = 1;
}

void	print_moves(t_data *data)
{
	t_list	*ants[data->ants + 1];
	int		counter;
	int		first;

	if (!data->unique_paths)
		error(NULL, data);
	counter = 0;
	set_routes(data, ants);
	while (((t_room*)data->end->content)->ant != data->ants && !(counter = 0) && !(first = 0))
		while (++counter <= data->ants)
		{
			if (ants[counter]->content != data->end->content)
				if (!((t_room*)ants[counter]->next->content)->ant ||
						ants[counter]->next->content == data->end->content)// || set_alternative_route(data, &ants[counter]))
					put_one_move(data, ants, counter, &first);
			if (counter == data->ants)
			{
				if (data->flag_vizualize == 2)
					print_situation(data);
				else
					ft_putstr("\n");
				data->s_lines += 1;
			}
		}
}
