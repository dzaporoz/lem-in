#include "project.h"

static void    add_node(char **string, t_data *data, int room)
{
    int     err_flag;
    t_room  new_room;
    t_list  *new_room_p;

    new_room.name = ft_strdup(*string);
    new_room.x = ft_atoi(string[1]);
    new_room.y = ft_atoi(string[2]);
    new_room.level = INT_MAX;
    new_room.links = NULL;
    err_flag = (!(ft_atoi_check(string[1], new_room.x) && ft_atoi_check(string[2], new_room.y))) ? 1 : 0;
    ft_splitdel(string);
    if (err_flag || (room == START_ROOM && data->start) || (room == END_ROOM && data->end))
        error(NULL, data);
    new_room_p = ft_lstnew(&new_room, sizeof(t_room));
    ft_lstadd(&data->rooms, new_room_p);
    if (room == START_ROOM)
        data->start = new_room_p;
    else if (room == END_ROOM)
        data->end = new_room_p;
}

static void    read_node_data(char *string, t_data *data, int room)
{
    char    **room_data;

    if ((room == END_ROOM && data->end) || (room == START_ROOM && data->start))
        error(string, data);
    if (room != REG_ROOM)
    {
        free(string);
        string = NULL;
        if (get_next_line(0, &string) < 1)
            error(string, data);
    }
    if (ft_count_words(string, ' ') != 3 || *string == 'L')
        error(string, data);
    room_data = ft_strsplit(string, ' ');
    free(string);
    add_node(room_data, data, room);
}

static int      check_dup_edges(t_room *room1, t_room *room2)
{
    t_list *links;

    links = room1->links;
    while (links)
    {
        if (links->content == room2)
            return (1);
        links = links->next;
    }
    return (0);
}

static void    add_edge(char *string, t_data *data)
{
    char    **links;
    t_list  *room1;
    t_list  *room2;

    links = ft_strsplit(string, '-');
    free(string);
    if (!ft_strcmp(links[0], links[1]))
        error(NULL, data);
    room1 = data->rooms;
    room2 = data->rooms;
    while (room1 && ft_strcmp(((t_room*)room1->content)->name, links[0]))
        room1 = room1->next;
    while (room2 && ft_strcmp(((t_room*)room2->content)->name, links[1]))
        room2 = room2->next;
    ft_splitdel(links);
    if (!room1 || !room2 || (check_dup_edges(room1->content, room2->content)))
        error(NULL, data);
    ft_lstadd(&((t_room*)room1->content)->links, add_link(room2->content));
    ft_lstadd(&((t_room*)room2->content)->links, add_link(room1->content));
}

void    read_data(t_data *data)
{
    char    *string;
    int     rd;

    string = NULL;
    if (get_next_line(0, &string) < 1)
        error(string, data);
    data->ants = ft_atoi(string);
    if (data->ants < 1 || !ft_atoi_check(string, data->ants))
        error(string, data);
    free(string);
    while ((rd = get_next_line(0, &string)))
    {
        if (rd < 0)
            exit(EXIT_FAILURE);
        if (ft_count_words(string, ' ') == 3)
            read_node_data(string, data, REG_ROOM);
        else if (!ft_strcmp(string, "##end"))
            read_node_data(string, data, END_ROOM);
        else if (!ft_strcmp(string, "##start"))
            read_node_data(string, data, START_ROOM);
        else if (ft_count_words(string, '-') == 2)
            add_edge(string, data);
        else if (string[0] == '#')
            free(string);
        else
            error(string, data);
    }
}