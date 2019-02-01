#include "project.h"

void    del_unmalloced_list(void *p, size_t size)
{
    p = NULL;
    size = size;
}

t_list  *add_link(void *p)
{
    t_list  *new;

    new = (t_list*)malloc(sizeof(t_list));
    new->content = p;
    new->content_size = sizeof(void*);
    new->next = NULL;
    return (new);
}

void    free_room_data(void *data, size_t size)
{
    t_room *room_data;

    room_data = (t_room*)data;
    if (room_data->back_link)
        ft_lstdel(&room_data->back_link, del_unmalloced_list);
    if (room_data->links)
        ft_lstdel(&room_data->links, del_unmalloced_list);
    ft_strdel(&room_data->name);
    ft_bzero(room_data, size);
    free(room_data);
}

void    free_data(t_data *data)
{
    t_list  *temp;
    ft_lstdel(&data->rooms, free_room_data);
    if (data->routes)
    {
        temp = data->routes;
        while (temp)
        {
            ft_lstdel(&temp->content, del_unmalloced_list);
            temp = temp->next;
        }
        ft_lstdel(&data->routes, del_unmalloced_list);
    }

    ft_bzero(data, sizeof(t_data));
}

void    error(char *string, t_data *data)
{
    if (string)
        free(string);
    free_data(data);
    write(1, "ERROR\n", 6);
    exit(EXIT_SUCCESS);
}