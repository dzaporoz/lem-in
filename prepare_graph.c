#include "project.h"

void    delete_dead_end(t_room *room)
{
    t_room *link;
    t_list *edge;
    t_list *temp;

    link = room->back_link->content;
    ft_lstdel(&room->back_link, del_unmalloced_list);
    edge = link->back_link;
    if (edge->content == room)
    {
        temp = edge->next;
        ft_lstdel(&edge, del_unmalloced_list);
        link->back_link = temp;
    }
    while (edge)
    {
        if (edge->content == room)

        edge = edge->next;
    }
}

void    delete_dead_ends(t_data *data)
{
    t_list *rooms;

    rooms = data->rooms;
    while (rooms)
    {
        if (ft_lstcount(((t_room*)rooms->content)->back_link) == 1)
            delete_dead_end((t_room*)rooms->content);
        rooms = rooms->next;
    }


}