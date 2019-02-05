/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dzaporoz <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/05 13:29:58 by dzaporoz          #+#    #+#             */
/*   Updated: 2019/02/05 17:08:37 by dzaporoz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../project.h"

void	ft_splitdel(char **chrarr)
{
	int n;

	n = 0;
	while (chrarr[n])
		free(chrarr[n++]);
	free(chrarr);
}

int		ft_atoi_check(char *string, int integer)
{
	char *test;

	test = ft_itoa(integer);
	integer = (!ft_strcmp(string, test)) ? 1 : 0;
	free(test);
	return (integer);
}

int		main(int argc, char **argv)
{
	t_data data;

	ft_bzero(&data, sizeof(t_data));
	read_data(&data);
	check_map(&data);
	data.flag_vizualize = 0;
	data.flag_put_routes = 0;
	data.flag_put_stat = 1;
	data.flag_colorize = 1;
	if (!((t_room*)data.end->content)->links->next ||
			!((t_room*)data.start->content)->links->next || data.ants == 1)
		breadth_first_traversal(&data);
	else
		depth_first_traversal(&data);
	if (!data.routes)
		error(NULL, &data);
	if (data.flag_put_routes)
		print_routes(&data);
	((t_room*)data.start->content)->ant = data.ants;
	print_main_data(&data);
	print_moves(&data);
	if (data.flag_put_stat)
		put_stat_data(&data);
	if (data.flag_put_routes)
		print_routes(&data);
//	routes_intersections(&data, ft_lstcount(data.routes));
	free_data(&data);
	return (0);
}
