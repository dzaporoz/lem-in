/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dzaporoz <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/05 13:29:58 by dzaporoz          #+#    #+#             */
/*   Updated: 2019/02/06 13:10:26 by dzaporoz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../project.h"

void	read_args(t_data *data, char **argv)
{
	argv++;
	while (*argv)
	{
		if (!ft_strcmp(*argv, "--help"))
		{
			ft_printf("\noptions:\n\t\t--help : to read the manual\n\t\t"
				"--colorize : to print start and end ants position in "
				"color\n\t\t--stat : to print statistic data after main "
				"output\n\t\t--print-paths : to print the found paths\n");
			exit(EXIT_SUCCESS);
		}
		else if (!ft_strcmp(*argv, "--colorize"))
			data->flag_colorize = 1;
		else if (!ft_strcmp(*argv, "--stat"))
			data->flag_put_stat = 1;
		else if (!ft_strcmp(*argv, "--print-paths"))
			data->flag_put_routes = 1;
		else
		{
			ft_printf("\nusage: ./lem-in [option]\noptions:\n\t\t--help : to "
					"read the manual\n");
			exit(EXIT_SUCCESS);
		}
		argv++;
	}
}



int		main(int argc, char **argv)
{
	t_data data;

	ft_bzero(&data, sizeof(t_data));
	if (argc > 1)
		read_args(&data, argv);
	read_data(&data);
	check_map(&data);
	find_paths(&data);
//data.flag_vizualize = 2;
	if (!data.all_paths)
		error(NULL, &data);
	sort_paths(&data);
	prepare_paths_data(&data);
	((t_room*)data.start->content)->ant = data.ants;
//	print_main_data(&data);
	print_moves(&data);
	if (data.flag_put_stat)
		put_stat_data(&data);
	if (data.flag_put_routes)
		print_routes(&data);
	free_data(&data);
	return (0);
}
