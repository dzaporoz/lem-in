#include "project.h"

static void    paste_sort(t_list **dst, t_list *src)
{
    t_list *temp;
    t_list *new;

    if (*dst == NULL)
    {
        *dst = add_link(src->content);
        (*dst)->content_size = src->content_size;
    }
    else if (src->content_size < (*dst)->content_size)
    {
        temp = *dst;
        *dst = add_link(src->content);
        (*dst)->content_size = src->content_size;
        (*dst)->next = temp;
    }
    else
    {
        temp = *dst;
        while (temp->next && temp->next->content_size < src->content_size)
            temp = temp->next;
        new = add_link(src->content);
        new->content_size = src->content_size;
        new->next = temp->next;
        temp->next = new;
    }
}

static void    sort_routes(t_data *data)
{
    t_list *routes;
    t_list *new_routes;
    int min;

    min = INT_MAX;
    routes = data->routes;
    while (routes)
    {
        routes->content_size = ft_lstcount(routes->content);
        if (min > routes->content_size)
            min = routes->content_size;
        routes = routes->next;
    }
    min *= 3;
    routes = data->routes;
    new_routes = NULL;
    while (routes)
    {
        if (routes->content_size > min)
            ft_lstdel(&routes->content, del_unmalloced_list);
        else
            paste_sort(&new_routes, routes);
        routes = routes->next;
    }
    ft_lstdel(&data->routes, del_unmalloced_list);
    data->routes = new_routes;
}

static void     delete_link(t_room *what, t_room *where)
{
    t_list *temp;
    t_list *temp2;

    temp = where->links;
    if (where->links->content == what)
    {
        temp = where->links->next;
        ft_lstdelone(&where->links, del_unmalloced_list);
        where->links = temp;
    }
    else
    {

        while (temp && temp->next->content != what)
            temp = temp->next;
        temp2 = temp->next->next;
        ft_lstdelone(&temp->next, del_unmalloced_list);
        temp->next = temp2;
    }
    if (ft_lstcount(where->links) == 1)
    {
        delete_link(where, where->links->content);
        ft_lstdel(&where->links, del_unmalloced_list);
    }
}

void    cut_dead_ends(t_data *data)
{
    t_list *room;

    room = data->rooms;

    int test = 0;
    while (room)
    {
        if (((t_room*)room->content)->links && ((t_room*)room->content)->links->next == NULL)
        {
            delete_link(room->content, ((t_room*)room->content)->links->content);
            ft_lstdel(&((t_room*)room->content)->links, del_unmalloced_list);
            test++;
        }
        room = room->next;
    }
}

void    leave_the_shortest_route(t_data *data)
{
    t_list *route;

    route = data->routes->next;
    while (route)
    {
        ft_lstdel(&route->content, del_unmalloced_list);
        route = route->next;
    }
    if (data->routes->next)
        ft_lstdel(&data->routes->next, del_unmalloced_list);
    data->routes->next = NULL;
}

void    check_is_one_route(t_data *data)
{
    t_list *route;
    t_room *one_route;

    route = data->routes;
    one_route = (t_room*)((t_list*)route->content)->content;
    while (route)
    {
        if ((t_room*)((t_list*)route->content)->content != one_route)
            one_route = NULL;
        route = route->next;
    }
    if (one_route)
    {
        leave_the_shortest_route(data);
        return;
    }
    route = ((t_room*)data->start)->back_link;
    one_route = route->content;
    while (route)
    {
        if (route->content != one_route)
            one_route = NULL;
        route = route->next;
    }
    if (one_route)
        leave_the_shortest_route(data);
}

void    routes_optimization(t_data *data)
{
    sort_routes(data);
//    check_is_one_route(data);
}