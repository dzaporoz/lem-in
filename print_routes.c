#include "project.h"

void    print_routes(t_data *data)
{
    t_list *route;
    t_list *room;
    int n;

    route = data->routes;
    n = 1;
    while (route)
    {
        ft_printf(FT_PRINTF_COLOR_GREEN "Route #%d (%d nodes):\n" FT_PRINTF_COLOR_RESET, n, route->content_size);
        room = route->content;
        while (room)
        {
            if (room->content != data->start->content && room->content != data->end->content && ((t_room*)room->content)->back_link->next)
                ft_printf(FT_PRINTF_COLOR_BOLD_YELLOW);
            ft_printf("%s" FT_PRINTF_COLOR_MAGENTA "%s" FT_PRINTF_COLOR_RESET, ((t_room*)room->content)->name, (room->next) ? " -> " : "");
            room = room->next;
        }
        ft_printf(";\n%s", (route->next) ? "\n" : "");
        n++;
        route = route->next;
    }
    ft_printf(FT_PRINTF_COLOR_BOLD_GREEN "\nNumber of effective routes: %d\n" FT_PRINTF_COLOR_RESET, ft_lstcount(data->routes));
    ft_printf(FT_PRINTF_COLOR_BOLD_GREEN "Number of nodes: %d\n" FT_PRINTF_COLOR_RESET, ft_lstcount(data->rooms));
}