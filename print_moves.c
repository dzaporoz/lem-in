#include "project.h"

void    print_situation(t_data *data, t_list *ants[], int ants_count)
{
    t_list *rooms;
    t_list *route;

    sleep(1);
    system("clear");
    ants_count++;
    rooms = data->rooms;
    while (rooms)
    {
        ((t_room*)rooms->content)->level = 0;
        rooms = rooms->next;
    }
    while (--ants_count > 0)
        ((t_room*)(ants[ants_count]->content))->level += 1;
    route = data->routes;
    while (route)
    {
        ft_printf("%3d.", ++ants_count);
        rooms = route->content;
        while (rooms)
        {
            (((t_room*)rooms->content)->level) ? ft_putstr("\u2588") : ft_putstr(".");
            rooms = rooms->next;
        }
        ft_putstr("\n");
        route = route->next;
    }
}

void    set_routes(t_data *data, t_list **ants)
{
    int n;
    int i;
    t_list  *route;

    route = data->routes;
    n = 1;
    i = data->routes->content_size - 1;
    while (n <= data->ants)
    {
        if (route->content_size  - 1 < i)
            ants[n++] = route->content;
        route = route->next;
        if (!route)
        {
            route = data->routes;
            i++;
        }
    }
}

void    print_moves(t_data *data)
{
    t_list  *ants[data->ants + 1];
    int     counter;
    int     lines;
    int     first;

    ft_putstr("\n");
    counter = 0;
    lines = 0;
    set_routes(data, ants);
    while (((t_room*)data->end->content)->ant != data->ants && !(counter = 0) && !(first = 0))
        while (++counter <= data->ants)
        {
            if (ants[counter]->content != data->end->content)
            {
                if (!((t_room *) ants[counter]->next->content)->ant ||
                    ants[counter]->next->content == data->end->content)
                {
                    if (ants[counter]->content == data->start->content)
                        ft_printf(FT_PRINTF_COLOR_GREEN);
                    ((t_room *) (ants[counter]->content))->ant -= 1;
                    ((t_room *) ants[counter]->next->content)->ant += 1;
                    ants[counter] = ants[counter]->next;

                    if (data->vizualize == 1)
                        print_situation(data, ants, data->ants);
                    else if (data->vizualize == 0 && ants[counter]->content == data->end->content)
                        ft_printf(FT_PRINTF_COLOR_RED);
                    ft_printf("%sL%d-%s" FT_PRINTF_COLOR_RESET, (first) ? " " : "", counter,
                              ((t_room *) (ants[counter]->content))->name);
                    first = 1;
                }
            }
            if (counter == data->ants)
            {
                if (data->vizualize == 2)
                    print_situation(data, ants, data->ants);
                else
                    ft_putstr("\n");
                lines++;
            }
        }
    ft_printf("\nNumber of lines: %d.\n\n", lines);
}