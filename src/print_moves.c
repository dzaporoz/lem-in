/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_moves.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dzaporoz <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/05 16:43:44 by dzaporoz          #+#    #+#             */
/*   Updated: 2019/02/14 19:30:57 by dzaporoz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../project.h"

void	set_routes(t_data *data, t_list **ants)
{
	int		n;
	int		i;
	t_list	*route;

	route = data->unique_paths;
	while (route && !(((t_list*)route->content)->content_size = 0))
		route = route->next;
	n = 1;
	route = data->unique_paths;
	i = data->unique_paths->content_size;
	while (n <= data->ants)
	{
		if ((int)route->content_size < i)
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

void	put_one_move(t_data *data, t_list **ants, int counter, int *first_flag)
{
	if (ants[counter]->content == data->start->content && data->flag_colorize)
		ft_printf(FT_PRINTF_COLOR_GREEN);
	((t_room*)(ants[counter]->content))->ant -= 1;
	((t_room*)ants[counter]->next->content)->ant += 1;
	ants[counter] = ants[counter]->next;
	if (data->flag_colorize && ants[counter]->content == END)
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
	set_routes(data, ants);
	while ((int)((t_room*)END)->ant != data->ants)
	{
		counter = 0;
		first = 0;
		while (++counter <= data->ants)
		{
			if (ants[counter]->content != data->end->content)
				if (!((t_room*)ants[counter]->next->content)->ant ||
					ants[counter]->next->content == data->end->content)
					put_one_move(data, ants, counter, &first);
			if (counter == data->ants)
			{
				ft_putstr("\n");
				data->s_lines += 1;
			}
		}
	}
}
