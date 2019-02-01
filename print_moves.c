#include "project.h"

int    check_another_routes(t_data *data, t_list **ant)
{
    t_list *route;

    if ((*ant)->content != data->start->content)
        return (0);
    route = data->routes->next;
    while (route)
    {
        if (((t_room*)data->start->content)->ant < route->content_size - data->routes->content_size)
            return (0);
        else if (!((t_room*)((t_list*)route->content)->next->content)->ant)
        {
            *ant = route->content;
            return (1);
        }
        route = route->next;
    }
    return (0);
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
    while (++counter <= data->ants)
        ants[counter] = data->routes->content;
    while (((t_room*)data->end->content)->ant != data->ants && !(counter = 0) && !(first = 0))
        while (++counter <= data->ants)
        {
            if (ants[counter]->content != data->end->content)
            {
                if (!((t_room *) ants[counter]->next->content)->ant ||
                    ants[counter]->next->content == data->end->content || check_another_routes(data, &ants[counter]))
                {
                    if (ants[counter]->content == data->start->content)
                        ft_printf(FT_PRINTF_COLOR_GREEN);
                    ((t_room *) (ants[counter]->content))->ant -= 1;
                    ((t_room *) ants[counter]->next->content)->ant += 1;
                    ants[counter] = ants[counter]->next;


                    if (ants[counter]->content == data->end->content)
                        ft_printf(FT_PRINTF_COLOR_RED);
                    ft_printf("%sL%d-%s" FT_PRINTF_COLOR_RESET, (first) ? " " : "", counter,
                              ((t_room *) (ants[counter]->content))->name);
                    first = 1;
                }
            }
            if (counter == data->ants)
            {
                ft_putstr("\n");
                lines++;
            }
        }
    ft_printf("\nNumber of lines: %d.\n\n", lines);
}