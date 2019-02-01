#include "project.h"

static void    save_route(t_list **route_list, t_list *first_point, t_room *last_room)
{
    t_list *new_route;
    t_list  *pointer;

    new_route = add_link(first_point->content);
    pointer = new_route;
    while (first_point->content != last_room)
    {
        ft_lstadd(&((t_room*)first_point->content)->back_link, add_link(new_route));
        pointer->next = add_link(first_point->next->content);
        pointer = pointer->next;
        first_point = first_point->next;
    }
    ft_lstadd(route_list, add_link(new_route));
}

static void    back_to_intersection(t_list **stack, t_list **way)
{
    t_list  *temp;

    while (*way && *stack && (*way)->content == (*stack)->content)
    {
        temp = (*stack)->next;
        ft_lstdelone(stack, del_unmalloced_list);
        *stack = temp;
        temp = (*way)->next;
        ft_lstdelone(way, del_unmalloced_list);
        *way = temp;
    }
}

static int     loop_check(t_list *stack, t_room *room)
{
    while (stack)
    {
        if (stack->content == room)
            return (0);
        stack = stack->next;
    }

    return (1);
}

void    depth_first_traversal(t_data *data)
{
    t_list  *way;
    t_list  *stack;
    t_list  *link;
    int     loop_flag;

    stack = add_link(data->end->content);
    ((t_room*)data->end->content)->level = 0;
    while (stack)
    {
        ft_lstadd(&way, add_link(stack->content));
        if (stack->content == data->start->content)
        {
            save_route(&data->routes, way, data->end->content);
            back_to_intersection(&stack, &way);
        }
        else if (!((t_room*)stack->content)->links->next || (stack->content == data->end->content && way->next))
            back_to_intersection(&stack, &way);
        else
        {
            link = ((t_room *) stack->content)->links;
            loop_flag = 1;
            while (link && stack->content != data->start->content)
            {
                if (((t_room*)link->content)->level > ((t_room*)stack->content)->level && loop_check(stack, link->content))
                {
                    ((t_room *) link->content)->level = ((t_room *) stack->content)->level + 1;
                    ft_lstadd(&stack, add_link(link->content));
                    loop_flag = 0;
                }
                link = link->next;
            }
            if (loop_flag)
                back_to_intersection(&stack, &way);
        }
    }
    routes_optimization(data);
}
